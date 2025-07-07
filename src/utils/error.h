#ifndef INARITX_ERROR_H
#define INARITX_ERROR_H

#include <stdexcept>
#include <string>

namespace InariTx {

class InariTxException : public std::runtime_error {
public:
    explicit InariTxException(const std::string& message)
        : std::runtime_error(message) {}
};

// Specific error types
class InvalidTxidError : public InariTxException {
public:
    explicit InvalidTxidError(const std::string& txid)
        : InariTxException("Invalid TXID: " + txid) {}
};

class ApiError : public InariTxException {
public:
    explicit ApiError(const std::string& message)
        : InariTxException("API error: " + message) {}
};

class PdfError : public InariTxException {
public:
    explicit PdfError(const std::string& message)
        : InariTxException("PDF generation error: " + message) {}
};

} // namespace InariTx

#endif // INARITX_ERROR_H