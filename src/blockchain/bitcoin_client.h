#ifndef INARITX_BITCOIN_CLIENT_H
#define INARITX_BITCOIN_CLIENT_H

#include "client.h"
#include <curl/curl.h>

namespace InariTx {

class BitcoinClient : public BlockchainClient {
public:
    BitcoinClient();
    ~BitcoinClient() override;
    TransactionData fetchTransaction(const std::string& txid) override;
    bool isValidTxid(const std::string& txid) override;

private:
    CURL* curl_;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp);
};

} // namespace InariTx

#endif // INARITX_BITCOIN_CLIENT_H