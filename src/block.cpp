// src/Block.cpp
#include "../include/Block.h"
#include <iostream>

using namespace std;

Block::Block(int index, const string& previousHash, const string& validatorAddress)
    : index(index), previousHash(previousHash), validatorAddress(validatorAddress), nonce(0) {
    
    timestamp = Utils::getCurrentTimestamp();
    hash = ""; // Will be calculated when finalized
}

void Block::addTransaction(const Transaction& transaction) {
    if (transaction.isValid()) {
        transactions.push_back(transaction);
    } else {
        cout << "Warning: Invalid transaction not added to block" << endl;
    }
}

string Block::calculateMerkleRoot() const {
    if (transactions.empty()) {
        return Utils::sha256("empty");
    }
    
    // Simplified Merkle root - just hash all transaction IDs together
    string combined = "";
    for (const auto& tx : transactions) {
        combined += tx.getTransactionID();
    }
    return Utils::sha256(combined);
}

string Block::calculateHash() const {
    string merkleRoot = calculateMerkleRoot();
    string data = Utils::toString(index) + 
                  Utils::toString(timestamp) + 
                  previousHash + 
                  merkleRoot + 
                  validatorAddress +
                  Utils::toString(nonce);
    return Utils::sha256(data);
}

void Block::finalizeBlock() {
    hash = calculateHash();
}

bool Block::isValid() const {
    // Check if hash is correctly calculated
    if (hash != calculateHash()) {
        return false;
    }
    
    // Validate all transactions
    for (const auto& tx : transactions) {
        if (!tx.isValid()) {
            return false;
        }
    }
    
    return true;
}

void Block::print() const {
    cout << "\n========== BLOCK " << index << " ==========" << endl;
    cout << "Hash: " << hash << endl;
    cout << "Previous Hash: " << previousHash << endl;
    cout << "Validator: " << validatorAddress << endl;
    cout << "Timestamp: " << timestamp << endl;
    cout << "Transactions: " << transactions.size() << endl;
    cout << "\nTransactions in this block:" << endl;
    for (const auto& tx : transactions) {
        tx.print();
    }
    cout << "===========================\n" << endl;
}