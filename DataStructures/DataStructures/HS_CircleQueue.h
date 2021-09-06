//
//  HS_CircleQueue.h
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/8.
//  Copyright © 2020 Shun. All rights reserved.
//

#ifndef HS_CircleQueue_h
#define HS_CircleQueue_h

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include<stdlib.h>
#include <string.h>
#include "HS_Define.h"

//#ifndef HS_CQUEUE_ELEMENT_TYPE
//typedef int HS_CQUEUE_ELEMENT_TYPE;
//#endif

typedef struct hs_array_CircleQueue HS_CircleQueue;


/**
 * 创建队列
 * @return 返回队列指针
 */
HS_CircleQueue* hs_circleQueueNew(void);

/**
 * 清除所有元素
 * @param pQueue 队列指针
 */
void hs_circleQueueClear(HS_CircleQueue* pQueue);

/**
 * 返回队列元素的数量
 * @param pQueue 队列指针
 * @return 返回队列元素数
 */
HS_QUEUE_SIZE hs_circleQueueSize(HS_CircleQueue* pQueue);

/**
 * 队列是否为空
 * @param pQueue 队列指针
 * @return 队列无元素返回true，否则返回false
 */
bool hs_circleQueueIsEmpty(HS_CircleQueue* pQueue);

/**
 * 入队
 * @param pQueue 队列指针
 * @param element 待加入的元素
 */
void hs_circleQueueEnQueue(HS_CircleQueue* pQueue, HS_CQUEUE_ELEMENT_TYPE element);

/**
 * 出队
 * @param pQueue 队列指针
 * @return 返回队头元素
 */
HS_CQUEUE_ELEMENT_TYPE hs_circleQueueDeQueue(HS_CircleQueue* pQueue);

/**
 * 获取队头元素
 * @param pQueue 队列指针
 * @return 返回队头元素
 */
HS_CQUEUE_ELEMENT_TYPE hs_circleQueueFront(HS_CircleQueue* pQueue);

/**
 * 销毁队列
 * @param pQueue 队列指针
 */
void hs_circleQueueFree(HS_CircleQueue* pQueue);


void hs_print(HS_CircleQueue* pQueue);


#endif /* HS_CircleQueue_h */
