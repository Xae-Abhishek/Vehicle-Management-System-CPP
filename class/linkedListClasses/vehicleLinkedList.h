#ifndef VEHICLE_LINKED_LIST
#define VEHICLE_LINKED_LIST

#include<iostream>

#include "../baseClasses/vehicle.h"
#include "../returnTypeClasses/addOrDeleteVehicleReturn.h"


namespace VehcileLinkedListNamespace
{
class VehicleLinkedList
{
public:
        VehicleLinkedList();

        void insertNewVehicleInLinkedList( std::string vehicleNumber, std::string vehicleName, uint32_t vehiclePrice, uint32_t rentPrice, int32_t revenueGenerated, bool isRented  );       
        AddOrDeleteVehicleReturnNamespace::AddOrDeleteVehcileReturn delteVehicle( std::string vehicleNumber );
        
private:
        VehicleNameSpace::Vehicle* _head;
};
}
#endif