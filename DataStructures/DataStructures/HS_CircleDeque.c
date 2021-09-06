//
//  HS_CircleDeque.c
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/8.
//  Copyright © 2020 Shun. All rights reserved.
//

#include "HS_CircleDeque.h"

static const HS_QUEUE_SIZE HS_DEFAULT_CAPACITY = 10;

struct hs_array_CircleDeque {
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
    HS_ELEMENT_TYPE * elements;
    /**
     * 当前队列容量
     */
    HS_QUEUE_SIZE capacity;
    
};

void hs_circleDequePointerCheck(HS_CircleDeque* pQueue)
{
    assert(pQueue != NULL);
}

void hs_circleDequeEnsureCapacity(HS_CircleDeque* pQueue, HS_QUEUE_SIZE capacity)
{
    if (pQueue -> capacity >= capacity)
        return;
    
    //新容量为旧容量的1.5倍
    HS_QUEUE_SIZE oldCapacity = pQueue -> capacity;
    HS_QUEUE_SIZE addCapacity = oldCapacity >> 1;
    HS_QUEUE_SIZE newCapacity = oldCapacity + addCapacity;
    
    pQueue -> elements = (HS_ELEMENT_TYPE*) realloc(pQueue -> elements, newCapacity * sizeof(HS_ELEMENT_TYPE));
    memset(pQueue -> elements + oldCapacity, 0, addCapacity * sizeof(HS_ELEMENT_TYPE));
    if (pQueue -> front < addCapacity)
    {
        memmove(pQueue -> elements + oldCapacity, pQueue -> elements, pQueue -> front * sizeof(HS_ELEMENT_TYPE));
        memset(pQueue -> elements, 0, pQueue -> front * sizeof(HS_ELEMENT_TYPE));
    }
    else
    {
        memmove(pQueue -> elements + (addCapacity + pQueue -> front), pQueue -> elements + pQueue -> front, (oldCapacity - pQueue -> front) * sizeof(HS_ELEMENT_TYPE));
        memset(pQueue -> elements + pQueue -> front, 0, addCapacity * sizeof(HS_ELEMENT_TYPE));
        pQueue -> front += addCapacity;
    }
    
    pQueue -> capacity = newCapacity;
}

HS_QUEUE_INDEX hs_circleDequeGetIndex(HS_CircleDeque* pQueue, HS_QUEUE_INDEX index)
{
    index += pQueue -> front;
    index += (index < 0 ? (pQueue -> capacity) : 0);
    return index - (index >= pQueue -> capacity ? pQueue -> capacity: 0);
}

/**
 * 创建队列
 * @return 返回队列指针
 */
HS_CircleDeque* hs_circleDequeNew(void)
{
    HS_CircleDeque* pQueue = (HS_CircleDeque* )malloc(sizeof(HS_CircleDeque));
    if (pQueue)
    {
        pQueue -> capacity = HS_DEFAULT_CAPACITY;
        pQueue -> size = 0;
        pQueue -> front = 0;
        pQueue -> elements = (HS_ELEMENT_TYPE *) calloc(pQueue -> capacity, sizeof(HS_ELEMENT_TYPE));
    }
    return  pQueue;
}

/**
 * 清除所有元素
 * @param pQueue 队列指针
 */
void hs_circleDequeClear(HS_CircleDeque* pQueue)
{
    hs_circleDequePointerCheck(pQueue);
    if (pQueue -> size)
    {
        memset(pQueue -> elements , 0 , sizeof(HS_ELEMENT_TYPE) * pQueue -> capacity);
        pQueue -> size = 0;
        pQueue -> front = 0;
    }
}

/**
 * 返回队列元素的数量
 * @param pQueue 队列指针
 * @return 返回队列元素数
 */
HS_QUEUE_SIZE hs_circleDequeSize(HS_CircleDeque* pQueue)
{
    hs_circleDequePointerCheck(pQueue);
    return  pQueue -> size;
}

/**
 * 队列是否为空
 * @param pQueue 队列指针
 * @return 队列无元素返回true，否则返回false
 */
