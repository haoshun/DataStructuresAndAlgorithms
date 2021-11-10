//
//  HS_BTree.c
//  B-Tree
//
//  Created by 郝源顺 on 2021/10/27.
//

#include "HS_BTree.h"

#define KEYTYPE_LEN sizeof(HS_KEYTYPE)


struct _b_tree_node {
    /**
    * 孩子
    */
    struct _b_tree_node** _children;
    
    /**
    * 结点存储的关键字
    */
    HS_KEYTYPE * _keys;
    
    /**
    * 结点中关键字数量
    */
    unsigned int _keyCount;
    
    /**
    * 是否是叶子结点
    */
    bool _isLeaf;
};


struct hs_b_tree {
    /**
     B树根结点
    */
     HS_BT_Node* root;

    /**
     结点至多包含（2t-1）个关键字
    */
     HS_SCOPE max_keys;
    
    /**
     B树的最小度数（minmum degree）(t ≥ 2)
            
     假设一个结点存储的关键字个数为x
     根结点：1 ≤  x ≤ 2t - 1（树非空）
     非根结点：t - 1 ≤ x ≤ 2t - 1
     
     如果有孩子，孩子个数 y = x + 1
     根结点：2 ≤ y ≤ 2t
     非根结点：t ≤ y ≤ 2t
            
     参考：
        《算法导论》（中文版）（第三版）page： 279
    */
     HS_DEGREE t;

};

#pragma mark -
HS_SCOPE __get_max_keys(HS_DEGREE t)
{
    return (t << 1) - 1;
}


#pragma mark -

void _bt_pointer_check(HS_BTree* pBT)
{
    assert(pBT != NULL);
}


HS_BT_Node* _bt_createNode(HS_SCOPE max_keys)
{
    HS_BT_Node* pNode = (HS_BT_Node*)calloc(1, sizeof(HS_BT_Node));
    if (pNode)
    {
        pNode -> _children = (HS_BT_Node**)calloc(max_keys + 1, sizeof(HS_BT_Node*));
        pNode -> _keys = (HS_KEYTYPE*)calloc(max_keys, sizeof(HS_KEYTYPE));
        pNode -> _isLeaf = true;
    }
    return pNode;
}


HS_BT_Result* _bt_createResult(HS_BT_Node* pNode, HS_INDEX pos)
{
    HS_BT_Result* pResult = (HS_BT_Result*)malloc(sizeof(HS_BT_Result));
    if(pResult)
    {
        pResult -> node = pNode;
        pResult -> pos = pos;
    }
    return pResult;
}

void _bt_destroyNode(HS_BT_Node* pNode)
{
    if(pNode)
    {
        free(pNode -> _keys);
        free(pNode -> _children);
        free(pNode);
    }
}


void _bt_split_child(HS_BTree* pBT, HS_BT_Node* parent, HS_INDEX index)
{
    HS_BT_Node* newNode = _bt_createNode(pBT -> max_keys);
    if(newNode)
    {
        HS_BT_Node* pNode = parent -> _children[index];
        HS_SCOPE min_keys = pBT -> t - 1;
        
        newNode -> _isLeaf = pNode -> _isLeaf;
        newNode -> _keyCount = min_keys;
        memcpy(newNode -> _keys, pNode -> _keys + (min_keys + 1), sizeof(HS_KEYTYPE) * min_keys);
        if(!pNode -> _isLeaf)
            memcpy(newNode -> _children, pNode -> _children + (pBT -> t), sizeof(HS_BT_Node*) * pBT -> t);
        
        
        memset(pNode -> _keys + min_keys , 0, KEYTYPE_LEN * (pNode -> _keyCount - min_keys));
        memset(pNode -> _children + min_keys + 1, 0, sizeof(HS_BT_Node*) * (pNode -> _keyCount - min_keys));
        pNode -> _keyCount = min_keys;
        
        
        memmove(parent -> _keys + index + 1, parent -> _keys + index, sizeof(HS_KEYTYPE) * (parent -> _keyCount - index));
        parent -> _keys[index] = pNode -> _keys[pBT -> t];
        memmove(parent -> _children + index + 2, parent -> _children + index + 1, sizeof(HS_BT_Node*) * (parent -> _keyCount - index));
        parent -> _children[index + 1] = newNode;
        parent -> _keyCount ++;
        
    }
}


void _bt_insert_nonfull(HS_BTree* pBT, HS_BT_Node* pNode, HS_KEYTYPE key)
{
    int i = pNode -> _keyCount - 1;
    if(pNode -> _isLeaf)
    {
        for( ; i >= 0 && pNode -> _keys[i] > key ; --i)
            pNode -> _keys[i + 1] = pNode -> _keys[i];
        
        pNode -> _keys[i + 1] = key;
        pNode -> _keyCount ++;
    }
    else
    {
        while (i >= 0 && pNode -> _keys[i] > key)
            --i;
        ++i;
        
        if(pNode -> _children[i] ->_keyCount == pBT -> max_keys)
            _bt_split_child(pBT, pNode, i);
        
        if(key > pNode -> _keys[i])
            ++i;
        
        _bt_insert_nonfull(pBT, pNode -> _children[i], key);
    }
}







