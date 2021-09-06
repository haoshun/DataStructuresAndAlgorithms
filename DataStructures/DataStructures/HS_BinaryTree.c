//
//  HS_BinaryTree.c
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/12.
//  Copyright © 2020 Shun. All rights reserved.
//

#include "HS_BinaryTree.h"
#include "HS_CircleQueue.h"



#include "HS_Stack.h"
#include "HS_String.h"




struct hs_binary_tree{
    HS_Tree_Node* root;
    HS_TREE_SIZE size;
};






/**
 * 根据字符串按层序创建二叉树（类LeetCode测试用例的建树方式）
 * eg.   [1,2,3,4,0,null,6,null,8,10,null,11,12]
 * @param elements 元素数组
 * @param error 返回创建错误信息
 * @return 返回二叉树指针
 */
HS_BinaryTree* hs_binaryTreeNew(char* elements, HS_STATUS * error)
{
    HS_BinaryTree* result = NULL;
    char* verifiedStr = validString(elements, error);
    if (verifiedStr && (*error) == HS_SUCCEED)
    {
        result = (HS_BinaryTree*)malloc(sizeof(HS_BinaryTree));
        if (result)
        {
            result -> root = NULL;
            result -> size = 0;
        }
        if (strlen(verifiedStr))
        {
            HS_CircleQueue* pQueue = hs_circleQueueNew();
            unsigned long e_len = strlen(verifiedStr);
            int nodeValue = 0;
            HS_Tree_Node* pNode = NULL, *parent;
            bool isLeftChild = true;
            for (unsigned long i = 0, left = 0,  numLen  = 0 ; i < e_len; ++i)
            {
                if (verifiedStr[i] == '-')
                    numLen++;
                else if(verifiedStr[i] >='0' && verifiedStr[i] <= '9')
                    numLen++;
                else if(verifiedStr[i] == 'n')
                {
                    if (!isLeftChild) {
                        hs_circleQueueDeQueue(pQueue);
                    }
                    left += 5;
                    i += 4;
                    isLeftChild = !isLeftChild;
                }
                else
                {
                    nodeValue = strToInt(verifiedStr + left, numLen);
                    pNode = hs_treeNodeNew(nodeValue);
                    if (!result -> size)
                    {
                        result -> root = pNode;
                    }
                    else
                    {
                        parent  = hs_circleQueueFront(pQueue);
                        if (isLeftChild) {
                            parent -> left = pNode;
                        }
                        else
                        {
                            parent -> right = pNode;
                            hs_circleQueueDeQueue(pQueue);
                        }
                        isLeftChild = !isLeftChild;
                    }
                    hs_circleQueueEnQueue(pQueue, pNode);
                    result -> size ++;
                    left += numLen + 1;
                    numLen = 0;
                }
                if (i == e_len - 1)
                {
                    if (numLen)
                    {
                        nodeValue = strToInt(verifiedStr + left, numLen);
                        pNode = hs_treeNodeNew(nodeValue);
                        if (!result -> size)
                        {
                            result -> root = pNode;
                        }
                        else
                        {
                            parent  = hs_circleQueueFront(pQueue);
                            if (isLeftChild) {
                                parent -> left = pNode;
                            }
                            else
                            {
                                parent -> right = pNode;
                                
                            }
                        }
                        result -> size ++;
                        hs_circleQueueFree(pQueue);
                    }
                }
            }
        }
    }
    return result;
}


/**
 * 二叉树是否为空树
 * @param pTree 二叉树指针
 * @return 若为空树返回true，否则false
 */
bool hs_binaryTreeEmpty(HS_BinaryTree* pTree)
{
    return pTree && !pTree -> root;
}


/**
 * 返回二叉树元素的数量
 * @param pTree 二叉树指针
 * @return 返回二叉树元素数
 */
HS_TREE_SIZE hs_binaryTreeSize(HS_BinaryTree* pTree)
{
    return pTree ? pTree -> size : 0;
}


HS_TREE_SIZE hs_depth(HS_Tree_Node* root)
{
    return !root ? 0: (hs_max(hs_depth(root -> left), hs_depth(root -> right)) + 1);
}

/**
 * @param pTree 二叉树指针
 * @return 返回二叉树的高度
 */
HS_TREE_SIZE hs_binaryTreeDepth(HS_BinaryTree* pTree)
{
    return pTree && pTree -> root ? hs_depth(pTree -> root): 0;
}


