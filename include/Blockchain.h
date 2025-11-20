// include/Blockchain.h
#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <vector>
#include <map>
#include <queue>
#include <memory>
#include "Block.h"
#include "Transaction.h"
#include "Validator.h"
#include "Wallet.h"

using namespace std;

class Blockchain {
private:
    vector<Block> chain;
    queue<Transaction> pendingTransactions;
    map<string, double> balances; // Address -> Balance (Account-based model)
    map<string, Validator> validators; // Address -> Validator
    double miningReward;
    int maxTransactionsPerBlock;
    double totalStake;

public:
    // Constructor
    Blockchain();
    
    // Genesis block creation
    void createGenesisBlock();
    
    // Block operations
    void addBlock(Block& newBlock);
    Block* getLatestBlock();
    
    // Transaction operations
    void addTransaction(const Transaction& transaction);
    void processTransactions(const string& validatorAddress);
    
    // Validator operations
    void registerValidator(const string& address, double stake);
    string selectValidator(); // POS: Select validator based on stake
    void distributeReward(const string& validatorAddress);
    
    // Balance operations
    double getBalance(const string& address);
    void updateBalance(const string& address, double amount);
    bool hasBalance(const string& address, double amount);
    
    // Validation
    bool isChainValid() const;
    
    // Display
    void printChain() const;
    void printPendingTransactions() const;
    void printValidators() const;
    void printBalances() const;
    
    // Getters
    int getChainLength() const { return chain.size(); }
    int getPendingTransactionCount() const { return pendingTransactions.size(); }
    double getTotalStake() const { return totalStake; }
};

#endif