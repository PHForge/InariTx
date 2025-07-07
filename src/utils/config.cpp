#include "config.h"
#include "utils/error.h"

namespace InariTx {

Config::Config() : api_key_(""), default_language_(Language::EN) {
    // TODO: Load from config file (e.g., JSON) in future phases
}

std::string Config::getApiKey() const {
    if (api_key_.empty()) {
        throw InariTxException("API key not configured");
    }
    return api_key_;
}

Language Config::getDefaultLanguage() const {
    return default_language_;
}

} // namespace InariTx