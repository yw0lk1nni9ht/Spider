#ifndef DATAHANDLE_H
#define DATAHANDLE_H
#include <queue>
#include <iostream>
#include <boost/thread/mutex.hpp>
#include <list>

class DataHandle
{
public:
    DataHandle();
    static void AddDataToAQueue(std::string href);
    static void AddDataToIMGQueue(std::string img);
    static std::string GetDataFromAQueue();
    static std::string GetDataFromIMGQueue();
    static int GetAQueueLength();
private:
    static void AddDataToQueue(std::string data,int id);
    static std::list<std::string*> A_QUEUE;
    static std::list<std::string> IMG_QUEUE;
};

#endif // DATAHANDLE_H
