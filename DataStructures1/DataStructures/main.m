//
//  main.m
//  DataStructures
//
//  Created by 郝 源顺 on 2019/1/5.
//  Copyright © 2019年 Shun. All rights reserved.
//

#import <Foundation/Foundation.h>

#include "HS_LinkedList.h"
#include "HS_Stack.h"
#include "HS_Queue.h"
#include "HS_Deque.h"


int main(int argc, const char * argv[]) {
    @autoreleasepool {

        //双链表
//        HS_LinkedList* list = hs_linkedListNew();
//
//        for(int i = 0 ; i < 10 ; ++i)
//        {
//            hs_linkedListAdd(list, i);
//        }
//
//        hs_linkedListAddToIndex(list, 100, 10);
//
//        hs_linkedListAddToIndex(list, -100, 0);
//
//        hs_linkedListRemoveAtIndex(list, 5);
//
//        printf("%lld , %d" , hs_linkedListIndexOf(list, 3) , hs_linkedListGetOfIndex(list, 4));
//
//        hs_linkedListClear(list);
//
//        printf("%d" , hs_linkedListIsEmpty(list));
        
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
        HS_Deque* pDeque = hs_dequeNew();

        for (int i = 0 ; i < 10 ; ++i) {
            hs_dequeEnQueueRear (pDeque, i);
            hs_dequeEnQueueFront(pDeque, 100 - i);
        }

        printf("deque size: %lu \n" , hs_dequeSize(pDeque));

        while (!hs_dequeIsEmpty(pDeque)) {
            printf("%d ", hs_dequeDeQueueFront(pDeque));
        }
        printf("\n");

        for (int i = 0 ; i < 10 ; ++i) {
            hs_dequeEnQueueRear(pDeque, i * 10);
        }

        printf("queue size: %lu \n" , hs_dequeSize(pDeque));


        for (int i = 0 ; i < 3 ; ++i) {
            printf("%d ", hs_dequeDeQueueFront(pDeque));
            printf("%d ", hs_dequeDeQueueRear(pDeque));
        }
        printf("%d ", hs_dequeFront(pDeque));
        printf("%d ", hs_dequeRear(pDeque));

        printf("\n");

        hs_dequeFree(pDeque);
        
        
        
    }
    return 0;
}
