/*
 * Copyright 2019,2020-, Roconics Co., All Rights Reserved.
 */

#include "user_rule_sl.hpp"


using namespace std;

namespace ursl {


	int UserRule_sl::userRuleSetup()
	{
		simulation = true;
		annex_only = false;

		// active's
		exs.push_back(roc::DUKAS);
		ins.push_back(roc::EURUSD);
		tfs.push_back(roc::MIN1);
		tfs.push_back(roc::HOUR1);

		return 0;
	}

	int UserRule_sl::userRuleMemoryDbInit()
	{
		if (!annex_only) { // UserMemoryDB

			if (simulation) {

				for (auto ex : exs) {
					for (auto in : ins) {
						for (auto tf : tfs) {
							roc::TfInfoIF* tf_i = roc::getTfInfo(ex, in, tf);
							if (tf != roc::TICK) {
								UMemDB_sl* user_memory_db = new UMemDB_sl(ex, in, tf);
								user_memory_db->init();
								tf_i->setDataElemType(roc::DE_TOHLCV);
								tf_i->setUserMemoryDb(user_memory_db);

							}

							if (tf == roc::MIN1) {
							}
						}
					}
				}

			}
			else { // real-time

				for (auto ex : exs) {
					for (auto in : ins) {
						for (auto tf : tfs) {
							roc::TfInfoIF* tf_i = roc::getTfInfo(ex, in, tf);
							if (tf == roc::TICK) {
								tf_i->initTimeSeries(20000, roc::DE_TickData);
							}

							if (tf != roc::TICK) {
								tf_i->initTimeSeries(2000, roc::DE_TOHLCV);

								UMemDB_sl* user_memory_db = new UMemDB_sl(ex, in, tf);
								user_memory_db->init();
								tf_i->setUserMemoryDb(user_memory_db);

							}
						}

					}
				}

			}

			// set AnnexMemDB_sl
			annex_memory_db[roc::DUKAS][roc::EURUSD][roc::MIN1] = new AnnexMemDB_sl(roc::DUKAS, roc::EURUSD, roc::MIN1);
			annex_memory_db[roc::DUKAS][roc::EURUSD][roc::MIN1]->init();
			annex_memory_db[roc::DUKAS][roc::EURUSD][roc::HOUR1] = 0;

			vector<roc::Parameter> parm_best;
			parm_best.push_back(roc::Parameter("sl_int", "int", 0));
			parm_best.push_back(roc::Parameter("sl_uint64_t", "uint64_t", (uint64_t)0));
			parm_best.push_back(roc::Parameter("sl_bool", "bool", true));
			parm_best.push_back(roc::Parameter("sl_float", "float", 0.1f));
			parm_best.push_back(roc::Parameter("sl_alpha", "double", 0.33));
			parm_best.push_back(roc::Parameter("sl_alpha", "chars", "chars0"));

			annex_memory_db[roc::DUKAS][roc::EURUSD][roc::MIN1]->setParam(parm_best);


			// optimization
			userRuleOptomizationSetup();
		}

		return 0;
	}


