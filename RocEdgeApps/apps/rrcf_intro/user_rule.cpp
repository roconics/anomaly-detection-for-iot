/*
 * Copyright 2019,2020-, Roconics Co., All Rights Reserved.
 */

#include <functional>
#include <random>
#include "user_rule.hpp"

using namespace std;

namespace urule {


	int UserRule::userRuleSetup()
	{
		simulation = true;
		annex_only = false;


		return 0;
	}

	int UserRule::userRuleMemoryDbInit()
	{

		return 0;
	}


	// MemoryDB ---- members
	void UMemDB_sl::init()
	{

	}

	void UserRule::onTick(roc::TfInfoIF* tf_i)
	{
		// process with memory_db and annex_memory_db
	}

	void UserRule::onBar(roc::TfInfoIF* tf_i)
	{
		// process with memory_db and annex_memory_db
	}

	void UserRule::onBarCloseAnnex(roc::TfInfoIF* tf_i)
	{
		// calculate annex_memory_db
	}

	void UserRule::onBarClose(roc::TfInfoIF* tf_i)
	{



	}

	void UserRule::simulator_main(string& period, string& data_input_dir_)
	{

		rrcp_bath_detection();

		rrcp_streaming_detection();

		rrcp_comparison();
	}

	void UserRule::rrcp_bath_detection()
	{
		PLOGW << "rrcp_bath_detection started.";

		const int n = 2010;
		int iot_de_count = 3;
		int num_trees = 100;
		int tree_size = 256;
		int num_threads = 0;  // number of cpu's if 0
		int64_t seed = -1;		// not specfied if not positive
		vector<int> bars;

		struct MyEdgeDataDouble_IoT {
			uint64_t	tval;
			double      value[3];
		};
		MyEdgeDataDouble_IoT* data_X = new MyEdgeDataDouble_IoT[n];

		std::random_device rd{};
		std::mt19937 gen{ rd() };
		std::normal_distribution<> d{ 0,1 };

		for (auto i = 0; i < n; i++) {
			data_X[i].tval = i;
			data_X[i].value[1] = 0;
			data_X[i].value[2] = 0;
			if (i < 1000) {
				data_X[i].value[0] = 5.;
			}
			else if (i < 2000) {
				data_X[i].value[0] = -5.;
			}
			else data_X[i].value[0] = 0;

			for (auto k = 0; k < 3; k++) {
				data_X[i].value[k] += 0.01 * d(gen);
			}
			bars.push_back(i);
		}

		// create forest
		shared_ptr<roc::RRCF> rrcf = roc::createRRCF(num_trees, tree_size,
			[&](int bar) {
				return (roc::EdgeDataDouble_IoT*) & data_X[bar];
			},
			iot_de_count, bars, num_threads, seed);


		std::shared_ptr<double[]> col_disp = rrcf->getCollusiveDisplacement();

		// write to csv-file
		string fname = roc::output_dir + "rrcf_batch.csv";

		std::ofstream ss(fname);
		if (!ss.is_open()) {
			PLOGE << fname << " open failed.";
			return;
		}
		for (auto i = 0; i < n; i++) {
			ss << data_X[i].value[0] << "," << data_X[i].value[1] << "," << data_X[i].value[2] << "," << col_disp[i] << endl;
		}
		ss.close();

		delete[] data_X;

		PLOGW << "rrcp_bath_detection ended." << endl;

	}

