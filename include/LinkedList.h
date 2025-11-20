// include/LinkedList.h
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include "Block.h"

using namespace std;

// Node structure for linked list
template<typename T>
struct Node {
    T data;
    Node* next;
    
    Node(const T& data) : data(data), next(nullptr) {}
};

// Linked List class for blockchain
class BlockchainList {
private:
    Node<Block>* head;
    Node<Block>* tail;
    int size;

public:
    // Constructor
    BlockchainList();
    
    // Destructor
    ~BlockchainList();
    
    // Add block to end of chain
    void append(const Block& block);
    
    // Get block at index
    Block* getBlock(int index);
    
    // Get last block
    Block* getLastBlock();
    
    // Get first block (genesis)
    Block* getFirstBlock();
    
    // Get chain size
    int getSize() const { return size; }
    
    // Check if chain is empty
    bool isEmpty() const { return head == nullptr; }
    
    // Traverse and print all blocks
    void printAll() const;
    
    // Validate entire chain
    bool validateChain() const;
    
    // Clear the chain
    void clear();
};

#endif