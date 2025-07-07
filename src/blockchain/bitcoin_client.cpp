#include "bitcoin_client.h"
#include <stdexcept>

namespace InariTx {

BitcoinClient::BitcoinClient(const Config& config) : config_(config) {
    curl_ = curl_easy_init();
    if (!curl_) {
        throw InariTxException("Failed to initialize libcurl");
    }
}

BitcoinClient::~BitcoinClient() {
    if (curl_) {
        curl_easy_cleanup(curl_);
    }
}

size_t BitcoinClient::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

bool BitcoinClient::isValidTxid(const std::string& txid) {
    if (txid.empty() || txid.length() != 64) {
        return false;
    }
    try {
        auto data = fetchTransaction(txid);
        return !data.txid.empty();
    } catch (const InariTxException&) {
        return false;
    }
}

TransactionData BitcoinClient::fetchTransaction(const std::string& txid) {
    if (txid.empty() || txid.length() != 64) {
        throw InvalidTxidError(txid);
    }
    std::string response;
    std::string url = "https://api.blockcypher.com/v1/btc/main/txs/" + txid;
    // TODO: Add API key to URL when needed (e.g., ?token=config_.getApiKey())
    curl_easy_setopt(curl_, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl_, CURLOPT_CAINFO, "cacert.pem"); // Use CA bundle
    curl_easy_setopt(curl_, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl_, CURLOPT_WRITEDATA, &response);
    CURLcode res = curl_easy_perform(curl_);
    if (res != CURLE_OK) {
        throw ApiError("Failed to fetch transaction: " + std::string(curl_easy_strerror(res)));
    }
    json data = json::parse(response, nullptr, false);
    if (data.is_discarded() || !data.contains("hash")) {
        throw InvalidTxidError(txid);
    }
    TransactionData result;
    result.txid = txid;
    result.sender = data["inputs"][0]["addresses"][0].get<std::string>();
    result.receiver = data["outputs"][0]["addresses"][0].get<std::string>();
    result.amount = data["total"].get<double>() / 1e8; // Convert satoshis to BTC
    result.date = data["confirmed"].get<std::string>();
    return result;
}

} // namespace InariTx