HS_BT_Result* _bt_search(HS_BT_Node* pNode, HS_KEYTYPE key)
{
    int i = 0;
    
    while (i < pNode ->_keyCount && key > pNode -> _keys[i])
        ++i;
    
    if(i < pNode -> _keyCount && key == pNode -> _keys[i])
        return _bt_createResult(pNode, i);
    
    if(pNode -> _isLeaf)
        return NULL;
    
    return _bt_search(pNode -> _children[i], key);
}


void _bt_merge_child(HS_BTree* pBT, HS_BT_Node* parent, HS_INDEX index)
{
    HS_KEYTYPE key = parent -> _keys[index];
    HS_BT_Node* leftChild = parent -> _children[index];
    HS_BT_Node* rightChild = parent -> _children[index + 1];
    
    parent -> _keyCount --;
    memmove(parent -> _keys + index, parent -> _keys + index + 1, KEYTYPE_LEN * (parent -> _keyCount - index));
    memset(parent -> _keys + parent -> _keyCount, 0, KEYTYPE_LEN);
    memmove(parent -> _children + index + 1, parent -> _children + index + 2, sizeof(HS_BT_Node*) * (parent -> _keyCount - index));
    parent -> _children[parent -> _keyCount] = NULL;
    if(!parent -> _keyCount)
    {
        _bt_destroyNode(parent);
        pBT -> root = leftChild;
    }
        
    
    leftChild -> _keys[leftChild -> _keyCount] = key;
    leftChild -> _keyCount ++;
    
    memcpy(leftChild -> _keys + leftChild -> _keyCount, rightChild -> _keys, KEYTYPE_LEN * rightChild -> _keyCount);
    memcpy(leftChild -> _children + leftChild -> _keyCount, rightChild -> _children, sizeof(HS_BT_Node*) * (rightChild -> _keyCount + 1));
    leftChild -> _keyCount += rightChild -> _keyCount;
    
    _bt_destroyNode(rightChild);
    
}


void _bt_counterclockwise_rotate(HS_BT_Node* parent, HS_INDEX index)
{
    HS_BT_Node* leftChild = parent -> _children[index];
    HS_BT_Node* rightChild = parent -> _children[index + 1];
    
    leftChild -> _keys[leftChild -> _keyCount++] = parent -> _keys[index];
    leftChild -> _children[leftChild -> _keyCount] = rightChild -> _children[0];
    
    parent -> _keys[index] = rightChild -> _keys[0];
    
    memmove(rightChild -> _keys, rightChild -> _keys + 1, KEYTYPE_LEN * (rightChild -> _keyCount - 1));
    memmove(rightChild -> _children, rightChild -> _children + 1, sizeof(HS_BT_Node*) * rightChild -> _keyCount);
    rightChild -> _children[rightChild -> _keyCount--] = NULL;
}

void _bt_clockwise_rotate(HS_BT_Node* parent, HS_INDEX index)
{
    HS_BT_Node* leftChild = parent -> _children[index - 1];
    HS_BT_Node* rightChild = parent -> _children[index];
    
    memmove(rightChild -> _keys + 1, rightChild -> _keys, KEYTYPE_LEN * rightChild -> _keyCount);
    memmove(rightChild -> _children + 1, rightChild -> _children, sizeof(HS_BT_Node*) * (++rightChild -> _keyCount));
    rightChild -> _children[0] = leftChild -> _children[leftChild -> _keyCount];
    rightChild -> _keys[0] = parent -> _keys[index - 1];
    
    parent -> _keys[index - 1] = leftChild -> _keys[--leftChild ->_keyCount];
}


