#include<iostream>
#include <cstdint>

#include "class/loggerClasses/logger.h"
#include "class/baseClasses/company.h"
#include "class/validateInputClasses/validateInput.h"


int main()
{
    CompanyNamespace::Company*    myCompany = CompanyNamespace::Company::getInstance();
    LoggerNamespace::LoggerClass* myLogger = LoggerNamespace::LoggerClass::getInstance();
    uint16_t                      choice;
    
    while ( true ) {        
        myLogger->log( "Enter 1 to insert a branch in Company" );
        myLogger->log( "Enter 2 to print detils of the company" );
        myLogger->log( "Enter 3 to print details of a branch" );
        myLogger->log( "Enter 4 to enter vehicles in a branch" );
        myLogger->log( "Enter 5 to delete a vehicle in a branch" );
        myLogger->log( "Enter 6 to free a Vehicle in a branch" );
        myLogger->log( "Enter 7 to free a rent in a branch");
        myLogger->log( "Enter 10 to exit" );
        myLogger->logNoNewLine( "Choice : " );

        if ( ! ValidateInputNamespace::takeAndCheckNumberInput( choice ) ) {
            myLogger->logEmptyLine();
            myLogger->log( "***Invalid Input Type****" );
        }
        myLogger->logEmptyLine();
        myLogger->logEmptyLine();
        switch ( choice ){
            case 1:
                myCompany->addBranchInput();
                break;
            case 2:
                myCompany->printdetailsOfBranch();
                break;
            case 3:
                myCompany->printdetailsOfBranch();
                break;
            case 4:
                myCompany->addVehicle();
                break;
            case 5:
                myCompany->deleteVehicle();
                break;
            case 10:
                myLogger->log( "EXIT" );
                break;
            default:
                myLogger->log( "Invalid Choice, choose frome given choices only ! " );
                break;       
        }
        if ( choice == 10 ) {
            myLogger->log( "Closing the program" );
            return 0;
        }
        myLogger->log( "Press Enter to continue..." );
        std::cin.ignore();   
    }
}