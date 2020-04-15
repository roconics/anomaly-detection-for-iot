/*
 * Copyright 2019, 2020 - , Roconics Co., All Rights Reserved.
 */

#include <string>
#include <vector>
#include <stdarg.h> 
#include <iostream>
#include "user_rule.hpp"

using namespace std;

namespace roc {
    extern void bstree_main();
}

int  main(int argc, char* argv[])
{

    string input_dir = "../RocEdgeAppsData/";

    string output_dir =
#ifdef _MSC_BUILD 
        "../RocEdgeOut/rrcf_intro/";
#else
        "../RocEdgeOut/rrcf_intro/";
#endif

    urule::UserRule user_rule;

    roc::commonSetup(input_dir, output_dir, &user_rule);


    if (user_rule.userRuleSetup()) {
        cout << "Something error occured in userRuleSetup." << endl;
        return 0;
    }

    string period = "";
    roc::UserRuleBase* user_rule_root = &user_rule;
    vector< roc::UserRuleBase* >& user_rule_threads = user_rule.multi_user_rules;

    string data_input_dir = "";

    PLOGW << "---------";
    PLOGW << "Simulation started.";

    user_rule.simulator_main(period, data_input_dir);

    PLOGW << "Simulation ended." << endl;


    roc::endCommonTerminate();

    return 0;
}

