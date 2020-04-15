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

		// active's
		exs.push_back(roc::EX_0);
		ins.push_back(roc::IN_0);
		tfs.push_back(roc::MIN30);

		userRuleMemoryDbInit();

		return 0;
	}

	int UserRule::userRuleMemoryDbInit()
	{

		if (!annex_only) { // UserMemoryDB

			if (simulation) {

				for (auto ex : exs) {
					for (auto in : ins) {
						int rrcf_d = 1;

						for (auto tf : tfs) {
							roc::TfInfoIF* tf_i = roc::getTfInfo(ex, in, tf);
							UMemDB* user_memory_db = new UMemDB(ex, in, tf);
							tf_i->initTimeSeries(15000, roc::DE_EdgeDataDouble_IoT_not_syncronized_array, rrcf_d);
							tf_i->setUserMemoryDb(user_memory_db);
							user_memory_db->init();
						}

					}
				}
			}
			else { // real-time

				for (auto ex : exs) {
					for (auto in : ins) {
						int rrcf_d = 1;

						for (auto tf : tfs) {
							roc::TfInfoIF* tf_i = roc::getTfInfo(ex, in, tf);
							tf_i->initTimeSeries(20000, roc::DE_EdgeDataDouble_IoT_not_syncronized_array, rrcf_d);
							UMemDB* user_memory_db = new UMemDB(ex, in, tf);
							tf_i->setUserMemoryDb(user_memory_db);
							user_memory_db->init();
						}

					}
				}

			}


			// optimization
			//userRuleOptomizationSetup();
		}


		return 0;
	}


	// MemoryDB ---- members
	void UMemDB::init()
	{
		tf_info = roc::getTfInfo(ex, in, tf);
		assert(tf_info->_series_length() > 0); // alloc memory first

		// ex is roc::EX_0
		// in is roc::IN_0
		// tf is roc::MIN30

		// raw_edge_data
		iot_timeseries = roc::newEdgeDataDoubleIoTAccessor(tf_info);

		// rrcf parameters
		int num_trees = 200;
		int tree_size = 1000;
		int iot_de_count = shingle_size;
		vector<int> bars;
		int num_threads = 0;   // number of cpu's if 0
		int64_t seed = -1;		// not specfied if not positive

		shingle_data = roc::newEdgeDataDoubleIoTArrayData(tf_info, roc::DE_EdgeDataDouble_IoT, shingle_size, 15000);
		
		
		// create forest
		rrcf = roc::createRRCF(num_trees, tree_size, rrcf_func,
				iot_de_count, bars, num_threads, seed);

	
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
		// calculate memory_db
		int ex = tf_i->exchange();
		int in = tf_i->instrument();
		int tf = tf_i->timeframe();
		
		// ex == roc::EX_0
		// in == roc::IN_0
		// tf == roc::MIN30

		if (tf_i->_current_bar() < 47)return;
		
		UMemDB *umem = (UMemDB*)tf_i->_user_memory_db();

		MyEdgeDataDouble_IoT ed;

		roc::EdgeDataDouble_IoT* ts = (*umem->iot_timeseries)[shingle_size-1];
		// This time(tval) is the bar open time, so the bar close time is 30min later.
		ed.tval = ts->tval;
		for (auto i = 0; i < shingle_size; i++) {
			ts = (*umem->iot_timeseries)[shingle_size - 1 - i];
			ed.value[i] = ts->value[0];
		}
		
		umem->shingle_data->setIoT(0, (roc::EdgeDataDouble_IoT *)&ed);

		double co_disp = umem->rrcf->addPoint(tf_i->_current_bar());

		umem->ave_codisp.push_back(co_disp);

	}

	void UserRule::simulator_main(string& period, string& data_input_dir_)
	{
		rrcp_nyc_taxi_data_pump();

	}

	void UserRule::rrcp_nyc_taxi_data_pump()
	{
		PLOGW << "rrcp_nyc_taxi_data_pump started.";

		int ex = roc::EX_0;
		int in = roc::IN_0;
		int tf = roc::MIN30;

		const int n = 2010;
		int iot_de_count = 3;
		int num_trees = 100;
		int tree_size = 256;
		int num_threads = 0;	// number of cpu's if 0
		int64_t seed = 777;
		vector<int> bars;

		roc::EdgeDataDouble_IoT raw_edge_data;

		string fname = roc::input_dir + "numenta/nyc_taxi.csv";

		std::ifstream fs(fname);
		if (!fs.is_open()) {
			PLOGE << fname << " open failed.";
			return;
		}
		string line;
		getline(fs, line); // header

		roc::EdgeDataDouble_IoT ed;
		int count = 0;
		while(!fs.eof()) {
			getline(fs, line);
	
			// 2014-07-01 00:30:00,8127
			string _d = line.substr(0, 19);
			string _dt = roc::string_format("%s-%s-%sT%s:%s:00.000000",
				_d.substr(0, 4).c_str(),
				_d.substr(5, 2).c_str(),
				_d.substr(8, 2).c_str(),
				_d.substr(11, 2).c_str(),
				_d.substr(14, 2).c_str());
			ed.tval = roc::timeStringToTimeval(_dt.c_str());
			
			ed.value[0] = stod( line.substr(20) );

			pumpEdgeDataIoT(ex, in, tf, &ed);
			count++;
		}
		fs.close();

		PLOGW << count << " records are processed. rrcp_nyc_taxi_data_pump ended." << endl;


	}

}