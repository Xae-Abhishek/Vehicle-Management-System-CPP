#ifndef VEHICLE
#define VEHICLE

#include<iostream>
#include<cstdint>

namespace VehicleNameSpace{
class Vehicle
{
public:
                    Vehicle( std::string vehicleNumber, std::string vehicleName, uint32_t vehiclePrice, uint32_t rentPrice, int32_t revenueGenerated = 0, bool isRented = false );
                    Vehicle();
        Vehicle *   getNext();
        void        setNext( Vehicle * );
        std::string getVehcileNumber();
        bool        getIsRented();
        int32_t     getRevenueGenerated();
        uint32_t    getVehiclePrice();
private:      
        std::string _vehicleName;
        std::string _vehicleNumber;
        uint32_t    _vehiclePrice;
        int32_t     _revenueGenerated;
        uint32_t    _rentPrice;
        bool        _isRented = false;
        Vehicle *   _next;
};
}
#endif