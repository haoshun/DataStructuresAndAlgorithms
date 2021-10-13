//
//  HS_UnionFind_QF.h
//  UnionFind
//
//  Created by 郝源顺 on 2021/10/13.
//

#ifndef HS_UnionFind_QF_h
#define HS_UnionFind_QF_h


#include "HS_Define.h"

/*
 Quick Find 思路实现并查集
 查找（Find）时间复杂度O(1)
 合并（Union）时间复杂度O(n)
 
 不推荐使用这个思路实现
 */



typedef struct hs_union_find_qf HS_UnionFind_QF;


/**
 * 创建并查集
 * @param capacity 并查集容量
 * @return 返回并查集指针
 */
HS_UnionFind_QF* hs_uf_qf_Create(HS_SIZE capacity);


/**
 * 查找v所属的集合（根节点）
 * @param pUF 并查集指针
 * @param v 元素
 * @return 返回根节点索引
 */
HS_INDEX hs_uf_qf_Find(HS_UnionFind_QF* pUF, HS_TYPE v);


/**
 * 将v1所在集合的所有元素，都嫁接到v2的父节点上
 * @param pUF 并查集指针
 * @param v1 元素1
 * @param v2 元素2
 */
void hs_uf_qf_Union(HS_UnionFind_QF* pUF, HS_TYPE v1, HS_TYPE v2);


/**
 * 检查v1、v2是否属于同一个集合
 * @param pUF 并查集指针
 * @param v1 元素1
 * @param v2 元素2
 * @return 是否在同一集合
 */
bool hs_uf_qf_SameSet(HS_UnionFind_QF* pUF, HS_TYPE v1, HS_TYPE v2);


/**
 * 销毁并查集
 * @param pUF 并查集指针
 */
void hs_uf_qf_Free(HS_UnionFind_QF* pUF);


#endif /* HS_UnionFind_QF_h */


