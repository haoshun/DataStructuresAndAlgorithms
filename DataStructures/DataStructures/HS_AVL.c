//
//  HS_AVL.c
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/28.
//  Copyright © 2020 Shun. All rights reserved.
//

#include "HS_AVL.h"

struct hs_avl_tree{
    HS_AVL_Node* root;
    HS_TREE_SIZE size;
};

HS_AVL_Node* hs_avlNodeNew(HS_TREE_ELEMENT_TYPE val)
{
    HS_AVL_Node* pNode = (HS_AVL_Node*) malloc(sizeof(HS_AVL_Node));
    if (pNode)
    {
        pNode -> left = NULL;
        pNode -> right = NULL;
        pNode -> val = val;
        pNode -> height = 0;
    }
    return pNode;
}

HS_TREE_HEIGHT hs_avl_height(HS_AVL_Node* pNode)
{
    return pNode ? pNode -> height: 0;
}

void hs_update_height(HS_AVL_Node* pNode)
{
    pNode -> height = hs_max(hs_avl_height(pNode -> left), hs_avl_height(pNode -> right)) + 1;
}

//LL 右旋
HS_AVL_Node* hs_left_left_rotate(HS_AVL_Node* pNode)
{
    HS_AVL_Node* pLeftChild = pNode -> left;
    pNode -> left = pLeftChild -> right;
    pLeftChild -> right = pNode;
    
    hs_update_height(pNode);
    hs_update_height(pLeftChild);
    
    return pLeftChild;
}

//RR 左旋
HS_AVL_Node* hs_right_right_rotate(HS_AVL_Node* pNode)
{
    HS_AVL_Node* pRightChild = pNode -> right;
    pNode -> right = pRightChild -> left;
    pRightChild -> left = pNode;
    
    hs_update_height(pNode);
    hs_update_height(pRightChild);
    
    return pRightChild;
}

//LR: 先RR(左旋) 再LL(右旋)
HS_AVL_Node* hs_left_right_rotate(HS_AVL_Node* pNode)
{
    pNode -> left = hs_right_right_rotate(pNode -> left);
    return hs_left_left_rotate(pNode);
}

//RL: 先LL(右旋) 再RR(左旋)
HS_AVL_Node* hs_right_left_rotate(HS_AVL_Node* pNode)
{
    pNode -> right = hs_left_left_rotate(pNode -> right);
    return hs_right_right_rotate(pNode);
}

//向AVL树添加节点
HS_AVL_Node* hs_insert(HS_AVL_Node* pRoot, HS_TREE_ELEMENT_TYPE element)
{
    if(!pRoot)
    {
        pRoot = hs_avlNodeNew(element);
        if(!pRoot)
        {
            printf("ERROR: create avltree node failed!\n");
            return NULL;
        }
    }
    else if(element < pRoot -> val)
    {
        pRoot -> left = hs_insert(pRoot -> left, element);
        /*因为添加节点导致树失衡
         根据element和左子树的val的比较关系确认：是由于添加到左子树的左子树还是左子树的右子树而引发的。
         然后通过LL或LR旋转操作使树恢复平衡
         */
        if(hs_avl_height(pRoot -> left) - hs_avl_height(pRoot -> right) == 2)
            pRoot = pRoot -> left -> val > element ? hs_left_left_rotate(pRoot) : hs_left_right_rotate(pRoot);
        
    }
    else if (element > pRoot -> val)
    {
        pRoot -> right = hs_insert(pRoot -> right, element);
        /*因为添加节点导致树失衡
         根据element和右子树的val的比较关系确认：是由于添加到右子树的左子树还是右子树的右子树而引发的。
         然后通过LL或LR旋转操作使树恢复平衡
         */
        if(hs_avl_height(pRoot -> right) - hs_avl_height(pRoot -> left) == 2)
            pRoot = pRoot -> right -> val < element ? hs_right_right_rotate(pRoot) : hs_right_left_rotate(pRoot);
    }
    else //element == pRoot -> val 树中有和element 相等的节点 如何处理看具体需求 本实现未做任何操作
    {
        
    }
    
    hs_update_height(pRoot);
    
    return pRoot;
}

