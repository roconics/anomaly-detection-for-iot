/*
 * Copyright 2019,2020-, Roconics Co., All Rights Reserved.
 */

#include "user_rule_sl.hpp"

#


namespace ursl {

	void UserRule_sl::endOfSimulatorRun()
	{
		int ex = roc::DUKAS;
		int in = roc::EURUSD;
		int tf = roc::MIN1;

		if (annex_only)return;

		// backtest      1/2010–8/2019
		// scaling law   2004- 2019
		string fname = roc::output_dir + "EURUSD_dc_Jan2010-Aug2019.csv";

		string fname_MIN1 = roc::output_dir + "EURUSD_MIN1_Jan2010-Aug2019.csv";
		string fname_HOUR1 = roc::output_dir + "EURUSD_HOUR1_Jan2010-Aug2019.csv";


		//   "2014-03-07T20:52:17.453618Z"
		uint64_t start_tv;
		start_tv = roc::timeStringToTimeval("2010-01-01T00:00:00.000000");

		uint64_t end_tv;
		end_tv = roc::timeStringToTimeval("2019-09-01T00:00:00.000000");


		//writeDCtoCsv( ex, in, MIN1, start_tv, end_tv, fname);

		//writeTfToCsv(ex, in, MIN1, start_tv, end_tv, fname_MIN1);
		//writeTfToCsv(ex, in, HOUR1, start_tv, end_tv, fname_HOUR1);
		//----

		fname = roc::output_dir + "EURUSD_dc_feb2007-dec2019.csv";
		start_tv = roc::timeStringToTimeval("2007-02-01T00:00:00.000000");
		end_tv = roc::timeStringToTimeval("2020-01-01T00:00:00.000000");

		writeDCtoCsv(ex, in, roc::MIN1, start_tv, end_tv, fname);

		string fname_HOUR1_all = roc::output_dir + "EURUSD_HOUR1_Jan2007-Jan2020.csv";
		uint64_t start_tv_all;
		start_tv_all = roc::timeStringToTimeval("2007-01-01T00:00:00.000000");

		uint64_t end_tv_all;
		end_tv_all = roc::timeStringToTimeval("2020-02-01T00:00:00.000000");
		writeTfToCsv(ex, in, roc::HOUR1, start_tv_all, end_tv_all, fname_HOUR1_all);

		string fname_MIN1_all = roc::output_dir + "EURUSD_MIN1_Jan2007-Jan2020.csv";
		writeTfToCsv(ex, in, roc::MIN1, start_tv_all, end_tv_all, fname_MIN1_all);

	}



