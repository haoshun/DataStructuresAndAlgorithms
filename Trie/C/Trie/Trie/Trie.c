//
//  Trie.c
//  Trie
//
//  Created by 郝源顺 on 2021/9/13.
//

#include "Trie.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_LEN 26

typedef struct _trie_node {
    struct _trie_node* children[MAX_LEN];
    bool isWord;
}Trie_Node;


struct hs_trie{
    Trie_Node* root;
    HS_SIZE size;
};


void _trie_pointer_check(HS_TRIE* pTrie)
{
    assert(pTrie != NULL);
}


void _str_check(const char* str)
{
    assert(str != NULL && strlen(str));
}

void _initialized_check(HS_TRIE* pTrie, const char* str)
{
    _trie_pointer_check(pTrie);
    _str_check(str);
}

Trie_Node* _trie_node_create(void)
{
    Trie_Node* pNode = (Trie_Node*) calloc(1, sizeof(Trie_Node));

    return pNode;
}


/**
 * 创建Trie
 * @return 返回Trie指针
 */
HS_TRIE* hs_trieCreate(void)
{
    HS_TRIE* pTrie = (HS_TRIE*)malloc(sizeof(HS_TRIE));
    if (pTrie)
    {
        pTrie -> root = _trie_node_create();
        pTrie -> size = 0;
    }
    
    return pTrie;
}


/**
 * 获取字典树单词的数量
 * @param pTrie 树指针
 * @return 返回字典树单词数
 */
HS_SIZE hs_trieSize(HS_TRIE* pTrie)
{
    _trie_pointer_check(pTrie);
    return pTrie -> size;
}


/**
 * Trie是否为空
 * @param pTrie 树指针
 * @return 若为空树返回true，否则false
 */
bool hs_trieIsEmpty(HS_TRIE* pTrie)
{
    _trie_pointer_check(pTrie);
    return !pTrie -> root || pTrie -> size == 0;
}


/**
 * 清空Trie
 * @param pTrie 树指针
 */
void hs_trieClear(HS_TRIE* pTrie)
{
//    if(hs_trieIsEmpty(pTrie))
//    {
//        
//        pTrie -> size = 0;
//        pTrie -> root = NULL;
//    }
}


/**
 * 向Trie中添加单词
 * @param pTrie 树指针
 * @param key 关键字
*/
void hs_trieAdd(HS_TRIE* pTrie, const char* key)
{
    _initialized_check(pTrie, key);
    
    if(!pTrie -> root)
        pTrie -> root = _trie_node_create();
    
    unsigned long len = strlen(key);
    Trie_Node* parent = pTrie -> root, ** child = NULL;
    
    for(int i = 0 ; i < len ; parent = *child, ++i)
    {
        child = &(parent -> children[key[i] - 'a']);
        if(!*child)
            *child = _trie_node_create();
            
        if(i == len - 1 && !(*child) -> isWord)
        {
            pTrie -> size ++;
            (*child) -> isWord = true;
        }
    }
}


/**
 * 关键字是否在Trie中
 * @param pTrie 树指针
 * @param key 关键字
 * @return 若关键字在树中返回true，否则false
 */
bool hs_trieSearch(HS_TRIE* pTrie, const char* key)
{
    _initialized_check(pTrie, key);
    
    if(hs_trieIsEmpty(pTrie))
        return false;
    
    unsigned long len = strlen(key);
    Trie_Node* parent = pTrie -> root, * child = NULL;
    for(int i = 0 ; i < len ; parent = child, ++i)
    {
        child = parent -> children[key[i] - 'a'];
        if(!child)
            break;
        
        if(i == len - 1 && child -> isWord)
            return true;
    }
    return false;
}


/**
 * 关键字是否是Trie中的前缀
 * @param pTrie 树指针
 * @param key 关键字
 * @return 若关键字为树中前缀返回true，否则false
 */
bool hs_trieStartWith(HS_TRIE* pTrie, const char* key)
{
    _initialized_check(pTrie, key);
    
    if(hs_trieIsEmpty(pTrie))
        return false;
    
    unsigned long len = strlen(key);
    Trie_Node* parent = pTrie -> root, * child = NULL;
    for(int i = 0 ; i < len ; parent = child, ++i)
    {
        child = parent -> children[key[i] - 'a'];
        
        if(!child)
            return  false;
    }
    return true;
}