/**
 * 获取二叉树的根
 * @param pTree 二叉树指针
 * @return 若树存在返回二叉树的根
 */
HS_Tree_Node* hs_binaryTreeRoot(HS_BinaryTree* pTree)
{
    return pTree && pTree -> root ? pTree -> root: NULL;
}


void hs_preOrderRecursion(HS_Tree_Node* root, HS_TREE_ELEMENT_TYPE* pArray, HS_TREE_SIZE* index)
{
    if (!root) {
        return;
    }
    pArray[(*index)++] = root -> val;
    hs_preOrderRecursion(root -> left, pArray, index);
    hs_preOrderRecursion(root -> right, pArray, index);
}

void hs_preOrderIteration(HS_Tree_Node* root, HS_TREE_ELEMENT_TYPE* pArray)
{
    if(root && pArray)
    {
        HS_Tree_Node* tmp = root;
        HS_Stack* pStack = hs_stackNew();
        HS_TREE_SIZE index = 0;
        while (tmp || hs_stackSize(pStack))
        {
            if(!tmp)
                tmp = hs_stackPop(pStack);
            
            pArray[index++] = tmp -> val;
            
            if (tmp -> right) {
                hs_stackPush(pStack, tmp -> right);
            }
            
            tmp = tmp -> left;
        }
        hs_stackFree(pStack);
    }
}


/**
 * 返回二叉树元素的前序遍历
 * @param pTree 二叉树指针
 * @return 返回遍历结果指针
 */
HS_TREE_ELEMENT_TYPE* hs_preOrderTraversal(HS_BinaryTree* pTree)
{
    if (pTree && pTree -> size)
    {
        HS_TREE_ELEMENT_TYPE* pArray =(HS_TREE_ELEMENT_TYPE*) malloc(sizeof(HS_TREE_ELEMENT_TYPE) *pTree -> size);
        HS_TREE_SIZE index = 0;
        
        //hs_preOrderRecursion(pTree -> root, pArray, &index);
        hs_preOrderIteration(pTree -> root, pArray);
        return pArray;
    }
    return NULL;
}



void hs_inOrderRecursion(HS_Tree_Node* root, HS_TREE_ELEMENT_TYPE* pArray, HS_TREE_SIZE* index)
{
    if (!root) {
        return;
    }
    hs_inOrderRecursion(root -> left, pArray, index);
    pArray[(*index)++] = root -> val;
    hs_inOrderRecursion(root -> right, pArray, index);
}

void hs_inOrderIteration(HS_Tree_Node* root, HS_TREE_ELEMENT_TYPE* pArray)
{
    if(root && pArray)
    {
        HS_Tree_Node* tmp = root;
        HS_Stack* pStack = hs_stackNew();
        HS_TREE_SIZE index = 0;
        while (tmp || hs_stackSize(pStack))
        {
            if(!tmp)
                tmp = hs_stackPop(pStack);
            else
            {
                if (tmp -> left)
                {
                    hs_stackPush(pStack, tmp);
                    tmp = tmp -> left;
                    continue;
                }
            }
            
            pArray[index++] = tmp -> val;
            
            tmp = tmp -> right;
        }
        hs_stackFree(pStack);
    }
}

/**
 * 返回二叉树元素的中序遍历
 * @param pTree 二叉树指针
 * @return 返回遍历结果指针
 */
HS_TREE_ELEMENT_TYPE* hs_inOrderTraversal(HS_BinaryTree* pTree)
{
    if (pTree && pTree -> size)
    {
        HS_TREE_ELEMENT_TYPE* pArray =(HS_TREE_ELEMENT_TYPE*) malloc(sizeof(HS_TREE_ELEMENT_TYPE) *pTree -> size);
        HS_TREE_SIZE index = 0;
        
//        hs_inOrderRecursion(pTree -> root, pArray, &index);
        hs_inOrderIteration(pTree -> root, pArray);
        return pArray;
    }
    return NULL;
}


void hs_postOrderRecursion(HS_Tree_Node* root, HS_TREE_ELEMENT_TYPE* pArray, HS_TREE_SIZE* index)
{
    if (!root) {
        return;
    }
    hs_postOrderRecursion(root -> left, pArray, index);
    hs_postOrderRecursion(root -> right, pArray, index);
    pArray[(*index)++] = root -> val;
}

