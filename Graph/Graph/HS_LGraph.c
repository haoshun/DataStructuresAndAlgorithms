//
//  HS_LGraph.c
//  Graph
//
//  Created by 郝源顺 on 2021/1/20.
//

#include "HS_LGraph.h"

typedef struct hs_edge_list_node {
    /**
    * 下一个以该顶点为起点的边
    */
    struct hs_edge_list_node* next;
    /**
    * 边的权值
    */
    HS_WEIGHT_TYPE weight;
    /**
    * 该边指向的顶点
    */
    HS_GRAPH_INDEX tVex;
} HS_ENODE;


typedef struct hs_vertex_node{
    /**
    * 顶点数据
    */
    HS_ELEMENT_TYPE data;
    /**
    * 第一个以该顶点为起点的边
    */
    HS_ENODE* edges;
} HS_VNODE ;


struct hs_list_graph {
    /**
    * 顶点数组
    */
    HS_VNODE * elements;
    /**
     * 顶点数
     */
    HS_VERTEX_SIZE vexSize;
    /**
     * 边数
     */
    HS_EDGE_SIZE edgSize;
};


HS_VNODE* hs_vNodeNew(HS_ELEMENT_TYPE data)
{
    HS_VNODE* pNode = (HS_VNODE*)calloc(1, sizeof(HS_VNODE));
    if (pNode)
    {
        pNode -> data = data;
    }
    return pNode ?: NULL;
}


HS_ENODE* hs_eNodeNew(HS_GRAPH_INDEX tVex, HS_WEIGHT_TYPE weight, HS_ENODE* pNext)
{
    HS_ENODE* pNode = (HS_ENODE*)calloc(1, sizeof(HS_ENODE));
    if(pNode)
    {
        pNode -> tVex = tVex;
        pNode -> weight = weight;
        pNode -> next = pNext;
    }
    return pNode ?: NULL;
}



/**
 * 创建基于邻接表存储的图
 * @return 返回图指针
 */
HS_LGraph* hs_graphNew(void)
{
    HS_LGraph* pGraph = (HS_LGraph*)calloc(1, sizeof(HS_LGraph));
    return pGraph ?: NULL;
}

/**
 * 根据顶点数组和边缘列表创建基于邻接表存储的图
 * @param datas 顶点元素数组
 * @param dataNum 顶点数
 * @param grid 边缘列表（二维数组，每行第一列表示边的起点，第二列表示边的终点，若为带权图，则有第三列代表该边的权值）
 * @param gridSize 边缘列表行数（边数）
 * @param hasDirected 是否是有向图
 * @param hasWeight 是否是带权图（若为带全图则边缘列表列数为3，最后一行表示权值）
 * @return 返回图指针
 */
HS_LGraph* hs_graphCreate(HS_ELEMENT_TYPE* datas, HS_VERTEX_SIZE dataNum, HS_ELEMENT_TYPE** grid, HS_EDGE_SIZE gridSize, bool hasDirected, bool hasWeight)
{
    if(!datas || !dataNum)
        return NULL;
    
    HS_LGraph* pGraph = hs_graphNew();
    if(pGraph)
    {
        pGraph -> vexSize = dataNum;
        pGraph -> edgSize = gridSize;
        //创建图顶点
        pGraph -> elements = (HS_VNODE*)calloc(dataNum , sizeof(HS_VNODE));
        for (HS_GRAPH_INDEX i = 0 ; i < dataNum; ++i)
            pGraph -> elements[i].data = datas[i];
        
        //添加边信息
        if (grid && gridSize)
        {
            for (HS_GRAPH_INDEX i = 0 ; i < gridSize ; ++i)
            {
                HS_ENODE* newEdge = hs_eNodeNew(
                                                grid[i][1],
                                                hasWeight ? grid[i][2]:0,
                                                pGraph ->elements[grid[i][0]].edges);
                if (newEdge)
                    pGraph -> elements[grid[i][0]].edges = newEdge;
                
                //若为无向图则再添加相反的边
                if (!hasDirected)
                {
                    HS_ENODE* newEdge = hs_eNodeNew(
                                                    grid[i][0],
                                                    hasWeight ? grid[i][2]:0,
                                                    pGraph ->elements[grid[i][1]].edges);
                    if (newEdge)
                        pGraph -> elements[grid[i][1]].edges = newEdge;
                }
            }
        }
    }
    return pGraph;
}



