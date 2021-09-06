//
//  HS_LinkedList.c
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/7.
//  Copyright © 2020 Shun. All rights reserved.
//

#include "HS_LinkedList.h"

const HS_LIST_INDEX HS_ELEMENT_NOT_FOUND = -1;

struct hs_Linked_List_Node {
    /**
    * 前序节点
    */
    struct hs_Linked_List_Node* prev;
    /**
    * 后继节点
    */
    struct hs_Linked_List_Node* next;
    /**
    * 存储元素
    */
    HS_ELEMENT_TYPE element;
};

typedef struct hs_Linked_List_Node HS_List_Node;

struct hs_Linked_List {
    /**
     * 元素的数量
     */
    HS_LIST_SIZE size;
    /**
    * 表头元素
    */
    HS_List_Node * first;
    /**
     * 表尾元素
     */
    HS_List_Node * last;
    /**
     * 元素比较方法，相等为1，不相等为0
     */
    HS_COMPARE pCompare;
};

void hs_linkedListPointerCheck(HS_LinkedList* pList)
{
    assert(pList != NULL);
}

void hs_linkedListRangeCheck(HS_LinkedList* pList, HS_LIST_INDEX index)
{
    assert(index >= 0 && index < pList -> size);
}

void hs_linkedListRangeCheckForAdd(HS_LinkedList* pList, HS_LIST_INDEX index)
{
    assert(index >= 0 && index <= pList -> size);
}

HS_List_Node* hs_listNodeCreate(HS_List_Node* prev, HS_List_Node* next, HS_ELEMENT_TYPE element)
{
    HS_List_Node* pNode = (HS_List_Node*) malloc(sizeof(HS_List_Node));
    if (pNode)
    {
        pNode -> prev = prev;
        pNode -> next = next;
        pNode -> element = element;
    }
    return pNode;
}

HS_List_Node* hs_linkedListNodeOfIndex(HS_LinkedList* pList, HS_LIST_INDEX index)
{
    HS_List_Node* pNode = NULL;
    if (index < (pList -> size >> 1))
    {
        pNode = pList -> first;
        for (int i = 0; i < index; i++)
            pNode = pNode -> next;
    }
    else
    {
        pNode = pList -> last;
        for (HS_LIST_SIZE i = pList -> size - 1; i > index; i--)
            pNode = pNode -> prev;
    }
    return pNode;
}


/**
 * 创建链表
 * @return 返回链表指针
 */
HS_LinkedList* hs_linkedListNew(void)
{
    return hs_linkedListNewWihCompare(NULL);
}

/**
 * 创建链表
 * @param compare 设置比较函数
 * @return 返回链表指针
 */
HS_LinkedList* hs_linkedListNewWihCompare(HS_COMPARE compare)
{
    HS_LinkedList* pList = (HS_LinkedList*) malloc(sizeof(HS_LinkedList));
    if (pList)
    {
        pList -> size = 0;
        pList -> first = NULL;
        pList -> last = NULL;
        pList -> pCompare = compare;
    }
    return  pList;
}

/**
 * 清除所有元素
 * @param pList 链表指针
 */
void hs_linkedListClear(HS_LinkedList* pList)
{
    hs_linkedListPointerCheck(pList);
    if(!hs_linkedListIsEmpty(pList))
    {
        HS_List_Node* tmp = NULL;
        while (pList -> first)
        {
            tmp = pList -> first;
            pList -> first = pList -> first -> next;
            free(tmp);
        }
        pList -> last = NULL;
        pList -> size = 0;
    }
}

/**
 * 返回链表元素的数量
 * @param pList 链表指针
 * @return 返回链表元素数
 */
HS_LIST_SIZE hs_linkedListGetSize(HS_LinkedList* pList)
{
    hs_linkedListPointerCheck(pList);
    return pList -> size;
}

/**
 * 链表是否为空
 * @param pList 链表指针
 * @return 链表无元素返回true，否则返回false
 */
bool hs_linkedListIsEmpty(HS_LinkedList* pList)
{
    hs_linkedListPointerCheck(pList);
    return !pList -> size;
}

/**
 * 添加元素到尾部
 * @param pList 动态数组指针
 * @param element 待加入的元素
 */
void hs_linkedListAdd(HS_LinkedList* pList, HS_ELEMENT_TYPE element)
{
    hs_linkedListAddToIndex(pList, element, pList -> size);
}

/**
 * 在index位置插入一个元素
 * @param pList 链表指针
 * @param element 待加入的元素
 * @param index 加入的位置，链表从0开始计算索引
 */
