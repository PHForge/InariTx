// client.h
// Abstract interface for blockchain clients

#ifndef CLIENT_H
#define CLIENT_H

#include <string>

namespace InariTx {

// Structure to hold transaction data
struct TransactionData {
    std::string txid;
    std::string sender_address;
    std::string receiver_address;
    double amount; // Amount in BTC (or equivalent for other blockchains)
    std::string timestamp;
    // Add metadata fields for future extensibility
    std::string sender_name;
    std::string receiver_name;
};

// Abstract base class for blockchain clients
class BlockchainClient {
public:
    virtual ~BlockchainClient() = default;

    // Fetch transaction data given a transaction ID (TXID)
    virtual TransactionData fetchTransaction(const std::string& txid) = 0;

    // Validate the format of a TXID
    virtual bool validateTxid(const std::string& txid) const = 0;
};

} // namespace InariTx

#endif // CLIENT_H