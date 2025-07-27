// bitcoin_client.h
// Bitcoin-specific blockchain client for fetching transaction data

#ifndef BITCOIN_CLIENT_H
#define BITCOIN_CLIENT_H

#include "client.h"
#include <string>

namespace InariTx {

class BitcoinClient : public BlockchainClient {
public:
    BitcoinClient();
    ~BitcoinClient() override = default;

    // Fetch transaction data from Blockcypher API
    TransactionData fetchTransaction(const std::string& txid) override;

    // Validate Bitcoin TXID format (64-character hexadecimal)
    bool validateTxid(const std::string& txid) const override;

private:
    // Base URL for Blockcypher API
    const std::string api_base_url = "https://api.blockcypher.com/v1/btc/main/txs/";
};

} // namespace InariTx

#endif // BITCOIN_CLIENT_H