#include "response_parse.h"
#include <iostream>
#include <modest/finder/finder.h>
#include <myhtml/myhtml.h>
#include <myhtml/serialization.h>
#include <mycss/mycss.h>
#include <mycss/selectors/init.h>
#include <mycss/selectors/serialization.h>

mycss_entry_t * create_css_parser(void);
myhtml_tree_t * parse_html(myhtml_t* myhtml, const char* data, size_t data_size);
mycss_selectors_list_t * prepare_selector(mycss_entry_t *css_entry, const char* selector, size_t selector_size);
myhtml_collection_t * find_by_selectors_list(modest_finder_t *finder, myhtml_tree_node_t *scope, mycss_selectors_list_t *list);
mystatus_t serialization_callback(const char* data, size_t len, void* ctx);
mystatus_t serialization_bad_selectors(const char* data, size_t len, void* ctx);
void print_found_result(const char* caption, myhtml_tree_t* html_tree, myhtml_collection_t *collection);

response_parse::response_parse()
{

}

void response_parse::parse(std::string response)
{

    //const char *selector    = "div:not(:has(a))";
    const char *selector = "div > :nth-child(2n+1):not(:has(a))";

    /* init MyHTML */
     myhtml_t *myhtml = myhtml_create();
     myhtml_init(myhtml, MyHTML_OPTIONS_DEFAULT, 1, 0);

     /* create css parser and finder for selectors */
     mycss_entry_t *css_entry = create_css_parser();
     modest_finder_t *finder = modest_finder_create_simple();

     /* create tree and parse html */
     myhtml_tree_t *tree_first  = parse_html(myhtml, response.c_str(), response.length());

     /* prepare/parse selector */
     mycss_selectors_list_t *selectors_list = prepare_selector(css_entry, selector, strlen(selector));

     /* find nodes by selector */
     myhtml_collection_t *collection_first  = find_by_selectors_list(finder, tree_first->node_html, selectors_list);

     //mycss_selectors_serialization_list(mycss_entry_selectors(css_entry), selectors_list, serialization_callback, NULL);

     std::cout << "node_html:" << (tree_first->node_html->data) << std::endl;
     std::cout << "node_html:" << (tree_first->node_html->child->data) << std::endl;

     //myhtml_serialization_tree_callback(tree_first->node_body , serialization_callback, NULL);
     print_found_result("In First tree" , tree_first , collection_first);

}


mycss_entry_t * create_css_parser(void)
{
    // base init
    mycss_t *mycss = mycss_create();
    mystatus_t status = mycss_init(mycss);

    if(status) {
        fprintf(stderr, "Can't init CSS Parser\n");
        exit(EXIT_FAILURE);
    }

    // currenr entry work init
    mycss_entry_t *entry = mycss_entry_create();
    status = mycss_entry_init(mycss, entry);

    if(status) {
        fprintf(stderr, "Can't init CSS Entry\n");
        exit(EXIT_FAILURE);
    }

    return entry;
}

myhtml_tree_t * parse_html(myhtml_t* myhtml, const char* data, size_t data_size)
{
    myhtml_tree_t* tree = myhtml_tree_create();
    myhtml_tree_init(tree, myhtml);

    myhtml_parse(tree, MyENCODING_UTF_8, data, data_size);

    return tree;
}

mycss_selectors_list_t * prepare_selector(mycss_entry_t *css_entry, const char* selector, size_t selector_size)
{
    mystatus_t out_status;
    mycss_selectors_list_t *list = mycss_selectors_parse(mycss_entry_selectors(css_entry),
                                                         MyENCODING_UTF_8, selector, selector_size,
                                                         &out_status);
    /* check parsing errors */
    if(list == NULL || (list->flags & MyCSS_SELECTORS_FLAGS_SELECTOR_BAD)) {
        fprintf(stderr, "Bad CSS Selectors\n");

        if(list) {
            (mycss_entry_selectors(css_entry), list, serialization_bad_selectors, NULL);
            printf("\n");
        }

        exit(EXIT_FAILURE);
    }

    return list;
}

myhtml_collection_t * find_by_selectors_list(modest_finder_t *finder, myhtml_tree_node_t *scope, mycss_selectors_list_t *list)
{
    myhtml_collection_t *collection = NULL;
    modest_finder_by_selectors_list(finder, scope, list, &collection);

    return collection;
}

mystatus_t serialization_callback(const char* data, size_t len, void* ctx)
{
    printf("%.*s", (int)len, data);
    return MyCORE_STATUS_OK;
}

mystatus_t serialization_bad_selectors(const char* data, size_t len, void* ctx)
{
    printf("%.*s", (int)len, data);
    return MyCORE_STATUS_OK;
}

void print_found_result(const char* caption, myhtml_tree_t* html_tree, myhtml_collection_t *collection)
{
    if(collection) {
        printf("%s:\n", caption);

        for(size_t i = 0; i < collection->length; i++) {
            printf("\t\n\n");
            myhtml_serialization_node_callback(collection->list[i], serialization_callback, NULL);
        }

        printf("\n");
    }
    else {
        printf("%s: empty\n", caption);
    }
}
