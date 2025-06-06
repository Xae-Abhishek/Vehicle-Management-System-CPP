#include <iostream>
#include "branch.h"
#include <vector>
#include <fstream>

#include "../loggerClasses/logger.h"
#include "../validateInputClasses/validateInput.h"

namespace BranchNameSpace{

LoggerNamespace::LoggerClass* myLogger = LoggerNamespace::LoggerClass::getInstance();
Branch::Branch( std::string branchName, uint16_t branchNumber, int64_t totalRevenueGenerated , uint16_t totalVehicles , uint16_t rentedVehicles , uint16_t freeVehicles , uint64_t totalWorthOfAllVehicles ) : 
        _branchName( branchName ),
        branchNumber( branchNumber ),
        _totalRevenueGenerated( totalRevenueGenerated ),
        _totalVehicles( totalVehicles ),
        _rentedVehicles( rentedVehicles ),
        _freeVehicles( freeVehicles ),
        _totalWorthOfAllVehicles( totalWorthOfAllVehicles ),
        _next( nullptr )
{

}
AddOrDeleteVehicleReturnNamespace::AddOrDeleteVehcileReturn  Branch::addNewVehicle( )
{
    std::string                                                 vehicleNumber;
    std::string                                                 vehicleName;
    uint32_t                                                    vehiclePrice;
    uint32_t                                                    rentPrice;
    AddOrDeleteVehicleReturnNamespace::AddOrDeleteVehcileReturn returnClassObj;

    myLogger->logNoNewLine( "Enter Vehicle Number : " );
    if (  ValidateInputNamespace::takeAndCheckStringInput( vehicleNumber ) ) {
        myLogger->log( "Invalid Input with vehicle number" );
        return returnClassObj;
    }
    myLogger->logEmptyLine();

    myLogger->logNoNewLine( "Enter Vehicle Name : " );
    if (  ValidateInputNamespace::takeAndCheckStringInput( vehicleName ) ) {
        myLogger->log( "Invalid Input" );
        return returnClassObj;
    }
    myLogger->logEmptyLine();

    myLogger->logNoNewLine( "Enter Vehicle price : " );
    if ( ! ValidateInputNamespace::takeAndCheckNumberInput( vehiclePrice ) ) {
        myLogger->log( "Invalid Input" );
        return returnClassObj;
    }
    myLogger->logEmptyLine();

    myLogger->logNoNewLine( "Enter Vehicle Rent Price : " );
    if ( ! ValidateInputNamespace::takeAndCheckNumberInput( rentPrice ) ) {
        myLogger->log( "Invalid Input" );
        return returnClassObj;
    }
    myLogger->logEmptyLine();

    branchVehicles.insertNewVehicleInLinkedList( vehicleNumber, vehicleName, vehiclePrice, rentPrice,/*Revenue Generated*/ 0, /*Is Rented*/false );
    _totalVehicles++;
    _freeVehicles++;
    _totalWorthOfAllVehicles    += vehiclePrice;
    returnClassObj.status        = true;
    returnClassObj.vehiclePrice  = vehiclePrice;

    std::fstream             file( "Data/data.txt" );
    std::vector<std::string> array;
    std::string              s1;
    std::stringstream        ss;

    while (std::getline( file, s1 )) {
        array.push_back( s1 );
    }
    file.close();

    ss<<"BranchNo : "<<branchNumber;
    for ( int i = 0 ; i < array.size() ; i++) {
        if ( array[ i ].find(ss.str()) != std::string::npos ) {
            ss.clear();
            ss.str("");
            ss<<"VehicleNo : "<<vehicleNumber<<" Name : "<<vehicleName<<" Price : "<<vehiclePrice<<" isrented : "<<"false"<<" RentPrice : "<<rentPrice<<" RevenueGenerated : "<<0;
            array.insert(array.begin()+(i+1),ss.str());
            break;
        }
    }
    std::fstream file2( "Data/data.txt", std::ios::trunc | std::ios::out);   
    for( int i = 0 ; i<array.size() ; i++) {
        file2<<array[ i ]<<"\n";
    }
    file2.close();   
    return returnClassObj;
}

AddOrDeleteVehicleReturnNamespace::AddOrDeleteVehcileReturn  Branch::deleteVehicle( )
{
    std::string                                                 vehicleNumber;
    AddOrDeleteVehicleReturnNamespace::AddOrDeleteVehcileReturn returnClassObj;
    myLogger->logNoNewLine( "Enter Vehicle Number : " );
    if (  ValidateInputNamespace::takeAndCheckStringInput( vehicleNumber ) ) {
        myLogger->log( "Invalid Input with vehicle number" );
        return returnClassObj;
    }
    myLogger->logEmptyLine();

    returnClassObj = branchVehicles.delteVehicle(vehicleNumber);

    if ( returnClassObj.status == false ) {
        return returnClassObj;
    }

    _totalVehicles--;

    if ( returnClassObj.isRented == true ) { 
        _rentedVehicles--;
    }
    else {
        _freeVehicles--;
    }

    _totalRevenueGenerated -= returnClassObj.revenueGenerated;
    _totalWorthOfAllVehicles -= returnClassObj.vehiclePrice;

    std::fstream             file ( "Data/data.txt" );
    std::vector<std::string> array;
    std::string              s1;

    while (std::getline( file, s1 )) {
        array.push_back( s1 );
    }
    file.close();

    std::stringstream ss;
    ss<<"VehicleNo  : "<<vehicleNumber;

    for ( int i = 0 ;i < array.size() ; i++) {
        if ( array[ i ].find(ss.str()) != std::string::npos ) {
            array.erase(array.begin()+i);
            break;
        }
    }
    std::fstream file2( "Data/data.txt", std::ios::trunc | std::ios::out);
        
    for( int i = 0 ; i<array.size() ; i++) {
        file2<<array[ i ]<<"\n";
    }
    file2.close(); 

    updateBranchInMemory();
    return returnClassObj;
}

void Branch::updateBranchInMemory()
{
    std::fstream             file ( "Data/data.txt" );
    std::vector<std::string> array;
    std::string              s1;

    while (std::getline( file, s1 )) {
        array.push_back( s1 );
    }
    file.close();

    std::stringstream       ss;
    ss<<"BranchNo : "<<branchNumber;

    for ( int i = 0 ;i < array.size() ; i++) {
        if ( array[ i ].find(ss.str()) != std::string::npos ) {
            ss.clear();
            ss.str("");
            ss<<"BrnachName : "<<_branchName<<" BranchNo : "<<branchNumber<<" RevenueGenerated : "<<_totalRevenueGenerated<<" Vehicle : "<<_totalVehicles<<" Rented : "<<_rentedVehicles<<" Free : "<<_freeVehicles<<" Worth : "<<_totalWorthOfAllVehicles;
            array[ i ] = ss.str();
            break;
        }
    }

    std::fstream file2( "Data/data.txt", std::ios::trunc | std::ios::out);    
    for( int i = 0 ; i<array.size() ; i++) {
        file2<<array[ i ]<<"\n";
    }
    file2.close();
}

void Branch::addVehicleViaFileSystem( std::string vehicleNumber, std::string vehicleName, uint32_t vehiclePrice, uint32_t rentPrice, int32_t revenueGenerated, bool isRented )
{
    branchVehicles.insertNewVehicleInLinkedList( vehicleNumber, vehicleName, vehiclePrice, rentPrice, revenueGenerated, isRented );
}

void Branch::printBranchDetails()
{
    myLogger->log( "Branch name : " ,_branchName );
    myLogger->log( "Branch Numeber : " ,branchNumber );
    myLogger->log( "Branch Toal Revenue Generated : " ,_totalRevenueGenerated );
    myLogger->log( "Branch Total Vehicles : " ,_totalVehicles );
    myLogger->log( "Branch Rented Vehicles : " ,_rentedVehicles );
    myLogger->log( "Branch Free Vehicles : " ,_freeVehicles );
    myLogger->log( "Branch Total Worth Of All Vehicles : " ,_totalWorthOfAllVehicles );   
}

Branch * Branch::getNext()
{
    return _next;
}

void Branch::setNext( Branch* setThis )
{
    _next = setThis;
}

}
