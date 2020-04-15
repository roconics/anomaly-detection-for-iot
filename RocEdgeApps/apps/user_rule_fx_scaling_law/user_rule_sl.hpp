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

namespace ursl {


	class UMemDB_sl : public roc::UserMemoryDBBaseIF {   // pointed from TBfInfo
	public:
		UMemDB_sl(int _ex, int _in, int _tf) :ex(_ex), in(_in), tf(_tf), UserMemoryDBBaseIF() {}

		virtual ~UMemDB_sl(void) {}

		// Functionality
		void init();


		// Property
#if 1
		// return ratio = ( p[0]-p[1] ) / p[1]
		std::shared_ptr<roc::DoubleArrayDataIF> return_ratio;
		enum EN_return_mean_stddev_period {
			EN_ret_mean_stddev_3 = 0,
			EN_ret_mean_stddev_5 = 1,
			EN_ret_mean_stddev_10 = 2,
			EN_ret_mean_stddev_20 = 3,
			EN_ret_mean_stddev_40 = 4,
			EN_ret_mean_stddev_300 = 5,  // SEC1, SEC5 only
			EN_ret_mean_stddev_1000 = 6,  // SEC1 only
			NUM_RETURN_MEAN_STDDEV_PERIOD
		};
		int return_mean_stddev_period[NUM_RETURN_MEAN_STDDEV_PERIOD];

		//https://stackoverflow.com/questions/21377360/proper-way-to-create-unique-ptr-that-holds-an-allocated-array