bool hs_circleDequeIsEmpty(HS_CircleDeque* pQueue)
{
    hs_circleDequePointerCheck(pQueue);
    return  !pQueue -> size;
}

/**
 * 队头入队
 * @param pQueue 队列指针
 * @param element 待加入的元素
 */
void hs_circleDequeEnQueueFront(HS_CircleDeque* pQueue, HS_ELEMENT_TYPE element)
{
    hs_circleDequePointerCheck(pQueue);
    hs_circleDequeEnsureCapacity(pQueue, pQueue -> size + 1);
    pQueue -> front = hs_circleDequeGetIndex(pQueue, -1);
    pQueue -> elements[pQueue -> front] = element;
    (pQueue -> size)++;
}

/**
 * 队头出队
 * @param pQueue 队列指针
 * @return 返回队头元素
 */
HS_ELEMENT_TYPE hs_circleDequeDeQueueFront(HS_CircleDeque* pQueue)
{
    hs_circleDequePointerCheck(pQueue);
    HS_ELEMENT_TYPE element = pQueue -> elements[pQueue -> front];
    memset(pQueue -> elements + pQueue -> front, 0, sizeof(HS_ELEMENT_TYPE));
    pQueue -> front = hs_circleDequeGetIndex(pQueue, 1);
    (pQueue -> size)--;
    return  element;
}

/**
 * 队尾入队
 * @param pQueue 队列指针
 * @param element 待加入的元素
 */
void hs_circleDequeEnQueueRear(HS_CircleDeque* pQueue, HS_ELEMENT_TYPE element)
{
    hs_circleDequePointerCheck(pQueue);
    hs_circleDequeEnsureCapacity(pQueue, pQueue -> size + 1);
    HS_QUEUE_INDEX realIndex = hs_circleDequeGetIndex(pQueue, pQueue -> size);
    pQueue -> elements[realIndex] = element;
    (pQueue -> size)++;
}

/**
 * 队尾出队
 * @param pQueue 队列指针
 * @return 返回队尾元素
 */
HS_ELEMENT_TYPE hs_circleDequeDeQueueRear(HS_CircleDeque* pQueue)
{
    hs_circleDequePointerCheck(pQueue);
    HS_QUEUE_INDEX rearIndex = hs_circleDequeGetIndex(pQueue, pQueue -> size - 1);
    HS_ELEMENT_TYPE element = pQueue -> elements[rearIndex];
    memset(pQueue -> elements + rearIndex, 0, sizeof(HS_ELEMENT_TYPE));
    (pQueue -> size)--;
    return element;
}

/**
 * 获取队头元素
 * @param pQueue 队列指针
 * @return 返回队头元素
 */
HS_ELEMENT_TYPE hs_circleDequeFront(HS_CircleDeque* pQueue)
{
    hs_circleDequePointerCheck(pQueue);
    return pQueue -> elements[pQueue -> front];
}

/**
 * 获取队尾元素
 * @param pQueue 队列指针
 * @return 返回队尾元素
 */
HS_ELEMENT_TYPE hs_circleDequeRear(HS_CircleDeque* pQueue)
{
    hs_circleDequePointerCheck(pQueue);
    HS_QUEUE_INDEX rearIndex = hs_circleDequeGetIndex(pQueue, pQueue -> size - 1);
    memset(pQueue -> elements + rearIndex, 0, sizeof(HS_ELEMENT_TYPE));
    (pQueue -> size)--;
    return pQueue -> elements[rearIndex];
}

/**
 * 销毁队列
 * @param pQueue 队列指针
 */
void hs_circleDequeFree(HS_CircleDeque* pQueue)
{
    hs_circleDequePointerCheck(pQueue);
    if (pQueue -> elements) {
        free(pQueue -> elements);
    }
    free(pQueue);
}


void hs_deque_print(HS_CircleDeque* pQueue)
{
    hs_circleDequePointerCheck(pQueue);
    for (int i = 0; i < pQueue -> capacity; ++i) {
        printf("%d ", pQueue -> elements[i]);
    }
    printf("\n");
}

