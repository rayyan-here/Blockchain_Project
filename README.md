File are compiled by 
g++ -o blockchain.exe main.cpp src/Utils.cpp src/Transaction.cpp src/Block.cpp src/Validator.cpp src/Wallet.cpp src/Blockchain.cpp -I./include -lssl -lcrypto -std=c++17

also there is a test case for main (no user input), the above code is for understanding the functionality of the code
