//
//  HS_Array.h
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/3.
//

#ifndef HS_Array_h
#define HS_Array_h

#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "HS_Define.h"

//#ifndef HS_ELEMENT_TYPE
//typedef int HS_ELEMENT_TYPE;
//#endif

typedef long long HS_ARRAY_SIZE;
typedef HS_ARRAY_SIZE HS_ARRAY_INDEX;
typedef struct hs_Array_List HS_Array;
typedef int(*HS_COMPARE)(HS_ELEMENT_TYPE,HS_ELEMENT_TYPE) ;

extern const HS_ARRAY_INDEX HS_ELEMENT_NOT_FOUND;

/**
 * 创建动态数组
 * @return 返回动态数组指针
 */
HS_Array* hs_arrayNew(void);

/**
 * 创建动态数组
 * @param size 设置数组的长度
 * @return 返回动态数组指针
 */
HS_Array* hs_arrayNewWithSize(HS_ARRAY_SIZE size);

/**
 * 创建动态数组
 * @param size 设置数组的长度
 * @param compare 设置比较函数
 * @return 返回动态数组指针
 */
HS_Array* hs_arrayNewWihSizeCompare(HS_ARRAY_SIZE size, HS_COMPARE compare);

/**
 * 清除所有元素
 * @param pArray 动态数组指针
 */
void hs_arrayClear(HS_Array* pArray);

/**
 * 返回数组元素的数量
 * @param pArray 动态数组指针
 * @return 返回数组元素数
 */
HS_ARRAY_SIZE hs_arrayGetSize(HS_Array* pArray);

/**
 * 数组是否为空
 * @param pArray 动态数组指针
 * @return 数组无元素返回true，否则返回false
 */
bool hs_arrayIsEmpty(HS_Array* pArray);

/**
 * 是否包含某个元素
 * @param pArray 动态数组指针
 * @param element 需要确认的元素
 * @return 若数组包含该元素，返回true;若不包含该元素，返回false
 */
bool hs_arrayContains(HS_Array* pArray, HS_ELEMENT_TYPE element);


/**
 * 添加元素到尾部
 * @param pArray 动态数组指针
 * @param element 待加入的元素
 */
void hs_arrayAdd(HS_Array* pArray, HS_ELEMENT_TYPE element);

/**
 * 在index位置插入一个元素
 * @param pArray 动态数组指针
 * @param element 待加入的元素
 * @param index 加入的位置，数组从0开始计算索引
 */
void hs_arrayAddToIndex(HS_Array* pArray, HS_ELEMENT_TYPE element, HS_ARRAY_INDEX index);

/**
 * 获取index位置的元素
 * @param pArray 动态数组指针
 * @param index 元素的索引，数组从0开始计算索引
 * @return 返回索引处的元素
 */
HS_ELEMENT_TYPE hs_arrayGetOfIndex(HS_Array* pArray, HS_ARRAY_INDEX index);

/**
 * 设置index位置的元素
 * @param pArray 动态数组指针
 * @param element 替换的元素
 * @param index 元素的索引，数组从0开始计算索引
 * @return 原来的元素ֵ
 */
HS_ELEMENT_TYPE hs_arraySetToIndex(HS_Array* pArray, HS_ELEMENT_TYPE element, HS_ARRAY_INDEX index);

/**
 * 删除index位置的元素
 * @param pArray 动态数组指针
 * @param index 元素的索引，数组从0开始计算索引
 * @return 返回被删除的元素
 */
HS_ELEMENT_TYPE hs_arrayRemoveAtIndex(HS_Array* pArray, HS_ARRAY_INDEX index);

/**
 * 查看元素的索引
 * @param pArray 动态数组指针
 * @param element 待查询的元素
 * @return 若数组包含该元素，返回索引值，索引从0开始计算；若不包含该元素，返回HS_ELEMENT_NOT_FOUND
 */
HS_ARRAY_INDEX hs_arrayIndexOf(HS_Array* pArray, HS_ELEMENT_TYPE element);

/**
 * 最小化实例存储
 * @param pArray 动态数组指针
 */
void hs_arrayTrimToSize(HS_Array* pArray);

/**
 * 销毁数组
 * @param pArray 动态数组指针
 */
void hs_arrayFree(HS_Array* pArray);



#endif /* HS_Array_h */
