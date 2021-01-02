//
//  HS_Define.h
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/8.
//  Copyright © 2020 Shun. All rights reserved.
//

#ifndef HS_Define_h
#define HS_Define_h

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

//#define AVL_TREETEST
#define TREETEST

typedef long long HS_QUEUE_SIZE;
typedef HS_QUEUE_SIZE HS_QUEUE_INDEX;

typedef unsigned long HS_TREE_SIZE;
typedef HS_TREE_SIZE HS_TREE_HEIGHT;
typedef int HS_TREE_ELEMENT_TYPE;

struct hs_binary_tree_node{
    struct hs_binary_tree_node* left;
    struct hs_binary_tree_node* right;
    HS_TREE_ELEMENT_TYPE val;
};
typedef struct hs_binary_tree_node HS_Tree_Node;


struct hs_avl_node{
    struct hs_avl_node* left;
    struct hs_avl_node* right;
    HS_TREE_HEIGHT height;
    HS_TREE_ELEMENT_TYPE val;
};
typedef struct hs_avl_node HS_AVL_Node;


typedef  enum
{
    //黑色
    HS_BLACK = 1,
    //红色
    HS_RED
} HS_COLOR;


struct hs_r_b_node{
    struct hs_r_b_node* left;
    struct hs_r_b_node* right;
    struct hs_r_b_node* parent;
    HS_TREE_ELEMENT_TYPE val;
    HS_COLOR color;
};
typedef struct hs_r_b_node HS_RBT_Node;

//#ifdef TREETEST
//typedef HS_Tree_Node* HS_ELEMENT_TYPE;
//
//#else
//typedef int HS_ELEMENT_TYPE;
//
//#endif

#ifdef AVL_TREETEST
typedef HS_AVL_Node* HS_ELEMENT_TYPE;

#else
typedef HS_Tree_Node* HS_ELEMENT_TYPE;

#endif



typedef  enum
{
    //成功
    HS_SUCCEED = 1,
    //输入错误
    HS_INPUT_ERROR
} HS_STATUS;






typedef HS_Tree_Node* HS_CQUEUE_ELEMENT_TYPE;
typedef HS_Tree_Node*  HS_STACK_ELEMENT_TYPE;

unsigned long hs_max(unsigned long num1, unsigned long num2);

HS_Tree_Node* hs_treeNodeNew(HS_TREE_ELEMENT_TYPE val);


#endif /* HS_Define_h */
