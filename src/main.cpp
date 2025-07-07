#include "blockchain/bitcoin_client.h"
#include "pdf/pdf_generator.h"
#include "qr/qr_generator.h"
#include <thread>
#include <vector>
#include <iostream>

namespace InariTx {

void processTransaction(const std::string& txid, Language lang) {
    try {
        BitcoinClient client;
        if (!client.isValidTxid(txid)) {
            throw InvalidTxidError(txid);
        }
        TransactionData data = client.fetchTransaction(txid);
        std::string qr_svg = QRGenerator::generateQRCode(txid);
        PDFGenerator pdf_gen(lang);
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

    std::string txid = argv[1];
    InariTx::Language lang = (argc > 2 && std::string(argv[2]) == "fr") 
        ? InariTx::Language::FR : InariTx::Language::EN;

    std::vector<std::string> txids = {txid}; // Placeholder for multiple TXIDs
    std::vector<std::thread> threads;
    for (const auto& id : txids) {
        threads.emplace_back(InariTx::processTransaction, id, lang);
    }
    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}