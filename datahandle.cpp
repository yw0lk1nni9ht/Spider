#include "datahandle.h"

DataHandle::DataHandle()
{

}

static boost::mutex push_mutex;
static boost::mutex pop_mutex;
static std::queue<std::string> A_QUEUE;
static std::queue<std::string> IMG_QUEUE;

int DataHandle::GetAQueueLength()
{
    return A_QUEUE.size();
}
std::string DataHandle::GetDataFromAQueue(){
    if(!A_QUEUE.empty())
    {
        pop_mutex.lock();
        std::string ret = A_QUEUE.front();
        A_QUEUE.pop();
        pop_mutex.unlock();
        return ret;
    }
    else {
        return "";
    }
}

std::string DataHandle::GetDataFromIMGQueue(){
    if(!IMG_QUEUE.empty())
    {
        pop_mutex.lock();
        std::string ret = IMG_QUEUE.front();
        IMG_QUEUE.pop();
        pop_mutex.unlock();
        return ret;
    }
    else {
        return "";
    }
}

void DataHandle::AddDataToAQueue(std::string href){
    AddDataToQueue(href,1);
}

void DataHandle::AddDataToIMGQueue(std::string img){
    AddDataToQueue(img,2);
}

void DataHandle::AddDataToQueue(std::string data, int id)
{
    if (id == 1)
    {
        push_mutex.lock();
        //add to Aqueue
        A_QUEUE.push(data);
        push_mutex.unlock();
    }
    else if (id == 2){
        push_mutex.lock();
        //add to IMGqueue
        IMG_QUEUE.push(data);
        push_mutex.unlock();
    }
}
