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
#include "downloadhandle.h"
#include "datahandle.h"

using namespace std;
void StartUrl();



/**
 * @brief 回调函数，用于获取Request类请求页面后的Body数据,并且解析
 * @param data      数据
 *
 */
void print_callback(string data){
    response_parse test;
    test.parse(data,1);
    //test.parse(data,2);
}


/**
 * @brief 用于启动
 * @param print_callback      回调
 * @param url               要请求的url
 *
 */
void StartUrl()
{
    RequestHandle t2;
    int ret = t2.Connect(print_callback,"https://www.nvshens.net");
    if (ret != t2.SUCCESS)
    {
        return;
    }
    string hostname = t2.GetHostName();
    if(hostname != "")
    {
        cout << hostname << endl;
    }

    while(true)
    {
        std::string temp = DataHandle::GetDataFromAQueue();
        if (temp == "")
        {
            break;
        }
        else
            t2.Connect(print_callback,hostname+temp);
    }
}


int main()
{

    //DownLoadHandle::DownLoad("https://img.onvshen.com:85/girl/22370/22370_s.jpg");

    std::thread t(StartUrl);
    t.join();
    //获取网站的数据，并通过回调返回
//    while(true)
//    {
//        std::string temp = DataHandle::GetDataFromAQueue();
//        if (temp == "")
//        {
//            break;
//        }
//        else
//            std::cout << temp << std::endl;
//    }
}
