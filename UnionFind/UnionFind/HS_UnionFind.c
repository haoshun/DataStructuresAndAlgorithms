//
//  HS_UnionFind.c
//  UnionFind
//
//  Created by 郝源顺 on 2021/4/1.
//

#include "HS_UnionFind.h"

//#define UF_QF

//size 和 rank 优先选择使用rank（即树高）方式
//#define UF_QF_S
#define UF_QF_R

struct hs_union_find {
    /**
    * 所有的元素
    */
     HS_INDEX * parents;
    
#ifdef UF_QF_S
    /**
    * 以index元素为根节点的树的节点数
    */
     HS_SIZE * sizes;
#endif
#ifdef UF_QF_R
    /**
    * 所有的元素
    */
     HS_HEIGHT * ranks;
#endif
    
    /**
     * 元素的数量
     */
    HS_SIZE capacity;
   
};



#pragma mark -  QF
HS_INDEX _uf_qf_Find(HS_UnionFind* pUF, HS_TYPE target)
{
    return pUF -> parents[target];
}

void _uf_qf_Union(HS_UnionFind* pUF, HS_TYPE target1, HS_TYPE target2)
{
    HS_INDEX index1 = _uf_qf_Find(pUF, target1);
    HS_INDEX index2 = _uf_qf_Find(pUF, target2);
    
    if(index1 == index2) return;
    
    for(int i = 0 ; i < pUF -> capacity ; ++i)
        if(pUF -> parents[i] == index1)
            pUF -> parents[i] = index2;
}




#pragma mark -  QU
HS_INDEX _uf_qu_Find(HS_UnionFind* pUF, HS_TYPE target)
{
    while (target != pUF -> parents[target]) {
        target = pUF -> parents[target];
    }
    return target;
}

void _uf_qu_Union(HS_UnionFind* pUF, HS_TYPE target1, HS_TYPE target2)
{
    HS_INDEX index1 = _uf_qu_Find(pUF, target1);
    HS_INDEX index2 = _uf_qu_Find(pUF, target2);
    
    if(index1 == index2) return;
    
#ifdef UF_QF_S
    if(pUF -> sizes[index1] < pUF -> sizes[index2])
    {
        pUF -> parents[index1] = index2;
        pUF -> sizes[index2] += pUF -> sizes[index1];
    }
    else
    {
        pUF -> parents[index2] = index1;
        pUF -> sizes[index1] += pUF -> sizes[index2];
    }
    
#else
    
#ifdef UF_QF_R
    
    
    if(pUF -> ranks[index1] < pUF -> ranks[index2])
        pUF -> parents[index1] = index2;
    else if(pUF -> ranks[index1] > pUF -> ranks[index2])
        pUF -> parents[index2] = index1;
    else
    {
        pUF -> parents[index1] = index2;
        (pUF -> ranks[index2]) += 1;
    }
    
#else
    pUF -> parents[index1] = index2;
    
#endif
#endif

}


/**
 * 创建并查集
 * @param capacity 并查集容量
 * @return 返回并查集指针
 */
HS_UnionFind* hs_ufCreate(HS_SIZE capacity)
{
    HS_UnionFind* pUF = (HS_UnionFind*) malloc(sizeof(HS_UnionFind));
    if(pUF)
    {
        pUF -> capacity = capacity;
        pUF -> parents = (HS_INDEX*) malloc(sizeof(HS_INDEX) * pUF -> capacity);
        for(int i = 0 ; i < pUF -> capacity ; ++i)
            pUF -> parents[i] = i;
#ifdef UF_QF_S
        pUF -> sizes = (HS_SIZE*) malloc(sizeof(HS_SIZE) * pUF -> capacity);
        memset(pUF -> sizes, 1, sizeof(HS_SIZE) * pUF -> capacity);
#endif
#ifdef UF_QF_R
        pUF -> ranks = (HS_HEIGHT*) malloc(sizeof(HS_HEIGHT) * pUF -> capacity);
        memset(pUF -> ranks, 1, sizeof(HS_HEIGHT) * pUF -> capacity);
#endif
    }
    return pUF;
}


/**
 * 查找target所属的集合（根节点）
 * @param pUF 并查集指针
 * @param target 目标元素
 * @return 返回根节点索引
 */
HS_INDEX hs_ufFind(HS_UnionFind* pUF, HS_TYPE target)
{
#ifdef UF_QF
    return _uf_qf_Find(pUF, target);
#else
    return _uf_qu_Find(pUF, target);
#endif
}


/**
 * 将v1所在集合的所有元素，都嫁接到v2的父节点上
 * @param pUF 并查集指针
 * @param target1 目标元素1
 * @param target2 目标元素2
 */
void hs_ufUnion(HS_UnionFind* pUF, HS_TYPE target1, HS_TYPE target2)
{
#ifdef UF_QF
    _uf_qf_Union(pUF, target1, target2);
#else
    _uf_qu_Union(pUF, target1, target2);
#endif

}


/**
 * 检查v1、v2是否属于同一个集合
 * @param pUF 并查集指针
 * @param target1 目标元素1
 * @param target2 目标元素2
 * @return 是否在同一集合
 */
bool hs_ufSameSet(HS_UnionFind* pUF, HS_TYPE target1, HS_TYPE target2)
{
    return hs_ufFind(pUF, target1) == hs_ufFind(pUF, target2);
}




/**
 * 销毁并查集
 * @param pUF 并查集指针
 */
void hs_ufFree(HS_UnionFind* pUF)
{
    if(pUF)
    {
        if(pUF -> parents && pUF -> capacity)
            free(pUF -> parents);
        free(pUF);
    }
}