/**
 * 根据顶点数组和边缘列表创建基于邻接表存储的无向无权图
 * @param datas 顶点元素数组
 * @param dataNum 顶点数
 * @param grid 边缘列表（二维数组，每行第一列表示边的起点，第二列表示边的终点）
 * @param gridSize 边缘列表行数
 * @return 返回图指针
 */
HS_LGraph* hs_graphCreateUG(HS_ELEMENT_TYPE* datas, HS_VERTEX_SIZE dataNum, HS_ELEMENT_TYPE** grid, HS_EDGE_SIZE gridSize)
{
    return hs_graphCreate(datas, dataNum, grid, gridSize, false, false);
}

/**
 * 根据顶点数组和边缘列表创建基于邻接表存储的无向有权图
 * @param datas 顶点元素数组
 * @param dataNum 顶点数
 * @param grid 边缘列表（二维数组，每行第一列表示边的起点，第二列表示边的终点，第三列代表该边的权值）
 * @param gridSize 边缘列表行数
 * @return 返回图指针
 */
HS_LGraph* hs_graphCreateUGWithWeight(HS_ELEMENT_TYPE* datas, HS_VERTEX_SIZE dataNum, HS_ELEMENT_TYPE** grid, HS_EDGE_SIZE gridSize)
{
    return hs_graphCreate(datas, dataNum, grid, gridSize, false, true);
}

/**
 * 根据顶点数组和边缘列表创建基于邻接表存储的有向无权图
 * @param datas 顶点元素数组
 * @param dataNum 顶点数
 * @param grid 边缘列表（二维数组，每行第一列表示边的起点，第二列表示边的终点）
 * @param gridSize 边缘列表行数
 * @return 返回图指针
 */
HS_LGraph* hs_graphCreateDG(HS_ELEMENT_TYPE* datas, HS_VERTEX_SIZE dataNum, HS_ELEMENT_TYPE** grid, HS_EDGE_SIZE gridSize)
{
    return hs_graphCreate(datas, dataNum, grid, gridSize, true, false);
}

/**
 * 根据顶点数组和边缘列表创建基于邻接表存储的有向有权图
 * @param datas 顶点元素数组
 * @param dataNum 顶点数
 * @param grid 边缘列表（二维数组，每行第一列表示边的起点，第二列表示边的终点，第三列代表该边的权值）
 * @param gridSize 边缘列表行数
 * @return 返回图指针
 */
HS_LGraph* hs_graphCreateDGWithWeight(HS_ELEMENT_TYPE* datas, HS_VERTEX_SIZE dataNum, HS_ELEMENT_TYPE** grid, HS_EDGE_SIZE gridSize)
{
    return hs_graphCreate(datas, dataNum, grid, gridSize, true, true);
}



/**
 * 最小生成树(MST)
 * Prim 算法
 * 有权连通图
 * @param pGraph 图指针
 * @param start 从该顶点开始生成
 * @param gridSize 边缘列表行数
 * @return 按边缘列表方式返回MST的所有边（前两列表示边的两个顶点，第三列代表该边权值）
 */