void hs_linkedListAddToIndex(HS_LinkedList* pList, HS_ELEMENT_TYPE element, HS_LIST_INDEX index)
{
    hs_linkedListPointerCheck(pList);
    hs_linkedListRangeCheckForAdd(pList, index);
    if (index == pList -> size)
    {
        HS_List_Node* tmp = pList -> last;
        pList -> last = hs_listNodeCreate(tmp, NULL, element);
        if (!tmp)
            pList -> first = pList -> last;
        else
            tmp -> next = pList -> last;
    }
    else
    {
        HS_List_Node* pNext = hs_linkedListNodeOfIndex(pList, index);
        HS_List_Node* pPrev = pNext -> prev;
        HS_List_Node* pNewNode = hs_listNodeCreate(pPrev, pNext, element);
        pNext -> prev = pNewNode;
        //index == 0
        if (!pPrev)
            pList -> first = pNewNode;
        else
            pPrev -> next = pNewNode;
    }
    (pList -> size)++;
}

/**
 * 获取index位置的元素
 * @param pList 链表指针
 * @param index 元素的索引，链表从0开始计算索引
 * @return 返回索引处的元素
 */
HS_ELEMENT_TYPE hs_linkedListGetOfIndex(HS_LinkedList* pList, HS_LIST_INDEX index)
{
    hs_linkedListPointerCheck(pList);
    hs_linkedListRangeCheck(pList, index);
    return  hs_linkedListNodeOfIndex(pList, index) -> element;
}

/**
 * 设置index位置的元素
 * @param pList 链表指针
 * @param element 替换的元素
 * @param index 元素的索引，链表从0开始计算索引
 * @return 原来的元素ֵ
 */
HS_ELEMENT_TYPE hs_linkedListSetToIndex(HS_LinkedList* pList, HS_ELEMENT_TYPE element, HS_LIST_INDEX index)
{
    hs_linkedListPointerCheck(pList);
    hs_linkedListRangeCheck(pList, index);
    HS_List_Node* pNode = hs_linkedListNodeOfIndex(pList, index);
    HS_ELEMENT_TYPE oldElement = pNode -> element;
    pNode -> element = element;
    return  oldElement;
}

/**
 * 删除index位置的元素
 * @param pList 链表指针
 * @param index 元素的索引，链表从0开始计算索引
 * @return 返回被删除的元素
 */
HS_ELEMENT_TYPE hs_linkedListRemoveAtIndex(HS_LinkedList* pList, HS_LIST_INDEX index)
{
    hs_linkedListPointerCheck(pList);
    hs_linkedListRangeCheck(pList, index);
    
    HS_List_Node* removeNode = hs_linkedListNodeOfIndex(pList, index);
    HS_List_Node* pPrev = removeNode -> prev;
    HS_List_Node* pNext = removeNode -> next;
    
    if (pPrev)
        pPrev -> next = pNext;
    else
        pList -> first = pNext;
    
    if (pNext)
        pNext -> prev = pPrev;
    else
        pList -> last = pPrev;
    
    (pList -> size)--;
    
    HS_ELEMENT_TYPE removedElement = removeNode -> element;
    free(removeNode);
    
    return  removedElement;
}

/**
 * 查看元素的索引
 * @param pList 链表指针
 * @param element 待查询的元素
 * @return 若链表包含该元素，返回索引值，索引从0开始计算；若不包含该元素，返回HS_ELEMENT_NOT_FOUND
 */
HS_LIST_INDEX hs_linkedListIndexOf(HS_LinkedList* pList, HS_ELEMENT_TYPE element)
{
    hs_linkedListPointerCheck(pList);
    HS_List_Node* pNode = pList -> first;
    if (pList -> pCompare)
    {
        for (HS_LIST_INDEX i = 0 ; i < pList -> size; ++i, pNode = pNode -> next)
        {
            if ((*(pList -> pCompare))(pNode -> element, element)) {
                return i;
            }
        }
    }
    else
    {
        for (HS_LIST_INDEX i = 0 ; i < pList -> size; ++i, pNode = pNode -> next)
        {
            if (pNode -> element == element) {
                return i;
            }
        }
    }
    return  HS_ELEMENT_NOT_FOUND;
}

/**
 * 销毁链表
 * @param pList 链表指针
 */
void hs_linkedListFree(HS_LinkedList* pList)
{
    hs_linkedListPointerCheck(pList);
    if(!hs_linkedListIsEmpty(pList))
    {
        HS_List_Node* tmp = NULL;
        while (pList -> first)
        {
            tmp = pList -> first;
            pList -> first = pList -> first -> next;
            free(tmp);
        }
    }
    free(pList);
}


