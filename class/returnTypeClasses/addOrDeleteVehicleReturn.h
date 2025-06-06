#ifndef ADD_OR_DELETE_VEHICLE_RETURN_TYPE
#define ADD_OR_DELETE_VEHICLE_RETURN_TYPE

#include<iostream>
namespace AddOrDeleteVehicleReturnNamespace
{
    class AddOrDeleteVehcileReturn
    {
        // This is only a return type there won't be any important obj of this class so the vars are set public
        public:
            bool     status;
            bool     isRented;
            uint32_t vehiclePrice;
            int32_t  revenueGenerated;
        AddOrDeleteVehcileReturn():
            status( false ),
            isRented( false ),
            vehiclePrice( 0 ),
            revenueGenerated( 0 )
            {
                
            }
    };
}

#endif