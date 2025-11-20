// src/Validator.cpp
#include "../include/Validator.h"
#include <iostream>

using namespace std;

// Default constructor
Validator::Validator() 
    : address(""), stake(0.0), totalRewards(0.0), isActive(false) {
}

Validator::Validator(const string& address, double initialStake)
    : address(address), stake(initialStake), totalRewards(0.0), isActive(true) {
}

void Validator::addStake(double amount) {
    if (amount > 0) {
        stake += amount;
        cout << "Added " << amount << " X to stake. New stake: " << stake << " X" << endl;
    }
}

bool Validator::removeStake(double amount) {
    if (amount > 0 && amount <= stake) {
        stake -= amount;
        cout << "Removed " << amount << " X from stake. New stake: " << stake << " X" << endl;
        return true;
    }
    cout << "Cannot remove " << amount << " X. Insufficient stake." << endl;
    return false;
}

void Validator::addReward(double reward) {
    if (reward > 0) {
        totalRewards += reward;
        stake += reward; // Rewards automatically added to stake
    }
}

void Validator::activate() {
    isActive = true;
    cout << "Validator " << address << " activated." << endl;
}

void Validator::deactivate() {
    isActive = false;
    cout << "Validator " << address << " deactivated." << endl;
}

void Validator::print() const {
    cout << "\n--- Validator Info ---" << endl;
    cout << "Address: " << address << endl;
    cout << "Stake: " << stake << " X" << endl;
    cout << "Total Rewards: " << totalRewards << " X" << endl;
    cout << "Status: " << (isActive ? "Active" : "Inactive") << endl;
    cout << "---------------------\n" << endl;
}