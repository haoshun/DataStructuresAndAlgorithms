//
//  main.m
//  DataStructures
//
//  Created by 郝 源顺 on 2019/1/5.
//  Copyright © 2019年 Shun. All rights reserved.
//

#import <Foundation/Foundation.h>
#include"HS_Array.h"
#include "HS_Stack.h"
#include "HS_Queue.h"
#include "HS_Deque.h"
#include "HS_CircleQueue.h"
#include "HS_CircleDeque.h"

#include "HS_BinaryTree.h"
#include "HS_Tree_Helper.h"
#include "HS_String.h"
#include "HS_BST.h"
#include "HS_AVL.h"

#include "HS_RBT.h"

void printArray(HS_TREE_ELEMENT_TYPE* pArray, HS_TREE_SIZE size)
{
    if (pArray && size)
    {
        for (HS_TREE_SIZE i = 0; i < size; ++i) {
            printf("%d ", pArray[i]);
        }
        printf("\n");
    }
}


int* LIS(int* arr, int arrLen, int* returnSize ) {
    // write code here
    int longest = 0;
    int* result = NULL;
    if(arr && arrLen)
    {
        int* dp = (int*) malloc(sizeof(int) * arrLen);
        memset(dp, 0, sizeof(int) * arrLen);

        for(int i = 0, lis_i ; i < arrLen ; ++i)
        {
            lis_i = 0;
            for(int j = 0 ; j < i ; ++j)
                if(arr[i] > arr[j] && lis_i < dp[j])
                    lis_i = dp[j];
            dp[i] = lis_i + 1;
            if(dp[i] > longest)
                longest = dp[i];
        }
        
        result = (int*)malloc(sizeof(int) * longest);
        for(int i = 0 ; i < longest ; ++i)
        result[i] = INT_MAX;
        *returnSize = longest;
        
        for(int index = longest - 1, rear = arrLen - 1 ; index >= 0 ; --index ,--rear, --longest)
        {
            for(int i = rear; i >= 0 ; --i)
            {
                if(dp[i] == longest)
                {
                    if(arr[i] < result[index])
                    {
                        result[index] = arr[i];
                        rear = i;
                    }
                }
            }
        }
        free(dp);
    }
    return result;
}



