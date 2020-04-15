/*
 * Copyright 2019,2020-, Roconics Co., All Rights Reserved.
 */

#include "user_rule.hpp"

#


namespace urule {

	void UserRule::endOfSimulatorRun()
	{
		int ex = roc::DUKAS;
		int in = roc::EURUSD;
		int tf = roc::TICK;

		if (annex_only)return;

		writeCsv();
	}

	void UserRule::writeCsv()
	{
		int ex = roc::EX_0;
		int in = roc::IN_0;
		int tf = roc::MIN30;

		PLOGW << "Writing codisp into csv file." << endl;

		roc::TfInfoIF* tf_i = roc::getTfInfo(ex, in, tf);

		UMemDB* umem = (UMemDB*)tf_i->_user_memory_db();

		MyEdgeDataDouble_IoT* ed;

		// write to csv-file
		string fname = roc::output_dir + "rrcf_nyc_taxi.csv";

		std::ofstream ss(fname);
		if (!ss.is_open()) {
			PLOGE << fname << " open failed.";

			return;
		}
		for (auto i = 0; i < umem->ave_codisp.size(); i++) {
			ed = (MyEdgeDataDouble_IoT *)umem->shingle_data->barData(shingle_size - 1 + i);
			ss << umem->ave_codisp[i];
			for (auto j = 0; j < shingle_size; j++) {
				ss << "," << ed->value[j];
			}
			ss	<< endl;
		}
		ss.close();

	}

}