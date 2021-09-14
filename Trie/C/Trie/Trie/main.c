//
//  main.c
//  Trie
//
//  Created by 郝源顺 on 2021/9/13.
//

#include <stdio.h>

#include "Trie.h"

int main(int argc, const char * argv[]) {
    
    
    HS_TRIE* pTrie = hs_trieCreate();
    
    hs_trieAdd(pTrie, "sdh");
    hs_trieAdd(pTrie, "cow");
    hs_trieAdd(pTrie, "cowboy");
    hs_trieAdd(pTrie, "sdh");
    
    hs_trieAdd(pTrie, "cowbo");
    
    
    printf("%d\n", hs_trieSearch(pTrie, "cow"));
    printf("%d\n", hs_trieSearch(pTrie, "cowb"));
    printf("%d\n", hs_trieSearch(pTrie, "abc"));
    printf("%d\n", hs_trieSearch(pTrie, "sdh"));
    printf("%d\n", hs_trieStartWith(pTrie, "cow"));
    printf("%d\n", hs_trieStartWith(pTrie, "cowb"));
    printf("%d\n", hs_trieStartWith(pTrie, "abc"));
    printf("%d\n", hs_trieStartWith(pTrie, "sdh"));
    
    
    return 0;
}
