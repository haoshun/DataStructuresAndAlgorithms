//
//  HS_BinaryHeap.c
//  Heaps
//
//  Created by 郝源顺 on 2021/1/2.
//

#include "HS_BinaryHeap.h"

//#define TOP_DOWN
#define UNSWAP

static const HS_HEAP_SIZE HS_DEFAULT_CAPACITY = 10;

struct hs_binary_heap {
    /**
    * 所有的元素
    */
    HS_ELEMENT_TYPE * elements;
    /**
     * 堆元素数量
     */
    HS_HEAP_SIZE size;
    /**
     * 当前堆容量
     */
    HS_HEAP_SIZE capacity;
};


void hs_binaryHeapPointerCheck(HS_BinaryHeap* pHeap)
{
    assert(pHeap != NULL);
}

void hs_binaryHeapEmptyCheck(HS_BinaryHeap* pHeap)
{
    assert(!hs_binaryHeapIsEmpty(pHeap));
}

void hs_ensureCapacity(HS_BinaryHeap* pQueue, HS_HEAP_SIZE capacity)
{
    if(pQueue -> capacity >= capacity + 1)
        return;
    
    HS_HEAP_SIZE oldCapacity = pQueue -> capacity;
    HS_HEAP_SIZE addCapacity = oldCapacity >> 1;
    
    pQueue -> capacity = oldCapacity + addCapacity;
    pQueue -> elements = (HS_ELEMENT_TYPE*) realloc(pQueue -> elements, sizeof(HS_ELEMENT_TYPE) * pQueue -> capacity);
    memset(pQueue -> elements + oldCapacity, 0, addCapacity * sizeof(HS_ELEMENT_TYPE));
}

//上滤
void siftUp(HS_ELEMENT_TYPE* elements, HS_HEAP_INDEX index)
{
#ifdef UNSWAP
    //采用赋值而不交换值
    HS_ELEMENT_TYPE element = elements[index];
    
    for (HS_HEAP_INDEX parent = index >> 1;
         parent > 0 && elements[parent] < element;
         index = parent, parent >>= 1)
        elements[index] = elements[parent];
    
    elements[index] = element;

#else
    
    HS_HEAP_INDEX parent = index >> 1;
    while (parent)
    {
        if(elements[parent] < elements[index])
            hs_swap(elements + parent, elements + index);
        index = parent;
        parent = index >> 1;
    }
    
#endif
}

//下滤
void siftDown(HS_ELEMENT_TYPE* elements, HS_HEAP_SIZE elementSize, HS_HEAP_INDEX index)
{
#ifdef UNSWAP
    //采用赋值而不交换值
    HS_ELEMENT_TYPE element = elements[index];
    
    for (HS_HEAP_INDEX maxIndex = index, child;
         index > 0 && index <= elementSize;
         index = maxIndex)
    {
        child = index << 1;
        if(child <= elementSize && elements[child] > element)
            maxIndex = child;
        if(child + 1 <= elementSize && elements[child + 1] > (maxIndex != index ? elements[maxIndex]: element))
            maxIndex = child + 1;
        if (maxIndex == index)
        {
            elements[index] = element;
            break;
        }
        else
            elements[index] = elements[maxIndex];
    }
#else
    
    HS_HEAP_INDEX maxIndex = index, child;
    while (index <= elementSize)
    {
        child = index << 1;
        if(child <= elementSize && elements[child] > elements[index])
            maxIndex = child;
        if(child + 1 <= elementSize && elements[child + 1] > elements[maxIndex])
            maxIndex = child + 1;
        if (maxIndex == index)
            break;
        hs_swap(elements + index, elements + maxIndex);
        index = maxIndex;
    }
#endif
    
}


HS_ELEMENT_TYPE* hs_heapify(HS_ELEMENT_TYPE* elements, HS_HEAP_SIZE elementSize)
{
    
#ifdef TOP_DOWN
    
    //自顶向下建堆（自上而下的上滤）O(nlog(n))
    for(HS_HEAP_INDEX i = 1; i <= elementSize; ++i)
        siftUp(elements, i);
    
#else
    
    //自底向上建堆（自下而上的下滤）O(n)
    for (HS_HEAP_INDEX i = elementSize / 2; i >= 1; --i)
        siftDown(elements, elementSize, i);
    
#endif

    return elements;
}

/**
 * 创建二叉堆
 * @return 返回堆指针
 */
HS_BinaryHeap* hs_binaryHeapNew(void)
{
    return hs_binaryHeapNewWithCapacity(HS_DEFAULT_CAPACITY);
}

/**
 * 创建二叉堆，指定堆的容量
 * @param capacity 堆容量
 * @return 返回堆指针
 */
