//
//  main.c
//  SkipList
//
//  Created by 郝源顺 on 2021/10/22.
//

#include <stdio.h>
#include "HS_SkipList.h"



int main(int argc, const char * argv[]) {
    // insert code here...

    printf("create -----------------------------\n");
    HS_SkipList* pSL = hs_slCreate();
    for(int i = 0, key = 0, value = 0 ; i < 20 ; i++)
    {
        key = rand() % 30 + 1 ;
        value = key + i * 10;
        hs_slInsert(pSL, key, value);
    }
    
    print_sl(pSL);
    
    printf("\nget -----------------------------\n");
    for (int i = 0, key = 0 ; i < 5; ++i) {
        key = rand() % 40 + 1;
        printf("find: %d\n", key);
        HS_VALUE value = hs_slGet(pSL, key);
        if(HS_NONE != value)
            printf("key: %d, value: %ld\n", key, value);
        else
            printf("key not found!\n");
    }
    
    printf("\nremove -----------------------------\n");
    for(int i = 0, key = 0 ; i < 3 ; ++i)
    {
        key = rand() % 40 + 1;
        printf("remove: %d\n", key);
        if(HS_NONE != hs_slRemove(pSL, key))
        {
            print_sl(pSL);
            printf("-----------------------\n");
        }
        else
            printf("key not found!\n");
    }
        
    
    
    return 0;
}


