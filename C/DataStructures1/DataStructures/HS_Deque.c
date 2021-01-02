//
//  HS_Deque.c
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/8.
//  Copyright © 2020 Shun. All rights reserved.
//

#include "HS_Deque.h"
#include "HS_LinkedList.h"

struct hs_linkedListDeque {
    /**
    * 所有的元素
    */
    HS_LinkedList * elements;
    /**
     * 队列内元素的数量
     */
    HS_QUEUE_SIZE size;
   
};

void hs_dequePointerCheck(HS_Deque* pDeque)
{
    assert(pDeque != NULL);
}

/**
 * 创建双端队列
 * @return 返回双端队列指针
 */
HS_Deque* hs_dequeNew(void)
{
    HS_Deque* pDeque = (HS_Deque*)malloc(sizeof(HS_Deque));
    if (pDeque)
    {
        pDeque -> elements = hs_linkedListNew();
        pDeque -> size = 0;
    }
    return pDeque;
}

/**
 * 返回双端队列元素的数量
 * @param pDeque 双端队列指针
 * @return 返回双端队列元素数
 */
HS_QUEUE_SIZE hs_dequeSize(HS_Deque* pDeque)
{
    hs_dequePointerCheck(pDeque);
    return pDeque -> size;
}

/**
 * 双端队列是否为空
 * @param pDeque 队列指针
 * @return 队列无元素返回true，否则返回false
 */
bool hs_dequeIsEmpty(HS_Deque* pDeque)
{
    hs_dequePointerCheck(pDeque);
    return !pDeque -> size;
}

/**
 * 清除所有元素
 * @param pDeque 队列指针
 */
void hs_dequeClear(HS_Deque* pDeque)
{
    hs_dequePointerCheck(pDeque);
    if (pDeque -> size)
    {
        hs_linkedListClear(pDeque -> elements);
        pDeque -> size = 0;
    }
}

/**
 * 队尾入队
 * @param pDeque 双端队列指针
 * @param element 待加入的元素
 */
void hs_dequeEnQueueRear(HS_Deque* pDeque, HS_ELEMENT_TYPE element)
{
    hs_dequePointerCheck(pDeque);
    hs_linkedListAdd(pDeque -> elements, element);
    ++(pDeque -> size);
}

/**
 * 队头出队
 * @param pDeque 队列指针
 * @return 返回队头元素
 */
HS_ELEMENT_TYPE hs_dequeDeQueueFront(HS_Deque* pDeque)
{
    hs_dequePointerCheck(pDeque);
    HS_ELEMENT_TYPE element = hs_linkedListRemoveAtIndex(pDeque -> elements, 0);
    --(pDeque -> size);
    return element;
}

/**
 * 队头入队
 * @param pDeque 双端队列指针
 * @param element 待加入的元素
 */
void hs_dequeEnQueueFront(HS_Deque* pDeque, HS_ELEMENT_TYPE element)
{
    hs_dequePointerCheck(pDeque);
    hs_linkedListAddToIndex(pDeque -> elements, element, 0);
    ++(pDeque -> size);
}

/**
 * 队尾出队
 * @param pDeque 队列指针
 * @return 返回队头元素
 */
HS_ELEMENT_TYPE hs_dequeDeQueueRear(HS_Deque* pDeque)
{
    hs_dequePointerCheck(pDeque);
    return hs_linkedListRemoveAtIndex(pDeque -> elements, --(pDeque-> size));
}

/**
 * 获取队头元素
 * @param pDeque 队列指针
 * @return 返回队头元素
 */
HS_ELEMENT_TYPE hs_dequeFront(HS_Deque* pDeque)
{
    hs_dequePointerCheck(pDeque);
    return hs_linkedListGetOfIndex(pDeque -> elements, 0);
}

/**
 * 获取队尾元素
 * @param pDeque 队列指针
 * @return 返回队尾元素
 */
HS_ELEMENT_TYPE hs_dequeRear(HS_Deque* pDeque)
{
    hs_dequePointerCheck(pDeque);
    return hs_linkedListGetOfIndex(pDeque -> elements, pDeque -> size - 1);
}

/**
 * 销毁双端队列
 * @param pDeque 队列指针
 */
void hs_dequeFree(HS_Deque* pDeque)
{
    hs_dequePointerCheck(pDeque);
    if (!hs_dequeIsEmpty(pDeque)) {
        hs_linkedListFree(pDeque -> elements);
    }
    free(pDeque);
}
