//
//  main.swift
//  Trie
//
//  Created by 郝源顺 on 2021/9/16.
//

import Foundation

var trie = Trie()



trie.add(key: "sdh")
trie.add(key: "cow")
trie.add(key: "cowboy")
trie.add(key: "sdh")
trie.add(key: "cowbo")

print(trie.search(key: "cow"))
print(trie.search(key: "cowb"))
print(trie.search(key: "abc"))
print(trie.search(key: "sdh"))
print(trie.startWith(key: "cow"))
print(trie.startWith(key: "cowb"))
print(trie.startWith(key: "abc"))
print(trie.startWith(key: "sdh"))