HS_ELEMENT_TYPE** hs_graphMSTPrim(HS_LGraph* pGraph, HS_GRAPH_INDEX start, HS_EDGE_SIZE* gridSize)
{
    if(!pGraph || pGraph -> vexSize <= start)
        return NULL;
    
    HS_VERTEX_SIZE vSize = pGraph -> vexSize;
    HS_EDGE_SIZE edg_count = pGraph -> vexSize - 1;
    
    *gridSize = edg_count;
    HS_ELEMENT_TYPE** pEdges = (HS_ELEMENT_TYPE**) calloc(edg_count, sizeof(HS_ELEMENT_TYPE*));
    
    int* mst = (int*)malloc(vSize * sizeof(int));
    for (int i = 0 ; i < vSize; ++i)
        mst[i] = -2;
    mst[start] = -1;
    
    HS_MinHeap* minHeap = hs_minHeapNew();
    HS_VNODE vNode;
    HS_ENODE* tmpEdg = NULL;
    for (HS_GRAPH_INDEX i = 0, cur_from = start ; i < edg_count ; ++i)
    {
        vNode = pGraph -> elements[cur_from];
        tmpEdg = vNode.edges;
        while (tmpEdg)
        {
            if (mst[tmpEdg -> tVex] == -2)
            {
                //这里借用了为Dijkstra 定义的结构体，HS_DNode 中的dist 存储边的权值
                HS_DNode e_info = {cur_from, tmpEdg -> tVex, tmpEdg -> weight};
                hs_minHeapAdd(minHeap, e_info);
            }
            tmpEdg  = tmpEdg -> next;
        }
        
        HS_ELEMENT_TYPE* mstEdge = (HS_ELEMENT_TYPE*) malloc(sizeof(HS_ELEMENT_TYPE));
        pEdges[i] = mstEdge;
        
        HS_DNode minDNode = hs_minHeapRemove(minHeap);
        mstEdge[0] = minDNode.f_index;
        mstEdge[1] = minDNode.g_index;
        mstEdge[2] = minDNode.dist;
        
        mst[minDNode.g_index] = minDNode.f_index;
        cur_from = minDNode.g_index;
    }
    
    //这里的mst已然可以回溯出最小生成树了，如果要求返回一维数组表示的最小生成树，可直接返回mst
    free(mst);
    
    return pEdges;
}




/**
 * 单源最短路径
 * Dijkstra 算法
 * 不能有负权边
 * @param pGraph 图指针
 * @param vex_s 从顶点s出发
 * @param vex_t 到顶点t
 * @param path 路径数组
 * @param pathLen 路径数组长度
 * @return 返回最短路径值
 */
HS_DISTANCE hs_graphDijkstra(HS_LGraph* pGraph, HS_GRAPH_INDEX vex_s, HS_GRAPH_INDEX vex_t, HS_PATH** path, HS_PATH* pathLen)
{
    if (!pGraph || !pGraph -> vexSize || vex_s == vex_t)
        return 0;
    
    HS_DISTANCE minDistance = 0;
    HS_VERTEX_SIZE vSize = pGraph -> vexSize;
    
    //初始化返回路径数组
    *path = (HS_PATH*)calloc(vSize, sizeof(HS_PATH));
    *pathLen = vSize;
    
    //初始化从s到所有顶点距离数组，默认除源点s外都为无穷大
    HS_DNode* dp = (HS_DNode*)calloc(vSize, sizeof(HS_DNode));
    for (HS_GRAPH_INDEX i = 0 ; i < vSize ; ++i)
    {
        dp[i].dist = INT_MAX;
        dp[i].g_index = i;
    }
    dp[vex_s].dist = 0;
    
    //使用小顶堆辅助获取当前距离最近的顶点，先将源点s加入堆中
    HS_MinHeap* minHeap = hs_minHeapNew();
    bool* inHeap = (bool*) calloc(vSize, sizeof(bool));
    hs_minHeapAdd(minHeap, dp[vex_s]);
    inHeap[vex_s] = true;
    
    //当堆不为空时，取出堆顶元素，即下一个路径最短的顶点
    while (!hs_minHeapIsEmpty(minHeap))
    {
        HS_DNode minDNode = hs_minHeapRemove(minHeap);
        //若顶点为目的顶点，则得到结果，算法退出
        if (minDNode.g_index == vex_t)
        {
            minDistance = minDNode.dist;
            break;
        }
        
        //若顶点非目的顶点，则遍历从它出发的所有边，看是否能实现松弛操作
        //松弛操作是指：从当前顶点经过的路径所指向的顶点中，是否存在比现在已知的路径更短的路径。
        HS_ENODE* tmpEdge = pGraph -> elements[minDNode.g_index].edges;
        while (tmpEdge)
        {
            //若有自环则认为路径为0
            if (tmpEdge -> tVex == minDNode.g_index)
                continue;
            
            HS_DNode* nextDNode = dp + tmpEdge -> tVex;
            //如果经过当前顶点到达下一顶点的路径比目前已知的到下一顶点的路径短，则更新到达下一顶点的最短路径长度值
            if (nextDNode -> dist > minDNode.dist + tmpEdge -> weight)
            {
                //更新路径和距离
                (*path)[nextDNode ->g_index] = minDNode.g_index;
                nextDNode -> dist = minDNode.dist + tmpEdge -> weight;
                //若下一顶点已在堆中，则更新其距离值，并按照小顶堆规则上滤；
                //若不在堆中，则加入堆
                if (inHeap[nextDNode -> g_index])
                {
                    hs_minHeapUpdate(minHeap, *nextDNode);
                }
                else
                {
                    hs_minHeapAdd(minHeap, *nextDNode);
                    inHeap[nextDNode -> g_index] = true;
                }
            }
            tmpEdge = tmpEdge -> next;
        }
    }
    
    return  minDistance;
}



