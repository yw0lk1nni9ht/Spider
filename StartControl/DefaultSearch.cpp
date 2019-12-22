#include "DefaultSearch.h"
#include "requesthandle.h"
#include "response_parse.h"
#include "downloadhandle.h"
#include "datahandle.h"
#include "threadpool.h"
#include "DataFilter/dataclean.h"
#include "DataFilter/bloomfilter.h"

BloomFilter filter;

DefaultSearch::DefaultSearch()
{

}

/**
 * @brief 回调函数，用于获取Request类请求页面后的Body数据,并且解析
 * @param data      数据
 *
 */
void DefaultSearch::request_callback(std::string data){
    response_parse test;
    test.parse(data,1,cleandata_callback);
    test.parse(data,2,cleandata_callback);
}

bool DefaultSearch::cleandata_callback(std::string data)
{
    if (filter.Test(data))
    {
        return true;
    }
    else {
        filter.Add(data);
        return false;
    }
}

/**
 * @brief 用于启动
 * @param print_callback      回调
 * @param url               要请求的url
 *
 */
void DefaultSearch::start()
{

    RequestHandle t2;https:
    //int ret = t2.Connect(request_callback,"www.nvshens.net/g/31660");
    int ret = t2.Connect(request_callback,"www.nvshens.net/girl/15877/");
    if (ret != t2.SUCCESS)
    {
        return;
    }
    std::string hostname = t2.GetHostName();
    if(hostname != "")
    {
        std::cout << hostname << std::endl;
    }

    ThreadPool pool(40);

    // enqueue and store future
    for(int i = 0; i < 60; ++i) {
        auto result = pool.enqueue([i]( std::string hostname) {
            RequestHandle t;
            while(true)
            {
                std::string temp = DataHandle::GetDataFromAQueue();
                if (temp != "")
                {
                    //cout << "A:" << hostname + temp << "\t AQueueLen:" << DataHandle::GetAQueueLength() << endl;
                    int _ret = t.Connect(request_callback,hostname+temp);
                    if (_ret != 0)
                    {
                        std::cout << "返回值：" << _ret << "\t" << hostname+temp << std::endl;
                    }
                }
            }
        },hostname);
    }


    //create thread pool with 4 worker threads
    ThreadPool pool2(100);

    // enqueue and store future
    for(int i = 0; i < 150; ++i) {
        auto result = pool2.enqueue([i] {
            while(true)
            {
                std::string temp = DataHandle::GetDataFromIMGQueue();
                if(temp != "")
                {
                    std::cout << "IMG:" << temp << "\t IMGQueueLen:" << DataHandle::GetIMGQueueLength() <<  std::endl;
                    DownLoadHandle::DownLoad(temp);
                }
            }
        });
    }
}

