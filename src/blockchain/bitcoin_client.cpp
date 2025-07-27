// bitcoin_client.cpp
// Implementation of BitcoinClient for fetching transaction data using libcurl

#include "bitcoin_client.h"
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <cctype>
#include <filesystem>
#include <fstream>

using json = nlohmann::json;

namespace InariTx {

BitcoinClient::BitcoinClient() {
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

bool BitcoinClient::validateTxid(const std::string& txid) const {
    // Bitcoin TXID is a 64-character hexadecimal string
    if (txid.length() != 64) {
        return false;
    }
    for (char c : txid) {
        if (!std::isxdigit(c)) {
            return false;
        }
    }
    return true;
}

// Callback function for libcurl to write response data
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    userp->append(static_cast<char*>(contents), size * nmemb);
    return size * nmemb;
}

TransactionData BitcoinClient::fetchTransaction(const std::string& txid) {
    if (!validateTxid(txid)) {
        throw std::invalid_argument("Invalid TXID format");
    }

    // Define the path to cacert.pem relative to the project root
    std::filesystem::path cacert_path = std::filesystem::absolute("cacert.pem");
    if (!std::filesystem::exists(cacert_path)) {
        throw std::runtime_error("CA certificate file (cacert.pem) not found at: " + cacert_path.string());
    }

    CURL* curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to initialize libcurl");
    }

    std::string response_string;
    std::string url = api_base_url + txid;

    // Set libcurl options
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
    curl_easy_setopt(curl, CURLOPT_CAINFO, cacert_path.string().c_str()); // Use absolute path

    // Perform the request
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        curl_easy_cleanup(curl);
        throw std::runtime_error("API request failed: " + std::string(curl_easy_strerror(res)));
    }

    // Clean up curl
    curl_easy_cleanup(curl);

    // Parse JSON response
    try {
        json j = json::parse(response_string);

        TransactionData data;
        data.txid = txid;
        data.sender_address = j["inputs"][0]["addresses"][0].get<std::string>();
        data.receiver_address = j["outputs"][0]["addresses"][0].get<std::string>();
        data.amount = j["total"].get<double>() / 100000000.0; // Convert satoshis to BTC
        data.timestamp = j["confirmed"].get<std::string>();
        // Metadata fields are empty for now
        data.sender_name = "";
        data.receiver_name = "";

        return data;
    } catch (const json::exception& e) {
        throw std::runtime_error("Failed to parse JSON response: " + std::string(e.what()));
    }
}

} // namespace InariTx