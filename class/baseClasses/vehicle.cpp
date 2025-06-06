#include<iostream>
#include <cstdint>

#include "vehicle.h"


namespace VehicleNameSpace{

Vehicle::Vehicle( std::string vehicleNumber, std::string vehicleName, uint32_t vehiclePrice,  uint32_t rentPrice, int32_t revenueGenerated , bool isRented ) : 
    _vehicleNumber( vehicleNumber ),
    _vehicleName( vehicleName ),
    _vehiclePrice( vehiclePrice ),
    _rentPrice( rentPrice ),
    _revenueGenerated( revenueGenerated ),
    _isRented( isRented ),
    _next( nullptr )
{

};
Vehicle::Vehicle() :
    _next( nullptr )
{

}

Vehicle* Vehicle::getNext()
{
    return _next;        
}

void Vehicle::setNext( Vehicle* setThis )
{
    _next = setThis;
}

std::string Vehicle::getVehcileNumber()
{
    return _vehicleNumber;
}
bool Vehicle :: getIsRented()
{
    return _isRented;

}
int32_t Vehicle::getRevenueGenerated()
{
    return _revenueGenerated;
}
uint32_t Vehicle::getVehiclePrice()
{   
    return _vehiclePrice;
}   

}
