#ifndef LOGGER
#define LOGGER

#include <iostream>
#include<ctime>

namespace LoggerNamespace
{
    class LoggerClass
    {
    public:
        template<typename... arr>
        void log(arr... parameter)
        {
            std::time_t nowTime = std::time(nullptr);
            std::string myTimeString = std::ctime(&nowTime);
            myTimeString.pop_back();
            std::cout<< "Time : "<<myTimeString<<"\t -- VMS : ";
            ( ( std::cout<<parameter<<" " ), ... );
            std::cout<<std::endl;
        }

        template<typename... arr>
        void logNoNewLine(arr... parameter)
        {
            std::time_t nowTime = std::time(nullptr);
            std::string myTimeString = std::ctime(&nowTime);
            myTimeString.pop_back();
            std::cout<< "Time : "<<myTimeString<<"\t -- VMS : ";
            ( ( std::cout<<parameter<<" " ), ... );
        }

        void logEmptyLine()
        {
            std::time_t nowTime = std::time(nullptr);
            std::string myTimeString = std::ctime(&nowTime);
            myTimeString.pop_back();
            std::cout<< "Time : "<<myTimeString<<"\t -- VMS : "<<std::endl;
        }

        static LoggerClass* getInstance()
        {   
            if( instance == nullptr )
            {
                instance = new LoggerClass();
            }
            return instance;
        }
        LoggerClass& operator=( const LoggerClass& ) = delete;
        LoggerClass( const LoggerClass&  ) = delete;

    private:
            LoggerClass()
            {

            }
        static LoggerClass* instance;
    };
inline LoggerClass* LoggerClass::instance = nullptr;
}
#endif