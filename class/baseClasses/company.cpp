#include<iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

#include "company.h"
#include "../loggerClasses/logger.h"
#include "../validateInputClasses/validateInput.h"


namespace CompanyNamespace{
    LoggerNamespace::LoggerClass* myLogger = LoggerNamespace::LoggerClass::getInstance();
    Company* Company::            _instance = nullptr;

    Company::Company( std::string companyName, uint16_t totalBranch, uint64_t totalVehicleAcrossAllBranch, uint64_t totalWorthOfAllVehiclesAcrossAllBranch, int64_t totalRevenueAcrossAllBranches ) : 
            _companyName( companyName ),
            _totalBranch( totalBranch ),
            _totalVehicleAcrossAllBranch( totalVehicleAcrossAllBranch ),
            _totalWorthOfAllVehiclesAcrossAllBranch( totalWorthOfAllVehiclesAcrossAllBranch ),
            _totalRevenueAcrossAllBranches( totalRevenueAcrossAllBranches )
    {
        loadDataFromFileSystem();
    }
    Company* Company::getInstance()
    {
        if ( _instance == nullptr) {
            _instance = new Company( "LIVE U" );
        }
        return _instance;
    }
    void Company::updateCompanyInFile()
    {
        std::fstream              file ( "Data/data.txt" );
        std::vector <std::string> array;
        std::string               s1;
        std::stringstream         temp;

        while ( std::getline( file, s1 ) ) {
            array.push_back( s1 );
        }
        file.close();

        temp <<"Branch : "<<_totalBranch<<"   Vehicle : "<<_totalVehicleAcrossAllBranch<<"   Worth : "<<_totalWorthOfAllVehiclesAcrossAllBranch<<"   Revenue : "<<_totalRevenueAcrossAllBranches;

        std::fstream file2( "Data/data.txt",std::ios::out | std::ios::trunc );
        array[ 0 ] = temp.str();

        for ( int i = 0 ; i < array.size(); i++ ) {
            file2<<array[ i ]<<"\n";
        }
        file2.close();
    }

    void Company::addBranch( std::string branchName, uint16_t branchNumber, int64_t totalRevenueGenerated , uint16_t totalVehicles , uint16_t rentedVehicles , uint16_t freeVehicles , uint64_t totalWorthOfAllVehicles  )
    {
        _totalBranch += 1;
        _companyBranches.insertNewBranch( branchName, branchNumber, totalRevenueGenerated, totalVehicles, rentedVehicles, freeVehicles, totalWorthOfAllVehicles );
        updateCompanyInFile();
    }

    void Company::printdetailsOfCompany()
    {
        myLogger->log( "Company Name : ", _companyName );
        myLogger->log( "Total Branch : ", _totalBranch );
        myLogger->log( "Total Number Of Vehicle Across All Branch  : ", _totalVehicleAcrossAllBranch );
        myLogger->log( "Total Worth Of All Vehicle : ", _totalWorthOfAllVehiclesAcrossAllBranch );
        myLogger->log( "Total Revenue Across All Branches : ", _totalRevenueAcrossAllBranches );
    }

    void Company::addBranchInput()
    {
        std::string branchName;
        uint16_t    branchNumber; 

        myLogger->logNoNewLine( "Enter Branch Name : " );
        if ( ValidateInputNamespace::takeAndCheckStringInput( branchName ) ) {
            myLogger->log( "***Invalid Input Type***" );
            return;
        }
        myLogger->logNoNewLine( "Enter Branch Number : " );

        if ( ! ValidateInputNamespace::takeAndCheckNumberInput( branchNumber ) ) {
            std::cin.clear();
            myLogger->log( "***Invalid Input Type***" );
            return;
        }
        if ( checkBranchNumber( branchNumber ) ) {
            myLogger->log( "***Sorry Branch Number already exists ***" );
            return;
        }
        addBranch( branchName, branchNumber, /* totalRevenueGenerated = */ 0, /* totalVehicles */ 0, /* rentedVehicles */ 0, /* freeVehicles */ 0, /* totalWorthOfAllVehicles */ 0 );
    }

    void Company::printdetailsOfBranch()
    {
        myLogger->logNoNewLine( "\nEnter Branch Number : " );
        uint16_t searchBranchNumber;
        if ( ! ( ValidateInputNamespace::takeAndCheckNumberInput( searchBranchNumber ) ) ) {
            myLogger->log( "Invalid Input" );
            return;
        }
        BranchNameSpace::Branch *temp;

        if ( checkBranchNumber( searchBranchNumber , &temp ) ) {
            temp->printBranchDetails();
        }
        else {
            myLogger->log( "Invalid Branch Number" );
            return;
        }
    }

