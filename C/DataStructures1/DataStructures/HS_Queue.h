//
//  HS_Queue.h
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/8.
//  Copyright © 2020 Shun. All rights reserved.
//

#ifndef HS_Queue_h
#define HS_Queue_h

#include <stdio.h>
#include<stdbool.h>

#ifndef HS_ELEMENT_TYPE
typedef int HS_ELEMENT_TYPE;
#endif

typedef unsigned long HS_QUEUE_SIZE;
typedef struct hs_linkedListQueue HS_Queue;

/**
 * 创建队列
 * @return 返回队列指针
 */
HS_Queue* hs_queueNew(void);

/**
 * 清除所有元素
 * @param pQueue 队列指针
 */
void hs_queueClear(HS_Queue* pQueue);

/**
 * 返回队列元素的数量
 * @param pQueue 队列指针
 * @return 返回队列元素数
 */
HS_QUEUE_SIZE hs_queueSize(HS_Queue* pQueue);

/**
 * 队列是否为空
 * @param pQueue 队列指针
 * @return 队列无元素返回true，否则返回false
 */
bool hs_queueIsEmpty(HS_Queue* pQueue);

/**
 * 入队
 * @param pQueue 队列指针
 * @param element 待加入的元素
 */
void hs_queueEnQueue(HS_Queue* pQueue, HS_ELEMENT_TYPE element);

/**
 * 出队
 * @param pQueue 队列指针
 * @return 返回队头元素
 */
HS_ELEMENT_TYPE hs_queueDeQueue(HS_Queue* pQueue);

/**
 * 获取队头元素
 * @param pQueue 队列指针
 * @return 返回队头元素
 */
HS_ELEMENT_TYPE hs_queueFront(HS_Queue* pQueue);

/**
 * 销毁队列
 * @param pQueue 队列指针
 */
void hs_queueFree(HS_Queue* pQueue);

#endif /* HS_Queue_h */
