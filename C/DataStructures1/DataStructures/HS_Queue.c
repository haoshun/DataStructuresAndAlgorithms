//
//  HS_Queue.c
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/8.
//  Copyright © 2020 Shun. All rights reserved.
//

#include "HS_Queue.h"
#include "HS_LinkedList.h"

struct hs_linkedListQueue {
    /**
    * 所有的元素
    */
    HS_LinkedList * elements;
    /**
     * 队列内元素的数量
     */
    HS_QUEUE_SIZE size;
   
};


void hs_queuePointerCheck(HS_Queue* pQueue)
{
    assert(pQueue != NULL);
}

/**
 * 创建队列
 * @return 返回队列指针
 */
HS_Queue* hs_queueNew(void)
{
    HS_Queue* pQueue = (HS_Queue*)malloc(sizeof(HS_Queue));
    if (pQueue)
    {
        pQueue -> elements = hs_linkedListNew();
        pQueue -> size = 0;
    }
    return pQueue;
}

/**
 * 清除所有元素
 * @param pQueue 队列指针
 */
void hs_queueClear(HS_Queue* pQueue)
{
    hs_queuePointerCheck(pQueue);
    if (pQueue -> size)
    {
        hs_linkedListClear(pQueue -> elements);
        pQueue -> size = 0;
    }
}

/**
 * 返回队列元素的数量
 * @param pQueue 队列指针
 * @return 返回队列元素数
 */
HS_QUEUE_SIZE hs_queueSize(HS_Queue* pQueue)
{
    hs_queuePointerCheck(pQueue);
    return pQueue -> size;
}

/**
 * 队列是否为空
 * @param pQueue 队列指针
 * @return 队列无元素返回true，否则返回false
 */
bool hs_queueIsEmpty(HS_Queue* pQueue)
{
    hs_queuePointerCheck(pQueue);
    return !pQueue -> size;
}

/**
 * 入队
 * @param pQueue 队列指针
 * @param element 待加入的元素
 */
void hs_queueEnQueue(HS_Queue* pQueue, HS_ELEMENT_TYPE element)
{
    hs_queuePointerCheck(pQueue);
    hs_linkedListAdd(pQueue -> elements, element);
    ++(pQueue -> size);
}

/**
 * 出队
 * @param pQueue 队列指针
 * @return 返回队头元素
 */
HS_ELEMENT_TYPE hs_queueDeQueue(HS_Queue* pQueue)
{
    hs_queuePointerCheck(pQueue);
    HS_ELEMENT_TYPE element = hs_linkedListRemoveAtIndex(pQueue -> elements, 0);
    --(pQueue -> size);
    return element;
}

/**
 * 获取队头元素
 * @param pQueue 队列指针
 * @return 返回队头元素
 */
HS_ELEMENT_TYPE hs_queueFront(HS_Queue* pQueue)
{
    hs_queuePointerCheck(pQueue);
    return hs_linkedListGetOfIndex(pQueue -> elements, 0);
}

/**
 * 销毁队列
 * @param pQueue 队列指针
 */
void hs_queueFree(HS_Queue* pQueue)
{
    hs_queuePointerCheck(pQueue);
    if (!hs_queueIsEmpty(pQueue)) {
        hs_linkedListFree(pQueue -> elements);
    }
    free(pQueue);
}
