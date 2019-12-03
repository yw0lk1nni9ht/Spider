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

#include "curl/curl.h"

using namespace std;
void _test();



/**
 * @brief 回调函数，用于获取Request类请求页面后的Body数据,并且解析
 * @param data      数据
 *
 */
void print_callback(string data){
    response_parse test;
    test.parse(data);
}


/**
 * @brief 用于启动
 * @param print_callback      回调
 * @param url               要请求的url
 *
 */
void _test()
{
    RequestHandle t2;
    int ret = t2.Connect(print_callback,"https://www.nvshens.net");
}


size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main()
{
    CURL *curl;
    FILE *fp;
    CURLcode res;
    char *url = "https://img.onvshen.com:85/girl/22370/22370_s.jpg";
    char outfilename[FILENAME_MAX] = "page.jpg";
    curl = curl_easy_init();
    if (curl)
    {
        fp = fopen(outfilename,"wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        fclose(fp);
    }

//    int fin = open("https://img.onvshen.com:85/girl/22370/22370_s.jpg", O_RDONLY, 0777);
//    int fout = open("/home/ywin/下载3.jpg", O_WRONLY|O_CREAT, 0777);

//    char buff[1024] = {'\0'};
//    int len = 0;
//    while((len = read(fin, buff, sizeof(buff))) > 0)
//    {
//        write(fout, buff, len);
//    }

//    close(fin);
//    close(fout);


//    FILE *fp;
//    if(fp=fopen("https://img.onvshen.com:85/girl/22370/22370_s.jpg","wb"))
//        puts("打开文件成功");
//    else
//        puts("打开文件成败");


        std::thread t(_test);
    t.join();
    //获取网站的数据，并通过回调返回

}
