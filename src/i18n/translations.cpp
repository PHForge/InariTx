#include "translations.h"

namespace InariTx {

Translations::Translations(Language lang) : language_(lang) {
    // English translations
    en_translations_ = {
        {"title", "InariTx: Crypto Transaction Receipt"},
        {"txid", "TXID: "},
        {"from", "From: "},
        {"to", "To: "},
        {"amount", "Amount: "},
        {"verify", "Verify via QR code"}
    };
    // French translations
    fr_translations_ = {
        {"title", "InariTx : Reçu de Transaction Crypto"},
        {"txid", "TXID : "},
        {"from", "De : "},
        {"to", "À : "},
        {"amount", "Montant : "},
        {"verify", "Vérifiez via QR code"}
    };
}

std::string Translations::get(const std::string& key) const {
    if (language_ == Language::EN) {
        return en_translations_.at(key);
    }
    return fr_translations_.at(key);
}

} // namespace InariTx