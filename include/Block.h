// include/Block.h
#ifndef BLOCK_H
#define BLOCK_H

#include <string>
#include <vector>
#include <memory>
#include "Transaction.h"
#include "Utils.h"

using namespace std;

class Block {
private:
    int index;
    long long timestamp;
    vector<Transaction> transactions;
    string previousHash;
    string hash;
    string validatorAddress;
    int nonce; // Can be used for additional randomness

public:
    // Constructor
    Block(int index, const string& previousHash, const string& validatorAddress);
    
    // Add transaction to block
    void addTransaction(const Transaction& transaction);
    
    // Calculate block hash (including all transactions)
    string calculateHash() const;
    
    // Calculate Merkle root of transactions
    string calculateMerkleRoot() const;
    
    // Mine/Finalize the block
    void finalizeBlock();
    
    // Validate block
    bool isValid() const;
    
    // Getters
    int getIndex() const { return index; }
    string getHash() const { return hash; }
    string getPreviousHash() const { return previousHash; }
    string getValidatorAddress() const { return validatorAddress; }
    long long getTimestamp() const { return timestamp; }
    const vector<Transaction>& getTransactions() const { return transactions; }
    int getTransactionCount() const { return transactions.size(); }
    
    // Display block info
    void print() const;
};

#endif