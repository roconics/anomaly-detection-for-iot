/*
 * Copyright 2019, 2020 - , Roconics Co., All Rights Reserved.
 */

#include <string>
#include <vector>
#include <stdarg.h> 
#include <iostream>
#include "user_rule_sl.hpp"

using namespace std;



int  main(int argc, char *argv[])
{

  string input_dir = "./";

  string output_dir =
#ifdef _MSC_BUILD 
	  "../RocEdgeOut/fx_scaling_law/";
#else
	  "../RocEdgeOut/fx_scaling_law/";
#endif

  ursl::UserRule_sl user_rule;

  roc::commonSetup(input_dir, output_dir, &user_rule);


  if (user_rule.userRuleSetup()) {
	  cout << "Something error occured in userRuleSetup." << endl;
  }
  
  string exchanges = "DUKAS";
  string instruments = "EURUSD";
  string timeframes = "MIN1,HOUR1";
  string period = "2007-01-01_2020-01-31";
  roc::UserRuleBase *user_rule_root = &user_rule;
  vector< roc::UserRuleBase * > &user_rule_threads = user_rule.multi_user_rules; 

  string data_input_dir =
#ifdef _MSC_BUILD 
  "../RocEdgeAppsData/tf_data/";
#else
  "../RocEdgeAppsData/tf_data/";
#endif
  PLOGW << "---------" << endl;
  PLOGW << "Simulation started." << endl;

    roc::simulator_main(		  
	    period,
	    user_rule_root, 				// UserRuleBase *
	    data_input_dir
    );

  PLOGW << "Simulation ended." << endl;


  roc::endCommonTerminate();

  return 0;
}