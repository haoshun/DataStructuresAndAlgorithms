//
//  HS_SkipList.h
//  SkipList
//
//  Created by 郝源顺 on 2021/10/23.
//

#ifndef HS_SkipList_h
#define HS_SkipList_h

#include "HS_Define.h"


typedef struct hs_skip_list HS_SkipList;



/**
 * 创建跳表
 * @return 返回跳表指针
 */
HS_SkipList* hs_slCreate(void);



/**
 * 添加键值
 * @param pSL 跳表指针
 * @param key 键
 * @param value 值
 * @return 若键已存在，新值覆盖旧值，返回旧值；若不存在，返回NULL
 */
HS_VALUE hs_slInsert(HS_SkipList* pSL, HS_KEY key, HS_VALUE value);



/**
 * 获取键对应的值
 * @param pSL 跳表指针
 * @param key 键
 * @return 若键值存在，返回旧值；若不存在，返回NULL
 */
HS_VALUE hs_slGet(HS_SkipList* pSL, HS_KEY key);



/**
 * 删除键值
 * @param pSL 跳表指针
 * @param key 键
 * @return 若键值存在，返回旧值；若不存在，返回NULL
 */
HS_VALUE hs_slRemove(HS_SkipList* pSL, HS_KEY key);




#endif /* HS_SkipList_h */