HS_BinaryHeap* hs_binaryHeapNewWithCapacity(HS_HEAP_SIZE capacity)
{
    HS_BinaryHeap* pHeap = (HS_BinaryHeap*)malloc(sizeof(HS_BinaryHeap));
    if (pHeap)
    {
        pHeap -> size = 0;
        pHeap -> capacity = (capacity > HS_DEFAULT_CAPACITY ? capacity: HS_DEFAULT_CAPACITY) + 1;
        pHeap -> elements = (HS_ELEMENT_TYPE*)calloc(pHeap -> capacity, sizeof(HS_ELEMENT_TYPE));
    }
    return pHeap;
}

/**
 * 根据数组创建二叉堆
 * 这里对输入数组进行了深拷贝
 * @param elements 元素数组
 * @param elementSize 数组长度
 * @return 返回堆指针
 */
HS_BinaryHeap* hs_binaryHeapNewWithElements(HS_ELEMENT_TYPE* elements, HS_HEAP_SIZE elementSize)
{
    assert(elements && elementSize);
    HS_BinaryHeap* pHeap = hs_binaryHeapNewWithCapacity(elementSize);
    if (pHeap)
    {
        memcpy(pHeap -> elements + 1, elements, sizeof(HS_ELEMENT_TYPE) * elementSize);
        pHeap -> size = elementSize;
        hs_heapify(pHeap -> elements, pHeap -> size);
    }
    return pHeap;
}

/**
 * 二叉堆是否为空
 * @param pHeap 堆指针
 * @return 若为空 返回true，否则false
 */
bool hs_binaryHeapIsEmpty(HS_BinaryHeap* pHeap)
{
    return !(pHeap && pHeap -> size);
}

/**
 * 清除二叉堆所有元素
 * @param pHeap 堆指针
 */
void hs_binaryHeapClear(HS_BinaryHeap* pHeap)
{
    if (!hs_binaryHeapIsEmpty(pHeap))
    {
        memset(pHeap -> elements, 0, sizeof(HS_ELEMENT_TYPE) * pHeap -> capacity);
    }
}


/**
 * 获取二叉堆元素的数量
 * @param pHeap 堆指针
 * @return 返回堆元素数
 */
HS_HEAP_SIZE hs_binaryHeapSize(HS_BinaryHeap* pHeap)
{
    return pHeap && pHeap -> size ? pHeap -> size: 0;
}

/**
 * 向二叉堆添加元素
 * @param pHeap 树指针
 * @param element 待添加元素
 */
void hs_binaryHeapAdd(HS_BinaryHeap* pHeap, HS_ELEMENT_TYPE element)
{
    hs_binaryHeapPointerCheck(pHeap);
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
HS_ELEMENT_TYPE hs_binaryHeapGet(HS_BinaryHeap* pHeap)
{
    hs_binaryHeapEmptyCheck(pHeap);

    return pHeap -> elements[1];
}

/**
 * 删除二叉堆堆顶元素
 * @param pHeap 堆指针
 * @return 删除的元素
 */
HS_ELEMENT_TYPE hs_binaryHeapRemove(HS_BinaryHeap* pHeap)
{
    hs_binaryHeapEmptyCheck(pHeap);
    
    HS_ELEMENT_TYPE heapTop = hs_binaryHeapGet(pHeap), replaceElement = pHeap -> elements[pHeap -> size];
    pHeap -> elements[1] = replaceElement;
    memset(pHeap -> elements + pHeap -> size, 0, sizeof(HS_ELEMENT_TYPE));
    pHeap -> size--;
    
    siftDown(pHeap -> elements, pHeap -> size, 1);
    
//    for (HS_HEAP_INDEX index = 1, maxIndex = 1; pHeap -> size; index = maxIndex)
//    {
//        if (2 * index <= pHeap -> size && pHeap -> elements[2 * index] > pHeap -> elements[index])
//            maxIndex = 2 * index;
//        if (2 * index + 1 <= pHeap -> size && pHeap -> elements[2 * index + 1] > pHeap -> elements[maxIndex])
//            maxIndex = 2 * index + 1;
//        if (maxIndex == index)
//            break;
//        hs_swap(pHeap -> elements + maxIndex, pHeap -> elements + index);
//    }
//    for (HS_HEAP_INDEX index = 1, maxIndex = 1; pHeap -> size; index = maxIndex)
//    {
//        if (2 * index <= pHeap -> size && pHeap -> elements[2 * index] > replaceElement)
//            maxIndex = 2 * index;
//        if (2 * index + 1 <= pHeap -> size && pHeap -> elements[2 * index + 1] > pHeap -> elements[maxIndex])
//            maxIndex = 2 * index + 1;
//        if (maxIndex == index)
//        {
//            pHeap -> elements[index] = replaceElement;
//            break;
//        }
//        else
//            pHeap -> elements[index] = pHeap -> elements[maxIndex];
//    }
    
    return heapTop;
}
