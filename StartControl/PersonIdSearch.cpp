#include "PersonIdSearch.h"
#include "requesthandle.h"
#include "response_parse.h"
#include "downloadhandle.h"
#include "datahandle.h"
#include "threadpool.h"
#include "DataFilter/dataclean.h"
#include "DataFilter/bloomfilter.h"


BloomFilter filter_personid;

PersonIDSearch::PersonIDSearch()
{

}

/**
 * @brief 回调函数，用于获取Request类请求页面后的Body数据,并且解析
 * @param data      数据
 *
 */
void PersonIDSearch::request_callback(std::string data){
    std::cout << data << std::endl;
    response_parse test;
    test.parse(data,1,cleandata_callback);
    test.parse(data,2,cleandata_callback);
}

bool PersonIDSearch::cleandata_callback(std::string data)
{
    if (data.substr(0,3) == "/g/")
    {
        if (filter_personid.Test(data))
        {
            return true;
        }
        else {
            filter_personid.Add(data);
            return false;
        }
    }
}

/**
 * @brief 用于启动
 * @param print_callback      回调
 * @param url               要请求的url
 *
 */
void PersonIDSearch::start()
{
//c++ V8
//Post https://www.nvshens.net/ajax/girl_query_handler.ashx name=飞儿 搜索人物
//Post https://www.nvshens.net/ajax/score_get_handler.ashx id=15877  获取分数
//
    std::string searchid = "";
    std::cout << "搜索的姓名:" ;
    std::cin >> searchid;
    RequestHandle t2;
    //int ret = t2.Connect(request_callback,"https://www.nvshens.net/ajax/girl_query_handler.ashx?name="+searchid);
    int ret = t2.Connect(request_callback,"https://www.nvshens.net/girl/15877/album/");
    if (ret != t2.SUCCESS)
    {
        return;
    }
    std::string hostname = t2.GetHostName();
    if(hostname != "")
    {
        std::cout << hostname << std::endl;
    }

    ThreadPool pool(1);

    // enqueue and store future
    for(int i = 0; i < 1; ++i) {
        auto result = pool.enqueue([i]( std::string hostname) {
            RequestHandle t;
            while(true)
            {
                std::string temp = DataHandle::GetDataFromAQueue();
                if (temp != "")
                {
                    std::cout << "A:" << hostname + temp << "\t AQueueLen:" << DataHandle::GetAQueueLength() << std::endl;
                    int _ret = t.Connect(request_callback,hostname+temp);
                    if (_ret != 0)
                    {
                        std::cout << "返回值：" << _ret << "\t" << hostname+temp << std::endl;
                    }
                }
            }
        },hostname);
    }


//    //create thread pool with 4 worker threads
//    ThreadPool pool2(1);

//    // enqueue and store future
//    for(int i = 0; i < 1; ++i) {
//        auto result = pool2.enqueue([i] {
//            while(true)
//            {
//                std::string temp = DataHandle::GetDataFromIMGQueue();
//                if(temp != "")
//                {
//                    std::cout << "IMG:" << temp << "\t IMGQueueLen:" << DataHandle::GetIMGQueueLength() <<  std::endl;
//                    DownLoadHandle::DownLoad(temp);
//                }
//            }
//        });
//    }
}
