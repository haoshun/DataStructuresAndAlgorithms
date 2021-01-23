//
//  HS_LGraph.h
//  Graph
//
//  Created by 郝源顺 on 2021/1/20.
//

#ifndef HS_LGraph_h
#define HS_LGraph_h

#include <stdio.h>
#include "HS_Define.h"
#include "HS_MinHeap.h"


typedef struct hs_list_graph HS_LGraph;

/**
 * 创建基于邻接表存储的图
 * @return 返回图指针
 */
HS_LGraph* hs_graphNew(void);

/**
 * 根据顶点数组和边缘列表创建基于邻接表存储的无向无权图
 * @param datas 顶点元素数组
 * @param dataNum 顶点数
 * @param grid 边缘列表（二维数组，每行第一列表示边的起点，第二列表示边的终点）
 * @param gridSize 边缘列表行数
 * @return 返回图指针
 */
HS_LGraph* hs_graphCreateUG(HS_ELEMENT_TYPE* datas, HS_VERTEX_SIZE dataNum, HS_ELEMENT_TYPE** grid, HS_EDGE_SIZE gridSize);

/**
 * 根据顶点数组和边缘列表创建基于邻接表存储的无向有权图
 * @param datas 顶点元素数组
 * @param dataNum 顶点数
 * @param grid 边缘列表（二维数组，每行第一列表示边的起点，第二列表示边的终点，第三列代表该边的权值）
 * @param gridSize 边缘列表行数
 * @return 返回图指针
 */
HS_LGraph* hs_graphCreateUGWithWeight(HS_ELEMENT_TYPE* datas, HS_VERTEX_SIZE dataNum, HS_ELEMENT_TYPE** grid, HS_EDGE_SIZE gridSize);

/**
 * 根据顶点数组和边缘列表创建基于邻接表存储的有向无权图
 * @param datas 顶点元素数组
 * @param dataNum 顶点数
 * @param grid 边缘列表（二维数组，每行第一列表示边的起点，第二列表示边的终点）
 * @param gridSize 边缘列表行数
 * @return 返回图指针
 */
HS_LGraph* hs_graphCreateDG(HS_ELEMENT_TYPE* datas, HS_VERTEX_SIZE dataNum, HS_ELEMENT_TYPE** grid, HS_EDGE_SIZE gridSize);

/**
 * 根据顶点数组和边缘列表创建基于邻接表存储的有向有权图
 * @param datas 顶点元素数组
 * @param dataNum 顶点数
 * @param grid 边缘列表（二维数组，每行第一列表示边的起点，第二列表示边的终点，第三列代表该边的权值）
 * @param gridSize 边缘列表行数
 * @return 返回图指针
 */
HS_LGraph* hs_graphCreateDGWithWeight(HS_ELEMENT_TYPE* datas, HS_VERTEX_SIZE dataNum, HS_ELEMENT_TYPE** grid, HS_EDGE_SIZE gridSize);


/**
 * 最小生成树(MST)
 * Prim 算法
 * 有权连通图
 * @param pGraph 图指针
 * @param start 从该顶点开始生成
 * @param gridSize 边缘列表行数
 * @return 按边缘列表方式返回MST的所有边（前两列表示边的两个顶点，第三列代表该边权值）
 */
HS_ELEMENT_TYPE** hs_graphMSTPrim(HS_LGraph* pGraph, HS_GRAPH_INDEX start, HS_EDGE_SIZE* gridSize);


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
HS_DISTANCE hs_graphDijkstra(HS_LGraph* pGraph, HS_GRAPH_INDEX vex_s, HS_GRAPH_INDEX vex_t, HS_PATH** path, HS_PATH* pathLen);


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
HS_DISTANCE* hs_graphBellman_Ford(HS_LGraph* pGraph, HS_GRAPH_INDEX src, HS_VERTEX_SIZE* distLen, bool* hasNWL);


/**
 * 多源最短路径
 * Floyd 算法
 * 支持负权边
 * @param pGraph 图指针
 * @param distRow 返回的矩阵行数
 * @param distColume 返回的矩阵每行的列数
 * @return 返回路径距离矩阵
 */
HS_DISTANCE** hs_graphFloyd(HS_LGraph* pGraph, HS_VERTEX_SIZE* distRow, HS_VERTEX_SIZE** distColume);



/**
 * 释放图
 * @param pGraph 图指针
 */
void hs_graphFree(HS_LGraph* pGraph);




/**
 * 打印图
 * @param pGraph 图指针
 */
void hs_graphPrint(HS_LGraph* pGraph);

/**
 * 打印路径
 * @param path 路径数据
 * @param pathLen 路径数据长度
 * @param from 起始顶点
 * @param to 目的顶点
 */
void hs_graphPrintPath(HS_PATH* path, HS_PATH pathLen, HS_GRAPH_INDEX from, HS_GRAPH_INDEX to);

#endif /* HS_LGraph_h */
