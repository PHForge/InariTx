/*
* InariTx - Professional Bitcoin Transaction Receipts
* version 0.0.1
* MIT License
*/

#include <iostream>
#include "blockchain/bitcoin_client.h"

int main() {
    std::cout << "Welcome to InariTx - Professional Bitcoin Transaction Receipts" << std::endl;

    try {
        InariTx::BitcoinClient client;
        std::string txid = "f4184fc596403b9d6d3d9c2e143e2b1b1a8d5b6e6f0e4e7e6d8e9f0a1c2b3d4e"; // Example TXID
        if (client.validateTxid(txid)) {
            InariTx::TransactionData data = client.fetchTransaction(txid);
            std::cout << "Transaction Data:" << std::endl;
            std::cout << "TXID: " << data.txid << std::endl;
            std::cout << "Sender: " << data.sender_address << std::endl;
            std::cout << "Receiver: " << data.receiver_address << std::endl;
            std::cout << "Amount: " << data.amount << " BTC" << std::endl;
            std::cout << "Timestamp: " << data.timestamp << std::endl;
        } else {
            std::cout << "Invalid TXID format" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}