void hs_postOrderIteration(HS_Tree_Node* root, HS_TREE_ELEMENT_TYPE* pArray)
{
    if(root && pArray)
    {
        HS_Tree_Node* tmp = root , *parent = NULL;
        HS_Stack* pStack = hs_stackNew();
        HS_TREE_SIZE index = 0;
        while (tmp || hs_stackSize(pStack))
        {
            if(!tmp)
                tmp = hs_stackPop(pStack);
            else
            {
                if (tmp -> left)
                {
                    hs_stackPush(pStack, tmp);
                    tmp = tmp -> left;
                    continue;
                }
                if (tmp -> right)
                {
                    hs_stackPush(pStack, tmp);
                    tmp = tmp -> right;
                    continue;
                }
            }
            
            pArray[index++] = tmp -> val;
            
            if (hs_stackSize(pStack))
            {
                parent = hs_stackTop(pStack);
                if (parent -> left == tmp) {
                    tmp = parent -> right;
                    continue;
                }
            }
            
            tmp = NULL;
        }
        hs_stackFree(pStack);
    }
}

/**
 * 返回二叉树元素的后序遍历
 * @param pTree 二叉树指针
 * @return 返回遍历结果指针
 */
HS_TREE_ELEMENT_TYPE* hs_postOrderTraversal(HS_BinaryTree* pTree)
{
    if (pTree && pTree -> size)
    {
        HS_TREE_ELEMENT_TYPE* pArray =(HS_TREE_ELEMENT_TYPE*) malloc(sizeof(HS_TREE_ELEMENT_TYPE) *pTree -> size);
        HS_TREE_SIZE index = 0;
        
//        hs_postOrderRecursion(pTree -> root, pArray, &index);
        hs_postOrderIteration(pTree -> root, pArray);
        return pArray;
    }
    return NULL;
}


/**
 * 返回二叉树元素的层序遍历
 * @param pTree 二叉树指针
 * @return 返回遍历结果指针
 */
HS_TREE_ELEMENT_TYPE* hs_levelOrderTraversal(HS_BinaryTree* pTree)
{
    if (pTree && pTree -> size)
    {
        HS_TREE_ELEMENT_TYPE* pArray =(HS_TREE_ELEMENT_TYPE*) malloc(sizeof(HS_TREE_ELEMENT_TYPE) *pTree -> size);
        HS_TREE_SIZE index = 0;
        
        HS_Tree_Node* tmp = NULL;
        HS_CircleQueue* pQueue = hs_circleQueueNew();
        hs_circleQueueEnQueue(pQueue, pTree -> root);
        while (hs_circleQueueSize(pQueue))
        {
            tmp = hs_circleQueueDeQueue(pQueue);
            pArray[index++] = tmp -> val;
            if (tmp -> left) {
                hs_circleQueueEnQueue(pQueue, tmp -> left);
            }
            if (tmp -> right) {
                hs_circleQueueEnQueue(pQueue, tmp -> right);
            }
        }
        return pArray;
    }
    return NULL;
}


/**
 * 二叉树是否为完全二叉树
 * @param pTree 二叉树指针
 * @return 若为完全二叉树返回true，否则false
 */
bool hs_binaryTreeIsComplete(HS_BinaryTree* pTree)
{
    if (!pTree)
        return false;
    if (hs_binaryTreeEmpty(pTree))
        return true;
    HS_CircleQueue *pQueue = hs_circleQueueNew();
    HS_Tree_Node* tmp = NULL;
    hs_circleQueueEnQueue(pQueue, pTree -> root);
    bool isLeaf = false;
    HS_TREE_SIZE index = 0;
    while (hs_circleQueueSize(pQueue))
    {
        tmp = hs_circleQueueDeQueue(pQueue);
        index++;
        
        if (isLeaf && (tmp -> left || tmp -> right))
            break;
        
        if (!tmp -> left && tmp -> right)
            break;
            
        if (tmp -> left) {
            hs_circleQueueEnQueue(pQueue, tmp -> left);
        }
        
        if (tmp -> right) {
            hs_circleQueueEnQueue(pQueue, tmp -> right);
        }
        
        if (!tmp -> left && !tmp -> right) {
            isLeaf = true;
        }
    }
    hs_circleQueueFree(pQueue);
    
    return index == pTree -> size;
}





