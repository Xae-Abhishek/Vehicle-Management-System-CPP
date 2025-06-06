#ifndef BRANCH
#define BRANCH

#include <iostream>
#include "../linkedListClasses/vehicleLinkedList.h"
#include "../returnTypeClasses/addOrDeleteVehicleReturn.h"

namespace BranchLinkedListNamespace
{
        class BranchLinkedList;
}
namespace BranchNameSpace{

class Branch
{

public:

                                                                    Branch( std::string branchName, uint16_t branchNumber, int64_t toalRevenueGenerated = 0, uint16_t totalVehicles = 0, uint16_t rentedVehicles = 0, uint16_t freeVehicles = 0, uint64_t totalWorthOfAllVehicles = 0 );
        AddOrDeleteVehicleReturnNamespace::AddOrDeleteVehcileReturn addNewVehicle( );
        AddOrDeleteVehicleReturnNamespace::AddOrDeleteVehcileReturn deleteVehicle( );
        void                                                        addVehicleViaFileSystem( std::string vehicleNumber, std::string vehicleName, uint32_t vehiclePrice, uint32_t rentPrice, int32_t revenueGenerated, bool isRented  );
        void                                                        printBranchDetails();
        void                                                        updateBranchInMemory();
        void                                                        setNext( Branch* setThis );
        VehcileLinkedListNamespace::VehicleLinkedList               branchVehicles;
        uint16_t                                                    branchNumber;
        Branch*                                                     getNext( );
private:
        int64_t     _totalRevenueGenerated;
        uint16_t    _totalVehicles;
        uint16_t    _rentedVehicles;
        uint16_t    _freeVehicles;
        uint64_t    _totalWorthOfAllVehicles;
        std::string _branchName;
        Branch*     _next;
};
}
#endif