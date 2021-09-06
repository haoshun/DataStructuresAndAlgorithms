//
//  HS_RBT.c
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/30.
//  Copyright © 2020 Shun. All rights reserved.
//

#include "HS_RBT.h"

struct hs_r_b_tree{
    HS_RBT_Node* root;
    HS_TREE_SIZE size;
};

void hs_setColor(HS_RBT_Node* pNode, HS_COLOR color)
{
    if(pNode)
        pNode -> color = color;
}

void hs_setBlack(HS_RBT_Node* pNode)
{
    hs_setColor(pNode, HS_BLACK);
}

void hs_setRed(HS_RBT_Node* pNode)
{
    hs_setColor(pNode, HS_RED);
}

HS_COLOR hs_colorOf(HS_RBT_Node* pNode)
{
    return !pNode ? HS_BLACK : pNode -> color;
}

bool hs_isBlack(HS_RBT_Node* pNode)
{
    return hs_colorOf(pNode) == HS_BLACK;
}

bool hs_isRed(HS_RBT_Node* pNode)
{
    return hs_colorOf(pNode) == HS_RED;
}

bool hs_isLeftChild(HS_RBT_Node* pNode)
{
    return pNode && pNode -> parent ? pNode == pNode -> parent -> left : false;
}

bool hs_isRightChild(HS_RBT_Node* pNode)
{
    return pNode && pNode -> parent ? pNode == pNode -> parent -> right : false;
}

HS_RBT_Node* hs_get_sibling(HS_RBT_Node* pNode)
{
    return pNode && pNode -> parent ? (hs_isLeftChild(pNode) ? pNode -> parent -> right : pNode -> parent -> left) : NULL;
}

HS_TREE_HEIGHT hs_height_(HS_RBT_Node* pRoot)
{
    return pRoot ? (hs_max(hs_height_(pRoot -> left), hs_height_(pRoot -> right)) + 1) : 0;
}

//RR 左旋
void hs_left_rotate(HS_RBT* pTree, HS_RBT_Node* pNode)
{
    HS_RBT_Node* pNewRoot = pNode -> right;
    pNode -> right = pNewRoot -> left;
    if(pNewRoot -> left)
        pNewRoot -> left -> parent = pNode;
    
    pNewRoot -> left = pNode;
    
    if(!pNode -> parent)
        pTree -> root = pNewRoot;
    else
    {
        if(hs_isLeftChild(pNode))
            pNode -> parent -> left = pNewRoot;
        else
            pNode -> parent -> right = pNewRoot;
    }
    
    pNewRoot -> parent = pNode -> parent;
    
    pNode -> parent = pNewRoot;
}

//LL 右旋
void hs_right_rotate(HS_RBT* pTree, HS_RBT_Node* pNode)
{
    HS_RBT_Node* pNewRoot = pNode -> left;
    pNode -> left = pNewRoot -> right;
    if(pNewRoot -> right)
        pNewRoot -> right -> parent = pNode;
    
    pNewRoot -> right = pNode;
    
    if(!pNode -> parent)
        pTree -> root = pNewRoot;
    else
    {
        if (hs_isLeftChild(pNode))
            pNode -> parent -> left = pNewRoot;
        else
            pNode -> parent -> right = pNewRoot;
    }
    
    pNewRoot -> parent = pNode -> parent;
    
    pNode -> parent = pNewRoot;
}


void hs_add_fixup(HS_RBT* pTree, HS_RBT_Node* pNode)
{
    //当节点为根节点时
    if(!pNode -> parent)
    {
        hs_setBlack(pNode);
        return;
    }
    
    //当父节点为黑色时，直接返回
    if(hs_isBlack(pNode -> parent))
        return;
    
    HS_RBT_Node* uncle = hs_get_sibling(pNode -> parent);
    HS_RBT_Node* grand = pNode -> parent -> parent;
    //无论下面哪种情况发生都要将祖父节点置红。
    hs_setRed(grand);
    //当叔父节点为黑色时
    if (hs_isBlack(uncle))
    {
        if (hs_isLeftChild(pNode -> parent))
        {
            //LR 先左旋父节点，再右旋祖父节点
            if(hs_isRightChild(pNode))
                hs_left_rotate(pTree, pNode -> parent);
            //LL只需右旋祖父节点
            hs_right_rotate(pTree, grand);
        }
        else
        {
            //RL 先右旋父节点，再左旋祖父节点
            if(hs_isLeftChild(pNode))
                hs_right_rotate(pTree, pNode -> parent);
            //RR 只需左旋祖父节点
            hs_left_rotate(pTree, grand);
        }
        hs_setBlack(grand -> parent);
        return;
    }
    
    //当叔父节点为红色时，将父节点、叔父节点置黑，将祖父节点作为修复节点，递归继续恢复
    hs_setBlack(pNode -> parent);
    hs_setBlack(uncle);
    hs_add_fixup(pTree, grand);
}


