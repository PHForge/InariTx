#include "qr_generator.h"
#include <qrcodegen.hpp>

namespace InariTx {

std::string QRGenerator::generateQRCode(const std::string& txid) {
    if (txid.empty()) {
        throw InariTxException("Empty TXID provided for QR code generation");
    }
    std::string url = "https://blockchain.com/btc/tx/" + txid;
    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(url.c_str(), qrcodegen::QrCode::Ecc::MEDIUM);
    return qr.toSvgString(4); // SVG for PDF integration
}

} // namespace InariTx