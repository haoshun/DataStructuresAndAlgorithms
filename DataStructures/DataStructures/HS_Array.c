//
//  HS_Array.c
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/3.
//

#include "HS_Array.h"

static const HS_ARRAY_SIZE HS_DEFAULT_CAPACITY = 10;
const HS_ARRAY_INDEX HS_ELEMENT_NOT_FOUND = -1;

struct hs_Array_List {
    /**
     * 元素的数量
     */
    HS_ARRAY_SIZE size;
    /**
    * 所有的元素
    */
    HS_ELEMENT_TYPE * elements;
    /**
     * 当前Array容量
     */
    HS_ARRAY_SIZE capacity;
    
    //todo: 未验证
    /**
     * 元素比较方法，相等为1，不相等为0
     */
    HS_COMPARE pCompare;
};

void hs_arrayPointerCheck(HS_Array* pArray)
{
    assert(pArray != NULL);
}

void hs_arrayRangeCheck(HS_Array* pArray, HS_ARRAY_INDEX index)
{
    assert(index >= 0 && index < pArray -> size);
}

void hs_arrayRangeCheckForAdd(HS_Array* pArray, HS_ARRAY_INDEX index)
{
    assert(index >= 0 && index <= pArray -> size);
}

void hs_arrayEnsureCapacity(HS_Array* pArray, HS_ARRAY_SIZE capacity)
{
    if (pArray -> capacity >= capacity)
        return;
    
    //新容量为旧容量的1.5倍
    HS_ARRAY_SIZE oldCapacity = pArray -> capacity;
    
    HS_ARRAY_SIZE newCapacity = oldCapacity + (oldCapacity >> 1);
    pArray -> elements = (HS_ELEMENT_TYPE*) realloc(pArray -> elements, newCapacity * sizeof(HS_ELEMENT_TYPE));
    memset(pArray -> elements + oldCapacity, 0, (oldCapacity >> 1) * sizeof(HS_ELEMENT_TYPE));
    
    pArray -> capacity = newCapacity;
}







HS_Array* hs_arrayNew(void)
{
    return hs_arrayNewWithSize(HS_DEFAULT_CAPACITY);
}

HS_Array* hs_arrayNewWithSize(HS_ARRAY_SIZE size)
{
    return hs_arrayNewWihSizeCompare(size, NULL);
}

HS_Array* hs_arrayNewWihSizeCompare(HS_ARRAY_SIZE size, HS_COMPARE compare)
{
    assert(size >= 0);
    HS_Array* pArray = (HS_Array* )malloc(sizeof(HS_Array));
    if (pArray)
    {
        pArray -> capacity = size < HS_DEFAULT_CAPACITY ? HS_DEFAULT_CAPACITY : size;
        pArray -> size = 0;
        pArray -> elements = (HS_ELEMENT_TYPE *) calloc(pArray -> capacity, sizeof(HS_ELEMENT_TYPE));
        pArray -> pCompare = compare;
    }
    return  pArray;
}



void hs_arrayClear(HS_Array* pArray)
{
    hs_arrayPointerCheck(pArray);
    if(pArray -> size)
    {
        memset(pArray -> elements , 0 , sizeof(HS_ELEMENT_TYPE) * pArray -> size);
        pArray -> size = 0;
    }
}


HS_ARRAY_SIZE hs_arrayGetSize(HS_Array* pArray)
{
    hs_arrayPointerCheck(pArray);
    return pArray -> size;
}


bool hs_arrayIsEmpty(HS_Array* pArray)
{
    hs_arrayPointerCheck(pArray);
    return !pArray -> size;
}


bool hs_arrayContains(HS_Array* pArray, HS_ELEMENT_TYPE element)
{
    return  hs_arrayIndexOf(pArray, element) != HS_ELEMENT_NOT_FOUND;
}


void hs_arrayAdd(HS_Array* pArray, HS_ELEMENT_TYPE element)
{
    hs_arrayPointerCheck(pArray);
    hs_arrayAddToIndex(pArray, element, pArray -> size);
}


void hs_arrayAddToIndex(HS_Array* pArray, HS_ELEMENT_TYPE element, HS_ARRAY_INDEX index)
{
    hs_arrayPointerCheck(pArray);
    hs_arrayRangeCheckForAdd(pArray, index);
    hs_arrayEnsureCapacity(pArray, pArray -> size +1);
    if (index < pArray -> size) {
        memmove(pArray -> elements + index + 1 , pArray -> elements + index, (pArray -> size - index)*sizeof(HS_ELEMENT_TYPE));
    }
    pArray -> elements[index] = element;
    pArray -> size ++;
}


HS_ELEMENT_TYPE hs_arrayGetOfIndex(HS_Array* pArray, HS_ARRAY_INDEX index)
{
    hs_arrayPointerCheck(pArray);
    hs_arrayRangeCheck(pArray, index);
    return pArray -> elements[index];
}


HS_ELEMENT_TYPE hs_arraySetToIndex(HS_Array* pArray, HS_ELEMENT_TYPE element, HS_ARRAY_INDEX index)
{
    hs_arrayPointerCheck(pArray);
    hs_arrayRangeCheck(pArray, index);
    
    HS_ELEMENT_TYPE old = pArray -> elements[index];
    pArray -> elements[index] = element;
    return  old;
}

HS_ELEMENT_TYPE hs_arrayRemoveAtIndex(HS_Array* pArray, HS_ARRAY_INDEX index)
{
    hs_arrayPointerCheck(pArray);
    hs_arrayRangeCheck(pArray, index);
    
    HS_ELEMENT_TYPE old = pArray -> elements[index];
    memmove(pArray -> elements + index, pArray -> elements + index + 1, (pArray -> size - index -1) * sizeof(HS_ELEMENT_TYPE));
    memset(pArray -> elements + (--pArray -> size), 0, sizeof(HS_ELEMENT_TYPE));
    return old;
}


HS_ARRAY_INDEX hs_arrayIndexOf(HS_Array* pArray, HS_ELEMENT_TYPE element)
{
    hs_arrayPointerCheck(pArray);
    if (pArray -> pCompare)
    {
        for (HS_ARRAY_INDEX index = 0; index < pArray -> size;  ++index) {
            if ((*(pArray -> pCompare))(pArray -> elements[index], element)) {
                return index;
            }
        }
    }
    else
    {
        for (HS_ARRAY_INDEX index = 0; index < pArray -> size;  ++index) {
            if (pArray -> elements[index] == element) {
                return  index;
            }
        }
    }
    return HS_ELEMENT_NOT_FOUND;
}


void hs_arrayTrimToSize(HS_Array* pArray)
{
    hs_arrayPointerCheck(pArray);
    if (pArray -> capacity > pArray -> size)
    {
        HS_ARRAY_SIZE tinyCapacity = pArray -> size < HS_DEFAULT_CAPACITY ? HS_DEFAULT_CAPACITY : pArray -> size;
        pArray -> elements = (HS_ELEMENT_TYPE*) realloc(pArray -> elements, tinyCapacity * sizeof(HS_ELEMENT_TYPE));
        pArray -> capacity = tinyCapacity;
    }
}

void hs_arrayFree(HS_Array* pArray)
{
    hs_arrayPointerCheck(pArray);
    if (pArray -> elements) {
        free(pArray -> elements);
    }
    free(pArray);
}
