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
void _test(std::string temp);


void print_callback(string data){
    std::thread t(_test, data);
    t.join();
}
void _test(std::string temp)
{
    response_parse test;
    test.parse(temp);
}
int main()
{
    //获取网站的数据，并通过回调返回
    RequestHandle t2;
    int ret = t2.Connect(print_callback,"www.nvshens.net");
    if (ret == t2.SUCCESS)
    {
    }
}
