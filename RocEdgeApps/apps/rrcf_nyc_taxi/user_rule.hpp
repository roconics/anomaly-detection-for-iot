/*
 * Copyright 2019,2020-, Roconics Co., All Rights Reserved.
 */

#pragma once

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <memory>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <assert.h>
#include <functional>

#include <roc_edge/user_rule_base.hpp> 
#include <roc_edge/roc_edge_interface.hpp> 


using namespace std;

namespace urule {

	struct RrcfEdgeDataDouble_IoT {
		uint64_t	tval;
		double      value[48];
	};

	const int shingle_size{ 48 };

	class UMemDB : public roc::UserMemoryDBBaseIF {   // pointed from TBfInfo
	public:
		UMemDB(int _ex, int _in, int _tf) :ex{ _ex }, in{ _in }, tf{ _tf }, UserMemoryDBBaseIF() {}

		virtual ~UMemDB(void) {};

		//
		void init();

		/// platorm defined timeseries accessor
		std::shared_ptr<roc::EdgeDataDoubleIoTAccessorIF> ed_access{nullptr};

		/// rrcf tree
		shared_ptr<roc::RRCF> rrcf;

		/// raw_edge_data
		std::shared_ptr<roc::EdgeDataDoubleIoTAccessorIF> iot_timeseries;

		/// single data 
		shared_ptr<roc::EdgeDataDoubleIoTArrayDataIF> shingle_data;

		vector<double>  ave_codisp;

		function<roc::EdgeDataDouble_IoT*(int)> rrcf_func = [&](int bar) {
			return shingle_data->barData(bar);
		};


		// ------------
		int ex;
		int in;
		int tf;
		roc::TfInfoIF* tf_info;

	};

	struct MyEdgeDataDouble_IoT {
		uint64_t	tval;						// tval.sec is 0 if empty,     usec_since_epoch
		double      value[shingle_size];		// number of values is  _iot_de_count() of InInfo
	};


	class UserRule : public roc::UserRuleBase
	{
	public:

		UserRule() :roc::UserRuleBase() {}

		virtual ~UserRule(void) {}

		//Functionality from roc_edge
		virtual int userRuleMemoryDbInit();   // init UserMemoryDB, and initialize indicators of UMemDB

		virtual void onTick(roc::TfInfoIF* tf_i);

		virtual void onBar(roc::TfInfoIF* tf_i);

		virtual void onBarClose(roc::TfInfoIF* tf_i);

		virtual void onBarCloseAnnex(roc::TfInfoIF* tf_i);

		virtual bool getData(std::string& msg, std::string& data) { return false; } // rest servce

		virtual void endOfSimulatorRun();

		//Functionality to roc_edge by user 
	
		int userRuleSetup();

		int userRuleOptomizationSetup();

		void simulator_main(string& period, string& data_input_dir_);

		void rrcp_nyc_taxi_data_pump();

		void writeCsv();

	private:


	};



}
