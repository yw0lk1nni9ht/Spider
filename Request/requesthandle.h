//#ifndef REQUESTHANDLE_H
//#define REQUESTHANDLE_H
#include<iostream>


class RequestHandle
{
public:
    RequestHandle();
    int Connect(std::string url);
    std::string GetRetMessage(int retnum);
    std::string GetRetData();

};
//#endif // REQUESTHANDLE_H

