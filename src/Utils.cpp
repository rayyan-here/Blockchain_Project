// src/Utils.cpp
#include "../include/Utils.h"
#include <openssl/sha.h>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

// SHA256 hashing implementation
string Utils::sha256(const string& data) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.c_str(), data.length());
    SHA256_Final(hash, &sha256);
    
    stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

// Generate random string for addresses/IDs
string Utils::generateRandomString(int length) {
    const string chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, chars.size() - 1);
    
    string result;
    for(int i = 0; i < length; i++) {
        result += chars[distribution(generator)];
    }
    return result;
}

// Get current Unix timestamp
long long Utils::getCurrentTimestamp() {
    return chrono::duration_cast<chrono::seconds>(
        chrono::system_clock::now().time_since_epoch()
    ).count();
}