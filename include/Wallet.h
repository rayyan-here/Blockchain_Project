// include/Wallet.h
#ifndef WALLET_H
#define WALLET_H

#include <string>
#include "Utils.h"

using namespace std;

class Wallet {
private:
    string address;
    double balance;
    string publicKey;   // Simplified
    string privateKey;  // Simplified

public:
    // Constructor - generates new wallet
    Wallet();
    
    // Constructor with existing address
    Wallet(const string& address);
    
    // Generate wallet address
    string generateAddress();
    
    // Balance management
    void addBalance(double amount);
    bool subtractBalance(double amount);
    
    // Getters
    string getAddress() const { return address; }
    double getBalance() const { return balance; }
    string getPublicKey() const { return publicKey; }
    
    // Display wallet info
    void print() const;
};

#endif