//删除AVL树中val 与element相等的节点
HS_AVL_Node* hs_delete(HS_AVL_Node* pRoot, HS_AVL_Node* target)
{
    if(!pRoot || !target)
        return  NULL;
    
    if (pRoot -> val > target -> val)
    {
        //若当前节点值大于目标节点值则继续到其左子树中搜索目标节点
        pRoot -> left = hs_delete(pRoot -> left, target);
        
        /*
         若删除后打破AVL树的平衡则一定是右子树的高度过高了，进入右子树中进行平衡旋转
         若右子树的左子树的高度大于右子树的右子树的高度，则进行RL旋转
         若右子树的左子树的高度小于或等于右子树的右子树的高度，则进行RR旋转
         */
        if(hs_avl_height(pRoot -> right) - hs_avl_height(pRoot -> left)  == 2 )
        {
            HS_AVL_Node* rightChild = pRoot -> right;
            
            pRoot = hs_avl_height(rightChild -> left) > hs_avl_height(rightChild -> right)? hs_right_left_rotate(pRoot) : hs_right_right_rotate(pRoot);
        }
    }
    else if (pRoot -> val < target -> val)
    {
        //若当前节点值小于目标节点值则继续到其右子树中搜索目标节点
        pRoot -> right = hs_delete(pRoot -> right, target);
        
        /*
         若删除后打破AVL树的平衡则一定是左子树的高度过高了，进入左子树中进行平衡旋转
         若左子树的右子树的高度大于左子树的左子树的高度，则进行LR旋转
         若左子树的右子树的高度小于或等于左子树的左子树高度，则进行LL旋转
         */
        if (hs_avl_height(pRoot -> left) - hs_avl_height(pRoot -> right) == 2)
        {
            HS_AVL_Node* leftChild = pRoot -> left;

            pRoot = hs_avl_height(leftChild -> right) > hs_avl_height(leftChild -> left) ? hs_left_right_rotate(pRoot) : hs_left_left_rotate(pRoot);
        }
    }
    else
    {
        if(pRoot -> left && pRoot -> right)
        {
            //如果目标节点左子树的高度大于右子树高度，则将它前驱节点的值替换到目标节点
            //然后删除前驱节点
            if(hs_avl_height(pRoot -> left) > hs_avl_height(pRoot -> right))
            {
                HS_AVL_Node* predecessor = pRoot -> left;
                while (predecessor)
                    predecessor = predecessor -> right;
                
                pRoot -> val = predecessor -> val;
                pRoot -> left = hs_delete(pRoot -> left, predecessor);
            }
            //如果目标节点右子树的高度大于等于左子树高度，则将它后继节点的值替换到目标节点
            //然后删除后继节点
            else
            {
                HS_AVL_Node* successor = pRoot -> right;
                while (successor)
                    successor = successor -> left;
                
                pRoot -> val = successor -> val;
                pRoot -> right = hs_delete(pRoot -> right, successor);
            }
        }
        else
        {
            //若节点度为1或为叶子节点，则将其唯一子树或NULL替换到它的位置
            HS_AVL_Node* tmp = pRoot;
            pRoot = pRoot -> left ? pRoot -> left : pRoot -> right;
            free(tmp);
        }
    }
    
    if (pRoot)
        hs_update_height(pRoot);
    
    return pRoot;
}

/**
 * 创建AVL树
 * @return 返回AVL树指针
 */
HS_AVL* hs_avlNew(void)
{
    HS_AVL* pAVL = (HS_AVL*)malloc(sizeof(HS_AVL));
    if(pAVL)
    {
        pAVL -> root = NULL;
        pAVL -> size = 0;
    }
    return pAVL;
}


/**
 * 根据数组创建AVL树
 * @param elements 元素数组
 * @param elementSize 数组长度
 * @return 返回AVL树指针
 */
HS_AVL* hs_avlNewWithElements(HS_TREE_ELEMENT_TYPE* elements, HS_TREE_SIZE elementSize)
{
    HS_AVL* pAVL = NULL;
    if (elements && elementSize)
    {
        pAVL = hs_avlNew();
        if (pAVL)
            for (HS_TREE_SIZE i = 0 ; i < elementSize ; ++i)
                hs_avlAdd(pAVL, elements[i]);
    }
    return pAVL;
}


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
bool hs_avlIsEmpty(HS_AVL* pTree)
{
    return pTree && !pTree -> root;
}


/**
 * 获取AVL树节点的数量
 * @param pTree 树指针
 * @return 返回AVL树元素数
 */
HS_TREE_SIZE hs_avlSize(HS_AVL* pTree)
{
    return pTree ? pTree -> size : 0;
}


/**
 * 获取AVL树的根
 * @param pTree 树指针
 * @return 若树存在返回AVL树的根
 */
HS_AVL_Node* hs_avlRoot(HS_AVL* pTree)
{
    return pTree && pTree -> root ? pTree -> root: NULL;
}


/**
 * 获取AVL树的高度
 * @param pTree 树指针
 * @return 返回AVL树高度
 */
HS_TREE_HEIGHT hs_avlHeight(HS_AVL* pTree)
{
    return pTree ? hs_avl_height(pTree -> root) : 0;
}


/**
 * 元素是否在AVL树中
 * @param pTree 树指针
 * @param element 待判定元素
 * @return 若在树中返回节点指针，否则返回NULL
 */
HS_AVL_Node* hs_avlSearch(HS_AVL* pTree, HS_TREE_ELEMENT_TYPE element)
{
    if (hs_avlIsEmpty(pTree))
        return NULL;
    HS_AVL_Node* target = pTree -> root;
    while (target)
    {
        if (target -> val == element)
            break;
        else if (target -> val > element)
            target = target -> left;
        else
            target = target -> right;
    }
    return target;
}


/**
 * 向AVL树添加元素
 * @param pTree 树指针
 * @param element 待添加元素
 */
void hs_avlAdd(HS_AVL* pTree, HS_TREE_ELEMENT_TYPE element)
{
    if (pTree)
    {
        pTree -> root = hs_insert(pTree -> root, element);
        pTree -> size++;
    }
}


/**
 * 删除AVL树中与element相等的节点
 * @param pTree 树指针
 * @param element 待删除元素
 */
void hs_avlRemove(HS_AVL* pTree, HS_TREE_ELEMENT_TYPE element)
{
    if(pTree)
    {
        HS_AVL_Node* target = hs_avlSearch(pTree, element);
        if (target)
        {
            pTree -> root = hs_delete(pTree -> root, target);
            pTree -> size--;
        }
    }
}


/**
 * 销毁AVL树
 * @param pTree 树指针
 */
void hs_avlDestroy(HS_AVL* pTree);

