//
//  HS_BST.h
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/23.
//  Copyright © 2020 Shun. All rights reserved.
//

#ifndef HS_BST_h
#define HS_BST_h

#include <stdio.h>

#include "HS_Define.h"

typedef struct hs_binary_search_tree HS_BST;


/**
 * 创建二叉搜索树
 * @return 返回二叉搜索树指针
 */
HS_BST* hs_bstNew(void);


/**
 * 根据数组创建二叉搜索树
 * @param elements 元素数组
 * @param elementSize 数组长度
 * @return 返回二叉搜索树指针
 */
HS_BST* hs_bstNewWithElements(HS_TREE_ELEMENT_TYPE* elements, HS_TREE_SIZE elementSize);


/**
 * 清除二叉搜索树所有元素
 * @param pTree 树指针
 */
void hs_bstClear(HS_BST* pTree);


/**
 * 二叉搜索树是否为空树
 * @param pTree 树指针
 * @return 若为空树返回true，否则false
 */
bool hs_bstIsEmpty(HS_BST* pTree);


/**
 * 获取二叉搜索树节点的数量
 * @param pTree 树指针
 * @return 返回二叉树元素数
 */
HS_TREE_SIZE hs_bstSize(HS_BST* pTree);


/**
 * 获取二叉搜索树的根
 * @param pTree 树指针
 * @return 若树存在返回二叉树的根
 */
HS_Tree_Node* hs_bstRoot(HS_BST* pTree);


/**
 * 向二叉搜索树添加元素
 * @param pTree 树指针
 * @param element 待添加元素
 */
void hs_bstAdd(HS_BST* pTree, HS_TREE_ELEMENT_TYPE element);


/**
 * 元素是否在二叉搜索树中
 * @param pTree 树指针
 * @param element 待判定元素
 * @return 若在树中返回true，否则false
 */
bool hs_bstContains(HS_BST* pTree, HS_TREE_ELEMENT_TYPE element);


/**
 * 删除二叉搜索树中与element相等的节点
 * @param pTree 树指针
 * @param element 待删除元素
 */
void hs_bstRemove(HS_BST* pTree, HS_TREE_ELEMENT_TYPE element);

#endif /* HS_BST_h */
