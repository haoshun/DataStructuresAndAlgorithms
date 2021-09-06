//
//  HS_AVL.h
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/28.
//  Copyright © 2020 Shun. All rights reserved.
//

#ifndef HS_AVL_h
#define HS_AVL_h

#include <stdio.h>

#include "HS_Define.h"

typedef struct hs_avl_tree HS_AVL;

/**
 * 创建AVL树
 * @return 返回AVL树指针
 */
HS_AVL* hs_avlNew(void);


/**
 * 根据数组创建AVL树
 * @param elements 元素数组
 * @param elementSize 数组长度
 * @return 返回AVL树指针
 */
HS_AVL* hs_avlNewWithElements(HS_TREE_ELEMENT_TYPE* elements, HS_TREE_SIZE elementSize);


/**
 * 清除AVL树所有元素
 * @param pTree 树指针
 */
void hs_avlClear(HS_AVL* pTree);


/**
 * AVL树是否为空树
 * @param pTree 树指针
 * @return 若为空树返回true，否则false
 */
bool hs_avlIsEmpty(HS_AVL* pTree);


/**
 * 获取AVL树节点的数量
 * @param pTree 树指针
 * @return 返回AVL树元素数
 */
HS_TREE_SIZE hs_avlSize(HS_AVL* pTree);


/**
 * 获取AVL树的根
 * @param pTree 树指针
 * @return 若树存在返回AVL树的根
 */
HS_AVL_Node* hs_avlRoot(HS_AVL* pTree);


/**
 * 获取AVL树的高度
 * 这里取严蔚敏《数据结构（C语言版）》（第三版）中的定义
 * 树节点的层次从根开始定义，根为第1层。树中节点的最大层次称为树的深度或高度。
 * 在这个定义中，树节点的层次数和其所在的深度相等，高度为树最大层数减当前所在层数再加1
 * 即根节点深度为1，叶子节点高度为1
 * @param pTree 树指针
 * @return 返回AVL树高度
 */
HS_TREE_HEIGHT hs_avlHeight(HS_AVL* pTree);


/**
 * 元素是否在AVL树中
 * @param pTree 树指针
 * @param element 待判定元素
 * @return 若在树中返回节点指针，否则返回NULL
 */
HS_AVL_Node* hs_avlSearch(HS_AVL* pTree, HS_TREE_ELEMENT_TYPE element);


/**
 * 向AVL树添加元素
 * @param pTree 树指针
 * @param element 待添加元素
 */
void hs_avlAdd(HS_AVL* pTree, HS_TREE_ELEMENT_TYPE element);


/**
 * 删除AVL树中与element相等的节点
 * @param pTree 树指针
 * @param element 待删除元素
 */
void hs_avlRemove(HS_AVL* pTree, HS_TREE_ELEMENT_TYPE element);


/**
 * 销毁AVL树
 * @param pTree 树指针
 */
void hs_avlDestroy(HS_AVL* pTree);

#endif /* HS_AVL_h */
