//
//  HS_UnionFind_QF.c
//  UnionFind
//
//  Created by 郝源顺 on 2021/10/13.
//


#include "HS_UnionFind_QF.h"

struct hs_union_find_qf {
    /**
    * 所有的元素
    */
     HS_TYPE * parents;
    
    /**
     * 元素的数量
     */
    HS_SIZE capacity;
};



void _uf_qf_pointer_check(HS_UnionFind_QF* pUF)
{
    assert(pUF != NULL);
}

void _uf_qf_range_check(HS_UnionFind_QF* pUF, HS_INDEX index)
{
    _uf_qf_pointer_check(pUF);
    assert(index >= 0 && index < pUF -> capacity);
}




/**
 * 创建并查集
 * @param capacity 并查集容量
 * @return 返回并查集指针
 */
HS_UnionFind_QF* hs_uf_qf_Create(HS_SIZE capacity)
{
    HS_UnionFind_QF* pUF = (HS_UnionFind_QF*) malloc(sizeof(HS_UnionFind_QF));
    if(pUF)
    {
        pUF -> capacity = capacity;
        pUF -> parents = (HS_TYPE*) malloc(sizeof(HS_TYPE) * pUF -> capacity);
        
        for(int i = 0 ; i < pUF -> capacity ; ++i)
            pUF -> parents[i] = i;
    }
    return pUF;
}


/**
 * 查找v所属的集合（根节点）
 * @param pUF 并查集指针
 * @param v 元素
 * @return 返回根节点索引
 */
HS_INDEX hs_uf_qf_Find(HS_UnionFind_QF* pUF, HS_TYPE v)
{
    _uf_qf_range_check(pUF, v);
    return pUF -> parents[v];
}


/**
 * 将v1所在集合的所有元素，都嫁接到v2的父节点上
 * @param pUF 并查集指针
 * @param v1 元素1
 * @param v2 元素2
 */
void hs_uf_qf_Union(HS_UnionFind_QF* pUF, HS_TYPE v1, HS_TYPE v2)
{
    HS_INDEX p1 = hs_uf_qf_Find(pUF, v1);
    HS_INDEX p2 = hs_uf_qf_Find(pUF, v2);
    if(p1 == p2)
        return;
    
    for(int i = 0 ; i < pUF -> capacity ; ++i)
        if(pUF -> parents[i] == p1)
            pUF -> parents[i] = p2;
}


/**
 * 检查v1、v2是否属于同一个集合
 * @param pUF 并查集指针
 * @param v1 元素1
 * @param v2 元素2
 * @return 是否在同一集合
 */
bool hs_uf_qf_SameSet(HS_UnionFind_QF* pUF, HS_TYPE v1, HS_TYPE v2)
{
    return hs_uf_qf_Find(pUF, v1) == hs_uf_qf_Find(pUF, v2);
}




/**
 * 销毁并查集
 * @param pUF 并查集指针
 */
void hs_uf_qf_Free(HS_UnionFind_QF* pUF)
{
    _uf_qf_pointer_check(pUF);
    
    if(pUF -> parents && pUF -> capacity)
        free(pUF -> parents);
    free(pUF);
}



