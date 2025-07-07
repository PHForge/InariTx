#ifndef INARITX_CLIENT_H
#define INARITX_CLIENT_H

#include <nlohmann/json.hpp>
#include <string>
#include "error.h"

namespace InariTx {

using json = nlohmann::json;

struct TransactionData {
    std::string txid;
    std::string sender;
    std::string receiver;
    double amount;
    std::string date;
};

class BlockchainClient {
public:
    virtual ~BlockchainClient() = default;
    virtual TransactionData fetchTransaction(const std::string& txid) = 0;
    virtual bool isValidTxid(const std::string& txid) = 0;
};

} // namespace InariTx

#endif // INARITX_CLIENT_H