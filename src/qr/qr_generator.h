#ifndef INARITX_QR_GENERATOR_H
#define INARITX_QR_GENERATOR_H

#include <string>

namespace InariTx {

class QRGenerator {
public:
    static std::string generateQRCode(const std::string& txid);
};

} // namespace InariTx

#endif // INARITX_QR_GENERATOR_H