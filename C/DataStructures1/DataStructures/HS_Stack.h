//
//  HS_Stack.h
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/8.
//  Copyright © 2020 Shun. All rights reserved.
//

#ifndef HS_Stack_h
#define HS_Stack_h

#include <stdio.h>
#include <stdbool.h>

#ifndef HS_ELEMENT_TYPE
typedef int HS_ELEMENT_TYPE;
#endif

typedef unsigned long HS_STACK_SIZE;
typedef struct hs_linkedListStack HS_Stack;


/**
 * 创建栈
 * @return 返回栈指针
 */
HS_Stack* hs_stackNew(void);

/**
 * 清除所有元素
 * @param pStack 栈指针
 */
void hs_stackClear(HS_Stack* pStack);

/**
 * 返回栈元素的数量
 * @param pStack 栈指针
 * @return 返回栈元素数
 */
HS_STACK_SIZE hs_stackSize(HS_Stack* pStack);

/**
 * 栈是否为空
 * @param pStack 栈指针
 * @return 栈无元素返回true，否则返回false
 */
bool hs_stackIsEmpty(HS_Stack* pStack);

/**
 * 添加元素到栈
 * @param pStack 栈指针
 * @param element 待加入的元素
 */
void hs_stackPush(HS_Stack* pStack, HS_ELEMENT_TYPE element);

/**
 * 获取栈顶元素
 * @param pStack 栈指针
 * @return 返回栈顶元素
 */
HS_ELEMENT_TYPE hs_stackTop(HS_Stack* pStack);

/**
 * 栈顶元素出栈
 * @param pStack 栈指针
 * @return 返回栈顶元素
 */
HS_ELEMENT_TYPE hs_stackPop(HS_Stack* pStack);

/**
 * 销毁栈
 * @param pStack 栈指针
 */
void hs_stackFree(HS_Stack* pStack);


#endif /* HS_Stack_h */
