//
//  HS_BTree.h
//  B-Tree
//
//  Created by 郝源顺 on 2021/10/27.
//

#ifndef HS_BTree_h
#define HS_BTree_h


#include "HS_Define.h"

typedef struct hs_b_tree HS_BTree;

typedef struct _b_tree_node HS_BT_Node;

typedef struct hs_bt_result {
    /**
     B树的结点
    */
     HS_BT_Node* node;
    
    /**
     关键字在结点中的位置
    */
    HS_INDEX pos;
    
}HS_BT_Result;


/**
 * 创建B树
 * @param m B树的阶
 * @return 返回B树指针
 */
HS_BTree* hs_btCreate(HS_ORDER m);



/**
 * 判断B树是否含有元素
 * @param pBT B树指针
 * @return true 为空树
 */
bool hs_btIsEmpty(HS_BTree* pBT);



/**
 * 在B树中插入关键字
 * @param pBT B树指针
 * @param key 键
 */
void hs_btInsert(HS_BTree* pBT, HS_KEYTYPE key);



/**
 * 查找关键字
 * @param pBT B树指针
 * @param key 关键字
 * @return 若找到，返回封装的结果；若不存在，返回NULL
 */
HS_BT_Result* hs_btSearch(HS_BTree* pBT, HS_KEYTYPE key);


/**
 * 移除关键字
 * @param pBT B 树指针
 * @param key 键
 */
void hs_btDelete(HS_BTree* pBT, HS_KEYTYPE key);



/**
 * 销毁B树
 * @param pBT B树指针
 */
void hs_btFree(HS_BTree* pBT);



#endif /* HS_BTree_h */
