//#ifndef REQUESTHANDLE_H
//#define REQUESTHANDLE_H
#include<iostream>
#include"request.h"

class RequestHandle
{
public:
    enum ReturnNum {
        SUCCESS                 = 0x000,
        URL_ERROR               = 0x001,
        URL_ConnectFail         = 0x002,
        URL_301_302             = 0x003,
    };
    RequestHandle();
    int Connect(void(*printback)(std::string),std::string url,bool ishttps = false,bool isReConnect = false);
    std::string GetRetMessage(int retnum);
    std::string GetHostName();
private:
    std::string _hostname;
    BaseRequest * request = NULL;


};
//#endif // REQUESTHANDLE_H