/**
 * 单源最短路径
 * Bellman-Ford 算法
 * 可以有负权边 能检测是否有负权环
 * @param pGraph 图指针
 * @param src 起始顶点
 * @param distLen 返回的路径数组长度
 * @param hasNWL 图中是否有负权环， true 代表有
 * @return 返回起始顶点到所有顶点最短路径值
 */
HS_DISTANCE* hs_graphBellman_Ford(HS_LGraph* pGraph, HS_GRAPH_INDEX src, HS_VERTEX_SIZE* distLen, bool* hasNWL)
{
    if (!pGraph || src >= pGraph -> vexSize )
        return NULL;
    
    HS_VERTEX_SIZE vSize = pGraph -> vexSize;
    *distLen = vSize;
    HS_DISTANCE* dists = (HS_DISTANCE*)calloc(vSize, sizeof(HS_DISTANCE));
    for (int i = 0 ; i < vSize; ++i)
        dists[i] = INT_MAX;
    dists[src] = 0;
    
    for (int i = 1 ; i < pGraph -> vexSize; ++i)
    {
        for (int j = 0 ; j < vSize ; ++j)
        {
            HS_ENODE* tmpEdg = pGraph -> elements[j].edges;
            while (tmpEdg)
            {
                //松弛操作
                if (dists[j] != INT_MAX && dists[j] + tmpEdg -> weight < dists[tmpEdg -> tVex])
                {
                    dists[tmpEdg -> tVex] = dists[j] + tmpEdg -> weight;
                }
                tmpEdg = tmpEdg -> next;
            }
        }
    }
    //再多遍历一次 看是否有负权环
    for (int j = 0 ; j < vSize && !(*hasNWL) ; ++j)
    {
        HS_ENODE* tmpEdg = pGraph -> elements[j].edges;
        while (tmpEdg)
        {
            //松弛操作
            if (dists[j] != INT_MAX && dists[j] + tmpEdg -> weight < dists[tmpEdg -> tVex])
            {
                *hasNWL = true;
                break;
            }
            tmpEdg = tmpEdg -> next;
        }
    }

    return dists;
}


/**
 * 多源最短路径
 * Floyd 算法
 * 支持负权边
 * @param pGraph 图指针
 * @param distRow 返回的矩阵行数
 * @param distColume 返回的矩阵每行的列数
 * @return 返回路径距离矩阵
 */
