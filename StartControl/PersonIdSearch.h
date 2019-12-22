#ifndef PERSONIDSEARCH_H
#define PERSONIDSEARCH_H
#include<iostream>

class PersonIDSearch
{
public:
    PersonIDSearch();
    static void start();
private:
    static void request_callback(std::string data);
    static bool cleandata_callback(std::string data);
};

#endif // PERSONIDSEARCH_H
