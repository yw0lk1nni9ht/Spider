#include "response_parse.h"
#include <iostream>
#include <modest/finder/finder.h>
#include <myhtml/myhtml.h>
#include <myhtml/serialization.h>
#include <mycss/mycss.h>
#include <mycss/selectors/init.h>
#include <mycss/selectors/serialization.h>
#include "datahandle.h"

//mystatus_t serialization_callback2(const char* data, size_t len, void* ctx);
//void print_found_result(const char* caption, myhtml_tree_t* html_tree, myhtml_collection_t *collection);
std::string GetTagValue(std::string Tag,const char* _attributeName);
std::string Tag = "";
//myhtml_tag_id_t _tag_id = MyHTML_TAG__UNDEF;
response_parse::response_parse()
{

}

void response_parse::parse(std::string response,int id)
{
    if(id == 1)
    {
        _tag_id = MyHTML_TAG_A;
    }
    else if (id == 2)
    {
        _tag_id = MyHTML_TAG_IMG;
    }
    // 初始化
    myhtml_t* myhtml = myhtml_create();
    myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

    // 初始化树
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);

    // 解析
    myhtml_parse(tree, MyENCODING_UTF_8, response.c_str(), strlen(response.c_str()));

    // 获取包含所有ID标签的值的结构
    myhtml_collection_t *titles_list = myhtml_get_nodes_by_tag_id(tree, NULL, _tag_id, NULL);

    // 遍历元素
    print_found_result("In First tree" , tree , titles_list);

    // 释放资源
    myhtml_collection_destroy(titles_list);
    myhtml_tree_destroy(tree);
    myhtml_destroy(myhtml);
}



/**
 * @brief 解析标签，并加入到队列
 * @param data              标签字符串，如<a href="/girl/17886/" target="_blank">
 * @param len               标签长度，如39
 *
 * @return 返回说明
 *     -<em>mystatus_t</em> 状态值
 */
mystatus_t response_parse::ResolveTag(const char* data, size_t len, void* ctx)
{
    //转化成字符串
    std::string temp = std::string(data);

    // 获取<a>标签如: <a href="/girl/17886/" target="_blank">
    if (_tag_id == MyHTML_TAG_A)
    {
        //std::cout << GetTagValue("href=\"") << std::endl;
        std::string ret = GetTagValue(temp,"href=\"");
        if (ret.substr(0,1) == "/")
        {
            DataHandle::AddDataToAQueue(ret);
        }
        //std::cout << ret << std::endl;
    }

    //获取<img>标签如: <img src="img/grey.gif" data-original="img/example.jpg" width="640" heigh="480">
    if (_tag_id == MyHTML_TAG_IMG)
    {
        //如果存在"data-original"就获取这里的值, 如果没有，就从"src"获取
        std::string ret = GetTagValue(temp,"data-original=\"");
        if (ret == "")
        {
            ret = GetTagValue(temp,"src=\"");
        }

        DataHandle::AddDataToIMGQueue(ret);

        //std::cout << ret << std::endl;
    }

    return MyCORE_STATUS_OK;
}

void response_parse::print_found_result(const char* caption, myhtml_tree_t* html_tree, myhtml_collection_t *collection)
{
    if(collection) {
        for(size_t i = 0; i < collection->length; i++) {
            //myhtml_serialization_node_callback(collection->list[i], serialization_callback2, NULL);

            mycore_string_raw _data = {};
            myhtml_serialization_node(collection->list[i],&_data);
            ResolveTag(_data.data,_data.length,NULL);
        }
    }
    else {
        printf("%s: empty\n", caption);
    }
}



/**
 * @brief 获取标签的值
 * @param Tag       标签字符串，如<a href="/girl/17886/" target="_blank">
 * @param _attributeName       属性名称，如href="
 *
 * @return 返回说明
 *     -<em>string</em> 属性值，如/girl/17886/
 */
std::string GetTagValue(std::string Tag,const char* _attributeName)
{
    if (Tag.find(_attributeName) != std::string::npos)
    {
        std::string temp = Tag.substr(Tag.find(_attributeName) + strlen(_attributeName));
        return temp.substr(0,temp.find("\""));
    }
    else
        return "";
}
