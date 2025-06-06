#include <iostream>


#include "vehicleLinkedList.h"
#include "../returnTypeClasses/addOrDeleteVehicleReturn.h"

namespace VehcileLinkedListNamespace
{
    VehicleLinkedList::VehicleLinkedList() : 
        _head ( nullptr )
    {

    }

    void VehcileLinkedListNamespace::VehicleLinkedList::insertNewVehicleInLinkedList( std::string vehicleNumber, std::string vehicleName, uint32_t vehiclePrice, uint32_t rentPrice, int32_t revenueGenerated, bool isRented  )
    {
        VehicleNameSpace::Vehicle* newNode = new VehicleNameSpace::Vehicle( vehicleNumber, vehicleName, vehiclePrice, rentPrice, revenueGenerated , isRented );

        if ( _head == nullptr ) { 
            _head = newNode;
        }
        else {
            VehicleNameSpace::Vehicle* temp = _head;
            while ( temp->getNext() != nullptr ) {
                temp = temp->getNext();
            }
            temp->setNext( newNode );
        }
    }

    AddOrDeleteVehicleReturnNamespace::AddOrDeleteVehcileReturn VehicleLinkedList::delteVehicle( std::string vehicleNumber )
    {
        AddOrDeleteVehicleReturnNamespace::AddOrDeleteVehcileReturn r1;

        if ( _head->getVehcileNumber() == vehicleNumber ) {
            r1.status = true;
            r1.isRented = _head->getIsRented();
            r1.revenueGenerated = _head->getRevenueGenerated();
            r1.vehiclePrice = _head->getVehiclePrice();
            _head = _head->getNext();
            return r1;
        }
        VehicleNameSpace::Vehicle * temp = _head;
        VehicleNameSpace::Vehicle * prev = new VehicleNameSpace::Vehicle();
        prev->setNext( _head );

        while ( temp != nullptr ) {
            if ( temp->getVehcileNumber() == vehicleNumber) {
                r1.status = true;
                r1.isRented = temp->getIsRented();
                r1.revenueGenerated = temp->getRevenueGenerated();
                r1.vehiclePrice = temp->getVehiclePrice();
                prev->setNext( temp->getNext() );
                return r1;
            }
            temp = temp->getNext();
            prev = prev->getNext();
        }
        return r1;
    }
}