#include "downloadhandle.h"
#include "curl/curl.h"
#include <openssl/md5.h>
#include <string>
#include <fstream>
using namespace std;

DownLoadHandle::DownLoadHandle()
{

}

//md5
static string md5(string str, string& buff)
{
    MD5_CTX ctx;
        unsigned char md5[16] = {0};
        char tmp[3]={'\0'};
        int i;

        MD5_Init(&ctx);

        MD5_Update(&ctx, str.data(), str.length());

        MD5_Final(md5, &ctx);

        for(i = 0; i<16; i++)
        {
            sprintf(tmp, "%02x", md5[i]);
            //strcat(buff, tmp);
            buff = buff.append(tmp);
        }
        return buff;
}

void DownLoadHandle::DownLoad(string _url)
{
    CURL *curl;
    FILE *fp;
    CURLcode res;

    char *url = (char*)_url.c_str();
    char *outfilename = NULL;
    string ret ="Test/";
    md5(_url,ret);
    ret.append(_url.substr(_url.rfind('.')));
    outfilename = (char*)ret.c_str();

    //文件存在则不下载
    std::fstream _file;
    _file.open(ret, std::ios::in);
    if(_file)
    {
        //已经存在!
        _file.close();
        return;
    }
    else
    {
        //没有被创建!
        _file.close();
    }
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
}
