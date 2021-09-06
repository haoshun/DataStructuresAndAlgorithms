//
//  HS_MinHeap.h
//  Graph
//
//  Created by 郝源顺 on 2021/1/20.
//

#ifndef HS_MinHeap_h
#define HS_MinHeap_h

#include <stdio.h>
#include "HS_Define.h"

typedef unsigned int HS_HEAP_SIZE;
typedef HS_HEAP_SIZE HS_HEAP_INDEX;

typedef struct hs_dist_node{
    HS_GRAPH_INDEX f_index;
    HS_GRAPH_INDEX g_index;
    HS_DISTANCE dist;
}HS_DNode ;

typedef HS_DNode HS_HEAP_ELEMENT;

typedef struct hs_min_heap HS_MinHeap;



/**
 * 创建小顶堆
 * @return 返回堆指针
 */
HS_MinHeap* hs_minHeapNew(void);

/**
 * 小顶堆是否为空
 * @param pHeap 堆指针
 * @return 若为空 返回true，否则false
 */
bool hs_minHeapIsEmpty(HS_MinHeap* pHeap);

/**
 * 向小顶堆添加元素
 * @param pHeap 树指针
 * @param element 待添加元素
 */
void hs_minHeapAdd(HS_MinHeap* pHeap, HS_HEAP_ELEMENT element);

/**
 * 获取二叉堆中堆顶元素
 * @param pHeap 堆指针
 */
HS_HEAP_ELEMENT hs_minHeapGet(HS_MinHeap* pHeap);

/**
 * 删除小顶堆堆顶元素
 * @param pHeap 堆指针
 * @return 删除的元素
 */
HS_HEAP_ELEMENT hs_minHeapRemove(HS_MinHeap* pHeap);

/**
 * 删除小顶堆堆顶元素
 * @param pHeap 堆指针
 * @param element 删除的元素
 */
void hs_minHeapUpdate(HS_MinHeap* pHeap, HS_HEAP_ELEMENT element);

#endif /* HS_MinHeap_h */