HS_DISTANCE** hs_graphFloyd(HS_LGraph* pGraph, HS_VERTEX_SIZE* distRow, HS_VERTEX_SIZE** distColume)
{
    if (!pGraph || !pGraph -> vexSize)
        return NULL;
    
    HS_VERTEX_SIZE vSize = pGraph -> vexSize;
    *distRow = vSize;
    HS_DISTANCE** distM = (HS_DISTANCE**)calloc(vSize, sizeof(HS_DISTANCE*));
    *distColume = (HS_VERTEX_SIZE*)calloc(vSize, sizeof(HS_VERTEX_SIZE));
    for (int i = 0 ; i < vSize ; ++i)
    {
        distM[i] = (HS_DISTANCE*)calloc(vSize, sizeof(HS_DISTANCE));
        (*distColume)[i] = vSize;
    }
    
    for (HS_GRAPH_INDEX i = 0 ; i < vSize ; ++i)
        for (HS_GRAPH_INDEX j = 0 ; j < vSize; ++j)
            distM[i][j] = i == j ? 0: INT_MAX;
    
    //初始化距离矩阵
    for (HS_GRAPH_INDEX i = 0; i < vSize; ++i)
    {
        HS_ENODE* tmpEdg = pGraph -> elements[i].edges;
        while (tmpEdg)
        {
            distM[i][tmpEdg -> tVex] = tmpEdg -> weight;
            tmpEdg = tmpEdg -> next;
        }
    }
    
    for (HS_GRAPH_INDEX k = 0 ; k < vSize ; ++k)
    {
        for (HS_GRAPH_INDEX i = 0 ; i < vSize ; ++i)
        {
            for (HS_GRAPH_INDEX j = 0 ; j < vSize ; ++j)
            {
                if(distM[i][k] != INT_MAX && distM[k][j] != INT_MAX && distM[i][k] + distM[k][j] < distM[i][j])
                    distM[i][j] = distM[i][k] + distM[k][j];
            }
        }
    }
    
    return distM;
}


/**
 * 释放图
 * @param pGraph 图指针
 */
void hs_graphFree(HS_LGraph* pGraph)
{
    if(pGraph)
    {
        if(pGraph -> elements)
        {
            HS_ENODE * tmp = NULL;
            for (HS_GRAPH_INDEX i = 0 ; i < pGraph -> vexSize ; ++i)
            {
                while (pGraph -> elements[i].edges)
                {
                    tmp = pGraph -> elements[i].edges;
                    pGraph -> elements[i].edges = tmp -> next;
                    free(tmp);
                }
            }
            free(pGraph -> elements);
        }
        free(pGraph);
    }
}








void hs_graphPrint(HS_LGraph* pGraph)
{
    if(pGraph)
    {
        if(pGraph -> elements)
        {
            printf("图的顶点有：");
            for (HS_GRAPH_INDEX i = 0 ; i < pGraph -> vexSize ; ++i)
            {
                printf("%d, ", pGraph -> elements[i].data);
            }
        
            HS_ENODE * tmp = NULL;
            for (HS_GRAPH_INDEX i = 0 ; i < pGraph -> vexSize ; ++i)
            {
                printf("\n顶点 %d 指向：", pGraph -> elements[i].data);
                tmp = pGraph -> elements[i].edges;
                while (tmp)
                {
                    printf("%d ", tmp -> tVex);
                    printf(" 权值：%d, ", tmp -> weight);
                    tmp = tmp -> next;
                }
    
            }
            printf("\n");
        }
    }
}


/**
 * 打印路径
 * @param path 路径数据
 * @param pathLen 路径数据长度
 * @param from 起始顶点
 * @param to 目的顶点
 */
void hs_graphPrintPath(HS_PATH* path, HS_PATH pathLen, HS_GRAPH_INDEX from, HS_GRAPH_INDEX to)
{
    if(from >= pathLen || to >= pathLen)
    {
        printf("error : 路径出错" );
        return;
    }
    if (from == to)
        return;
    
    hs_graphPrintPath( path, pathLen, from, path[to]);
    printf(" -> %u", to);
}
