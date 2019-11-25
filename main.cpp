#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <string>
#include<thread>
#include "http_request.h"
#include "https_request.h"
#include "response_parse.h"
#include "requesthandle.h"

using namespace std;


void _test(std::string temp)
{
    response_parse test;
    test.parse(temp);
}
int main()
{


    //https_request test2;
    //string response =  test2.GetRequest("nvshens.net","/") ;
    //string a = response.body();
    //std::cout << response.body() << std::endl;

    RequestHandle t2;
    int ret = t2.Connect("www.nvshens.net");
    std::cout << t2.GetRetMessage(ret) << std::endl;

//    std::thread t(_test, response);
//    t.join();

}
