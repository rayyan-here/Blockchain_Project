// include/Validator.h
#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>

using namespace std;

class Validator {
private:
    string address;
    double stake;
    double totalRewards;
    bool isActive;

public:
    // Constructor
    Validator();
    Validator(const string& address, double initialStake);
    
    // Stake management
    void addStake(double amount);
    bool removeStake(double amount);
    
    // Reward management
    void addReward(double reward);
    
    // Validator status
    void activate();
    void deactivate();
    
    // Getters
    string getAddress() const { return address; }
    double getStake() const { return stake; }
    double getTotalRewards() const { return totalRewards; }
    bool getIsActive() const { return isActive; }
    
    // Display validator info
    void print() const;
};

#endif