	void UserRule::rrcp_streaming_detection()
	{
		PLOGW << "rrcp_streaming_detection started.";

		const int n = 730;
		int iot_de_count = 1 * 4;  // sliding window size = 4
		int num_threads = 0; // number of cpu's if 0
		int64_t seed = -1;		// not specfied if not positive

		struct MyEdgeDataDouble_IoT {
			uint64_t	tval;
			double      value[4];
		};

		double A = 50;
		double center = 100.;
		double phi = 30.;
		const double PI = 3.14159265358979323846;
		double T = 2. * PI / 100.;
		vector<double> s(n);
		for (auto i = 0; i < n; i++) {
			s[i] = A * sin(T * ((double)i - phi )) + center;
		}
		for (auto i = 235; i < 255; i++) {
			s[i] = 80.;
		}

		int num_trees = 40;
		int	tree_size = 256;
		vector<int> bars;
		vector<shared_ptr<MyEdgeDataDouble_IoT>> stream;

		// Create a forest of empty trees
		shared_ptr<roc::RRCF> rrcf = roc::createRRCF(num_trees, tree_size,
			[&](int bar) {
				return (roc::EdgeDataDouble_IoT*)stream[bar].get();
			},
			iot_de_count, bars, num_threads, seed);


		vector<double> avg_codisp;

		for (auto i = 4; i < s.size(); i++) {
			std::shared_ptr<MyEdgeDataDouble_IoT> tick = make_shared<MyEdgeDataDouble_IoT>();
			tick->tval = i - 4LL;
			tick->value[0] = s[i - 3LL];
			tick->value[1] = s[i - 2LL];
			tick->value[2] = s[i - 1LL];
			tick->value[3] = s[i - 0];
			stream.push_back(tick);
			double c = rrcf->addPoint(i - 4);
			avg_codisp.push_back(c);
		}

		// write to csv-file
		string fname = roc::output_dir + "rrcf_streaming.csv";

		std::ofstream ss(fname);
		if (!ss.is_open()) {
			PLOGE << fname << " open failed.";
			return;
		}
		ss << "sin,avg_codisp" << endl;
		for (auto i = 0; i < avg_codisp.size(); i++) {
			ss << stream[i]->value[3] << "," << avg_codisp[i] << endl;
		}
		ss.close();


		PLOGW << "rrcp_streaming_detection ended." << endl;
	}

	void UserRule::rrcp_comparison()
	{

		PLOGW << "rrcp_comparison started.";

		struct MyEdgeDataDouble_IoT {
			uint64_t	tval;
			double      value[2];
		};
		MyEdgeDataDouble_IoT* data_X = new MyEdgeDataDouble_IoT[400];

#define _NO_BATCH
#ifdef _NO_BATCH
		std::vector <int> col_disp[5];
#else
		std::shared_ptr<double[]> col_disp[5];
#endif
		int num_data[5];

		for (auto f = 0; f < 5; f++) {
			string fname = roc::input_dir + roc::string_format("comparison/comparison_%d.csv", f);

			std::ifstream fs(fname);
			if (!fs.is_open()) {
				PLOGE << fname << " open failed.";
				return;
			}
			string line;

			int bar = 0;
			vector<int> bars;

			while (!fs.eof()) {
				getline(fs, line);
				if (line == "")break;
				size_t pos = line.find(',');
				double d1 = stod( line.substr(0, pos) );
				double d2 = stod(line.substr(pos+1));

				data_X[bar].tval = bar;
				data_X[bar].value[0] = d1;
				data_X[bar].value[1] = d2;
				
				bars.push_back(bar);
				bar++;
			}
			fs.close();

			num_data[f] = bar;
			int iot_de_count = 2;
			int num_threads = 2;	// number of cpu's if 0
			int64_t seed = -1;		// not specfied if not positive

			int num_trees = 100;
			int	tree_size = 256;

#ifdef _NO_BATCH
			// Create a forest of empty trees
			vector<int> dummy;
			shared_ptr<roc::RRCF> rrcf = roc::createRRCF(num_trees, tree_size,
				[&](int bar) {
					return (roc::EdgeDataDouble_IoT*) & data_X[bar];
				},
				iot_de_count, dummy, num_threads, seed);


			for (auto _b=0; _b<bars.size(); _b++){
				double c = rrcf->addPoint(_b);
				col_disp[f].push_back(c);
			}

#else
			// ? Some trouble with the batch execution. 
			shared_ptr<roc::RRCF> rrcf = roc::createRRCF(num_trees, tree_size,
				[&](int bar) {
					return (roc::EdgeDataDouble_IoT*)&data_X[bar];
				},
				iot_de_count, bars, num_threads, seed);

			col_disp[f] = rrcf->getCollusiveDisplacement();
#endif
		}

		string fname = roc::output_dir + "rrcf_comparison_codisp.csv";

		std::ofstream ss(fname);
		if (!ss.is_open()) {
			PLOGE << fname << " open failed.";
			return;
		}
		
		int num = 0;
		for (auto f = 0; f < 5; f++) {
			if (num < num_data[f])num = num_data[f];
		}
		string str;
		for (auto i = 0; i < num; i++) {
			if (i < num_data[0])ss << col_disp[0][i] << ","; else ss << ",";
			if (i < num_data[1])ss << col_disp[1][i] << ","; else ss << ",";
			if (i < num_data[2])ss << col_disp[2][i] << ","; else ss << ",";
			if (i < num_data[3])ss << col_disp[3][i] << ","; else ss << ",";
			if (i < num_data[4])ss << col_disp[4][i];
			ss << endl;
		}
		ss.close();

		delete[] data_X;

		PLOGW << "rrcp_comparison ended.";

	}

}