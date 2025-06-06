#include <iostream>

#include "branchLinkedList.h"


namespace BranchLinkedListNamespace  
{
    BranchLinkedList::BranchLinkedList() : 
        _head( nullptr )
    {

    }

    void BranchLinkedList::insertNewBranch( std::string branchName, uint16_t branchNumber, int64_t toalRevenueGenerated, uint16_t totalVehicles, uint16_t rentedVehicles, uint16_t freeVehicles, uint64_t totalWorthOfAllVehicles)
    {
        BranchNameSpace::Branch* Newnode = new BranchNameSpace::Branch( branchName, branchNumber, toalRevenueGenerated, totalVehicles, rentedVehicles, freeVehicles, totalWorthOfAllVehicles );
        if ( _head == nullptr ){
            _head = Newnode;
        }
        else {
            
            BranchNameSpace::Branch* temp = _head;
            while ( temp->getNext() != nullptr ) {
                temp = temp->getNext();
            }
            temp->setNext( Newnode );
        }
    }
    BranchNameSpace::Branch* BranchLinkedList::gethead()
    {
        return _head;
    }
}