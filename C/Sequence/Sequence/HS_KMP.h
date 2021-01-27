//
//  HS_KMP.h
//  Sequence
//
//  Created by 郝源顺 on 2021/1/23.
//

#ifndef HS_KMP_h
#define HS_KMP_h

#include "HS_Define.h"

/**
 * 字符串匹配
 * KMP
 * @param text 文本串
 * @param pattern 模式串
 * @return 匹配到的第一个模式串的起始索引，若无法匹配，返回 -1
 */
HS_INDEX hs_kmp(char* text, char* pattern);


#endif /* HS_KMP_h */
