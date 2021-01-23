//
//  main.c
//  Graph
//
//  Created by 郝源顺 on 2021/1/18.
//

#include <stdio.h>
#include "HS_LGraph.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    
//    int v[5] = {0,1,2,3,4};
//
//    HS_ELEMENT_TYPE grid[7][3]={{0,4,100}, {0,3,30}, {0,1,10}, {1,2,50}, {2,4,10}, {3,2,20}, {3,4,60}};
    
    int v[6] = {0,1,2,3,4,5};
    
    HS_ELEMENT_TYPE grid[8][3]={{0,1,10}, {0,4,15}, {1,3,2}, {1,2,15}, {3,2,1}, {2,5,5}, {3,5,12},{4,5,10}};
    
    int** example = (int**) malloc(sizeof(int*) * 8);
    for (int i = 0 ;  i < 8; ++i)
    {
        example[i] = grid[i];
    }
    
    HS_LGraph* pGraph = hs_graphCreateDGWithWeight(v, 6, example, 8);
    
    hs_graphPrint(pGraph);
    HS_PATH* path = NULL, pathLen = 0;
    HS_GRAPH_INDEX s = 0, t = 5;
    printf("\n 顶点 %d 到 顶点 %d 的最短路径长度为：%u\n", s, t, hs_graphDijkstra(pGraph, s, t, &path, &pathLen));
    printf("路径为: %u", s);
    hs_graphPrintPath(path, pathLen, s, t);
    printf("\n\n");
    
    
    //HS_DISTANCE* dists = NULL;
    HS_VERTEX_SIZE distLen = 0;
    bool hasHWL = false;
    HS_GRAPH_INDEX src = 0;
    HS_DISTANCE* dists = hs_graphBellman_Ford(pGraph, src, &distLen, &hasHWL);
    
    printf("从顶点 %u 出发\n", src);
    for (int i = 0 ; i < distLen; ++i)
    {
        printf("到顶点 %u 的最短路径为： %d \n", i , dists[i]);
    }
    printf("\n\n");
    
    HS_VERTEX_SIZE distRow = 0;
    HS_VERTEX_SIZE* distColume = NULL;
    HS_DISTANCE** distM = hs_graphFloyd(pGraph,  &distRow, &distColume);
    
    for (HS_GRAPH_INDEX i = 0 ; i < distRow; ++i)
    {
        printf("顶点 %u --------------------\n", i);
        for (HS_GRAPH_INDEX j = 0 ; j < distColume[j]; ++j)
        {
            if (distM[i][j] != INT_MAX)
            {
                printf("到顶点 %u 的最短路径距离为 %d \n",  j, distM[i][j]);
            }
        }
    }
    
    
    //创建无向有全图
    HS_LGraph* pUWGraph = hs_graphCreateUGWithWeight(v, 6, example, 8);
    HS_GRAPH_INDEX start = 3;
    HS_GRAPH_SIZE mstRow = 0;
    HS_ELEMENT_TYPE** mst = hs_graphMSTPrim(pUWGraph, start, &mstRow);
    printf("\n从顶点 %u 生成的最小生成树为：\n" , start);
    for (HS_GRAPH_INDEX i = 0 ; i < mstRow ; ++i)
    {
        printf("边： %d ——  %d  权值：%d\n", mst[i][0], mst[i][1], mst[i][2]);
    }
    
    
    return 0;
}
