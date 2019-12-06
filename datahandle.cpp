#include "datahandle.h"

DataHandle::DataHandle()
{

}

static boost::mutex AQ_push_mutex;
static boost::mutex AQ_pop_mutex;

static boost::mutex IMGQ_push_mutex;
static boost::mutex IMGQ_pop_mutex;
static std::queue<std::string> A_QUEUE;
static std::queue<std::string> IMG_QUEUE;

int DataHandle::GetAQueueLength()
{
    return A_QUEUE.size();
}
std::string DataHandle::GetDataFromAQueue(){
    std::string ret = "";
    AQ_pop_mutex.lock();
    if(!A_QUEUE.empty())
    {
        ret = A_QUEUE.front();
        A_QUEUE.pop();
    }
    AQ_pop_mutex.unlock();
    return ret;
}

std::string DataHandle::GetDataFromIMGQueue(){
    std::string ret = "";
    IMGQ_pop_mutex.lock();
    if(!IMG_QUEUE.empty())
    {        
        ret = IMG_QUEUE.front();
        IMG_QUEUE.pop();
    }
    IMGQ_pop_mutex.unlock();
    return ret;
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
        AQ_push_mutex.lock();
        //add to Aqueue
        A_QUEUE.push(data);
        AQ_push_mutex.unlock();
    }
    else if (id == 2){
        IMGQ_push_mutex.lock();
        //add to IMGqueue
        IMG_QUEUE.push(data);
        IMGQ_push_mutex.unlock();
    }
}
