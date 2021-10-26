//
//  HS_SkipList.c
//  SkipList
//
//  Created by 郝源顺 on 2021/10/23.
//

#include "HS_SkipList.h"
#include <time.h>



typedef struct _sl_node {
    /**
    * 所有的元素
    */
    struct _sl_node** _next;
    /**
    * 所有的元素
    */
    HS_KEY _key;
    /**
    * 所有的元素
    */
    HS_VALUE _value;
    /**
    * 所有的元素
    */
    HS_LEVEL _level;
    
}HS_SL_Node;


struct hs_skip_list {
    /**
    * 头结点指针，不存储数据
    */
     HS_SL_Node* head;

    /**
    * 以index元素为根节点的树的节点数
    */
     HS_LEVEL max_level;

};

#pragma mark -

void _sl_pointer_check(HS_SkipList* pSL)
{
    assert(pSL != NULL);
}

HS_LEVEL _sl_randomLevel(void)
{
    HS_LEVEL level = 1;
    while((rand() * (1.0 / RAND_MAX) < SL_P) && (level < MAX_LEVEL))
        level++;
    return level;
}

HS_SL_Node* _sl_create_node(HS_KEY key, HS_VALUE value, HS_LEVEL level)
{
    HS_SL_Node* pNode = (HS_SL_Node*) malloc(sizeof(HS_SL_Node));
    if(pNode)
    {
        pNode -> _level = level;
        pNode -> _key = key;
        pNode -> _value = value;
        pNode -> _next = (HS_SL_Node**) calloc(sizeof(HS_SL_Node *), pNode -> _level);
    }
    return pNode;
}


#pragma mark -

/**
 * 创建跳表
 * @return 返回跳表指针
 */
HS_SkipList* hs_slCreate(void)
{
    HS_SkipList* pSL = (HS_SkipList*) malloc(sizeof(HS_SkipList));
    if(pSL)
    {
        srand((unsigned int)time(NULL));
        pSL -> head = _sl_create_node((HS_KEY)NULL, (HS_VALUE)NULL, MAX_LEVEL);
        pSL -> max_level = 0;
    }
    return pSL;
}


/**
 * 创建跳表
 * @param pSL 跳表指针
 * @param key 键
 * @param value 值
 * @return 若键已存在，新值覆盖旧值，返回旧值；若不存在，返回NULL
 */
HS_VALUE hs_slInsert(HS_SkipList* pSL, HS_KEY key, HS_VALUE value)
{
    _sl_pointer_check(pSL);
    
    HS_SL_Node* pNode = pSL -> head, * prev[pSL -> max_level];
    
    for (int i = pSL -> max_level ; i >= 0 ; --i)
    {
        while (pNode -> _next[i] && pNode -> _next[i] ->_key < key) {
            pNode = pNode -> _next[i];
        }
        if(pNode -> _next[i] && pNode -> _next[i] ->_key == key)
        {
            HS_VALUE oldValue = pNode -> _next[i] -> _value;
            pNode -> _next[i] -> _value = value;
            return oldValue;
        }
        prev[i] = pNode;
    }
    
    //创建新节点
    HS_LEVEL newLevel = _sl_randomLevel();
    HS_SL_Node* newNode = _sl_create_node(key, value, newLevel);
    
    //设置前驱和后继
    for(int i = 0 ; i < newLevel ; ++i)
    {
      if(i >= pSL -> max_level)
          pSL -> head -> _next[i] = newNode;
      else
      {
          newNode -> _next[i] = prev[i] -> _next[i];
          prev[i] -> _next[i] = newNode;
      }
    }
    
    
    if(newLevel > pSL -> max_level)
        pSL -> max_level = newLevel;
    
    return HS_NONE;
}



/**
 * 创建跳表
 * @param pSL 跳表指针
 * @param key 键
 * @return 若键值存在，返回旧值；若不存在，返回NULL
 */
HS_VALUE hs_slGet(HS_SkipList* pSL, HS_KEY key)
{
    _sl_pointer_check(pSL);
    
    HS_SL_Node* pNode = pSL -> head;
    for (int i = pSL -> max_level - 1; i >= 0 ; --i)
    {
        while (pNode -> _next[i] && pNode -> _next[i] ->_key < key) {
            pNode = pNode -> _next[i];
        }
        if(pNode -> _next[i] && pNode -> _next[i] ->_key == key)
            return pNode -> _next[i] ->_value;
    }
    
    return HS_NONE;
}




/**
 * 删除键值
 * @param pSL 跳表指针
 * @param key 键
 * @return 若键值存在，返回旧值；若不存在，返回NULL
 */
HS_VALUE hs_slRemove(HS_SkipList* pSL, HS_KEY key)
{
    _sl_pointer_check(pSL);
    
    HS_SL_Node* pNode = pSL -> head, * prev[pSL -> max_level];
    bool exist = false;
    
    for (int i = pSL -> max_level - 1; i >= 0 ; --i)
    {
        while (pNode -> _next[i] && pNode -> _next[i] ->_key < key) {
            pNode = pNode -> _next[i];
        }
        prev[i] = pNode;
        if(pNode -> _next[i] && pNode -> _next[i] ->_key == key)
            exist = true;
    }
    
    if(!exist)
        return HS_NONE;
    
    HS_SL_Node* removeNode = pNode -> _next[0];
    HS_VALUE value = removeNode -> _value;
    
    //设置后继
    for (int i = 0 ; i < removeNode -> _level; ++i)
        prev[i] -> _next[i] = removeNode -> _next[i];
    
    //跳表最高层数处理
    int newLevel = pSL -> max_level;
    while(--newLevel >= 0 && !pSL -> head -> _next[newLevel])
        pSL -> max_level = newLevel;
    
    
    return value;
}




#pragma mark - print

void print_sl(HS_SkipList* pSL)
{
    _sl_pointer_check(pSL);
    
    HS_SL_Node* pNode = pSL -> head;
    for(int i = pSL -> max_level - 1 ; i >= 0 ; --i, pNode = pSL -> head)
    {
        printf("level %d :", i);
        while (pNode ->_next[i]) {
            printf("(%ld,%ld), ", pNode -> _next[i] -> _key, pNode -> _next[i] -> _value);
            pNode = pNode -> _next[i];
        }
        printf("\n");
    }
}

