//
//  main.c
//  Sequence
//
//  Created by 郝源顺 on 2021/1/23.
//

#include <stdio.h>
#include "HS_KMP.h"
#include "HS_BM.h"

int main(int argc, const char * argv[]) {
    
    char* t1 = "DABCDABCFACBA";
    char* t2 = "ATGTGAGCTGGTGTGTGCFAA";
    char* p1= "ABCDABCE";
    char* p2 = "GTGTGCF";
    
//    printf("字符串%s 在 字符串%s 中的位置是：%d\n", p1, t1, hs_kmp(t1, p1));
//    printf("字符串%s 在 字符串%s 中的位置是：%d\n", p2, t2, hs_kmp(t2, p2));
    
    printf("字符串%s 在 字符串%s 中的位置是：%d\n", p2, t2, hs_bm(t2, p2));
    
    return 0;
}
