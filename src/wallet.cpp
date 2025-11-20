// src/Wallet.cpp
#include "../include/Wallet.h"
#include <iostream>

using namespace std;

Wallet::Wallet() {
    // Generate random keys (simplified - not real cryptography)
    privateKey = Utils::generateRandomString(64);
    publicKey = Utils::sha256(privateKey);
    address = generateAddress();
    balance = 0.0;
}

Wallet::Wallet(const string& address) : address(address), balance(0.0) {
    privateKey = Utils::generateRandomString(64);
    publicKey = Utils::sha256(privateKey);
}

string Wallet::generateAddress() {
    // Generate address from public key (simplified)
    string hash = Utils::sha256(publicKey);
    return "0x" + hash.substr(0, 40); // Take first 40 chars like Ethereum
}

void Wallet::addBalance(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

bool Wallet::subtractBalance(double amount) {
    if (amount > 0 && amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}

void Wallet::print() const {
    cout << "\n===== WALLET INFO =====" << endl;
    cout << "Address: " << address << endl;
    cout << "Balance: " << balance << " X" << endl;
    cout << "Public Key: " << publicKey.substr(0, 20) << "..." << endl;
    cout << "======================\n" << endl;
}