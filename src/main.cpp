#include "blockchain/bitcoin_client.h"
#include "pdf/pdf_generator.h"
#include "qr/qr_generator.h"
#include "utils/config.h"
#include <thread>
#include <vector>
#include <iostream>

namespace InariTx {

void processTransaction(const std::string& txid, const Config& config) {
    try {
        BitcoinClient client(config);
        if (!client.isValidTxid(txid)) {
            throw InvalidTxidError(txid);
        }
        TransactionData data = client.fetchTransaction(txid);
        std::string qr_svg = QRGenerator::generateQRCode(txid);
        PDFGenerator pdf_gen(config);
        pdf_gen.createReceiptPDF(data, qr_svg);
        std::cout << "Receipt generated for TXID: " << txid << std::endl;
    } catch (const InariTxException& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

} // namespace InariTx

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <TXID> [en|fr]" << std::endl;
        return 1;
    }

    Config config;
    std::string txid = argv[1];
    if (argc > 2 && std::string(argv[2]) == "fr") {
        config = Config(); // TODO: Set French language in Config
    }

    std::vector<std::string> txids = {txid}; // Support for multiple TXIDs
    std::vector<std::thread> threads;
    for (const auto& id : txids) {
        threads.emplace_back(InariTx::processTransaction, id, config);
    }
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}