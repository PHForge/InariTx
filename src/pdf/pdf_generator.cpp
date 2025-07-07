#include "pdf_generator.h"
#include <hpdf.h>
#include "utils/error.h"
#include <filesystem>

namespace InariTx {

PDFGenerator::PDFGenerator(const Config& config)
    : translations_(config.getDefaultLanguage()) {}

void PDFGenerator::createReceiptPDF(const TransactionData& data, const std::string& qr_svg) {
    HPDF_Doc pdf = HPDF_New([](HPDF_STATUS error_no, HPDF_STATUS detail_no, void* user_data) {
        throw PdfError("PDF error: " + std::to_string(error_no));
    }, nullptr);
    if (!pdf) {
        throw PdfError("Failed to initialize PDF document");
    }

    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
    HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", nullptr);
    HPDF_Page_SetFontAndSize(page, font, 12);

    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, 50, 750, translations_.get("title").c_str());
    HPDF_Page_TextOut(page, 50, 730, (translations_.get("txid") + data.txid).c_str());
    HPDF_Page_TextOut(page, 50, 710, (translations_.get("from") + data.sender).c_str());
    HPDF_Page_TextOut(page, 50, 690, (translations_.get("to") + data.receiver).c_str());
    HPDF_Page_TextOut(page, 50, 670, (translations_.get("amount") + std::to_string(data.amount) + " BTC").c_str());
    HPDF_Page_TextOut(page, 50, 650, translations_.get("verify").c_str());
    HPDF_Page_EndText(page);

    // Save QR code SVG to temporary file (libharu doesn't support SVG directly)
    std::string qr_file = "qr_" + data.txid + ".svg";
    std::ofstream qr_out(qr_file);
    qr_out << qr_svg;
    qr_out.close();

    // TODO: Convert SVG to PNG for libharu (requires external tool or library)
    HPDF_SaveToFile(pdf, ("receipt_" + data.txid + ".pdf").c_str());
    std::filesystem::remove(qr_file); // Clean up
    HPDF_Free(pdf);
}

} // namespace InariTx