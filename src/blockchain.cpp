// src/Blockchain.cpp
#include "../include/Blockchain.h"
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

Blockchain::Blockchain() {
    miningReward = 10.0; // 10 X coins per block
    maxTransactionsPerBlock = 10;
    totalStake = 0.0;
    createGenesisBlock();
}

void Blockchain::createGenesisBlock() {
    Block genesis(0, "0", "GENESIS");
    
    // Add genesis transaction (initial coin distribution)
    Transaction genesisTx("SYSTEM", "GENESIS", 0);
    genesisTx.signTransaction();
    genesis.addTransaction(genesisTx);
    
    genesis.finalizeBlock();
    chain.push_back(genesis);
    
    cout << "Genesis block created!" << endl;
}

void Blockchain::addBlock(Block& newBlock) {
    newBlock.finalizeBlock();
    
    if (newBlock.isValid()) {
        chain.push_back(newBlock);
        cout << "Block #" << newBlock.getIndex() << " added to blockchain!" << endl;
    } else {
        cout << "Error: Invalid block rejected!" << endl;
    }
}

Block* Blockchain::getLatestBlock() {
    if (!chain.empty()) {
        return &chain.back();
    }
    return nullptr;
}

void Blockchain::addTransaction(const Transaction& transaction) {
    // Validate transaction
    if (!transaction.isValid()) {
        cout << "Invalid transaction rejected!" << endl;
        return;
    }
    
    // Check if sender has sufficient balance (except for SYSTEM transactions)
    if (transaction.getSender() != "SYSTEM") {
        if (!hasBalance(transaction.getSender(), transaction.getAmount())) {
            cout << "Transaction rejected: Insufficient balance!" << endl;
            return;
        }
    }
    
    pendingTransactions.push(transaction);
    cout << "Transaction added to pending pool." << endl;
}

void Blockchain::processTransactions(const string& validatorAddress) {
    if (pendingTransactions.empty()) {
        cout << "No pending transactions to process." << endl;
        return;
    }
    
    // Create new block
    Block newBlock(chain.size(), getLatestBlock()->getHash(), validatorAddress);
    
    // Add transactions to block (up to max limit)
    int count = 0;
    vector<Transaction> processedTxs;
    
    while (!pendingTransactions.empty() && count < maxTransactionsPerBlock) {
        Transaction tx = pendingTransactions.front();
        pendingTransactions.pop();
        
        // Update balances
        if (tx.getSender() != "SYSTEM") {
            balances[tx.getSender()] -= tx.getAmount();
        }
        balances[tx.getReceiver()] += tx.getAmount();
        
        newBlock.addTransaction(tx);
        processedTxs.push_back(tx);
        count++;
    }
    
    // Add mining reward transaction
    Transaction rewardTx("SYSTEM", validatorAddress, miningReward);
    rewardTx.signTransaction();
    newBlock.addTransaction(rewardTx);
    balances[validatorAddress] += miningReward;
    
    // Add block to chain
    addBlock(newBlock);
    
    // Distribute reward to validator
    distributeReward(validatorAddress);
}

void Blockchain::registerValidator(const string& address, double stake) {
    if (stake < 100) { // Minimum stake requirement
        cout << "Minimum stake is 100 X!" << endl;
        return;
    }
    
    if (validators.find(address) != validators.end()) {
        cout << "Validator already registered!" << endl;
        return;
    }
    
    // Check if address has sufficient balance
    if (!hasBalance(address, stake)) {
        cout << "Insufficient balance to stake!" << endl;
        return;
    }
    
    // Lock the stake (subtract from available balance)
    balances[address] -= stake;
    
    Validator validator(address, stake);
    validators[address] = validator;
    totalStake += stake;
    
    cout << "Validator " << address << " registered with stake: " << stake << " X" << endl;
}

string Blockchain::selectValidator() {
    if (validators.empty()) {
        cout << "No validators available!" << endl;
        return "SYSTEM";
    }
    
    // Proof of Stake: Weighted random selection based on stake
    vector<string> addresses;
    vector<double> weights;
    
    for (auto& pair : validators) {
        if (pair.second.getIsActive()) {
            addresses.push_back(pair.first);
            weights.push_back(pair.second.getStake());
        }
    }
    
    if (addresses.empty()) {
        return "SYSTEM";
    }
    
    // Weighted random selection
    random_device rd;
    mt19937 gen(rd());
    discrete_distribution<> dist(weights.begin(), weights.end());
    
    int selectedIndex = dist(gen);
    string selectedValidator = addresses[selectedIndex];
    
    cout << "Validator selected: " << selectedValidator << endl;
    return selectedValidator;
}

void Blockchain::distributeReward(const string& validatorAddress) {
    if (validators.find(validatorAddress) != validators.end()) {
        validators[validatorAddress].addReward(miningReward);
        cout << "Reward of " << miningReward << " X distributed to " << validatorAddress << endl;
    }
}

double Blockchain::getBalance(const string& address) {
    if (balances.find(address) != balances.end()) {
        return balances[address];
    }
    return 0.0;
}

void Blockchain::updateBalance(const string& address, double amount) {
    balances[address] += amount;
}

bool Blockchain::hasBalance(const string& address, double amount) {
    return getBalance(address) >= amount;
}

bool Blockchain::isChainValid() const {
    // Check all blocks except genesis
    for (size_t i = 1; i < chain.size(); i++) {
        const Block& currentBlock = chain[i];
        const Block& previousBlock = chain[i - 1];
        
        // Validate current block
        if (!currentBlock.isValid()) {
            cout << "Block #" << currentBlock.getIndex() << " is invalid!" << endl;
            return false;
        }
        
        // Check if previous hash matches
        if (currentBlock.getPreviousHash() != previousBlock.getHash()) {
            cout << "Block #" << currentBlock.getIndex() << " has invalid previous hash!" << endl;
            return false;
        }
    }
    
    return true;
}

void Blockchain::printChain() const {
    cout << "\n========================================" << endl;
    cout << "       BLOCKCHAIN STATE" << endl;
    cout << "========================================" << endl;
    cout << "Total Blocks: " << chain.size() << endl;
    cout << "Total Validators: " << validators.size() << endl;
    cout << "Total Stake: " << totalStake << " X" << endl;
    cout << "========================================\n" << endl;
    
    for (const auto& block : chain) {
        block.print();
    }
}

void Blockchain::printPendingTransactions() const {
    cout << "\n--- Pending Transactions: " << pendingTransactions.size() << " ---" << endl;
}

void Blockchain::printValidators() const {
    cout << "\n========== VALIDATORS ==========" << endl;
    if (validators.empty()) {
        cout << "No validators registered." << endl;
    } else {
        for (const auto& pair : validators) {
            pair.second.print();
        }
    }
    cout << "================================\n" << endl;
}

void Blockchain::printBalances() const {
    cout << "\n========== ACCOUNT BALANCES ==========" << endl;
    for (const auto& pair : balances) {
        cout << "Address: " << pair.first << " -> Balance: " << pair.second << " X" << endl;
    }
    cout << "======================================\n" << endl;
}