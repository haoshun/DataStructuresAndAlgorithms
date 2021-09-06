//
//  HS_BinaryTree.h
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/12.
//  Copyright © 2020 Shun. All rights reserved.
//

#ifndef HS_BinaryTree_h
#define HS_BinaryTree_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HS_Define.h"
#include "HS_Array.h"


//#ifndef HS_ELEMENT_TYPE
//typedef int HS_ELEMENT_TYPE;
//#endif

typedef struct hs_binary_tree HS_BinaryTree;

/**
 * 根据字符串按层序创建二叉树（类LeetCode建树方式）
 * eg.   [1,2,3,4,0,null,6,null,8,10,null,11,12]
 * @param elements 元素数组
 * @param error 返回创建错误信息
 * @return 返回二叉树指针
 */
HS_BinaryTree* hs_binaryTreeNew(char* elements, HS_STATUS * error);

/**
 * 清除二叉树所有元素
 * @param pTree 二叉树指针
 */
void hs_binaryTreeClear(HS_BinaryTree* pTree);

/**
 * 二叉树是否为空树
 * @param pTree 二叉树指针
 * @return 若为空树返回true，否则false
 */
bool hs_binaryTreeEmpty(HS_BinaryTree* pTree);

/**
 * 获取二叉树元素的数量
 * @param pTree 二叉树指针
 * @return 返回二叉树元素数
 */
HS_TREE_SIZE hs_binaryTreeSize(HS_BinaryTree* pTree);

/**
 * 获取二叉树的深度（高度、最大层数）
 * 这里取严蔚敏《数据结构（C语言版）》（第三版）中的定义
 * 树节点的层次从根开始定义，根为第1层。树中节点的最大层次称为树的深度或高度。
 * 在这个定义中，树节点的层次数和其所在的深度相等，高度为树最大层数减当前所在层数再加1
 * 即根节点深度为1，叶子节点高度为1
 * @param pTree 二叉树指针
 * @return 返回二叉树的高度
 */
HS_TREE_SIZE hs_binaryTreeDepth(HS_BinaryTree* pTree);

/**
 * 获取二叉树的根
 * @param pTree 二叉树指针
 * @return 若树存在返回二叉树的根
 */
HS_Tree_Node* hs_binaryTreeRoot(HS_BinaryTree* pTree);

/**
 * 返回二叉树元素的前序遍历
 * @param pTree 二叉树指针
 * @return 返回遍历结果指针
 */
HS_TREE_ELEMENT_TYPE* hs_preOrderTraversal(HS_BinaryTree* pTree);

/**
 * 返回二叉树元素的中序遍历
 * @param pTree 二叉树指针
 * @return 返回遍历结果指针
 */
HS_TREE_ELEMENT_TYPE* hs_inOrderTraversal(HS_BinaryTree* pTree);

/**
 * 返回二叉树元素的后序遍历
 * @param pTree 二叉树指针
 * @return 返回遍历结果指针
 */
HS_TREE_ELEMENT_TYPE* hs_postOrderTraversal(HS_BinaryTree* pTree);

/**
 * 返回二叉树元素的层序遍历
 * @param pTree 二叉树指针
 * @return 返回遍历结果指针
 */
HS_TREE_ELEMENT_TYPE* hs_levelOrderTraversal(HS_BinaryTree* pTree);

/**
 * 二叉树是否为完全二叉树
 * @param pTree 二叉树指针
 * @return 若为完全二叉树返回true，否则false
 */
bool hs_binaryTreeIsComplete(HS_BinaryTree* pTree);


#endif /* HS_BinaryTree_h */
