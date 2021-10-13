//
//  Trie.swift
//  Trie
//
//  Created by 郝源顺 on 2021/9/16.
//

import Foundation

class Trie_Node {
    var isWord = false
    var children = Dictionary<Character, Trie_Node>()
}

class Trie {
    let root = Trie_Node()
    
    init() {}
    
    func add(key: String) {
        var child = root
        var next: Trie_Node
        for c in key {
            if  child.children[c] == nil {
                
                next = Trie_Node()
                child.children[c] = next
                child = next
            }
            else{
                child = child.children[c]!
            }
        }
        child.isWord = true
    }
    
    
    func search(key: String) -> Bool {
        var child = root
        for c in key {
            if child.children[c] == nil{
                return false
            }
            child = child.children[c]!
        }
        return child.isWord
    }
    
    
    func startWith(key: String) -> Bool {
        var child = root
        for c in key {
            if child.children[c] == nil{
                return false
            }
            child = child.children[c]!
        }
        return true
    }
    
    
}
