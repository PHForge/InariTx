#ifndef INARITX_PDF_GENERATOR_H
#define INARITX_PDF_GENERATOR_H

#include "blockchain/client.h"
#include "i18n/translations.h"
#include "utils/config.h"
#include <string>

namespace InariTx {

class PDFGenerator {
public:
    PDFGenerator(const Config& config);
    void createReceiptPDF(const TransactionData& data, const std::string& qr_svg);

private:
    Translations translations_;
};

} // namespace InariTx

#endif // INARITX_PDF_GENERATOR_H