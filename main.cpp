// main.cpp
#include <iostream>
#include "include/Blockchain.h"
#include "include/Wallet.h"
#include "include/Utils.h"

using namespace std;

int main() {
    cout << "=====================================" << endl;
    cout << "  BLOCKCHAIN WITH PROOF OF STAKE" << endl;
    cout << "  Currency: X Coin" << endl;
    cout << "=====================================" << endl;
    
    // Initialize blockchain
    Blockchain blockchain;
    
    cout << "\n--- Step 1: Creating Wallets ---" << endl;
    
    // Create wallets
    Wallet alice("Alice");
    Wallet bob("Bob");
    Wallet charlie("Charlie");
    Wallet dave("Dave");
    
    // Give initial balances (simulating initial coin distribution)
    blockchain.updateBalance("Alice", 1000);
    blockchain.updateBalance("Bob", 800);
    blockchain.updateBalance("Charlie", 1200);
    blockchain.updateBalance("Dave", 500);
    
    cout << "Wallets created with initial balances." << endl;
    blockchain.printBalances();
    
    cout << "\n--- Step 2: Registering Validators ---" << endl;
    
    // Register validators with different stakes (POS)
    blockchain.registerValidator("Alice", 500);  // High stake
    blockchain.registerValidator("Bob", 300);    // Medium stake
    blockchain.registerValidator("Charlie", 200); // Low stake
    
    blockchain.printValidators();
    blockchain.printBalances();
    
    cout << "\n--- Step 3: Creating Transactions ---" << endl;
    
    // Create transactions
    Transaction tx1("Alice", "Dave", 100);
    tx1.signTransaction();
    blockchain.addTransaction(tx1);
    
    Transaction tx2("Bob", "Charlie", 50);
    tx2.signTransaction();
    blockchain.addTransaction(tx2);
    
    Transaction tx3("Charlie", "Alice", 75);
    tx3.signTransaction();
    blockchain.addTransaction(tx3);
    
    Transaction tx4("Dave", "Bob", 30);
    tx4.signTransaction();
    blockchain.addTransaction(tx4);
    
    cout << "\n--- Step 4: Processing Transactions (Block 1) ---" << endl;
    
    // Select validator using POS
    string validator1 = blockchain.selectValidator();
    blockchain.processTransactions(validator1);
    
    blockchain.printBalances();
    
    cout << "\n--- Step 5: More Transactions ---" << endl;
    
    Transaction tx5("Alice", "Bob", 120);
    tx5.signTransaction();
    blockchain.addTransaction(tx5);
    
    Transaction tx6("Charlie", "Dave", 80);
    tx6.signTransaction();
    blockchain.addTransaction(tx6);
    
    cout << "\n--- Step 6: Processing Transactions (Block 2) ---" << endl;
    
    string validator2 = blockchain.selectValidator();
    blockchain.processTransactions(validator2);
    
    blockchain.printBalances();
    
    cout << "\n--- Step 7: Even More Transactions ---" << endl;
    
    Transaction tx7("Bob", "Alice", 60);
    tx7.signTransaction();
    blockchain.addTransaction(tx7);
    
    Transaction tx8("Dave", "Charlie", 40);
    tx8.signTransaction();
    blockchain.addTransaction(tx8);
    
    Transaction tx9("Alice", "Charlie", 90);
    tx9.signTransaction();
    blockchain.addTransaction(tx9);
    
    cout << "\n--- Step 8: Processing Transactions (Block 3) ---" << endl;
    
    string validator3 = blockchain.selectValidator();
    blockchain.processTransactions(validator3);
    
    blockchain.printBalances();
    
    cout << "\n--- Step 9: Validating Blockchain Integrity ---" << endl;
    
    if (blockchain.isChainValid()) {
        cout << "✓ Blockchain is VALID!" << endl;
    } else {
        cout << "✗ Blockchain is INVALID!" << endl;
    }
    
    cout << "\n--- Step 10: Display Complete Blockchain ---" << endl;
    blockchain.printChain();
    
    cout << "\n--- Final Validator Stats ---" << endl;
    blockchain.printValidators();
    
    cout << "\n--- Final Account Balances ---" << endl;
    blockchain.printBalances();
    
    cout << "\n=====================================" << endl;
    cout << "  BLOCKCHAIN DEMO COMPLETED" << endl;
    cout << "  Total Blocks: " << blockchain.getChainLength() << endl;
    cout << "=====================================" << endl;
    
    return 0;
}