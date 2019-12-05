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
void Downloader();



/**
 * @brief 回调函数，用于获取Request类请求页面后的Body数据,并且解析
 * @param data      数据
 *
 */
void print_callback(string data){
    response_parse test;
    if (DataHandle::GetAQueueLength() < 25000)
    {
        test.parse(data,1);
    }
    test.parse(data,2);
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
    int ret = t2.Connect(print_callback,"www.4399.com");
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
        {
            cout << "A:" << hostname + temp << "\t QueueLen:" << DataHandle::GetAQueueLength() << endl;
            t2.Connect(print_callback,hostname+temp);
        }
    }
}



//下载器
void Downloader()
{
    int i = 0;
    while(true)
    {
        std::string temp = DataHandle::GetDataFromIMGQueue();
        if (temp == "")
        {
            sleep(1);
            i++;
            if ( i >= 30)
                break;
            else
                continue;
        }
        else
        {
            cout << "IMG:" << temp << endl;
            DownLoadHandle::DownLoad(temp);
        }
    }
}


// TODO 请求，SSL连接不断
// TODO 去重
// TODO 线程池

int main()
{

    //DownLoadHandle::DownLoad("https://img.onvshen.com:85/girl/22370/22370_s.jpg");

    std::thread t(StartUrl);
    std::thread t2(Downloader);
    t.join();
    t2.join();
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
