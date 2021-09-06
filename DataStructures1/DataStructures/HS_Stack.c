//
//  HS_Stack.c
//  DataStructures
//
//  Created by 郝源顺 on 2020/12/8.
//  Copyright © 2020 Shun. All rights reserved.
//

#include "HS_Stack.h"
#include "HS_LinkedList.h"


struct hs_linkedListStack {
    /**
    * 所有的元素
    */
    HS_LinkedList * elements;
    /**
     * 栈内元素的数量
     */
    HS_STACK_SIZE size;
};


void hs_stackPointerCheck(HS_Stack* pStack)
{
    assert(pStack != NULL);
}


/**
 * 创建栈
 * @return 返回栈指针
 */
HS_Stack* hs_stackNew(void)
{
    HS_Stack* pStack = (HS_Stack*)malloc(sizeof(HS_Stack));
    if (pStack)
    {
        pStack -> elements = hs_linkedListNew();
        pStack -> size = 0;
    }
    return pStack;
}

/**
 * 清除所有元素
 * @param pStack 栈指针
 */
void hs_stackClear(HS_Stack* pStack)
{
    hs_stackPointerCheck(pStack);
    if (pStack -> size)
    {
        hs_linkedListClear(pStack -> elements);
        pStack -> size = 0;
    }
}

/**
 * 返回栈元素的数量
 * @param pStack 栈指针
 * @return 返回栈元素数
 */
HS_STACK_SIZE hs_stackSize(HS_Stack* pStack)
{
    hs_stackPointerCheck(pStack);
    return pStack -> size;
}

/**
 * 栈是否为空
 * @param pStack 栈指针
 * @return 栈无元素返回true，否则返回false
 */
bool hs_stackIsEmpty(HS_Stack* pStack)
{
    hs_stackPointerCheck(pStack);
    return !pStack -> size;
}

/**
 * 添加元素到栈
 * @param pStack 栈指针
 * @param element 待加入的元素
 */
void hs_stackPush(HS_Stack* pStack, HS_ELEMENT_TYPE element)
{
    hs_stackPointerCheck(pStack);
    hs_linkedListAdd(pStack -> elements, element);
    ++(pStack -> size);
}

/**
 * 获取栈顶元素
 * @param pStack 栈指针
 * @return 返回栈顶元素
 */
HS_ELEMENT_TYPE hs_stackTop(HS_Stack* pStack)
{
    hs_stackPointerCheck(pStack);
    return hs_linkedListGetOfIndex(pStack -> elements, pStack -> size - 1);
}

/**
 * 栈顶元素出栈
 * @param pStack 栈指针
 * @return 返回栈顶元素
 */
HS_ELEMENT_TYPE hs_stackPop(HS_Stack* pStack)
{
    hs_stackPointerCheck(pStack);
    return hs_linkedListRemoveAtIndex(pStack -> elements, --(pStack-> size));
}

/**
 * 销毁栈
 * @param pStack 栈指针
 */
void hs_stackFree(HS_Stack* pStack)
{
    hs_stackPointerCheck(pStack);
    if (!hs_stackIsEmpty(pStack)) {
        hs_linkedListFree(pStack -> elements);
    }
    free(pStack);
}



