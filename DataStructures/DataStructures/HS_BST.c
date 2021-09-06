//
//  HS_BST.c
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/23.
//  Copyright © 2020 Shun. All rights reserved.
//

#include "HS_BST.h"

struct hs_binary_search_tree{
    HS_Tree_Node* root;
    HS_TREE_SIZE size;
};


/**
 * 根据数组创建二叉搜索树
 * @return 返回二叉搜索树指针
 */
HS_BST* hs_bstNew(void)
{
    HS_BST* pBST = (HS_BST*)malloc(sizeof(HS_BST));
    if (pBST)
    {
        pBST -> root = NULL;
        pBST -> size = 0;
    }
    return pBST;
}


/**
 * 根据数组创建二叉搜索树
 * @param elements 元素数组
 * @param elementSize 数组长度
 * @return 返回二叉搜索树指针
 */
HS_BST* hs_bstNewWithElements(HS_TREE_ELEMENT_TYPE* elements, HS_TREE_SIZE elementSize)
{
    HS_BST* pBST = NULL;
    if (elements && elementSize)
    {
        pBST = hs_bstNew();
        if(pBST)
            for (HS_TREE_SIZE i = 0 ; i < elementSize; ++i)
                hs_bstAdd(pBST, elements[i]);
    }
    return pBST;
}


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
bool hs_bstIsEmpty(HS_BST* pTree)
{
    return pTree && !pTree -> root;
}


/**
 * 获取二叉搜索树节点的数量
 * @param pTree 树指针
 * @return 返回二叉树元素数
 */
HS_TREE_SIZE hs_bstSize(HS_BST* pTree)
{
    return pTree ? pTree -> size : 0;
}


/**
 * 获取二叉搜索树的根
 * @param pTree 树指针
 * @return 若树存在返回二叉树的根
 */
HS_Tree_Node* hs_bstRoot(HS_BST* pTree)
{
    return pTree && pTree -> root ? pTree -> root: NULL;
}


/**
 * 向二叉搜索树添加元素
 * @param pTree 树指针
 * @param element 待添加元素
 */
void hs_bstAdd(HS_BST* pTree, HS_TREE_ELEMENT_TYPE element)
{
    if (pTree)
    {
        HS_Tree_Node* newNode = hs_treeNodeNew(element);
        if (!pTree -> root)
        {
            pTree -> root = newNode;
        }
        else
        {
            HS_Tree_Node* tmp = pTree -> root;
            HS_Tree_Node* parent = NULL;
            while (tmp)
            {
                //这里可以覆盖相等的值
                if (tmp -> val == element)
                    break;
                parent = tmp;
                if (tmp -> val > element)
                    tmp = tmp -> left;
                else
                    tmp = tmp -> right;
            }
            if (parent -> val > element)
                parent -> left = newNode;
            else
                parent -> right = newNode;
        }
        pTree -> size++;
    }
}


/**
 * 元素是否在二叉搜索树中
 * @param pTree 树指针
 * @param element 待判定元素
 * @return 若在树中返回true，否则false
 */
bool hs_bstContains(HS_BST* pTree, HS_TREE_ELEMENT_TYPE element)
{
    if(hs_bstIsEmpty(pTree))
        return false;
    HS_Tree_Node* target = pTree -> root;
    while (target)
    {
        if (target -> val == element)
            break;
        else if (target -> val > element)
            target = target -> left;
        else
            target = target -> right;
    }
    return target? true: false;
}


/**
 * 删除二叉搜索树中与element相等的节点
 * 若树中找不到相等的节点，不做任何操作
 * @param pTree 树指针
 * @param element 待删除元素
 */
void hs_bstRemove(HS_BST* pTree, HS_TREE_ELEMENT_TYPE element)
{
    if(!hs_bstIsEmpty(pTree))
    {
        HS_Tree_Node* target = pTree -> root, * parent = NULL;
        //搜索目标节点
        while(target)
        {
            if(target -> val == element)
                break;
            parent = target;
            if(target -> val > element)
                target = target -> left;
            else if(target -> val < element)
                target = target -> right;
        }
        if(target)
        {
            //叶子节点
            if(!target -> left && !target -> right)
            {
                //若为根节点
                if(target == pTree -> root)
                    pTree -> root = NULL;
                else
                {
                    if(parent -> left == target)
                        parent -> left = NULL;
                    else
                        parent -> right = NULL;
                }
            }
            //度为2的节点
            else if(target -> left && target -> right)
            {
                //寻找后继节点
                HS_Tree_Node* successor = target -> right;
                parent = target;
                while(successor -> left)
                {
                    parent = successor;
                    successor = successor -> left;
                }
                target -> val = successor -> val;
                //后继节点的度只能为0或1
                if(successor == parent -> left)
                    parent -> left = successor -> right;
                else
                    parent -> right = successor -> right;
            }
            //度为1的节点
            else
            {
                //这里也可以通过target != root 判断
                if(parent)
                {
                    if(parent -> left == target)
                        parent -> left = target -> left ? target -> left : target -> right;
                    else
                        parent -> right = target -> left ? target -> left : target -> right;
                }
                //若为根节点
                else
                    pTree -> root = pTree -> root -> left ?  pTree -> root -> left : pTree -> root -> right;

            }
            pTree -> size--;
        }
    }
}


