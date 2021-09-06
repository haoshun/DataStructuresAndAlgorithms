//
//  HS_Deque.h
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/6.
//

#ifndef HS_Deque_h
#define HS_Deque_h

#include <stdio.h>
#include<stdbool.h>
#include "HS_Define.h"

//#ifndef HS_ELEMENT_TYPE
//typedef int HS_ELEMENT_TYPE;
//#endif

typedef struct hs_arrayDeque HS_Deque;

/**
 * 创建双端队列
 * @return 返回双端队列指针
 */
HS_Deque* hs_dequeNew(void);

/**
 * 返回双端队列元素的数量
 * @param pDeque 双端队列指针
 * @return 返回双端队列元素数
 */
HS_QUEUE_SIZE hs_dequeSize(HS_Deque* pDeque);

/**
 * 双端队列是否为空
 * @param pDeque 队列指针
 * @return 队列无元素返回true，否则返回false
 */
bool hs_dequeIsEmpty(HS_Deque* pDeque);

/**
 * 清除所有元素
 * @param pDeque 队列指针
 */
void hs_dequeClear(HS_Deque* pDeque);

/**
 * 队尾入队
 * @param pDeque 双端队列指针
 * @param element 待加入的元素
 */
void hs_dequeEnQueueRear(HS_Deque* pDeque, HS_ELEMENT_TYPE element);

/**
 * 队头出队
 * @param pDeque 队列指针
 * @return 返回队头元素
 */
HS_ELEMENT_TYPE hs_dequeDeQueueFront(HS_Deque* pDeque);

/**
 * 队头入队
 * @param pDeque 双端队列指针
 * @param element 待加入的元素
 */
void hs_dequeEnQueueFront(HS_Deque* pDeque, HS_ELEMENT_TYPE element);

/**
 * 队尾出队
 * @param pDeque 队列指针
 * @return 返回队头元素
 */
HS_ELEMENT_TYPE hs_dequeDeQueueRear(HS_Deque* pDeque);

/**
 * 获取队头元素
 * @param pDeque 队列指针
 * @return 返回队头元素
 */
HS_ELEMENT_TYPE hs_dequeFront(HS_Deque* pDeque);

/**
 * 获取队尾元素
 * @param pDeque 队列指针
 * @return 返回队头元素
 */
HS_ELEMENT_TYPE hs_dequeRear(HS_Deque* pDeque);

/**
 * 销毁双端队列
 * @param pDeque 队列指针
 */
void hs_dequeFree(HS_Deque* pDeque);


#endif /* HS_Deque_h */
