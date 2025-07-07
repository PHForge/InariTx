#ifndef INARITX_TRANSLATIONS_H
#define INARITX_TRANSLATIONS_H

#include <string>
#include <unordered_map>

namespace InariTx {

enum class Language { EN, FR };

class Translations {
public:
    Translations(Language lang = Language::EN);
    std::string get(const std::string& key) const;

private:
    std::unordered_map<std::string, std::string> en_translations_;
    std::unordered_map<std::string, std::string> fr_translations_;
    Language language_;
};

} // namespace InariTx

#endif // INARITX_TRANSLATIONS_H