int main(int argc, const char * argv[]) {
    @autoreleasepool {

//        int * p = malloc(sizeof(int) * 10);
//        for (int i = 0; i < 10; ++i) {
//            p[i] = i;
//            printf("%d ", p[i]);
//        }
//
//        printf("\n%p \n", p);
//
//        int * p1 = realloc(p, 20* sizeof(int));
//        printf("%p \n", p1);
//        for (int i = 0; i < 20; ++i) {
//            printf("%d ", p1[i]);
//        }
//
//        int * p2 = realloc(p1, sizeof(int) * 5);
//        printf("%p  %lu\n", p2 , sizeof(int));
//        for (int i = 0; i < 5; ++i) {
//            printf("%d ", p2[i]);
//        }
//
//        printf("\n");
//
//        int * cp = calloc(10, sizeof(int));
//        for (int i = 0; i < 10; ++i) {
//            cp[i] = i;
//            printf("%d ", cp[i]);
//        }
//
//        int * cp1 = realloc(cp, 20* sizeof(int));
//        printf("%p \n", cp1);
//
//        memset(cp1 + 10, 0, sizeof(int) * 10);
//
//        for (int i = 0; i < 20; ++i) {
//            printf("%d ", cp1[i]);
//        }
        
        
        
        
//        int * cp2 = realloc(cp1, sizeof(int) * 5);
//        printf("%p  %lu\n", cp2 , sizeof(int));
//        for (int i = 0; i < 5; ++i) {
//            printf("%d ", cp2[i]);
//        }
        
        
    
        
        //struct stu* newStu = (struct stu*) malloc(sizeof(struct stu));
        
        //HS_Array array;
        
        //动态数组
//        HS_Array* pArray = hs_arrayNew();
//
//        for(int i = 1 ; i < 50 ; ++i)
//        {
//            hs_arrayAdd(pArray, i);
//        }
//
//        HS_ARRAY_SIZE arraySize = hs_arrayGetSize(pArray);
//
//        for (int i = 0; i <  arraySize;  ++i) {
//            printf("%d " , hs_arrayGetOfIndex(pArray, i));
//        }
//        printf("\n");
//        for(int i = 0 ; i < 30 ; i += 4)
//        {
//            printf("%d " , hs_arrayRemoveAtIndex(pArray, i));
//        }
//        printf("\n");
//        arraySize = hs_arrayGetSize(pArray);
//        for (int i = 0; i <  arraySize;  ++i) {
//            printf("%d " , hs_arrayGetOfIndex(pArray, i));
//        }
//        printf("\n");
//        for(int i = 0 ; i < 30 ; i += 3)
//        {
//            hs_arrayAddToIndex(pArray, 5 * i,i);
//        }
//        arraySize = hs_arrayGetSize(pArray);
//        for (int i = 0; i <  arraySize;  ++i) {
//            printf("%d " , hs_arrayGetOfIndex(pArray, i));
//        }
//        printf("\n");
//        hs_arrayTrimToSize(pArray);
//
//        hs_arrayFree(pArray);
//
//
//        printf("\n%p\n" , pArray);
//
//        char s1[] = "21474836490";
//        char s2[] = "2147383647";
//
//
//
//        int f = strncmp(s1, s2, 9);
//
//        int f1 = strncmp(s1, "2147483647", 10);
//
//        int f2 = strncmp(s1 + 2, s2 + 2, 4);
//
//        size_t size = sizeof(unsigned short);
        
        //栈
//        HS_Stack* pStack = hs_stackNew();
//
//        for (int i = 0 ; i < 50 ; ++i) {
//            hs_stackPush(pStack, i);
//        }
//
//        printf("stack size: %lu \n" , hs_stackSize(pStack));
//
//        while (!hs_stackIsEmpty(pStack)) {
//            printf("%d ", hs_stackPop(pStack));
//        }
//        printf("\n");
//
//        for (int i = 0 ; i < 10 ; ++i) {
//            hs_stackPush(pStack, i * 10);
//        }
//
//        printf("stack size: %lu \n" , hs_stackSize(pStack));
//        hs_stackFree(pStack);
        
        //队列
//        HS_Queue* pQueue = hs_queueNew();
//
//        for (int i = 0 ; i < 50 ; ++i) {
//            hs_queueEnQueue(pQueue, i);
//        }
//
//        printf("queue size: %lu \n" , hs_queueSize(pQueue));
//
//        while (!hs_queueIsEmpty(pQueue)) {
//            printf("%d ", hs_queueDeQueue(pQueue));
//        }
//        printf("\n");
//
//        for (int i = 0 ; i < 10 ; ++i) {
//            hs_queueEnQueue(pQueue, i * 10);
//        }
//
//        printf("queue size: %lu \n" , hs_queueSize(pQueue));
//
//        while (!hs_queueIsEmpty(pQueue)) {
//            printf("%d ", hs_queueDeQueue(pQueue));
//        }
//        printf("\n");
//
//        hs_queueFree(pQueue);
        
        //双端队列
//        HS_Deque* pDeque = hs_dequeNew();
//
//        for (int i = 0 ; i < 10 ; ++i) {
//            hs_dequeEnQueueRear (pDeque, i);
//            hs_dequeEnQueueFront(pDeque, 100 - i);
//        }
//
//        printf("deque size: %lu \n" , hs_dequeSize(pDeque));
//
//        while (!hs_dequeIsEmpty(pDeque)) {
//            printf("%d ", hs_dequeDeQueueFront(pDeque));
//        }
//        printf("\n");
//
//        for (int i = 0 ; i < 10 ; ++i) {
//            hs_dequeEnQueueRear(pDeque, i * 10);
//        }
//
//        printf("queue size: %lu \n" , hs_dequeSize(pDeque));
//
//
//        for (int i = 0 ; i < 3 ; ++i) {
//            printf("%d ", hs_dequeDeQueueFront(pDeque));
//            printf("%d ", hs_dequeDeQueueRear(pDeque));
//        }
//        printf("%d ", hs_dequeFront(pDeque));
//        printf("%d ", hs_dequeRear(pDeque));
//
//        printf("\n");
//
//        hs_dequeFree(pDeque);
        
        
//        //循环队列
//        HS_CircleQueue* cQueue = hs_circleQueueNew();
//
//        for(int i = 0 ; i < 51 ; ++i)
//        {
//            hs_circleQueueEnQueue(cQueue, i);
//            if(i > 12 && i < 30)
//                printf("%d ", hs_circleQueueDeQueue(cQueue));
//        }
//        printf("\n");
//
//        hs_print(cQueue);
//
//
//        while (!hs_circleQueueIsEmpty(cQueue)) {
//            printf("%d ", hs_circleQueueFront(cQueue));
//            hs_circleQueueDeQueue(cQueue);
//        }
//        printf("\n");
        
        //循环双端队列
//        HS_CircleDeque* cQueue = hs_circleDequeNew();
//        
//        for(int i = 0 ; i < 51 ; ++i)
//        {
//            hs_circleDequeEnQueueRear(cQueue, i);
//            if(i > 12 && i < 30)
//                printf("%d ", hs_circleDequeDeQueueFront(cQueue));
//        }
//        printf("\n");
//        
//        hs_deque_print(cQueue);
//            
//        
//        while (!hs_circleDequeIsEmpty(cQueue)) {
//            printf("%d ", hs_circleDequeFront(cQueue));
//            hs_circleDequeDeQueueFront(cQueue);
//        }
//        printf("\n");
//        
//        hs_circleDequeFree(cQueue);
        
//        HS_CircleDeque* pQueue = hs_circleDequeNew();
//
//        for (int i = 0;  i < 30 ; ++i) {
//            if (i < 20) {
//                if (i & 1) {
//                    hs_circleDequeEnQueueFront(pQueue, i );
//                }else
//                {
//                    hs_circleDequeEnQueueRear(pQueue, i );
//                }
//            }
//            else
//            {   hs_circleDequeEnQueueFront(pQueue, i );
//                printf("%d ," , hs_circleDequeDeQueueRear(pQueue));
//            }
//        }
//        printf("\n");
//
//        while (!hs_circleDequeIsEmpty(pQueue)) {
//            printf("%d ", hs_circleDequeDeQueueRear(pQueue));
//            //hs_circleDequeDeQueueFront(pQueue);
//        }
//        printf("\n");
//
//        hs_deque_print(pQueue);
        
        
        HS_STATUS status;
        //char* str = validString("   [   09  ,  1 , null]", &status);
        //char* str1 = validString("   [   9  ,  1 , null]", &status);
       //char* str2 = validString("[1,2,3,4,5,null,6 0,null,8,0,null,11,12     ]", &status);
//        char* str3 = validString("[1,2,3,4,5,null,60null,8,0,null,11,12     ]", &status);
//        char* str4 = validString("[1,2,3,4,5,null,6,0,-808,0,null,11,12     ]", &status);
        
        //char* str5 = validString("[  null]", &status);
        //unsigned long len = strlen(str5);
        
//        HS_BinaryTree* binaryTree = hs_binaryTreeNew("[1,2,3,null,null,4,5,null,null,7]", &status);
//
//        if (binaryTree && status == HS_SUCCEED) {
//            hs_printBinaryTree(binaryTree);
//
//            HS_TREE_SIZE treeSize = hs_binaryTreeSize(binaryTree);
//
//            HS_TREE_ELEMENT_TYPE* preOrderArray = hs_preOrderTraversal(binaryTree);
//            printArray(preOrderArray, treeSize);
//
//            HS_TREE_ELEMENT_TYPE* inOrderArray = hs_inOrderTraversal(binaryTree);
//            printArray(inOrderArray, treeSize);
//
//            HS_TREE_ELEMENT_TYPE* postOrderArray = hs_postOrderTraversal(binaryTree);
//            printArray(postOrderArray, treeSize);
//
//            HS_TREE_ELEMENT_TYPE* levelOrderArray = hs_levelOrderTraversal(binaryTree);
//            printArray(levelOrderArray, treeSize);
//
//            printf("深度：%lu \n" , hs_binaryTreeDepth(binaryTree));
//
//            printf("%s 完全二叉树\n", hs_binaryTreeIsComplete(binaryTree) ?"是" : "不是");
//
//        }
        
//        printf("%s \n" , intToStr(-0));
//
//        int test[] ={2,6,7,1,3,5,8,0,9};
//
//        int returnSize = 0;
//
//        int* returnArray = LIS(test, 9, &returnSize);
//
//        for(int i = 0 ; i < returnSize ; ++i)
//            printf("%d ,", returnArray[i]);
        
        
        HS_TREE_ELEMENT_TYPE element[15] = {30,20,10,40,50,60,70,160,150,140,130,120,110,100,80};
        
//        HS_BST* pBST = hs_bstNewWithElements(element, 16);
//
//        hs_printBinaryTree(hs_bstRoot(pBST));
//
//        printf("树深度为 %lu" , hs_binaryTreeDepth(pBST));
        
//        HS_AVL* pAVL = hs_avlNewWithElements(element, 16);
//
//        hs_avlRemove(pAVL, 8);
//        hs_avlRemove(pAVL, 12);
        
        //hs_bstRemove(pBST, 6);
//        hs_bstAdd(pBST, 4);
//
//        hs_printBinaryTree(hs_bstRoot(pBST));
        
        HS_RBT* pRBT = hs_rbtNewWithElements(element, 15);
        
        
        
        hs_rbtRemove(pRBT, 160);
        
        //!target -> left ^ !target -> right
        
        
        printf("\n");
        
        
        
    }
    return 0;
}
