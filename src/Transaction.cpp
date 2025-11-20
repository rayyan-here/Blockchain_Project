// src/Transaction.cpp
#include "../include/Transaction.h"
#include <iostream>

using namespace std;

Transaction::Transaction(const string& sender, const string& receiver, double amount)
    : sender(sender), receiver(receiver), amount(amount) {
    
    timestamp = Utils::getCurrentTimestamp();
    transactionID = calculateHash();
    signature = ""; // Will be set when signed
}

string Transaction::calculateHash() const {
    string data = sender + receiver + Utils::toString(amount) + Utils::toString(timestamp);
    return Utils::sha256(data);
}

bool Transaction::isValid() const {
    // Basic validation
    if (amount <= 0) {
        return false;
    }
    if (sender.empty() || receiver.empty()) {
        return false;
    }
    if (sender == receiver) {
        return false;
    }
    // Check if signature exists (for non-mining rewards)
    if (sender != "SYSTEM" && signature.empty()) {
        return false;
    }
    return true;
}

void Transaction::signTransaction() {
    // Simplified signing - just hash the transaction
    // In real blockchain, this would use private key cryptography
    signature = Utils::sha256(transactionID + sender);
}

void Transaction::print() const {
    cout << "Transaction ID: " << transactionID << endl;
    cout << "From: " << sender << endl;
    cout << "To: " << receiver << endl;
    cout << "Amount: " << amount << " X" << endl;
    cout << "Timestamp: " << timestamp << endl;
    cout << "Signature: " << (signature.empty() ? "Not signed" : signature.substr(0, 16) + "...") << endl;
    cout << "-------------------" << endl;
}