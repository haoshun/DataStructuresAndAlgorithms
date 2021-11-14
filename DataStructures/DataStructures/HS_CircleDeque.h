//
//  HS_CircleDeque.h
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/8.
//  Copyright © 2020 Shun. All rights reserved.
//

#ifndef HS_CircleDeque_h
#define HS_CircleDeque_h

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "HS_Define.h"

//#ifndef HS_ELEMENT_TYPE
//typedef int HS_ELEMENT_TYPE;
//#endif


typedef struct hs_array_CircleDeque HS_CircleDeque;

/**
 * 创建队列
 * @return 返回队列指针
 */
HS_CircleDeque* hs_circleDequeNew(void);

/**
 * 清除所有元素
 * @param pQueue 队列指针
 */
void hs_circleDequeClear(HS_CircleDeque* pQueue);

/**
 * 返回队列元素的数量
 * @param pQueue 队列指针
 * @return 返回队列元素数
 */
HS_QUEUE_SIZE hs_circleDequeSize(HS_CircleDeque* pQueue);

/**
 * 队列是否为空
 * @param pQueue 队列指针
 * @return 队列无元素返回true，否则返回false
 */
bool hs_circleDequeIsEmpty(HS_CircleDeque* pQueue);

/**
 * 队头入队
 * @param pQueue 队列指针
 * @param element 待加入的元素
 */
void hs_circleDequeEnQueueFront(HS_CircleDeque* pQueue, HS_ELEMENT_TYPE element);

/**
 * 队头出队
 * @param pQueue 队列指针
 * @return 返回队头元素
 */
HS_ELEMENT_TYPE hs_circleDequeDeQueueFront(HS_CircleDeque* pQueue);

/**
 * 队尾入队
 * @param pQueue 队列指针
 * @param element 待加入的元素
 */
void hs_circleDequeEnQueueRear(HS_CircleDeque* pQueue, HS_ELEMENT_TYPE element);

/**
 * 队尾出队
 * @param pQueue 队列指针
 * @return 返回队头元素
 */
HS_ELEMENT_TYPE hs_circleDequeDeQueueRear(HS_CircleDeque* pQueue);

/**
 * 获取队头元素
 * @param pQueue 队列指针
 * @return 返回队头元素
 */
HS_ELEMENT_TYPE hs_circleDequeFront(HS_CircleDeque* pQueue);

/**
 * 获取队尾元素
 * @param pQueue 队列指针
 * @return 返回队尾元素
 */
HS_ELEMENT_TYPE hs_circleDequeRear(HS_CircleDeque* pQueue);

/**
 * 销毁队列
 * @param pQueue 队列指针
 */
void hs_circleDequeFree(HS_CircleDeque* pQueue);


void hs_deque_print(HS_CircleDeque* pQueue);


void  test(int n);

#endif /* HS_CircleDeque_h */
