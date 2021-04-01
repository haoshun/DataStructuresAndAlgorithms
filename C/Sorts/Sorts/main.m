//
//  main.m
//  Sorts
//
//  Created by 郝 源顺 on 2018/11/15.
//  Copyright © 2018年 Shun. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "HS_BubbleSort.h"
#import "HS_SelectionSort.h"
#import "HS_InsertionSort.h"

#import "Shell_Sort/Shell_Sort.h"

#import "MedianFind.h"

#import "HS_MergeSort.h"
#include "HS_HeapSort.h"
#include "HS_QuickSort.h"



typedef char* S_TYPE;

typedef struct {
    S_TYPE* elements;
    int size;
    int capacity;
} S_Array;

S_Array* createArray()
{
    S_Array* pArray = (S_Array*) malloc(sizeof(S_Array));
    if(pArray)
    {
        pArray -> size = 0;
        pArray -> capacity = 10;
        pArray -> elements = (S_TYPE *)calloc(pArray -> capacity, sizeof(S_TYPE));
    }
    return pArray;
}

void ensureArrayCapacity(S_Array* pArray, int size)
{
    if(size <= pArray -> capacity)
        return;
    int oldCapacity = pArray -> capacity;
    int addCapacity = oldCapacity >> 1;
    int newCapacity = oldCapacity + addCapacity;
    pArray -> elements = (S_TYPE*) realloc(pArray -> elements, sizeof(S_TYPE) * newCapacity);
    pArray -> capacity = newCapacity;
}

void addArray(S_Array* pArray, S_TYPE element)
{
    ensureArrayCapacity(pArray, pArray -> size + 1);
    pArray -> elements[(pArray -> size)++] = element;
}

int cmp(void* a, void* b)
{
    return *(char*)a - *(char*)b;
}




//按序输出
void backTrack(char* s, int len, int selectedCount, int* vis, char* rowData, S_Array* container)
{
    if(selectedCount == len)
    {
        char* tmp = (char*)malloc(sizeof(char) * (len + 1));
        memcpy(tmp, rowData, sizeof(char) * (len + 1));
        addArray(container, tmp);
        return;
    }
    for(int i = 0; i < len ; ++i)
    {
        if(vis[i] || (i > 0 && s[i] == s[i - 1] && !vis[i - 1]))
            continue;
        rowData[selectedCount] = s[i];
        vis[i] = 1;
        backTrack(s, len, selectedCount + 1, vis, rowData, container);
        vis[i] = 0;
    }
}

char** wrap(char* s, int* returnSize)
{
    int len = strlen(s);

    qsort(s, len, sizeof(char), cmp);
    int* vis = (int*)calloc(len, sizeof(int));
    char* rowData = (char*)calloc(len + 1, sizeof(char));
    memset(rowData, '\0', sizeof(char) * (len + 1));
    S_Array* pArray = createArray();
    
    backTrack(s, len, 0, vis, rowData, pArray);

    int row = pArray -> size;
    *returnSize = row;


    
    char** result = (char**)malloc(sizeof(char*) * row);
    memcpy(result, pArray -> elements, sizeof(char*) * row);
    free(pArray);
    free(vis);
    free(rowData);
    
    return result;
}


int main(int argc, const char * argv[]) {
    @autoreleasepool {
        // insert code here...

        
        
        //int nums[200] ={5,2,4,6,1,3};
        //int nums[10] ={9,1,5,8,3,7,6,0,4,1};
        int nums[10] ={3,7,6,5,8,2,1,3,6,4};
        
        //insertionSort(nums, 0, 9);
        //shell_Sort(nums, 0, 9);
        
        //SelectionSort(nums, 0, 9);
        
        //bubbleSort(nums, 0, 9);
        //mergeSort(nums, 0, 9);
//        mergeSortDownToUp(nums, 0, 9);

//        printf("%d\n" , findMedian(nums, 10));
//
//        for (int i = 0 ; i<10; ++i)
//        {
//            printf("%d," , nums[i]);
//        }
//        printf("\n");
        
        //hs_bubbleSort(nums, 2, 9);
        //hs_selectionSort(nums, 2, 9);
        //hs_insertionSort(nums, 0, 9);
        
        //hs_mergeSort(nums, 2, 9);
        //hs_heapSort(nums, 3, 9);
        //hs_quickSort(nums, 0, 9);
        //hs_printElements(nums, 0, 9);
        
//        int a = 12, b = 0, z = 0;
//
//        z = (a >> 1) + (b >> 1);
//
//        z = (a&b) + ((a^b)>>1);
        
//        x = 131 % 4;
//        //equals:
//        y = 131 & (4 - 1);
        int num = 0;
        char test[10] = "suiys";
        char** result = wrap(test, &num);
    
    }
    return 0;
}