	// MemoryDB ---- members
	void UMemDB_sl::init()
	{
		tf_info = roc::getTfInfo(ex, in, tf);
		if (tf_info->_series_length() == 0) {
			PLOGE << "Time series length is 0." << endl;
			exit(-1);
		}
		//assert(tf_info->_series_length() > 0); // alloc memory first
#if 1
		return_mean_stddev_period[UMemDB_sl::EN_ret_mean_stddev_3] = 3;
		return_mean_stddev_period[UMemDB_sl::EN_ret_mean_stddev_5] = 5;
		return_mean_stddev_period[UMemDB_sl::EN_ret_mean_stddev_10] = 10;
		return_mean_stddev_period[UMemDB_sl::EN_ret_mean_stddev_20] = 20;
		return_mean_stddev_period[UMemDB_sl::EN_ret_mean_stddev_40] = 40;
		return_mean_stddev_period[UMemDB_sl::EN_ret_mean_stddev_300] = 300;
		return_mean_stddev_period[UMemDB_sl::EN_ret_mean_stddev_1000] = 1000;

		return_max_min_period[UMemDB_sl::EN_ret_max_min_3] = 3;
		return_max_min_period[UMemDB_sl::EN_ret_max_min_5] = 5;
		return_max_min_period[UMemDB_sl::EN_ret_max_min_10] = 10;
		return_max_min_period[UMemDB_sl::EN_ret_max_min_20] = 20;
		return_max_min_period[UMemDB_sl::EN_ret_max_min_300] = 300;
		return_max_min_period[UMemDB_sl::EN_ret_max_min_1000] = 1000;

		//-----------
		price_range_period[UMemDB_sl::EN_price_range_3] = 3;
		price_range_period[UMemDB_sl::EN_price_range_5] = 5;
		price_range_period[UMemDB_sl::EN_price_range_10] = 10;
		price_range_period[UMemDB_sl::EN_price_range_20] = 20;
		price_range_period[UMemDB_sl::EN_price_range_40] = 40;
		price_range_period[UMemDB_sl::EN_price_range_300] = 300;
		price_range_period[UMemDB_sl::EN_price_range_1000] = 1000;

		price_mean_stddev_period[UMemDB_sl::EN_price_mean_stddev_3] = 3;
		price_mean_stddev_period[UMemDB_sl::EN_price_mean_stddev_5] = 5;
		price_mean_stddev_period[UMemDB_sl::EN_price_mean_stddev_10] = 10;
		price_mean_stddev_period[UMemDB_sl::EN_price_mean_stddev_20] = 20;
		price_mean_stddev_period[UMemDB_sl::EN_price_mean_stddev_40] = 40;


		atr_adx_period[UMemDB_sl::EN_atr_adx_3] = 3;
		atr_adx_period[UMemDB_sl::EN_atr_adx_8] = 8;
		atr_adx_period[UMemDB_sl::EN_atr_adx_14] = 14;
		atr_adx_period[UMemDB_sl::EN_atr_adx_26] = 26;
		atr_adx_period[UMemDB_sl::EN_atr_adx_52] = 52;

		atr_long_period[UMemDB_sl::EN_atr_long_0] = 300;

		return_ratio = roc::newDoubleArrayData(tf_info,roc::DE_Numeric);


		for (int i = 0; i < UMemDB_sl::NUM_RETURN_MEAN_STDDEV_PERIOD; i++) {
			return_mean[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			return_stddev[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			if (i < UMemDB_sl::NUM_RETURN_MEAN_STDDEV_PERIOD - 2) {
				return_mean_over_stddev300[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			}
			if (i < UMemDB_sl::NUM_RETURN_MEAN_STDDEV_PERIOD - 2) {
				return_stddev_over_stddev300[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			}
			if (i < UMemDB_sl::NUM_RETURN_MEAN_STDDEV_PERIOD - 1) {
				return_mean_over_stddev1000[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			}
			if (i < UMemDB_sl::NUM_RETURN_MEAN_STDDEV_PERIOD - 1) {
				return_stddev_over_stddev1000[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			}
		}

		for (int i = 0; i < UMemDB_sl::NUM_RETURN_MAX_MIN_PERIOD; i++) {
			return_min[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			return_max[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);

			if (i < UMemDB_sl::NUM_RETURN_MAX_MIN_PERIOD - 2) {
				return_min_divided_300[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
				return_max_divided_300[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			}
			if (i < UMemDB_sl::NUM_RETURN_MAX_MIN_PERIOD - 1) {
				return_min_divided_1000[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
				return_max_divided_1000[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			}
		}
		//---------------
		for (int i = 0; i < UMemDB_sl::NUM_PRICE_RANGE_PERIOD; i++) {
			price_min[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			price_max[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
		}

		//---------------
		for (int i = 0; i < UMemDB_sl::NUM_PRICE_MEAN_STDDEV_PERIOD; i++) {
			price_mean[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			price_stddev[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			price_stddev_over_price[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
		}

		//---------------

		for (int i = 0; i < UMemDB_sl::NUM_ATR_ADX_PERIOD; i++) {
			atr[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			atr_velocity[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			atr_accel[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			//
			adx[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			plus_dm[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			minus_dm[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			adx_velocity[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			adx_accel[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
		}
#endif

		// --------------------------------------
		for (int i = 0; i < UMemDB_sl::NUM_ATR_LONG_PERIOD; i++) {
			atr_long[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			atr_long_velocity[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
			atr_long_accel[i] = roc::newDoubleArrayData(tf_info, roc::DE_Numeric);
		}



		if (tf != roc::MIN1)return;
		/*

				seg_height_ratio
			seg heght 70	0.005833333

		*/

		for (int ra = 0; ra < UMemDB_sl::NUM_DC_RATIO; ra++) {
			dc_delta[ra] = 0;
		}
		dc_info->clear();

		dc_delta[UMemDB_sl::EN_DC_RATIO_0] = 0.00125;
		dc_delta[UMemDB_sl::EN_DC_RATIO_1] = 0.001458333;
		dc_delta[UMemDB_sl::EN_DC_RATIO_2] = 0.001666667;
		dc_delta[UMemDB_sl::EN_DC_RATIO_3] = 0.001875;
		dc_delta[UMemDB_sl::EN_DC_RATIO_4] = 0.002083333;
		dc_delta[UMemDB_sl::EN_DC_RATIO_5] = 0.002291667;
		dc_delta[UMemDB_sl::EN_DC_RATIO_6] = 0.0025;
		dc_delta[UMemDB_sl::EN_DC_RATIO_7] = 0.002708333;
		dc_delta[UMemDB_sl::EN_DC_RATIO_8] = 0.002916667;
		dc_delta[UMemDB_sl::EN_DC_RATIO_9] = 0.003125;
		dc_delta[UMemDB_sl::EN_DC_RATIO_10] = 0.003333333;
		dc_delta[UMemDB_sl::EN_DC_RATIO_11] = 0.003541667;
		dc_delta[UMemDB_sl::EN_DC_RATIO_12] = 0.00375;

	}
	
	void AnnexMemDB_sl::init()
	{
		roc::TfInfoIF *tf_info = roc::getTfInfo(ex, in, tf);
		assert(tf_info->_series_length() > 0); // alloc memory first



	}

	void UserRule_sl::onTick(roc::TfInfoIF* tf_i)
	{
		// process with memory_db and annex_memory_db
	}

	void UserRule_sl::onBar(roc::TfInfoIF* tf_i)
	{
		// process with memory_db and annex_memory_db
	}

	void UserRule_sl::onBarCloseAnnex(roc::TfInfoIF* tf_i)
	{
		// calculate annex_memory_db
	}

	void UserRule_sl::onBarClose(roc::TfInfoIF* tf_i)
	{
		// calculate memory_db
		static double ave_elapsed_time = 0;
		static int	ave_count = 0;
		int ex = tf_i->exchange();
		int in = tf_i->instrument();
		int tf = tf_i->timeframe();

#ifdef 	PRINT_TIME
		auto start_onBarClose = std::chrono::high_resolution_clock::now();
#endif

		UMemDB_sl* mem_db = (UMemDB_sl*)tf_i->_user_memory_db();

#if 0 

		calculateReturns(mem_db->return_ratio);

		calculateReturnMeanStdddev(mem_db->return_ratio, UMemDB_sl::NUM_RETURN_MEAN_STDDEV_PERIOD,
			mem_db->return_mean_stddev_period,
			mem_db->return_mean, mem_db->return_stddev);

		calculateShortLongRatio(UMemDB_sl::NUM_RETURN_MEAN_STDDEV_PERIOD - 2,
			mem_db->return_mean, mem_db->return_mean_over_stddev300,
			mem_db->return_stddev[UMemDB_sl::EN_ret_mean_stddev_300]);

		calculateShortLongRatio(UMemDB_sl::NUM_RETURN_MEAN_STDDEV_PERIOD - 2,
			mem_db->return_stddev, mem_db->return_stddev_over_stddev300,
			mem_db->return_stddev[UMemDB_sl::EN_ret_mean_stddev_300]);

		calculateShortLongRatio(UMemDB_sl::NUM_RETURN_MEAN_STDDEV_PERIOD - 1,
			mem_db->return_mean, mem_db->return_mean_over_stddev1000,
			mem_db->return_stddev[UMemDB_sl::EN_ret_mean_stddev_1000]);

		calculateShortLongRatio(UMemDB_sl::NUM_RETURN_MEAN_STDDEV_PERIOD - 1,
			mem_db->return_stddev, mem_db->return_stddev_over_stddev1000,
			mem_db->return_stddev[UMemDB_sl::EN_ret_mean_stddev_1000]);

		for (auto i = 0; i < UMemDB_sl::NUM_RETURN_MAX_MIN_PERIOD; i++) {
			int period = mem_db->return_max_min_period[i];
			calculateReturnMin(mem_db->return_ratio, period, mem_db->return_min_window[i], mem_db->return_min[i]);
			calculateReturnMax(mem_db->return_ratio, period, mem_db->return_max_window[i], mem_db->return_max[i]);
		}

		//
		calculateShortLongRatio(UMemDB_sl::NUM_RETURN_MAX_MIN_PERIOD - 1,
			mem_db->return_min, mem_db->return_min_divided_1000,
			mem_db->return_min[UMemDB_sl::EN_ret_max_min_1000]);

		calculateShortLongRatio(UMemDB_sl::NUM_RETURN_MAX_MIN_PERIOD - 1,
			mem_db->return_max, mem_db->return_max_divided_1000,
			mem_db->return_max[UMemDB_sl::EN_ret_max_min_1000]);



		//----------------------	
		for (auto i = 0; i < UMemDB_sl::NUM_PRICE_RANGE_PERIOD; i++) {
			int period = mem_db->price_range_period[i];
			calculatePriceMin(period, mem_db->price_min_window[i], mem_db->price_min[i]);
			calculatePriceMax(period, mem_db->price_max_window[i], mem_db->price_max[i]);
		}

		calculatePriceMeanStdddev(UMemDB_sl::NUM_PRICE_MEAN_STDDEV_PERIOD, mem_db->price_mean_stddev_period, mem_db->price_mean, mem_db->price_stddev);

		calculatePriceStdddevOverPrice(UMemDB_sl::NUM_PRICE_MEAN_STDDEV_PERIOD, mem_db->price_mean_stddev_period, mem_db->price_stddev, mem_db->price_stddev_over_price);

		//----------------------	

		caluculateAtrAdx(mem_db->atr, mem_db->atr_velocity, mem_db->atr_accel,
			mem_db->adx, mem_db->plus_dm, mem_db->minus_dm,
			mem_db->adx_velocity, mem_db->adx_accel,
			UMemDB_sl::NUM_ATR_ADX_PERIOD, mem_db->atr_adx_period);

#endif

		caluculateAtr(mem_db->atr_long, mem_db->atr_long_velocity, mem_db->atr_long_accel,
			UMemDB_sl::NUM_ATR_LONG_PERIOD, mem_db->atr_long_period);

		if (in != roc::EURUSD || tf != roc::MIN1)return;
#define ATR (*mem_db->atr_long[UMemDB_sl::EN_atr_long_0])



		if (UMemDB_sl::NUM_DC_RATIO > 0) {
			for (auto ra = 0; ra < UMemDB_sl::NUM_DC_RATIO; ra++) {
					if (mem_db->dc_delta[ra] != 0) {

					bool b = roc::directionalChange(tf_i, mem_db->dc_delta[ra], mem_db->dc_delta[ra],
						mem_db->dc_info[ra],
						0, 0
					);
					// 
					if (b) {
						shared_ptr<roc::DirectionalChangeInfoIF> ete = mem_db->dc_info[ra].back();

						mem_db->dc_volatility_min1[ra].push_back(ATR[0]);

						//
						assert(tf != roc::HOUR1);
						roc::TfInfoIF* tf_i_hour1 = roc::getTfInfo(ex, in, roc::HOUR1);
						UMemDB_sl* mem_db_hour1 = (UMemDB_sl*)tf_i_hour1->_user_memory_db();

						shared_ptr<roc::TimeAccessorIF> _time = newTimeAccessor(tf_i);
						shared_ptr<roc::TimeAccessorIF> _time_hour1 = newTimeAccessor(tf_i_hour1);


						if ( (*_time)[0] + roc::timeframe_interval_in_us[tf_i->timeframe()] ==
							(*_time_hour1)[0] + roc::timeframe_interval_in_us[roc::HOUR1]) {
							// closed at the same time
							mem_db->dc_volatility_hour1[ra].push_back((*mem_db_hour1->atr_long[UMemDB_sl::EN_atr_long_0])[0]);
						}
						else {
							mem_db->dc_volatility_hour1[ra].push_back((*mem_db_hour1->atr_long[UMemDB_sl::EN_atr_long_0])[1]);
						}

					}
				}
			}
		}



#ifdef 	PRINT_TIME
		ave_elapsed_time += (double)(std::chrono::high_resolution_clock::now() - start_onBarClose).count();
		if (++ave_count >= TOTAL_COUNT) {
			std::cout << string_format("%.3fms", ave_elapsed_time / 1000000.0 / TOTAL_COUNT) << " onBarClose" << std::endl;
			ave_elapsed_time = 0;
			ave_count = 0;
		}
#endif


	}


}