//
//  HS_BM.c
//  Sequence
//
//  Created by 郝源顺 on 2021/1/24.
//

#include "HS_BM.h"


HS_INDEX* hs_createBC(char* pattern, HS_LENGTH p_len)
{
    //ASCII码映射
    HS_INDEX* bc = (HS_INDEX*)malloc(sizeof(HS_INDEX) * 256);
    memset(bc, -1, sizeof(HS_INDEX) * 256);
    
    for (HS_INDEX i = 0 ; i < p_len; ++i)
        bc[pattern[i]] = i;
    
    return bc;
}

void hs_createGS(char* pattern, HS_LENGTH p_len, HS_INDEX** suffix, bool** prefix)
{
    *suffix = (HS_INDEX*)malloc(sizeof(HS_INDEX) * p_len);
    memset(*suffix, -1, sizeof(HS_INDEX) * p_len);
    *prefix = (bool*)malloc(sizeof(bool) * p_len);
    memset(*prefix, 0, sizeof(bool) * p_len);
    
    for (HS_INDEX i = 0 ; i < p_len - 1; ++i)
    {
        int j = 0, k = 0;
        while (j >= 0 && pattern[j] == pattern[p_len - 1 - k])
        {
            --j;
            ++k;
            (*suffix)[k] = j + 1;
        }
        if (j == -1)
            (*prefix)[k] = true;
    }
}

HS_INDEX moveByGS(HS_INDEX j, HS_LENGTH p_len, HS_INDEX* suffix, bool* prefix)
{
    HS_INDEX k = p_len - 1 - j;
    if (suffix[k] != -1)
        return j - suffix[k] + 1;
    
    for (HS_INDEX r = j + 2; r <= p_len - 1; ++r)
        if (prefix[p_len - r])
            return r;
    
    return p_len;
}


/**
 * 字符串匹配
 * KMP
 * @param text 文本串
 * @param pattern 模式串
 * @return 匹配到的第一个模式串的起始索引，若无法匹配，返回-1
 */
HS_INDEX hs_bm(char* text, char* pattern)
{
    if (!text || !pattern)
        return HS_NOTFOUND;
    
    HS_LENGTH t_len = (HS_LENGTH)strlen(text);
    if (!t_len)
        return HS_NOTFOUND;
    
    HS_LENGTH p_len = (HS_LENGTH)strlen(pattern);
    if (!p_len)
        return HS_NOTFOUND;
    
    if (p_len > t_len)
        return HS_NOTFOUND;
    
    HS_INDEX* bc = hs_createBC(pattern, p_len);
    HS_INDEX* suffix = NULL;
    bool* prefix = NULL;
    hs_createGS(pattern, p_len, &suffix, &prefix);
    
    HS_INDEX i = 0;
    while (i <= t_len - p_len)
    {
        HS_INDEX j;
        for (j = p_len - 1; j >= 0 ; --j)
            if (text[i + j] != pattern[j])
                break;
                
        if (j < 0)
            return i;
            
        HS_INDEX x = j - bc[text[i + j]];
        HS_INDEX y = 0;
        if (j < p_len - 1)
            y = moveByGS(j, p_len, suffix, prefix);
        
        i += (x > y ? x : y);
    }
    
    return HS_NOTFOUND;
}
