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
#include "threadpool.h"
#include "DataFilter/dataclean.h"
#include "DataFilter/bloomfilter.h"

using namespace std;
void StartUrl();
void Downloader();
BloomFilter<std::string> filter(100);

/**
 * @brief 回调函数，用于获取Request类请求页面后的Body数据,并且解析
 * @param data      数据
 *
 */
void print_callback(string data){
    response_parse test;
    if (DataHandle::GetAQueueLength() < 2500)
    {
        test.parse(data,1);
    }
    test.parse(data,2);
}


int cleandata_callback(string data)
{
    if (filter->contains(data))
    {
        return false;
    }
    else {
        filter->insert(data);
        return true;
    }
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
    int ret = t2.Connect(print_callback,"www.nvshens.net");
    if (ret != t2.SUCCESS)
    {
        return;
    }
    string hostname = t2.GetHostName();
    if(hostname != "")
    {
        cout << hostname << endl;
    }

    ThreadPool pool(6);

    // enqueue and store future
    for(int i = 0; i < 10; ++i) {
        auto result = pool.enqueue([i](string hostname) {
            RequestHandle t;
            while(true)
            {
                std::string temp = DataHandle::GetDataFromAQueue();
                if (temp == "")
                {
                    //break;
                }
                else
                {
                    cout << "A:" << hostname + temp << "\t QueueLen:" << DataHandle::GetAQueueLength() << endl;
                    t.Connect(print_callback,hostname+temp);
                }
            }
        },hostname);
    }

//    while(true)
//    {
//        std::string temp = DataHandle::GetDataFromAQueue();
//        if (temp == "")
//        {
//            //break;
//        }
//        else
//        {
//            cout << "A:" << hostname + temp << "\t QueueLen:" << DataHandle::GetAQueueLength() << endl;
//            t2.Connect(print_callback,hostname+temp);
//        }
//        temp.shrink_to_fit();
//    }
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
            //if ( i >= 30)
                //break;
            //else
            //    continue;
        }
        else
        {
            //cout << "IMG:" << temp << endl;
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
    //std::thread t2(Downloader);

    //create thread pool with 4 worker threads
    ThreadPool pool(3);

    // enqueue and store future
    for(int i = 0; i < 3; ++i) {
        auto result = pool.enqueue([i] {
            while(true)
            {
                std::string temp = DataHandle::GetDataFromIMGQueue();
                if(temp != "")
                {
                    //cout << "IMG:" << temp << endl;
                    DownLoadHandle::DownLoad(temp);
                }
                else{
                    //cout << "IMG:   NULL"   << endl;
                }
                temp.shrink_to_fit();
            }
        });
    }

    t.join();
    //t2.join();

}
