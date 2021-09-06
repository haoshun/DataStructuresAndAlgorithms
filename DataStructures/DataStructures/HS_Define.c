//
//  HS_Define.c
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/8.
//  Copyright © 2020 Shun. All rights reserved.
//

#include "HS_Define.h"

unsigned long hs_max(unsigned long num1, unsigned long num2)
{
    return num1 > num2 ? num1 : num2;
}


HS_Tree_Node* hs_treeNodeNew(HS_TREE_ELEMENT_TYPE val)
{
    HS_Tree_Node* pNode = (HS_Tree_Node*) malloc(sizeof(HS_Tree_Node));
    if (pNode)
    {
        pNode -> left = NULL;
        pNode -> right = NULL;
        pNode -> val = val;
    }
    return pNode;
}


