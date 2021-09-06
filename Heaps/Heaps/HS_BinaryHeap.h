//
//  HS_BinaryHeap.h
//  Heaps
//
//  Created by 郝源顺 on 2021/1/2.
//

#ifndef HS_BinaryHeap_h
#define HS_BinaryHeap_h

#include <stdio.h>
#include "HS_Define.h"



typedef struct hs_binary_heap HS_BinaryHeap;

/**
 * 创建二叉堆
 * @return 返回堆指针
 */
HS_BinaryHeap* hs_binaryHeapNew(void);

/**
 * 创建二叉堆，指定堆的容量
 * @param capacity 堆容量
 * @return 返回堆指针
 */
HS_BinaryHeap* hs_binaryHeapNewWithCapacity(HS_HEAP_SIZE capacity);

/**
 * 根据数组创建二叉堆
 * @param elements 元素数组
 * @param elementSize 数组长度
 * @return 返回堆指针
 */
HS_BinaryHeap* hs_binaryHeapNewWithElements(HS_ELEMENT_TYPE* elements, HS_HEAP_SIZE elementSize);

/**
 * 二叉堆是否为空
 * @param pHeap 堆指针
 * @return 若为空 返回true，否则false
 */
bool hs_binaryHeapIsEmpty(HS_BinaryHeap* pHeap);

/**
 * 清除二叉堆所有元素
 * @param pHeap 堆指针
 */
void hs_binaryHeapClear(HS_BinaryHeap* pHeap);

/**
 * 获取二叉堆元素的数量
 * @param pHeap 堆指针
 * @return 返回堆元素数
 */
HS_HEAP_SIZE hs_binaryHeapSize(HS_BinaryHeap* pHeap);

/**
 * 向二叉堆添加元素
 * @param pHeap 树指针
 * @param element 待添加元素
 */
void hs_binaryHeapAdd(HS_BinaryHeap* pHeap, HS_ELEMENT_TYPE element);

/**
 * 获取二叉堆中堆顶元素
 * @param pHeap 堆指针
 */
HS_ELEMENT_TYPE hs_binaryHeapGet(HS_BinaryHeap* pHeap);

/**
 * 删除二叉堆堆顶元素
 * @param pHeap 堆指针
 * @return 删除的元素
 */
HS_ELEMENT_TYPE hs_binaryHeapRemove(HS_BinaryHeap* pHeap);



#endif /* HS_BinaryHeap_h */
