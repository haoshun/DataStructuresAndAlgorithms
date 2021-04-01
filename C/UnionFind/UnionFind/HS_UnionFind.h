//
//  HS_UnionFind.h
//  UnionFind
//
//  Created by 郝源顺 on 2021/4/1.
//

#ifndef HS_UnionFind_h
#define HS_UnionFind_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "HS_Define.h"

typedef struct hs_union_find HS_UnionFind;


/**
 * 创建并查集
 * @param capacity 并查集容量
 * @return 返回并查集指针
 */
HS_UnionFind* hs_ufCreate(HS_SIZE capacity);


/**
 * 查找target所属的集合（根节点）
 * @param pUF 并查集指针
 * @param target 目标元素
 * @return 返回根节点索引
 */
HS_INDEX hs_ufFind(HS_UnionFind* pUF, HS_TYPE target);


/**
 * 将v1所在集合的所有元素，都嫁接到v2的父节点上
 * @param pUF 并查集指针
 * @param target1 目标元素1
 * @param target2 目标元素2
 */
void hs_ufUnion(HS_UnionFind* pUF, HS_TYPE target1, HS_TYPE target2);


/**
 * 检查v1、v2是否属于同一个集合
 * @param pUF 并查集指针
 * @param target1 目标元素1
 * @param target2 目标元素2
 * @return 是否在同一集合
 */
bool hs_ufSameSet(HS_UnionFind* pUF, HS_TYPE target1, HS_TYPE target2);


/**
 * 销毁并查集
 * @param pUF 并查集指针
 */
void hs_ufFree(HS_UnionFind* pUF);


#endif /* HS_UnionFind_h */
