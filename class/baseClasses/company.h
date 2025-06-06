#ifndef COMPANY
#define COMPANY

#include<iostream>
#include<cstdint>

#include "branch.h"
#include "../linkedListClasses/branchLinkedList.h"
#include "../returnTypeClasses/addOrDeleteVehicleReturn.h"


namespace CompanyNamespace{
class Company
{
public:    
    void            addBranch( std::string branchName, uint16_t branchNumber, int64_t totalRevenueGenerated = 0, uint16_t totalVehicles = 0, uint16_t rentedVehicles = 0, uint16_t freeVehicles = 0, uint64_t totalWorthOfAllVehicles = 0 );
    void            addBranchInput();
    void            printdetailsOfCompany();
    void            printdetailsOfBranch();
    bool            checkBranchNumber( uint16_t checkNumber, BranchNameSpace::Branch** ptrAddress = nullptr );
    void            addVehicle();
    void            updateCompanyInFile();
    void            deleteVehicle();
    static Company* getInstance();
    Company ( const Company & ) = delete;
    Company & operator=( const Company & ) = delete;
private:
    static Company*                             _instance;
    std::string                                 _companyName;
    uint16_t                                    _totalBranch;
    uint64_t                                    _totalVehicleAcrossAllBranch;
    uint64_t                                    _totalWorthOfAllVehiclesAcrossAllBranch;
    int64_t                                     _totalRevenueAcrossAllBranches; 
    BranchLinkedListNamespace::BranchLinkedList _companyBranches;

    Company( std::string companyName, uint16_t totalBranch = 0, uint64_t totalVehicleAcrossAllBranch = 0, uint64_t totalWorthOfAllVehiclesAcrossAllBranch = 0, int64_t totalRevenueAcrossAllBranches = 0 );
    void loadDataFromFileSystem();
};
}
#endif