//#ifndef REQUESTHANDLE_H
//#define REQUESTHANDLE_H
#include<iostream>


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
    int Connect(void(*printback)(std::string),std::string url,bool ishttps = false);
    std::string GetRetMessage(int retnum);


};
//#endif // REQUESTHANDLE_H

