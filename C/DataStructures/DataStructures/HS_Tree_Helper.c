//
//  HS_Tree_Helper.c
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/15.
//  Copyright © 2020 Shun. All rights reserved.
//

#include "HS_Tree_Helper.h"
#include "HS_CircleQueue.h"

void hs_printBinaryTree(HS_Tree_Node* pTree)
{
    if (!(pTree))
    {
        printf("Empty tree \n");
    }
    else
    {
        HS_CircleQueue* pQueue = hs_circleQueueNew();
        hs_circleQueueEnQueue(pQueue, pTree);
        printf("%d \n" , pTree ->val);
        HS_Tree_Node* tmp = NULL;
        long long count = 1;
        while (hs_circleQueueSize(pQueue))
        {
            count = hs_circleQueueSize(pQueue);
            while (count) {
                tmp = hs_circleQueueDeQueue(pQueue);
                --count;
                if (tmp -> left) {
                    printf("%d ", tmp -> left -> val);
                    hs_circleQueueEnQueue(pQueue, tmp -> left);
                }
                else{
                    printf("null ");
                }
                if (tmp -> right) {
                    printf("%d ", tmp -> right -> val);
                    hs_circleQueueEnQueue(pQueue, tmp -> right);
                }
                else{
                    printf("null ");
                }
            }
            printf("\n");
        }
        hs_circleQueueFree(pQueue);
    }
}


