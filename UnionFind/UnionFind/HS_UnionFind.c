//
//  HS_UnionFind.c
//  UnionFind
//
//  Created by 郝源顺 on 2021/4/1.
//

#include "HS_UnionFind.h"


/*
 size 和 rank 优先选择使用rank（即树高）方式
 **/
//#define UF_QU_S




struct hs_union_find {
    /**
    * 所有的元素
    */
     HS_INDEX * parents;
    
#ifdef UF_QU_S
    /**
    * 以index元素为根节点的树的节点数
    */
     HS_SIZE * sizes;
#else
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

#pragma mark -


void _hs_uf_pointer_check(HS_UnionFind* pUF)
{
    assert(pUF != NULL);
}

void _hs_uf_range_check(HS_UnionFind* pUF, HS_INDEX index)
{
    _hs_uf_pointer_check(pUF);
    assert(index >= 0 && index < pUF -> capacity);
}

#pragma mark - Union

/*
 未加优化
 将p1整棵树嫁接到p2上
 p2为新的根节点
 不建议采用，可能会导致树退化为链表
 */
void _uf_union(HS_UnionFind* pUF, HS_INDEX p1, HS_INDEX p2)
{
    pUF -> parents[p1] = p2;
}

#ifdef UF_QU_S
/*
 将节点少的树嫁接到节点多的树的根节点上
 也可能出现树不平衡的情况
 不建议采用
 **/
void _uf_union_size(HS_UnionFind* pUF, HS_INDEX p1, HS_INDEX p2)
{
    if(pUF -> sizes[p1] < pUF -> sizes[p2])
    {
        pUF -> parents[p1] = p2;
        pUF -> sizes[p2] += pUF -> sizes[p1];
    }
    else
    {
        pUF -> parents[p2] = p1;
        pUF -> sizes[p1] += pUF -> sizes[p2];
    }
}

#else

/**
 将高度低的树嫁接到高度高的树的根节点上
 树会相对平衡一些
 但是随着Union次数的增多，树的高度依然会越来越高
 建议继续优化
 */
void _uf_union_rank(HS_UnionFind* pUF, HS_INDEX p1, HS_INDEX p2)
{
    if(pUF -> ranks[p1] < pUF -> ranks[p2])
        pUF -> parents[p1] = p2;
    else if(pUF -> ranks[p1] > pUF -> ranks[p2])
        pUF -> parents[p2] = p1;
    else
    {
        pUF -> parents[p1] = p2;
        (pUF -> ranks[p2]) += 1;
    }
}

#endif

#pragma mark - Find

HS_INDEX _uf_find(HS_UnionFind* pUF, HS_INDEX v)
{
    while (v != pUF -> parents[v]) {
        v = pUF -> parents[v];
    }
    return v;
}


/*
 使用路径压缩（Path Compression）优化
 路径上所有节点指向根节点
 在每次查找操作时将合并过来的节点指向更节点
 成本较高
 不推荐
**/
HS_INDEX _uf_find_pc(HS_UnionFind* pUF, HS_INDEX v)
{
    if (pUF -> parents[v] != v) {
        pUF -> parents[v] = _uf_find_pc(pUF, pUF -> parents[v]);
    }
    return pUF -> parents[v];
}


/*
 使用路径分裂（Path Spliting）优化
 使路径上的每个节点都指向其祖父节点
 推荐
**/
HS_INDEX _uf_find_ps(HS_UnionFind* pUF, HS_INDEX v)
{
    while (v != pUF -> parents[v]) {
        int parent = pUF -> parents[v];
        pUF -> parents[v] = pUF -> parents[parent];
        v = parent;
    }
    return v;
}


/*
 使用路径减半（Path Halving）优化
 使路径上每隔一个节点就指向其祖父节点
 推荐
**/
HS_INDEX _uf_find_ph(HS_UnionFind* pUF, HS_INDEX v)
{
    while (v != pUF -> parents[v]) {
        pUF -> parents[v] = pUF -> parents[pUF -> parents[v]];
        v = pUF -> parents[v];
    }
    return v;
}





#pragma mark -



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
#ifdef UF_QU_S
        pUF -> sizes = (HS_SIZE*) malloc(sizeof(HS_SIZE) * pUF -> capacity);
        memset(pUF -> sizes, 1, sizeof(HS_SIZE) * pUF -> capacity);
#else
        pUF -> ranks = (HS_HEIGHT*) malloc(sizeof(HS_HEIGHT) * pUF -> capacity);
        memset(pUF -> ranks, 1, sizeof(HS_HEIGHT) * pUF -> capacity);
#endif
    }
    return pUF;
}


/**
 * 查找v所属的集合（根节点）
 * @param pUF 并查集指针
 * @param v 元素
 * @return 返回根节点索引
 */
HS_INDEX hs_ufFind(HS_UnionFind* pUF, HS_TYPE v)
{
    _hs_uf_range_check(pUF, v);

    //未优化Find
    //return _uf_find(pUF, v);
    
    //使用路径压缩Find
    //return _uf_find_pc(pUF, v);
    
    //使用路径分裂Find
    //return _uf_find_ps(pUF, v);
    
    //使用路径减半Find
    return _uf_find_ph(pUF, v);
}


/**
 * 将v1所在集合的所有元素，都嫁接到v2的父节点上
 * @param pUF 并查集指针
 * @param v1 元素1
 * @param v2 元素2
 */
void hs_ufUnion(HS_UnionFind* pUF, HS_TYPE v1, HS_TYPE v2)
{
    HS_INDEX p1 = hs_ufFind(pUF, v1);
    HS_INDEX p2 = hs_ufFind(pUF, v2);
    
    if(p1 == p2) return;
    
    //未优化合并
    //_uf_union(pUF, p1, p2);
    

#ifdef UF_QU_S
    _uf_union_size(pUF, p1, p2);
    
#else
    _uf_union_rank(pUF, p1, p2);
    
#endif

}


/**
 * 检查v1、v2是否属于同一个集合
 * @param pUF 并查集指针
 * @param v1 元素1
 * @param v2 元素2
 * @return 是否在同一集合
 */
bool hs_ufSameSet(HS_UnionFind* pUF, HS_TYPE v1, HS_TYPE v2)
{
    return hs_ufFind(pUF, v1) == hs_ufFind(pUF, v2);
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






