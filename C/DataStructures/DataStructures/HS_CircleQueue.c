//
//  HS_CircleQueue.c
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/8.
//  Copyright © 2020 Shun. All rights reserved.
//

#include "HS_CircleQueue.h"

static const HS_QUEUE_SIZE HS_DEFAULT_CAPACITY = 10;

struct hs_array_CircleQueue {
    /**
     * 元素的数量
     */
    HS_QUEUE_SIZE size;
    /**
     * 队头索引
     */
    HS_QUEUE_INDEX front;
    /**
    * 所有的元素
    */
    HS_CQUEUE_ELEMENT_TYPE * elements;
    /**
     * 当前队列容量
     */
    HS_QUEUE_SIZE capacity;
    
};

void hs_circleQueuePointerCheck(HS_CircleQueue* pQueue)
{
    assert(pQueue != NULL);
}

void hs_circleQueueEnsureCapacity(HS_CircleQueue* pQueue, HS_QUEUE_SIZE capacity)
{
    if (pQueue -> capacity >= capacity)
        return;
    
    //新容量为旧容量的1.5倍
    HS_QUEUE_SIZE oldCapacity = pQueue -> capacity;
    HS_QUEUE_SIZE addCapacity = oldCapacity >> 1;
    HS_QUEUE_SIZE newCapacity = oldCapacity + addCapacity;
    
    pQueue -> elements = (HS_CQUEUE_ELEMENT_TYPE*) realloc(pQueue -> elements, newCapacity * sizeof(HS_CQUEUE_ELEMENT_TYPE));
    memset(pQueue -> elements + oldCapacity, 0, addCapacity * sizeof(HS_CQUEUE_ELEMENT_TYPE));
    if (pQueue -> front < addCapacity)
    {
        memmove(pQueue -> elements + oldCapacity, pQueue -> elements, pQueue -> front * sizeof(HS_CQUEUE_ELEMENT_TYPE));
        memset(pQueue -> elements, 0, pQueue -> front * sizeof(HS_CQUEUE_ELEMENT_TYPE));
    }
    else
    {
        memmove(pQueue -> elements + (addCapacity + pQueue -> front), pQueue -> elements + pQueue -> front, (oldCapacity - pQueue -> front) * sizeof(HS_CQUEUE_ELEMENT_TYPE));
        memset(pQueue -> elements + pQueue -> front, 0, addCapacity * sizeof(HS_CQUEUE_ELEMENT_TYPE));
        pQueue -> front += addCapacity;
    }
    
    pQueue -> capacity = newCapacity;
}

HS_QUEUE_INDEX hs_circleQueueGetIndex(HS_CircleQueue* pQueue, HS_QUEUE_INDEX index)
{
    index += pQueue -> front;
    return index - (index >= pQueue -> capacity ? pQueue -> capacity: 0);
}

/**
 * 创建队列
 * @return 返回队列指针
 */
HS_CircleQueue* hs_circleQueueNew(void)
{
    HS_CircleQueue* pQueue = (HS_CircleQueue* )malloc(sizeof(HS_CircleQueue));
    if (pQueue)
    {
        pQueue -> capacity = HS_DEFAULT_CAPACITY;
        pQueue -> size = 0;
        pQueue -> front = 0;
        pQueue -> elements = (HS_CQUEUE_ELEMENT_TYPE *) calloc(pQueue -> capacity, sizeof(HS_CQUEUE_ELEMENT_TYPE));
    }
    return  pQueue;
}

/**
 * 清除所有元素
 * @param pQueue 队列指针
 */
void hs_circleQueueClear(HS_CircleQueue* pQueue)
{
    hs_circleQueuePointerCheck(pQueue);
    if (pQueue -> size)
    {
        memset(pQueue -> elements , 0 , sizeof(HS_CQUEUE_ELEMENT_TYPE) * pQueue -> capacity);
        pQueue -> size = 0;
        pQueue -> front = 0;
    }
}

/**
 * 返回队列元素的数量
 * @param pQueue 队列指针
 * @return 返回队列元素数
 */
HS_QUEUE_SIZE hs_circleQueueSize(HS_CircleQueue* pQueue)
{
    hs_circleQueuePointerCheck(pQueue);
    return pQueue -> size;
}


/**
 * 队列是否为空
 * @param pQueue 队列指针
 * @return 队列无元素返回true，否则返回false
 */
bool hs_circleQueueIsEmpty(HS_CircleQueue* pQueue)
{
    hs_circleQueuePointerCheck(pQueue);
    return !pQueue -> size;
}

/**
 * 入队
 * @param pQueue 队列指针
 * @param element 待加入的元素
 */
void hs_circleQueueEnQueue(HS_CircleQueue* pQueue, HS_CQUEUE_ELEMENT_TYPE element)
{
    hs_circleQueuePointerCheck(pQueue);
    hs_circleQueueEnsureCapacity(pQueue, pQueue -> size + 1);
    HS_QUEUE_INDEX realIndex = hs_circleQueueGetIndex(pQueue, pQueue -> size);
    pQueue -> elements[realIndex] = element;
    (pQueue -> size)++;
}

/**
 * 出队
 * @param pQueue 队列指针
 * @return 返回队头元素
 */
HS_CQUEUE_ELEMENT_TYPE hs_circleQueueDeQueue(HS_CircleQueue* pQueue)
{
    hs_circleQueuePointerCheck(pQueue);
    HS_CQUEUE_ELEMENT_TYPE element = pQueue -> elements[pQueue -> front];
    memset(pQueue -> elements + pQueue -> front, 0, sizeof(HS_CQUEUE_ELEMENT_TYPE));
    pQueue -> front = hs_circleQueueGetIndex(pQueue, 1);
    (pQueue -> size)--;
    return  element;
}

/**
 * 获取队头元素
 * @param pQueue 队列指针
 * @return 返回队头元素
 */
HS_CQUEUE_ELEMENT_TYPE hs_circleQueueFront(HS_CircleQueue* pQueue)
{
    hs_circleQueuePointerCheck(pQueue);
    return pQueue -> elements[pQueue -> front];
}

/**
 * 销毁队列
 * @param pQueue 队列指针
 */
void hs_circleQueueFree(HS_CircleQueue* pQueue)
{
    hs_circleQueuePointerCheck(pQueue);
    if (pQueue -> elements) {
        free(pQueue -> elements);
    }
    free(pQueue);
}


void hs_print(HS_CircleQueue* pQueue)
{
    hs_circleQueuePointerCheck(pQueue);
    for (int i = 0; i < pQueue -> capacity; ++i) {
        printf("%d ", pQueue -> elements[i]);
    }
    printf("\n");
}
