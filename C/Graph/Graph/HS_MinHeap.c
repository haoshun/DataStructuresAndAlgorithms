//
//  HS_MinHeap.c
//  Graph
//
//  Created by 郝源顺 on 2021/1/20.
//

#include "HS_MinHeap.h"

static const HS_HEAP_SIZE HS_DEFAULT_CAPACITY = 10;

struct hs_min_heap {
    /**
    * 所有的元素
    */
    HS_HEAP_ELEMENT * elements;
    /**
     * 堆元素数量
     */
    HS_HEAP_SIZE size;
    /**
     * 当前堆容量
     */
    HS_HEAP_SIZE capacity;
};

//void hs_assign(HS_HEAP_ELEMENT* dest, HS_HEAP_ELEMENT* src)
//{
//    dest -> g_index = src -> g_index;
//    dest -> dist = src -> dist;
//}

void hs_minHeapPointerCheck(HS_MinHeap* pHeap)
{
    assert(pHeap != NULL);
}

void hs_minHeapEmptyCheck(HS_MinHeap* pHeap)
{
    assert(!hs_minHeapIsEmpty(pHeap));
}

void hs_ensureCapacity(HS_MinHeap* pQueue, HS_HEAP_SIZE capacity)
{
    if(pQueue -> capacity >= capacity + 1)
        return;
    
    HS_HEAP_SIZE oldCapacity = pQueue -> capacity;
    HS_HEAP_SIZE addCapacity = oldCapacity >> 1;
    
    pQueue -> capacity = oldCapacity + addCapacity;
    pQueue -> elements = (HS_HEAP_ELEMENT*) realloc(pQueue -> elements, sizeof(HS_HEAP_ELEMENT) * pQueue -> capacity);
    memset(pQueue -> elements + oldCapacity, 0, addCapacity * sizeof(HS_HEAP_ELEMENT));
}

//上滤
void siftUp(HS_HEAP_ELEMENT* elements, HS_HEAP_INDEX index)
{
    //采用赋值而不交换值
    HS_HEAP_ELEMENT element = elements[index];
    
    for (HS_HEAP_INDEX parent = index >> 1;
         parent > 0 && elements[parent].dist > element.dist;
         index = parent, parent >>= 1)
        elements[index] = elements[parent];
    
    elements[index] = element;
}

//下滤
void siftDown(HS_HEAP_ELEMENT* elements, HS_HEAP_SIZE elementSize, HS_HEAP_INDEX index)
{
    //采用赋值而不交换值
    HS_HEAP_ELEMENT element = elements[index];
    
    for (HS_HEAP_INDEX minIndex = index, child;
         index > 0 && index <= elementSize;
         index = minIndex)
    {
        child = index << 1;
        if(child <= elementSize && elements[child].dist < element.dist)
            minIndex = child;
        if(child + 1 <= elementSize && elements[child + 1].dist < (minIndex != index ? elements[minIndex].dist: element.dist))
            minIndex = child + 1;
        if (minIndex == index)
        {
            elements[index] = element;
            break;
        }
        else
            elements[index] = elements[minIndex];
    }
}


//HS_HEAP_ELEMENT* hs_heapify(HS_HEAP_ELEMENT* elements, HS_HEAP_SIZE elementSize)
//{
//    //自底向上建堆（自下而上的下滤）O(n)
//    for (HS_HEAP_INDEX i = elementSize / 2; i >= 1; --i)
//        siftDown(elements, elementSize, i);
//
//    return elements;
//}


/**
 * 创建小顶堆，指定堆的容量
 * @param capacity 堆容量
 * @return 返回堆指针
 */
HS_MinHeap* hs_minHeapNewWithCapacity(HS_HEAP_SIZE capacity)
{
    HS_MinHeap* pHeap = (HS_MinHeap*)malloc(sizeof(HS_MinHeap));
    if (pHeap)
    {
        pHeap -> size = 0;
        pHeap -> capacity = (capacity > HS_DEFAULT_CAPACITY ? capacity: HS_DEFAULT_CAPACITY) + 1;
        pHeap -> elements = (HS_HEAP_ELEMENT*)calloc(pHeap -> capacity, sizeof(HS_HEAP_ELEMENT));
    }
    return pHeap;
}

/**
 * 创建小顶堆
 * @return 返回堆指针
 */
HS_MinHeap* hs_minHeapNew(void)
{
    return hs_minHeapNewWithCapacity(HS_DEFAULT_CAPACITY);
}




/**
 * 小顶堆是否为空
 * @param pHeap 堆指针
 * @return 若为空 返回true，否则false
 */
bool hs_minHeapIsEmpty(HS_MinHeap* pHeap)
{
    return !(pHeap && pHeap -> size);
}

/**
 * 向小顶堆添加元素
 * @param pHeap 树指针
 * @param element 待添加元素
 */
void hs_minHeapAdd(HS_MinHeap* pHeap, HS_HEAP_ELEMENT element)
{
    hs_minHeapPointerCheck(pHeap);
    hs_ensureCapacity(pHeap, pHeap -> size + 1);
    
    HS_HEAP_INDEX rear = pHeap -> size + 1;
    pHeap -> elements[rear] = element;
    siftUp(pHeap -> elements, rear);
    pHeap -> size++;
}

/**
 * 获取二叉堆中堆顶元素
 * @param pHeap 堆指针
 */
HS_HEAP_ELEMENT hs_minHeapGet(HS_MinHeap* pHeap)
{
    hs_minHeapEmptyCheck(pHeap);

    return pHeap -> elements[1];
}

/**
 * 删除二叉堆堆顶元素
 * @param pHeap 堆指针
 * @return 删除的元素
 */
HS_HEAP_ELEMENT hs_minHeapRemove(HS_MinHeap* pHeap)
{
    hs_minHeapEmptyCheck(pHeap);
    
    HS_HEAP_ELEMENT heapTop = hs_minHeapGet(pHeap), replaceElement = pHeap -> elements[pHeap -> size];
    pHeap -> elements[1] = replaceElement;
    memset(pHeap -> elements + pHeap -> size, 0, sizeof(HS_HEAP_ELEMENT));
    pHeap -> size--;
    
    siftDown(pHeap -> elements, pHeap -> size, 1);
    return heapTop;
}


void hs_minHeapUpdate(HS_MinHeap* pHeap, HS_HEAP_ELEMENT element)
{
    hs_minHeapEmptyCheck(pHeap);
    
    HS_HEAP_INDEX target = 1;
    for (; target <= pHeap -> size &&  pHeap -> elements[target].g_index != element.g_index; ++target) ;
    
    pHeap -> elements[target] = element;
    siftUp(pHeap -> elements, target);
}
