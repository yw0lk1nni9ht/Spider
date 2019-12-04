#ifndef DATAHANDLE_H
#define DATAHANDLE_H
#include <queue>
#include <iostream>
#include <boost/thread/mutex.hpp>

class DataHandle
{
public:
    DataHandle();
    static void AddDataToAQueue(std::string href);
    static void AddDataToIMGQueue(std::string img);
    static std::string GetDataFromAQueue();
    static std::string GetDataFromIMGQueue();
private:
    static void AddDataToQueue(std::string data,int id);

};

#endif // DATAHANDLE_H
