#include "downloadhandle.h"
#include "curl/curl.h"
#include <openssl/md5.h>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include "unistd.h"
using namespace std;

DownLoadHandle::DownLoadHandle()
{

}

static int createdir(string str,string& retfilepath)
{
    int ret = 0;

    /*  https://img.onvshen.com:85/article/11106/01.jpg   */
    str = str.substr(str.find("://")+3);
    str = "Result/" + str;
    while(str.find('/') != string::npos)
    {
        string filename = str.substr(0,str.find('/'));
        retfilepath += filename;
        str = str.substr(str.find('/') + 1);

        //判断文件夹是否已经存在
        if(access(retfilepath.c_str(),00) < 0)
        {
            ret += mkdir(retfilepath.c_str(),S_IRWXU);
        }

        retfilepath += "/";
    }
    retfilepath.append(str);
    return ret;
    //int mkdir(const char *pathname, mode_t mode);
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

    string ret;
    if (createdir(_url,ret) < 0)
    {
        return;
    }
    char *url = (char*)_url.c_str();
    char *outfilename = NULL;
    outfilename = (char*)ret.c_str();

//    //通过把整个url编码成md5,来判断是否重复。需要先创建Test文件夹
//    char *url = (char*)_url.c_str();
//    char *outfilename = NULL;
//    string ret ="Test/";
//    md5(_url,ret);
//    ret.append(_url.substr(_url.rfind('.')));
//    outfilename = (char*)ret.c_str();

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