    void Company::addVehicle()
    {
        uint16_t tempBranchNumber;
        myLogger->logNoNewLine( "Enter Branch Number : " );

        if ( ! ValidateInputNamespace::takeAndCheckNumberInput( tempBranchNumber ) ) {
            myLogger->log("Invalid Input ");
        }
        myLogger->logEmptyLine();

        BranchNameSpace::Branch * currentBranch;

        if ( ! Company::checkBranchNumber( tempBranchNumber, &currentBranch ) ) {
            myLogger->log( "Invalid Branch Number" );
            return;
        }
        AddOrDeleteVehicleReturnNamespace::AddOrDeleteVehcileReturn returnType1 = currentBranch->addNewVehicle();
        if ( ! returnType1.status ) {
            myLogger->log( "Operation Failed ! " );
            return ;
        }   
        _totalVehicleAcrossAllBranch            += 1;
        _totalWorthOfAllVehiclesAcrossAllBranch += returnType1.vehiclePrice;
        updateCompanyInFile();
    }

    void Company::deleteVehicle()
    {
        uint16_t tempBranchNumber;
        myLogger->logNoNewLine( "Enter Branch Number : " );

        if ( ! ValidateInputNamespace::takeAndCheckNumberInput( tempBranchNumber ) ) {
            myLogger->log( "Invalid Input " );
        }
        myLogger->logEmptyLine();

        BranchNameSpace::Branch * currentBranch;

        if ( ! Company::checkBranchNumber( tempBranchNumber, &currentBranch ) ) {
            myLogger->log( "Invalid Branch Number" );
            return;
        }

        AddOrDeleteVehicleReturnNamespace::AddOrDeleteVehcileReturn returnType1 = currentBranch->deleteVehicle();
        if ( ! returnType1.status ) {
            myLogger->log( "Operation Failed ! " );
            return ;
        }   

        _totalVehicleAcrossAllBranch            -= 1;
        _totalWorthOfAllVehiclesAcrossAllBranch -= returnType1.vehiclePrice;
        _totalRevenueAcrossAllBranches          -= returnType1.revenueGenerated;
        updateCompanyInFile();
    }
    void Company::loadDataFromFileSystem()
    {
        std::string  line;
        std::string  label;

        std::fstream file( "Data/data.txt" );
        std::getline( file, line );
        std::replace(line.begin(), line.end(), ':', ' ');

        std::stringstream ss( line );
        ss>>label>>_totalBranch>>label>>_totalVehicleAcrossAllBranch>>label>>_totalWorthOfAllVehiclesAcrossAllBranch>>label>>_totalRevenueAcrossAllBranches;

        for ( int i = 0; i <_totalBranch ; i++){
            std::getline( file, line );
            std::replace( line.begin(), line.end(), ':', ' ' );
            ss.clear();
            ss.str("");
            ss.str( line );

            std::string branchName;
            uint16_t    branchNumber;
            int64_t     totalRevenueGenerated;
            uint16_t    totalVehicles;
            uint16_t    rentedVehicles; 
            uint16_t    freeVehicles;
            uint64_t    totalWorthOfAllVehicles;

            ss>>label>>branchName>>label>>branchNumber>>label>>totalRevenueGenerated>>label>>totalVehicles>>label>>rentedVehicles>>label>>freeVehicles>>label>>totalWorthOfAllVehicles;

            _companyBranches.insertNewBranch( branchName, branchNumber, totalRevenueGenerated, totalVehicles, rentedVehicles, freeVehicles, totalWorthOfAllVehicles );

            for ( int j = 0 ; j < totalVehicles ; j++ ){
                std::getline( file, line );
                std::replace( line.begin(), line.end(), ':', ' ');

                ss.clear();
                ss.str( "" );
                ss.str( line );

                std::string              vehicleNumber;
                std::string              vehicleName;
                uint32_t                 vehiclePrice;
                std::string              isRentedstr;
                bool                     isRented = false;
                uint32_t                 rentPrice;
                int32_t                  revenueGenerated;
                BranchNameSpace::Branch* thisBranch;

                ss>>label>>vehicleNumber>>label>>vehicleName>>label>>vehiclePrice>>label>>isRentedstr>>label>>rentPrice>>label>>revenueGenerated;

                if ( isRentedstr == "true" ) { 
                    isRented = true;
                }
                Company::checkBranchNumber( branchNumber, &thisBranch );
                thisBranch->addVehicleViaFileSystem( vehicleNumber, vehicleName, vehiclePrice, rentPrice, revenueGenerated, isRented );
            }
        }
        file.close();
    }

    bool Company::checkBranchNumber(uint16_t checkNumber, BranchNameSpace::Branch ** ptrAddress )
    {
        BranchNameSpace::Branch *temp = this->_companyBranches.gethead();
        while ( temp != nullptr ) {
            if ( temp->branchNumber == checkNumber ) { 
                if ( ptrAddress != nullptr ) {
                    *ptrAddress = temp;
                }
                return true;
            }
            else {
                temp = temp->getNext();
            }
        }
        return false;
    }
}