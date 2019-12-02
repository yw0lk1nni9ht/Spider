//#ifndef REQUESTHANDLE_H
//#define REQUESTHANDLE_H
#include<iostream>


class RequestHandle
{
public:
    RequestHandle();
    int Connect(std::string url,bool ishttps = false);
    std::string GetRetMessage(int retnum);
};
//#endif // REQUESTHANDLE_H

