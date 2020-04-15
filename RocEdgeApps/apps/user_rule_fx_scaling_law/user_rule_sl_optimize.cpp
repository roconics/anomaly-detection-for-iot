/*
 * Copyright 2019, 2020 - , Roconics Co., All Rights Reserved.
 */

#include "user_rule_sl.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

namespace ursl{


	int UserRule_sl::userRuleOptomizationSetup()
	{
		// multi-thread user_rules
		// initialize annex memory db
		// the ledger of trading is MIN1 db

		if (simulation) {

			int ex = roc::DUKAS;
			int in = roc::EURUSD;
			int tf = roc::MIN1;

			roc::TfInfoIF* tf_i = roc::getTfInfo(ex, in, tf);
			assert(tf_i->_series_length() > 0);

			vector<roc::Parameter> parm_;

			// thread 1
			UserRule_sl* user_rule_ = new UserRule_sl();
			user_rule_->annex_only = true;
			// Caveat!!   init UserMemoryDB
			user_rule_->annex_memory_db[ex][in][tf] = new AnnexMemDB_sl(ex, in, tf);
			user_rule_->annex_memory_db[ex][in][tf]->init();
			parm_.clear();
			parm_.push_back(roc::Parameter("sl_int", "int", 1));
			parm_.push_back(roc::Parameter("sl_uint64_t", "uint64_t", (uint64_t)1));
			parm_.push_back(roc::Parameter("sl_bool", "bool", true));
			parm_.push_back(roc::Parameter("sl_float", "float", 0.2f));
			parm_.push_back(roc::Parameter("sl_alpha", "double", 0.66));
			parm_.push_back(roc::Parameter("sl_alpha", "chars", "chars1"));
			user_rule_->annex_memory_db[ex][in][tf]->setParam(parm_);
			multi_user_rules.push_back(user_rule_);

			// thread 2
			user_rule_ = new UserRule_sl();
			user_rule_->annex_only = true;
			// Caveat!!   init UserMemoryDB
			user_rule_->annex_memory_db[ex][in][tf] = new AnnexMemDB_sl(ex, in, tf);
			user_rule_->annex_memory_db[ex][in][tf]->init();
			parm_.clear();
			parm_.push_back(roc::Parameter("sl_int", "int", 2));
			parm_.push_back(roc::Parameter("sl_uint64_t", "uint64_t", (uint64_t)2));
			parm_.push_back(roc::Parameter("sl_bool", "bool", true));
			parm_.push_back(roc::Parameter("sl_float", "float", 0.3f));
			parm_.push_back(roc::Parameter("sl_alpha", "double", 0.333));
			parm_.push_back(roc::Parameter("sl_alpha", "chars", "chars2"));
			user_rule_->annex_memory_db[ex][in][tf]->setParam(parm_);
			multi_user_rules.push_back(user_rule_);

			// thread 3
			user_rule_ = new UserRule_sl();
			user_rule_->annex_only = true;
			// Caveat!!   init UserMemoryDB
			user_rule_->annex_memory_db[ex][in][tf] = new AnnexMemDB_sl(ex, in, tf);
			user_rule_->annex_memory_db[ex][in][tf]->init();
			parm_.clear();
			parm_.push_back(roc::Parameter("sl_int", "int", 3));
			parm_.push_back(roc::Parameter("sl_uint64_t", "uint64_t", (uint64_t)3));
			parm_.push_back(roc::Parameter("sl_bool", "bool", true));
			parm_.push_back(roc::Parameter("sl_float", "float", 0.3f));
			parm_.push_back(roc::Parameter("sl_alpha", "double", 0.333));
			parm_.push_back(roc::Parameter("sl_alpha", "chars", "chars2"));
			user_rule_->annex_memory_db[ex][in][tf]->setParam(parm_);
			multi_user_rules.push_back(user_rule_);

		}

		return 0;
	}

}