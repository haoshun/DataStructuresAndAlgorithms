//
//  main.c
//  Heaps
//
//  Created by 郝源顺 on 2021/1/2.
//

#include <stdio.h>
#include "HS_BinaryHeap.h"

void testBinaryHeap()
{
    HS_ELEMENT_TYPE test1[30] = {48, 117, 151, 87, 66, 46, 79, 177, 107, 104, 192, 12, 130, 133, 187, 50, 9, 32, 150, 131, 162, 51, 61, 198, 63, 118, 60, 72, 56,100};
    
    HS_BinaryHeap* pHeap = hs_binaryHeapNewWithElements(test1, 30);
    
    
    hs_printArray(*(HS_ELEMENT_TYPE**) pHeap, hs_binaryHeapSize(pHeap));
    
    hs_binaryHeapAdd(pHeap, 258);

    hs_printArray(*(HS_ELEMENT_TYPE**) pHeap, hs_binaryHeapSize(pHeap));

    printf("删除堆顶： %d\n", hs_binaryHeapRemove(pHeap));

    hs_printArray(*(HS_ELEMENT_TYPE**) pHeap, hs_binaryHeapSize(pHeap));
    
}



char* getStr()
{
    int capacity = 10;
    int len = 1;
    char* str = (char*)calloc(capacity, sizeof(char));

    while('\n' != (str[len - 1] = getchar()))
    {
        len ++;
        if (len == capacity)
        {
            int addCapacity = capacity >> 1;
            str = realloc(str, (capacity + addCapacity) * sizeof(char));
            memset(str + capacity, 0, sizeof(char) * addCapacity);
            capacity += addCapacity;
        }
    }
    str[len - 1] = '\0';
    return str;
}

typedef struct {
    void* elements;
    int capacity;
    int size;
} S_Array;

// S_Path* createPath()
// {
//     S_Path* pPath = (S_Path*)malloc(sizeof(S_Path));
//     if(pPath)
//     {
//         pPath -> size = 0;
//         pPath -> capacity = kDefaultCapacity;
//         pPath -> elements = (int*) calloc(pPath -> capacity, sizeof(int));
//     }
//     return pPath;
// }

// S_PathArray* createArray()
// {
//     S_PathArray* pArray = (S_Path*)malloc(sizeof(S_Path));
//     if(pArray)
//     {
//         pArray -> size = 0;
//         pArray -> capacity = kDefaultCapacity >> 1;
//         pArray -> elements = (S_Path*) calloc(pArray -> capacity, sizeof(S_Path));
//     }
//     return pArray;
// }



int const kDefaultCapacity = 8;

typedef struct TreeNode T_Node;
// typedef struct {
//     int* elements;
//     int capacity;
//     int size;
// } S_Path;

// typedef struct {
//     S_Path* paths;
//     int capacity;
//     int size;
// } S_PathArray;

typedef struct {
    void* elements;
    int capacity;
    int size;
} S_Array;

// S_Path* createPath()
// {
//     S_Path* pPath = (S_Path*)malloc(sizeof(S_Path));
//     if(pPath)
//     {
//         pPath -> size = 0;
//         pPath -> capacity = kDefaultCapacity;
//         pPath -> elements = (int*) calloc(pPath -> capacity, sizeof(int));
//     }
//     return pPath;
// }

// S_PathArray* createArray()
// {
//     S_PathArray* pArray = (S_Path*)malloc(sizeof(S_Path));
//     if(pArray)
//     {
//         pArray -> size = 0;
//         pArray -> capacity = kDefaultCapacity >> 1;
//         pArray -> elements = (S_Path*) calloc(pArray -> capacity, sizeof(S_Path));
//     }
//     return pArray;
// }

S_Array* createArrayWithCapacity(int capacity, size_t __size)
{
    S_Array* pArray = (S_Array*)malloc(sizeof(S_Array));
    if(pArray)
    {
        pArray -> size = 0;
        pArray -> capacity = capacity;
        pArray -> elements = calloc(pArray -> capacity, __size);
    }
    return pArray;
}

S_Array* createArray(size_t __size)
{
    return createArrayWithCapacity(kDefaultCapacity, __size);
}

void ensureCapacity(S_Array* pArray, int size, size_t __size)
{
    if(!pArray || pArray -> capacity >= size)
        return;

    pArray -> capacity += pArray -> capacity >> 1;
    pArray -> elements = realloc(pArray -> elements, pArray -> capacity * __size);
}

void s_arrayAdd(S_Array* pArray, void* src, size_t __size)
{
    ensureCapacity(pArray, pArray -> size + 1, __size);
    memcpy(pArray -> elements + pArray -> size * __size, src, __size);
    pArray -> size ++;
}

void s_arrayRemove(S_Array* pArray, size_t __size)
{
    if(pArray && pArray -> size);
    {
        memset(pArray -> elements + (--(pArray -> size)), 0, __size);
    }
}

S_Array* s_arrayCopy(S_Array* src, size_t __size)
{
    if(src)
    {
        S_Array* dest = createArrayWithCapacity(src -> capacity, __size);
        if(dest)
        {
            dest -> size = src -> size;
            memcpy(dest -> elements, src -> elements, __size * dest -> size);
        }
    }
    return NULL;
}

void dfs(T_Node* root, int cur_sum, int tar_sum, S_Array** path, S_Array* pathArray)
{
    if(!root -> left && !root -> right)
    {
        if(cur_sum + root -> val == tar_sum)
        {
            S_Array* newPath = s_arrayCopy(*path, sizeof(int));
            s_arrayAdd(*path, &(root -> val), sizeof(int));
            s_arrayAdd(pathArray, *path, sizeof(S_Array));
            *path = newPath;
        }
        return;
    }

    s_arrayAdd(*path, &(root -> val), sizeof(int));

    if(root -> left)
        dfs(root -> left, cur_sum + root -> val, tar_sum, path, pathArray);

    if(root -> right)
        dfs(root -> right, cur_sum + root -> val, tar_sum, path, pathArray);
    
    s_arrayRemove(*path, sizeof(int));
}


int main(int argc, const char * argv[]) {

    testBinaryHeap();




    return 0;
}


