#include <iostream>

#include "../baseClasses/branch.h"


namespace BranchLinkedListNamespace 
{
    class BranchLinkedList
    {

    public:
                                 BranchLinkedList();
        void                     insertNewBranch( std::string branchName, uint16_t branchNumber, int64_t toalRevenueGenerated = 0, uint16_t totalVehicles = 0, uint16_t rentedVehicles = 0, uint16_t freeVehicles = 0, uint64_t totalWorthOfAllVehicles = 0 );
        BranchNameSpace::Branch* gethead();
    private:
        BranchNameSpace::Branch* _head;
    };
}