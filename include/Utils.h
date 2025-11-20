// include/Utils.h
#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

class Utils {
public:
    // Convert string to SHA256 hash
    static string sha256(const string& data);
    
    // Generate random string (for addresses, IDs)
    static string generateRandomString(int length);
    
    // Get current timestamp
    static long long getCurrentTimestamp();
    
    // Convert any data to string for hashing
    template<typename T>
    static string toString(const T& value) {
        ostringstream oss;
        oss << value;
        return oss.str();
    }
};

#endif