void hs_delete_fixup(HS_RBT* pTree, HS_RBT_Node* pNode)
{
    /*
     由红黑树性质可知，若叶子节点为黑色且不为根节点时，其必有兄弟。
     */
    HS_RBT_Node* parent = pNode -> parent;
    
    //删除的是根节点
    if (!parent)
        return;
    
    /*
     注意此时不能使用 hs_get_sibling来获取兄弟节点，因为此时parent节点的left或right已经和pNode指向的节点断连了。
    即可以用pNode找到父节点，但父节点找不到pNode了。
     */
    HS_RBT_Node* sibling = parent -> left ? parent -> left : parent -> right;
    
    /*
     若兄弟节点为红，将兄弟节点染黑，父节点染红
     若兄弟节点为左子树，进行LL右旋
     若兄弟节点为右子树，进行RR左旋
     操作后将问题转化为目标节点的兄弟节点为黑色的情况
     */
    if(hs_isRed(sibling))
    {
        hs_setBlack(sibling);
        hs_setRed(parent);
        if (sibling == parent -> left)
            hs_right_rotate(pTree, parent);
        else
            hs_left_rotate(pTree, parent);
       
        //更换兄弟
        sibling = parent -> left ? parent -> left : parent -> right;
    }
    
    /*
     由红黑树性质可知，若黑叶子节点的兄弟节点也为黑色，则该兄弟节点若有子节点，则子节点颜色必为红色
     */
    //若兄弟节点至少有一个红子节点
    if(hs_isRed(sibling -> left) || hs_isRed(sibling -> right))
    {
         //若兄弟节点为父节点左子节点，则当其至少有右孩子为红时，进行LR旋转，若只有左孩子为红时，进行LL旋转
        if(hs_isLeftChild(sibling))
        {
            if(hs_isRed(sibling -> right))
                hs_left_rotate(pTree, sibling);
            hs_right_rotate(pTree, parent);
        }
        //若兄弟节点为父节点右子节点，则当其至少有左孩子为红时，进行RL旋转，若只有右孩子为红时，进行RR旋转
        else
        {
            if(hs_isRed(sibling -> left))
                hs_right_rotate(pTree, sibling);
            hs_left_rotate(pTree, parent);
        }
        /*
         以上4种情况旋转完毕后，原parent节点变为新生成的子树的根节点的一个孩子
         将新生成的子树的根节点染成原parent节点的颜色
         将子树根节点的两个孩子染成黑色
         */
        HS_RBT_Node* newRoot = parent -> parent;
        hs_setColor(newRoot, parent -> color);
        hs_setBlack(newRoot -> left);
        hs_setBlack(newRoot -> right);
    }
    //兄弟节点无子节点
    else
    {
        bool isParentBlack = hs_isBlack(parent);
        hs_setBlack(parent);
        hs_setRed(sibling);
        if(isParentBlack)
            hs_delete_fixup(pTree, parent);
    }
}


HS_RBT_Node* hs_rbtNodeNew(HS_TREE_ELEMENT_TYPE val)
{
    HS_RBT_Node* pNode = (HS_RBT_Node*) malloc(sizeof(HS_RBT_Node));
    if (pNode)
    {
        pNode -> left = NULL;
        pNode -> right = NULL;
        pNode -> parent = NULL;
        pNode -> val = val;
        hs_setRed(pNode);
    }
    return pNode;
}


/**
 * 创建R-B树
 * @return 返回R-B树指针
 */
HS_RBT* hs_rbtNew(void)
{
    HS_RBT* pRBT = (HS_RBT*)malloc(sizeof(HS_RBT));
    if (pRBT)
    {
        pRBT -> root = NULL;
        pRBT -> size = 0;
    }
    return pRBT;
}

/**
 * 根据数组创建R-B树
 * @param elements 元素数组
 * @param elementSize 数组长度
 * @return 返回R-B树指针
 */
HS_RBT* hs_rbtNewWithElements(HS_TREE_ELEMENT_TYPE* elements, HS_TREE_SIZE elementSize)
{
    HS_RBT* pRBT = NULL;
    if (elements && elementSize)
    {
        pRBT = hs_rbtNew();
        if (pRBT)
            for (HS_TREE_SIZE i = 0; i < elementSize ; ++i)
                hs_rbtAdd(pRBT, elements[i]);
    }
    return pRBT;
}

/**
 * R-B树是否为空树
 * @param pTree 树指针
 * @return 若为空树返回true，否则false
 */
bool hs_rbtIsEmpty(HS_RBT* pTree)
{
    return !(pTree && pTree -> root);
}

