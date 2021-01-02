//
//  HS_LinkedList.h
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/7.
//  Copyright © 2020 Shun. All rights reserved.
//

#ifndef HS_LinkedList_h
#define HS_LinkedList_h

#include <stdio.h>
#include<stdbool.h>
#include <assert.h>
#include <stdlib.h>

#ifndef HS_ELEMENT_TYPE
typedef int HS_ELEMENT_TYPE;
#endif

typedef long long HS_LIST_SIZE;
typedef HS_LIST_SIZE HS_LIST_INDEX;
typedef struct hs_Linked_List HS_LinkedList;
typedef int(*HS_COMPARE)(HS_ELEMENT_TYPE,HS_ELEMENT_TYPE) ;

extern const HS_LIST_INDEX HS_ELEMENT_NOT_FOUND;

/**
 * 创建链表
 * @return 返回链表指针
 */
HS_LinkedList* hs_linkedListNew(void);

/**
 * 创建链表
 * @param compare 设置比较函数
 * @return 返回链表指针
 */
HS_LinkedList* hs_linkedListNewWihCompare(HS_COMPARE compare);

/**
 * 清除所有元素
 * @param pList 链表指针
 */
void hs_linkedListClear(HS_LinkedList* pList);

/**
 * 返回链表元素的数量
 * @param pList 链表指针
 * @return 返回链表元素数
 */
HS_LIST_SIZE hs_linkedListGetSize(HS_LinkedList* pList);

/**
 * 链表是否为空
 * @param pList 链表指针
 * @return 链表无元素返回true，否则返回false
 */
bool hs_linkedListIsEmpty(HS_LinkedList* pList);

/**
 * 添加元素到尾部
 * @param pList 动态数组指针
 * @param element 待加入的元素
 */
void hs_linkedListAdd(HS_LinkedList* pList, HS_ELEMENT_TYPE element);

/**
 * 在index位置插入一个元素
 * @param pList 链表指针
 * @param element 待加入的元素
 * @param index 加入的位置，链表从0开始计算索引
 */
void hs_linkedListAddToIndex(HS_LinkedList* pList, HS_ELEMENT_TYPE element, HS_LIST_INDEX index);

/**
 * 获取index位置的元素
 * @param pList 链表指针
 * @param index 元素的索引，链表从0开始计算索引
 * @return 返回索引处的元素
 */
HS_ELEMENT_TYPE hs_linkedListGetOfIndex(HS_LinkedList* pList, HS_LIST_INDEX index);

/**
 * 设置index位置的元素
 * @param pList 链表指针
 * @param element 替换的元素
 * @param index 元素的索引，链表从0开始计算索引
 * @return 原来的元素ֵ
 */
HS_ELEMENT_TYPE hs_linkedListSetToIndex(HS_LinkedList* pList, HS_ELEMENT_TYPE element, HS_LIST_INDEX index);

/**
 * 删除index位置的元素
 * @param pList 链表指针
 * @param index 元素的索引，链表从0开始计算索引
 * @return 返回被删除的元素
 */
HS_ELEMENT_TYPE hs_linkedListRemoveAtIndex(HS_LinkedList* pList, HS_LIST_INDEX index);

/**
 * 查看元素的索引
 * @param pList 链表指针
 * @param element 待查询的元素
 * @return 若链表包含该元素，返回索引值，索引从0开始计算；若不包含该元素，返回HS_ELEMENT_NOT_FOUND
 */
HS_LIST_INDEX hs_linkedListIndexOf(HS_LinkedList* pList, HS_ELEMENT_TYPE element);

/**
 * 销毁链表
 * @param pList 链表指针
 */
void hs_linkedListFree(HS_LinkedList* pList);


#endif /* HS_LinkedList_h */
