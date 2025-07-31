// main.cpp
// Entry point for the InariTx application

#include <iostream>
#include <string>
#include <limits> // Added for std::numeric_limits
#include <cctype>
#include "blockchain/bitcoin_client.h"

int main() {
    std::cout << "Welcome to InariTx - Professional Bitcoin Transaction Receipts" << std::endl;

    // Clear input buffer
     std::cin.clear();
    // Ignore any leftover characters in the input buffer
     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string txid;
    bool valid_input = false;

    while (!valid_input) {
        std::cout << "Enter a Bitcoin TXID (64-character hexadecimal, or 'quit' to exit): ";
        std::cout.flush(); // Ensure prompt is displayed
        std::getline(std::cin, txid);

        // Debug: Print the raw input
        std::cout << "Debug: Input received: '" << txid << "'" << std::endl;

        // Check if user wants to quit
        if (txid == "quit") {
            std::cout << "Exiting program." << std::endl;
            return 0;
        }

        try {
            InariTx::BitcoinClient client;
            if (client.validateTxid(txid)) {
                valid_input = true;
                InariTx::TransactionData data = client.fetchTransaction(txid);
                std::cout << "Transaction Data:" << std::endl;
                std::cout << "TXID: " << data.txid << std::endl;
                std::cout << "Sender: " << data.sender_address << std::endl;
                std::cout << "Receiver: " << data.receiver_address << std::endl;
                std::cout << "Amount: " << data.amount << " BTC" << std::endl;
                std::cout << "Timestamp: " << data.timestamp << std::endl;
            } else {
                std::cout << "Invalid TXID format. Please enter a 64-character hexadecimal string." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            std::cout << "Please try another TXID or type 'quit' to exit." << std::endl;
        }
    }

    return 0;
}