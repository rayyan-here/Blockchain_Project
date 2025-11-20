// include/Transaction.h
#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Utils.h"

using namespace std;

class Transaction {
private:
    string transactionID;
    string sender;
    string receiver;
    double amount;
    long long timestamp;
    string signature; // Simplified - just a hash for now

public:
    // Constructor
    Transaction(const string& sender, const string& receiver, double amount);
    
    // Calculate transaction hash
    string calculateHash() const;
    
    // Validate transaction
    bool isValid() const;
    
    // Sign transaction (simplified)
    void signTransaction();
    
    // Getters
    string getTransactionID() const { return transactionID; }
    string getSender() const { return sender; }
    string getReceiver() const { return receiver; }
    double getAmount() const { return amount; }
    long long getTimestamp() const { return timestamp; }
    string getSignature() const { return signature; }
    
    // Display transaction info
    void print() const;
};

#endif