/*
 * Copyright 2019,2020-, Roconics Co., All Rights Reserved.
 */

#pragma once
#include <string>
#include <vector>
#include <memory>

using namespace std;

//External Namespaces

namespace roc
{
    //Forward Declarations
   struct TfInfoIF;
 
   class UserRuleBase
    {
        public:
            //Friends
            
            //Definitions
            
            //Constructor
            UserRuleBase( void ) = default;
            
            virtual ~UserRuleBase( void ) = default;
           
            //Functionality from roc_edge
			virtual int userRuleMemoryDbInit() = 0;   // init UserMemoryDB, and initialize indicators of UMemDB

		    virtual void onTick( TfInfoIF *tf_i) = 0;

		    virtual void onBar( TfInfoIF *tf_i) = 0;

		    virtual void onBarClose( TfInfoIF *tf_i) = 0;

			virtual void onBarCloseAnnex(TfInfoIF* tf_i) = 0;

			virtual bool getData(string& msg, string& data) = 0;  // event from rest servce

			virtual void endOfSimulatorRun() = 0;

			//Properties set by roc_edge
			bool annex_only;

			//Properties set by the user
			bool simulation;  // simulation if ture, real-time if false

			// active's
			vector<int> exs;
			vector<int> ins;
			vector<int> tfs;

			vector<UserRuleBase*>  multi_user_rules;  // multi-threaded user_rules for optimization


            //Getters
            //virtual const std::type_info& type( void ) const = 0;
            
            //Setters
            
            //Operators
            
    


	/* load data
		data types
		sensor pumps for each instrument
		block data
		series by series
		the shortest timeframe for each instrument
		data compress     yes/no
	*/


        private:
            
            //Constructors
            UserRuleBase( const UserRuleBase& original ) = delete;
                      
            //Operators
            UserRuleBase& operator =( const UserRuleBase& value ) = delete;
            
    };

}