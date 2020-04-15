/*
 * Copyright 2019,2020-, Roconics Co., All Rights Reserved.
 */

#pragma once

//System Includes
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

#include <roc_edge/user_rule_base.hpp> 
#include <roc_edge/roc_edge_interface.hpp> 

using namespace std;

namespace urule {


	class UMemDB_sl : public roc::UserMemoryDBBaseIF {   // pointed from TBfInfo
	public:
		UMemDB_sl(int _ex, int _in, int _tf) :ex(_ex), in(_in), tf(_tf), UserMemoryDBBaseIF() {}

		virtual ~UMemDB_sl(void) {};

		// Functionality
		void init();


		// Property



		// ------------
		int ex;
		int in;
		int tf;
		roc::TfInfoIF* tf_info;

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

		void rrcp_bath_detection();

		void rrcp_streaming_detection();

		void rrcp_comparison();
		
	private:


	};



}
