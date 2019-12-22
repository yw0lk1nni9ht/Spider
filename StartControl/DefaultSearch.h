#ifndef DEFAULTSEARCH_H
#define DEFAULTSEARCH_H
#include<iostream>

class DefaultSearch
{
public:
    DefaultSearch();
    static void start();
private:
    static void request_callback(std::string data);
    static bool cleandata_callback(std::string data);
};

#endif // DEFAULTSEARCH_H