/**
 * 获取R-B树节点的数量
 * @param pTree 树指针
 * @return 返回R-B树元素数
 */
HS_TREE_SIZE hs_rbtSize(HS_RBT* pTree)
{
    return pTree ? pTree -> size : 0;
}

/**
 * 获取R-B树的根
 * @param pTree 树指针
 * @return 若树存在返回R-B树的根
 */
HS_RBT_Node* hs_rbtRoot(HS_RBT* pTree)
{
    return pTree && pTree -> root ? pTree -> root: NULL;
}

/**
 * 获取R-B树的高度
 * 这里取严蔚敏《数据结构（C语言版）》（第三版）中的定义
 * 树节点的层次从根开始定义，根为第1层。树中节点的最大层次称为树的深度或高度。
 * 在这个定义中，树节点的层次数和其所在的深度相等，高度为树最大层数减当前所在层数再加1
 * 即根节点深度为1，叶子节点高度为1
 * @param pTree 树指针
 * @return 返回R-B树高度
 */
HS_TREE_HEIGHT hs_rbtHeight(HS_RBT* pTree)
{
    return pTree && pTree -> root ? hs_height_(pTree -> root) : 0;
}

/**
 * 元素是否在R-B树中
 * @param pTree 树指针
 * @param element 待判定元素
 * @return 若在树中返回节点指针，否则返回NULL
 */
HS_RBT_Node* hs_rbtSearch(HS_RBT* pTree, HS_TREE_ELEMENT_TYPE element)
{
    if(hs_rbtIsEmpty(pTree))
        return NULL;
    HS_RBT_Node* target = pTree -> root;
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
 * 向R-B树添加元素
 * @param pTree 树指针
 * @param element 待添加元素
 */
void hs_rbtAdd(HS_RBT* pTree, HS_TREE_ELEMENT_TYPE element)
{
    if(pTree)
    {
        HS_RBT_Node* newNode = hs_rbtNodeNew(element);
        if(newNode)
        {
            if(!pTree -> root)
                pTree -> root = newNode;
            else
            {
                HS_RBT_Node* parent = NULL;
                HS_RBT_Node* tmp = pTree -> root;
                while (tmp)
                {
                    parent = tmp;
                    if (tmp -> val == element)
                    {
                        return;
                    }
                    else if(tmp -> val > element)
                        tmp = tmp -> left;
                    else
                        tmp = tmp -> right;
                }
                
                newNode -> parent = parent;
                
                if (element > parent -> val)
                    parent -> right = newNode;
                else
                    parent -> left = newNode;
            }
            
            hs_add_fixup(pTree, newNode);
            
            pTree -> size ++;
        }
    }
}

/**
 * 删除R-B树中与element相等的节点
 * @param pTree 树指针
 * @param element 待删除元素
 */
void hs_rbtRemove(HS_RBT* pTree, HS_TREE_ELEMENT_TYPE element)
{
    HS_RBT_Node* target = hs_rbtSearch(pTree, element);
    //元素不在红黑树中
    if(!target)
        return;
    
    HS_RBT_Node* parent = target -> parent;
    HS_RBT_Node* child = NULL;
    
    /*
     待删除节点度为2
     寻找它的后继节点，用后继节点的值替换目标节点的值
     将删除目标改为后继节点
     */
    if(target -> left && target -> right)
    {
        HS_RBT_Node* successor = target -> right;
        while (successor -> left)
        {
            parent = successor;
            successor = successor -> left;
        }
        target -> val = successor -> val;
        target = successor;
    }
    
    /*
     待删节点度为1
     由红黑树性质可知，若节点度为1，则该节点不可能为红色，那么该节点只能是黑色，其子节点也不能是黑色，只能是红色。
     注：这里可能会承接上面度为2的节点的替身删除
     */
    if(!target -> left ^ !target -> right)
    {
        child = target -> left ? target -> left: target -> right;
        
        if(!parent)
            pTree -> root = child;
        else
        {
            if (parent -> left == target)
                parent -> left = child;
            else
                parent -> right = child;
        }
        
        child -> parent = parent;
        hs_setBlack(child);
    }
    else
    {
        /*
         待删除节点为叶子节点
         若节点为红色，则直接删除
         若为黑色，则需要平衡红黑树
         注：这里可能会承接上面度为2的节点的替身删除
         */
        if (!parent)
            pTree -> root = NULL;
        else
        {
            if(target == parent -> left)
                parent -> left = NULL;
            else
                parent -> right = NULL;
        }
        
        if (hs_isBlack(target))
            hs_delete_fixup(pTree, target);
    }
    
    pTree -> size--;
    free(target);
}

/**
 * 销毁R-B树
 * @param pTree 树指针
 */
void hs_rbtDestroy(HS_RBT* pTree);

