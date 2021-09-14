//
//  Trie.h
//  Trie
//
//  Created by 郝源顺 on 2021/9/13.
//

#ifndef Trie_h
#define Trie_h

#include <stdio.h>
#include <stdbool.h>

typedef unsigned int HS_SIZE;

typedef struct hs_trie HS_TRIE;

typedef char E_TYPE;

/**
 * 创建Trie
 * @return 返回Trie指针
 */
HS_TRIE* hs_trieCreate(void);


/**
 * 获取字典树单词的数量
 * @param pTrie 树指针
 * @return 返回字典树单词数
 */
HS_SIZE hs_trieSize(HS_TRIE* pTrie);


/**
 * Trie是否为空
 * @param pTrie 树指针
 * @return 若为空树返回true，否则false
 */
bool hs_trieIsEmpty(HS_TRIE* pTrie);


/**
 * 清空Trie
 * @param pTrie 树指针
 */
void hs_trieClear(HS_TRIE* pTrie);


/**
 * 向Trie中添加单词
 * @param pTrie 树指针
 * @param key 关键字
 */
void hs_trieAdd(HS_TRIE* pTrie, const char* key);


/**
 * 关键字是否在Trie中
 * @param pTrie 树指针
 * @param key 关键字
 * @return 若关键字在树中返回true，否则false
 */
bool hs_trieSearch(HS_TRIE* pTrie, const char* key);


/**
 * 关键字是否是Trie中的前缀
 * @param pTrie 树指针
 * @param key 关键字
 * @return 若关键字为树中前缀返回true，否则false
 */
bool hs_trieStartWith(HS_TRIE* pTrie, const char* key);

#endif /* Trie_h */
