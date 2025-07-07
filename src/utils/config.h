#ifndef INARITX_CONFIG_H
#define INARITX_CONFIG_H

#include <string>
#include "i18n/translations.h"

namespace InariTx {

class Config {
public:
    Config();
    std::string getApiKey() const;
    Language getDefaultLanguage() const;

private:
    std::string api_key_;
    Language default_language_;
};

} // namespace InariTx

#endif // INARITX_CONFIG_H