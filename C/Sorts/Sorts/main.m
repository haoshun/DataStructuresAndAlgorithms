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
        hs_heapSort(nums, 3, 9);
        //hs_quickSort(nums, 0, 9);
        hs_printElements(nums, 0, 9);
    
    }
    return 0;
}