void _bt_delete(HS_BTree* pBT, HS_BT_Node** ppNode, HS_KEYTYPE key)
{
    HS_INDEX i = 0;
    HS_BT_Node* pNode = *ppNode;
    
    while (i < pNode -> _keyCount && key > pNode -> _keys[i])
        ++i;
    
    //在pNode中找到key
    if(i < pNode -> _keyCount && key == pNode -> _keys[i])
    {
        //pNode 为叶子结点
        if(pNode -> _isLeaf)
        {
            pNode -> _keyCount--;
            memmove(pNode -> _keys + i, pNode -> _keys + i + 1, KEYTYPE_LEN * (pNode -> _keyCount - i));
            memset(pNode -> _keys + pNode -> _keyCount, 0, KEYTYPE_LEN);
            
            //此叶子结点也是根结点 删除后树为空树
            if(!pNode -> _keyCount)
            {
                *ppNode = NULL;
                free(pNode);
            }
            return;
        }
        
        //pNode 为内部结点
        if(pNode -> _children[i] ->_keyCount >= pBT -> t)
        {
            HS_BT_Node* tmp = pNode -> _children[i];
            
            while (!tmp -> _isLeaf) {
                tmp = tmp -> _children[tmp -> _keyCount];
            }
            
            HS_KEYTYPE newKey = tmp -> _keys[tmp ->_keyCount - 1];
            pNode -> _keys[i] = newKey;
            _bt_delete(pBT, &(pNode -> _children[i]), newKey);
        }
        else if (pNode -> _children[i + 1] -> _keyCount >= pBT -> t)
        {
            HS_BT_Node* tmp = pNode -> _children[i + 1];
            
            while (!tmp -> _isLeaf) {
                tmp = tmp -> _children[0];
            }
            
            HS_KEYTYPE newKey = tmp -> _keys[0];
            pNode -> _keys[i] = newKey;
            _bt_delete(pBT, &(pNode -> _children[i + 1]), newKey);
        }
        else
        {
            _bt_merge_child(pBT, pNode, i);
            
            _bt_delete(pBT, &(pNode -> _children[i]), key);
        }
    }
    else
    {
        if(pNode -> _isLeaf)
            return;
        
        if(pNode -> _children[i] -> _keyCount == pBT -> t - 1)
        {
            HS_BT_Node* leftSibling = i ? pNode -> _children[i - 1] : NULL;
            HS_BT_Node* rightSibling = i < pNode -> _keyCount ? pNode -> _children[i + 1] : NULL;
            
            if((leftSibling && leftSibling -> _keyCount >= pBT -> t) &&
               (rightSibling && rightSibling -> _keyCount >= pBT -> t))
            {
                if(leftSibling ->_keyCount > rightSibling -> _keyCount)
                    _bt_clockwise_rotate(pNode, i);
                else
                    _bt_counterclockwise_rotate(pNode, i);
            }
            else if(leftSibling && leftSibling -> _keyCount >= pBT ->t)
            {
                _bt_clockwise_rotate(pNode, i);
            }
            else if (rightSibling && rightSibling -> _keyCount >= pBT -> t)
            {
                _bt_counterclockwise_rotate(pNode, i);
            }
            else
            {
                i -= !!leftSibling;
                _bt_merge_child(pBT, pNode, i);
            }
        }
        
        _bt_delete(pBT, &(pNode -> _children[i]), key);
    }
}





#pragma mark -

/**
 * 创建B树
 * @param t B树的最小度数（minimum degree），t ≥ 2
 * @return 返回B树指针
 */
HS_BTree* hs_btCreate(HS_DEGREE t)
{
    assert(t >= 2);
    
    HS_BTree* pBT = (HS_BTree*)malloc(sizeof(HS_BTree));
    if(pBT)
    {
        pBT -> t = t;
        pBT -> max_keys = __get_max_keys(pBT -> t);
        pBT -> root = NULL;
    }
    return pBT;
}


/**
 * 判断B树是否含有元素
 * @param pBT B树指针
 * @return true 为空树
 */
bool hs_btIsEmpty(HS_BTree* pBT)
{
    _bt_pointer_check(pBT);
    
    return pBT -> root == NULL;
}


/**
 * 在B树中插入关键字
 * @param pBT B树指针
 * @param key 键
 */
void hs_btInsert(HS_BTree* pBT, HS_KEYTYPE key)
{
    HS_BT_Node* pNode = NULL;
    
    if(hs_btIsEmpty(pBT))
    {
        pNode = _bt_createNode(pBT -> max_keys);
        if (pNode)
        {
            pNode -> _keys[0] = key;
            pNode -> _keyCount = 1;
            pBT -> root = pNode;
        }
        return;
    }
    
    HS_BT_Node* pRoot = pBT -> root;
    if(pRoot -> _keyCount == pBT -> max_keys)
    {
        HS_BT_Node* newRoot = _bt_createNode(pBT -> max_keys);
        if(newRoot)
        {
            pBT -> root = newRoot;
            newRoot -> _isLeaf = false;
            newRoot -> _children[0] = pRoot;

            _bt_split_child(pBT, newRoot, 0);
            
            _bt_insert_nonfull(pBT, pRoot, key);
        }
    }
    else
        _bt_insert_nonfull(pBT, pRoot, key);
}



/**
 * 查找关键字
 * @param pBT B树指针
 * @param key 关键字
 * @return 若找到，返回封装的结果；若不存在，返回NULL
 */
HS_BT_Result* hs_btSearch(HS_BTree* pBT, HS_KEYTYPE key)
{
    return hs_btIsEmpty(pBT) ?  NULL :  _bt_search(pBT -> root, key);
}


/**
 * 移除关键字
 * @param pBT B 树指针
 * @param key 键
 */
void hs_btDelete(HS_BTree* pBT, HS_KEYTYPE key)
{
    if (!hs_btIsEmpty(pBT))
        _bt_delete(pBT, &(pBT -> root), key);
}



/**
 * 销毁B树
 * @param pBT B树指针
 */
void hs_btFree(HS_BTree* pBT);