		std::shared_ptr<roc::DoubleArrayDataIF> return_mean[NUM_RETURN_MEAN_STDDEV_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> return_stddev[NUM_RETURN_MEAN_STDDEV_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> return_mean_over_stddev300[NUM_RETURN_MEAN_STDDEV_PERIOD - 2];
		std::shared_ptr<roc::DoubleArrayDataIF> return_stddev_over_stddev300[NUM_RETURN_MEAN_STDDEV_PERIOD - 2];
		std::shared_ptr<roc::DoubleArrayDataIF> return_mean_over_stddev1000[NUM_RETURN_MEAN_STDDEV_PERIOD - 1];
		std::shared_ptr<roc::DoubleArrayDataIF> return_stddev_over_stddev1000[NUM_RETURN_MEAN_STDDEV_PERIOD - 1];



		enum EN_return_max_min_period {
			EN_ret_max_min_3 = 0,
			EN_ret_max_min_5 = 1,
			EN_ret_max_min_10 = 2,
			EN_ret_max_min_20 = 3,
			EN_ret_max_min_300 = 4,     // SEC1, SEC5 only
			EN_ret_max_min_1000 = 5,    // SEC1 only
			NUM_RETURN_MAX_MIN_PERIOD
		};
		deque< roc::ValandIdx > return_max_window[NUM_RETURN_MAX_MIN_PERIOD];
		deque< roc::ValandIdx > return_min_window[NUM_RETURN_MAX_MIN_PERIOD];
		int return_max_min_period[NUM_RETURN_MAX_MIN_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> return_min[NUM_RETURN_MAX_MIN_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> return_max[NUM_RETURN_MAX_MIN_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> return_min_divided_300[NUM_RETURN_MAX_MIN_PERIOD - 2];
		std::shared_ptr<roc::DoubleArrayDataIF> return_max_divided_300[NUM_RETURN_MAX_MIN_PERIOD - 2];
		std::shared_ptr<roc::DoubleArrayDataIF> return_min_divided_1000[NUM_RETURN_MAX_MIN_PERIOD - 1];
		std::shared_ptr<roc::DoubleArrayDataIF> return_max_divided_1000[NUM_RETURN_MAX_MIN_PERIOD - 1];

		// price range
		enum EN_price_range_period {
			EN_price_range_3 = 0,
			EN_price_range_5 = 1,
			EN_price_range_10 = 2,
			EN_price_range_20 = 3,
			EN_price_range_40 = 4,
			EN_price_range_300 = 5,
			EN_price_range_1000 = 6,
			NUM_PRICE_RANGE_PERIOD
		};
		int  price_range_period[NUM_PRICE_RANGE_PERIOD];
		deque< roc::ValandIdx > price_max_window[NUM_PRICE_RANGE_PERIOD];
		deque< roc::ValandIdx > price_min_window[NUM_PRICE_RANGE_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> price_min[NUM_PRICE_RANGE_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> price_max[NUM_PRICE_RANGE_PERIOD];

		// price
		enum EN_price_mean_stddev_period {
			EN_price_mean_stddev_3 = 0,
			EN_price_mean_stddev_5 = 1,
			EN_price_mean_stddev_10 = 2,
			EN_price_mean_stddev_20 = 3,
			EN_price_mean_stddev_40 = 4,
			NUM_PRICE_MEAN_STDDEV_PERIOD
		};
		int  price_mean_stddev_period[NUM_PRICE_MEAN_STDDEV_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> price_mean[NUM_PRICE_MEAN_STDDEV_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> price_stddev[NUM_PRICE_MEAN_STDDEV_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> price_stddev_over_price[NUM_PRICE_MEAN_STDDEV_PERIOD];


		enum EN_atr_adx_period {
			EN_atr_adx_3 = 0,
			EN_atr_adx_8 = 1,
			EN_atr_adx_14 = 2,
			EN_atr_adx_26 = 3,
			EN_atr_adx_52 = 4,
			NUM_ATR_ADX_PERIOD
		};
		int  atr_adx_period[NUM_ATR_ADX_PERIOD];

		std::shared_ptr<roc::DoubleArrayDataIF> atr[NUM_ATR_ADX_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> atr_velocity[NUM_ATR_ADX_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> atr_accel[NUM_ATR_ADX_PERIOD];
		//
		std::shared_ptr<roc::DoubleArrayDataIF> adx[NUM_ATR_ADX_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> plus_dm[NUM_ATR_ADX_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> minus_dm[NUM_ATR_ADX_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> adx_velocity[NUM_ATR_ADX_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> adx_accel[NUM_ATR_ADX_PERIOD];
#endif

		enum EN_atr_long_period {
			EN_atr_long_0 = 0,
			NUM_ATR_LONG_PERIOD
		};
		int atr_long_period[NUM_ATR_LONG_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> atr_long[NUM_ATR_LONG_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> atr_long_velocity[NUM_ATR_LONG_PERIOD];
		std::shared_ptr<roc::DoubleArrayDataIF> atr_long_accel[NUM_ATR_LONG_PERIOD];

		enum EN_dc_ratio {
			EN_DC_RATIO_0,
			EN_DC_RATIO_1,
			EN_DC_RATIO_2,
			EN_DC_RATIO_3,
			EN_DC_RATIO_4,
			EN_DC_RATIO_5,
			EN_DC_RATIO_6,
			EN_DC_RATIO_7,
			EN_DC_RATIO_8,
			EN_DC_RATIO_9,
			EN_DC_RATIO_10,
			EN_DC_RATIO_11,
			EN_DC_RATIO_12,
			NUM_DC_RATIO
		};

		vector< shared_ptr<roc::DirectionalChangeInfoIF> > dc_info[NUM_DC_RATIO];
		vector< double > dc_volatility_min1[NUM_DC_RATIO];
		vector< double > dc_volatility_hour1[NUM_DC_RATIO];

		double dc_delta[NUM_DC_RATIO];

		//
		int ex;
		int in;
		int tf;
		roc::TfInfoIF* tf_info;

	};

	class AnnexMemDB_sl {   // This is used for Trading  ( /*: public OrderManagerIF */ )
	public:
		AnnexMemDB_sl(int ex_, int in_, int tf_): ex(ex_),in(in_),tf(tf_){}
		virtual ~AnnexMemDB_sl(void) {}


		// Functionality
		void init();

		int setParam(vector<roc::Parameter> &parm_) {  //initialize
			parm = parm_;
			return 0;
		}
		// Properties
		int ex;
		int in;
		int tf;
		vector<roc::Parameter> parm;

		// optimizing or optimized indicators

	};


	class AnnexMemDB_optimization_sl {   // This is used for optimization or Trading  ( /*: public OrderManagerIF */ )
	public:
		AnnexMemDB_optimization_sl(int _ex, int _in, int tf);
		virtual ~AnnexMemDB_optimization_sl(void);

		// Functionality
		int init(vector<roc::Parameter>& parm_) {  //initialize
			parm = parm_;
			return 0;
		}
		// Properties
		vector<roc::Parameter>& parm;

		// optimizing indicators


	};

	class UserRule_sl : public roc::UserRuleBase
	{
	public:
		// Friends

		// Definitions

		// Constructor
		UserRule_sl() :roc::UserRuleBase()
		{
			roc::UserRuleBase::annex_only = true;
			for (int ex = 0; ex < roc::NUM_NAMED_EXCHANGE; ex++) {
				for (int in = 0; in < roc::NUM_NAMED_INSTRUMENT; in++) {
					for (int tf = 0; tf < roc::NUM_TIMEFRAME; tf++) {
						annex_memory_db[ex][in][tf] = 0;
					}
				}
			}
		}

		virtual ~UserRule_sl(void)
		{
			for (int ex = 0; ex < roc::NUM_NAMED_EXCHANGE; ex++) {
				for (int in = 0; in < roc::NUM_NAMED_INSTRUMENT; in++) {
					for (int tf = 0; tf < roc::NUM_TIMEFRAME; tf++) {
						if (annex_memory_db[ex][in][tf] != 0)delete annex_memory_db[ex][in][tf];
						annex_memory_db[ex][in][tf] = 0;
					}
				}
			}
			return;
		}

		//Functionality from roc_edge
		virtual int userRuleMemoryDbInit();   // init UserMemoryDB, and initialize indicators of UMemDB

		virtual void onTick(roc::TfInfoIF* tf_i);

		virtual void onBar(roc::TfInfoIF* tf_i);

		virtual void onBarClose(roc::TfInfoIF* tf_i);

		virtual void onBarCloseAnnex(roc::TfInfoIF* tf_i);

		virtual bool getData(std::string& msg, std::string& data) { return false; } // rest servce

		virtual void endOfSimulatorRun();

		//Functionality to roc_edge by user 


		//Functionality
		int userRuleSetup();

		int userRuleOptomizationSetup();

		AnnexMemDB_sl* annex_memory_db[roc::NUM_NAMED_EXCHANGE][roc::NUM_NAMED_INSTRUMENT][roc::NUM_TIMEFRAME]; // This is also used for optimization 

	private:
		//Friends

		//Definitions

		//Constructors

		//Functionality


		bool writeDCtoCsv(int ex, int in, int tf, uint64_t start_tv, uint64_t end_tv, string& fname);
		// data for  the s&cof Feb2020 magagine article 
		bool writeTfToCsv(int ex, int in, int tf, uint64_t start_tv, uint64_t end_tv, string& fname);

		//--------

		//Getters

		//Setters

		//Operators

		//Properties


	};



}
