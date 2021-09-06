//
//  HS_RBT.h
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/30.
//  Copyright © 2020 Shun. All rights reserved.
//

#ifndef HS_RBT_h
#define HS_RBT_h

#include <stdio.h>
#include "HS_Define.h"

typedef struct hs_r_b_tree HS_RBT;

/**
 * 创建R-B树
 * @return 返回R-B树指针
 */
HS_RBT* hs_rbtNew(void);

/**
 * 根据数组创建R-B树
 * @param elements 元素数组
 * @param elementSize 数组长度
 * @return 返回R-B树指针
 */
HS_RBT* hs_rbtNewWithElements(HS_TREE_ELEMENT_TYPE* elements, HS_TREE_SIZE elementSize);

/**
 * R-B树是否为空树
 * @param pTree 树指针
 * @return 若为空树返回true，否则false
 */
bool hs_rbtIsEmpty(HS_RBT* pTree);

/**
 * 获取R-B树节点的数量
 * @param pTree 树指针
 * @return 返回R-B树元素数
 */
HS_TREE_SIZE hs_rbtSize(HS_RBT* pTree);

/**
 * 获取R-B树的根
 * @param pTree 树指针
 * @return 若树存在返回R-B树的根
 */
HS_RBT_Node* hs_rbtRoot(HS_RBT* pTree);

/**
 * 获取R-B树的高度
 * 这里取严蔚敏《数据结构（C语言版）》（第三版）中的定义
 * 树节点的层次从根开始定义，根为第1层。树中节点的最大层次称为树的深度或高度。
 * 在这个定义中，树节点的层次数和其所在的深度相等，高度为树最大层数减当前所在层数再加1
 * 即根节点深度为1，叶子节点高度为1
 * @param pTree 树指针
 * @return 返回R-B树高度
 */
HS_TREE_HEIGHT hs_rbtHeight(HS_RBT* pTree);

/**
 * 元素是否在R-B树中
 * @param pTree 树指针
 * @param element 待判定元素
 * @return 若在树中返回节点指针，否则返回NULL
 */
HS_RBT_Node* hs_rbtSearch(HS_RBT* pTree, HS_TREE_ELEMENT_TYPE element);

/**
 * 向R-B树添加元素
 * @param pTree 树指针
 * @param element 待添加元素
 */
void hs_rbtAdd(HS_RBT* pTree, HS_TREE_ELEMENT_TYPE element);

/**
 * 删除R-B树中与element相等的节点
 * @param pTree 树指针
 * @param element 待删除元素
 */
void hs_rbtRemove(HS_RBT* pTree, HS_TREE_ELEMENT_TYPE element);

/**
 * 销毁R-B树
 * @param pTree 树指针
 */
void hs_rbtDestroy(HS_RBT* pTree);

#endif /* HS_RBT_h */
