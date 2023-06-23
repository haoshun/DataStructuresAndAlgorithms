//
//  TestBTree.c
//  TestBTree
//
//  Created by 郝源顺 on 2021/11/14.
//

#include "TestBTree.h"
#include "HS_BTree.h"


#pragma mark - Printer

char* __get_node_str(HS_BT_Node* pNode, unsigned int* len)
{
    unsigned int size = 0;
    char* str = NULL;

    if(pNode -> _keyCount)
    {
        unsigned capacity = pNode -> _keyCount * 2 + 3;
        str = (char*) calloc(capacity, sizeof(char));

        str[size++] = ']';

        HS_KEYTYPE key;
        for(int i = pNode -> _keyCount - 1 ; i >= 0 ; --i)
        {
            key = pNode -> _keys[i];
            ato
        }

        str[size++] = '[';

        for(int i = 0, j = size - 1 ; i < j ; ++i, --j)
        {
            str[i] ^= str[j];
            str[j] ^= str[i];
            str[i] ^= str[j];
        }
    }

    *len = size;
    return str;
}