	bool UserRule_sl::writeDCtoCsv(int ex, int in, int tf, uint64_t start_tv, uint64_t end_tv, string& fname)  // data of the s&cof Feb2020 magagine article 
	{
		// ndc period  300 hours
		uint64_t ndx_period = 300LL * 3600LL * 1000000LL;

		std::ofstream ss(fname);
		if (!ss.is_open()) {
			cout << "open failed " << fname << endl;
			return false;
		}

		ss << "time,dc_delta,extreme,up_dn,seg_height,seg_time,n_ave_seg_height,n_ave_seg_return,n_ave_seg_time,m_seg_height,m_seg_return,m_seg_time,n_dc,atr" << endl;

		double fdig = roc::getRoundDigit(ex, in);

		string _fmt;
		if (roc::getDigit(ex, in) == 3) {
			_fmt = "%.3f";
		}
		else {
			_fmt = "%.5f";
		}

		roc::TfInfoIF* tf_i = roc::getTfInfo(ex, in, tf);
		UMemDB_sl* mem_db = (UMemDB_sl*)tf_i->_user_memory_db();

		for (auto ra = 0; ra < UMemDB_sl::NUM_DC_RATIO; ra++) {
			if (mem_db->dc_delta[ra] != 0) {

				vector<double> seg_height_sorted;
				vector<double> seg_return_sorted;
				vector<double> seg_time_sorted;

				int last_pos = mem_db->dc_info[ra].size() - 2;
				for (auto pos = 0; pos <= last_pos; pos++) {
					vector< shared_ptr<roc::DirectionalChangeInfoIF> >& ev = mem_db->dc_info[ra];
					shared_ptr<roc::DirectionalChangeInfoIF> ete = ev[pos];

					if (ete->_extream_tv() >= end_tv)break;
					if (ete->_extream_tv() < start_tv)continue;
					assert(pos > 2);

					string _time_str = roc::timeSinceEpoch_YYYY_mm_dd_HH_MM_SS_mmmmmm(ete->_extream_tv());
					ss << _time_str.substr(0, 19) << ","

						<< mem_db->dc_delta[ra] * 100.0 << ","      //  %

						<< roc::string_format(_fmt, (floor(ete->_extream_value() / fdig + 0.5)) * fdig) << ","

						// up_dn
						<<  (int)ete->_dc_event_type()  << ",";	// -1: goes down from peak  1: goes up from bottom

					 // seg_height (in pips)
					double h = (ete->_extream_value() - ete->_overshoot_extream_value()) * 100;
					ss << ((ete->_extream_type() == roc::DC_EXTREAM::UPPER) ? h : -h) << ",";

					// seg_time
					int t = ete->_overshoot_extream_bar() - ete->_extream_bar();
					ss << t << ",";



					int64_t n_min = ete->_overshoot_extream_tv() - ndx_period;

					int n_cnt = 0;
					double n_ave_seg_height = 0;
					double n_ave_seg_return = 0;
					double n_ave_seg_time = 0;

					for (auto k = pos; k >= 0; k--, n_cnt++) {
						vector< shared_ptr<roc::DirectionalChangeInfoIF> >& ev2 = mem_db->dc_info[ra];
						shared_ptr<roc::DirectionalChangeInfoIF> ete1 = ev2[k];

						n_ave_seg_height += abs(ete1->_extream_value() - ete1->_overshoot_extream_value());
						n_ave_seg_return += abs(ete1->_extream_value() - ete1->_overshoot_extream_value()) / ete1->_extream_value();
						n_ave_seg_time += ete1->_overshoot_extream_bar() - ete1->_extream_bar();

						if (k == pos) {
							seg_height_sorted.push_back(abs(ete1->_extream_value() - ete1->_overshoot_extream_value()));
							seg_return_sorted.push_back(
								(abs(ete1->_extream_value() - ete1->_overshoot_extream_value()) / ete1->_extream_value()) * 100.0);
							seg_time_sorted.push_back(ete1->_overshoot_extream_bar() - ete1->_extream_bar());
						}

						if (ete1->_extream_tv() < n_min)break;
					}
					// 
					n_ave_seg_height /= n_cnt;
					ss << n_ave_seg_height << ",";
					n_ave_seg_return /= n_cnt;
					ss << (n_ave_seg_return * 100.0) << ",";     //  %
					n_ave_seg_time /= n_cnt;
					ss << n_ave_seg_time << ",";

					//
#define  DC_NUM_LARGE_TH  1000			
#define  DC_NUM_SMALL_TH  300			
					if (seg_height_sorted.size() >= DC_NUM_SMALL_TH
						&& ra >= UMemDB_sl::EN_DC_RATIO_5 && ra <= UMemDB_sl::EN_DC_RATIO_9) {
						sort(seg_height_sorted.end() - DC_NUM_SMALL_TH, seg_height_sorted.end());
						//vector<double> seg_height_percentile_table(101);
						//for (int i = 0; i <= 100; i++) { // 
						//	seg_height_percentile_table[i] 
						//    = GetValueFromPercentile(DC_NUM_SMALL_TH, &seg_time_sorted[seg_height_sorted.size()-DC_NUM_SMALL_TH], 0.01 * i);
						//}
						//GetPercentileOfValueByTable(n_ave_seg_height, seg_height_percentile_table);
						ss << roc::getValueFromPercentile(DC_NUM_SMALL_TH, &seg_height_sorted[seg_height_sorted.size() - DC_NUM_SMALL_TH], 0.5) << ",";
						//-------
						std::sort(seg_return_sorted.begin(), seg_return_sorted.end());
						ss << roc::getValueFromPercentile(DC_NUM_SMALL_TH, &seg_return_sorted[seg_return_sorted.size() - DC_NUM_SMALL_TH], 0.5) << ",";
						//
						std::sort(seg_time_sorted.begin(), seg_time_sorted.end());
						ss << roc::getValueFromPercentile(DC_NUM_SMALL_TH, &seg_time_sorted[seg_time_sorted.size() - DC_NUM_SMALL_TH], 0.5) << ",";


					}
					else {
						ss << ",,,";
					}

					// n_dc
					ss << n_cnt << ",";

					ss << mem_db->dc_volatility_hour1[ra][pos]

						<< endl;
				}
			}

		}

		ss.close();


		// roc::TOHLCVAccessor tohlcv((roc::TfInfo *)&tf_i, true);


		return true;
	}

	bool UserRule_sl::writeTfToCsv(int ex, int in, int tf, uint64_t start_tv, uint64_t end_tv, string& fname)
	{

		roc::TfInfoIF* tf_i = roc::getTfInfo(ex, in, tf);

		std::ofstream ss(fname);
		if (!ss.is_open()) {
			cout << "open failed " << fname << endl;
			return false;
		}
		ss << "time,open,high,low,close\n";

		UMemDB_sl* mem_db = (UMemDB_sl*)tf_i->_user_memory_db();


		std::string _fmt_csv;
		if (roc::instrument_digit[ex][in] == 3)_fmt_csv = "%.3f,%.3f,%.3f,%.3f";
		else _fmt_csv = "%.5f,%.5f,%.5f,%.5f";

		double fdig = roc::getRoundDigit(ex, in);

		for (auto cb = 0; cb < tf_i->_series_length(); cb++) {

			roc::TOHLCV& tohlcv = tf_i->_tohlcv()[cb];

			uint64_t _time = tohlcv.tval_open;
			assert(_time > 0);

			if (_time >= end_tv)break;
			if (_time < start_tv)continue;

			string _time_str = roc::timeSinceEpoch_YYYY_mm_dd_HH_MM_SS_mmmmmm(_time);

			ss << _time_str.substr(0, 19) << ","

				<< roc::string_format(_fmt_csv,
				(floor(tohlcv.open / fdig + 0.5f)) * fdig,
					(floor(tohlcv.high / fdig + 0.5f)) * fdig,
					(floor(tohlcv.low / fdig + 0.5f)) * fdig,
					(floor(tohlcv.close / fdig + 0.5f)) * fdig) << endl;

		}

		ss.close();

		return true;
	}

}