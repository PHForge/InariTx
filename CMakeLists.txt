cmake_minimum_required(VERSION 3.10)
project(InariTx)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Répertoires pour les en-têtes et bibliothèques
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# Forcer la compilation statique de libcurl
add_definitions(-DCURL_STATICLIB)

# Trouver les dépendances système
find_library(ZLIB_LIBRARY NAMES z zlib libz PATHS /mingw64/lib)
find_library(PNG_LIBRARY NAMES png libpng PATHS /mingw64/lib)
find_library(CURL_LIBRARY NAMES curl libcurl PATHS /mingw64/lib)
find_library(OPENSSL_SSL_LIBRARY NAMES ssl libssl PATHS /mingw64/lib)
find_library(OPENSSL_CRYPTO_LIBRARY NAMES crypto libcrypto PATHS /mingw64/lib)
find_library(WS2_32_LIBRARY NAMES ws2_32 PATHS /mingw64/lib)
find_library(IDN2_LIBRARY NAMES idn2 libidn2 PATHS /mingw64/lib)
find_library(SSH2_LIBRARY NAMES ssh2 libssh2 PATHS /mingw64/lib)
find_library(WLDAP32_LIBRARY NAMES wldap32 PATHS /mingw64/lib)
find_library(PSL_LIBRARY NAMES psl libpsl PATHS /mingw64/lib)
find_library(BROTLI_LIBRARY NAMES brotlidec libbrotlidec PATHS /mingw64/lib)
find_library(ZSTD_LIBRARY NAMES zstd libzstd PATHS /mingw64/lib)
find_library(NGHTTP2_LIBRARY NAMES nghttp2 libnghttp2 PATHS /mingw64/lib)
find_library(BCRYPT_LIBRARY NAMES bcrypt PATHS /mingw64/lib)
find_library(IPHLPAPI_LIBRARY NAMES iphlpapi PATHS /mingw64/lib)
find_library(CRYPT32_LIBRARY NAMES crypt32 PATHS /mingw64/lib)

# Ajouter l'exécutable principal
add_executable(InariTx
    src/main.cpp
    src/blockchain/client.cpp
    src/blockchain/bitcoin_client.cpp
    src/pdf/pdf_generator.cpp
    src/qr/qr_generator.cpp
    src/i18n/translations.cpp
    src/utils/error.cpp
    src/utils/config.cpp
)

# Lier les bibliothèques
target_link_libraries(InariTx hpdf qrcodegen curl ${ZLIB_LIBRARY} ${PNG_LIBRARY} ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY} ${WS2_32_LIBRARY} ${IDN2_LIBRARY} ${SSH2_LIBRARY} ${WLDAP32_LIBRARY} ${PSL_LIBRARY} ${BROTLI_LIBRARY} ${ZSTD_LIBRARY} ${NGHTTP2_LIBRARY} ${BCRYPT_LIBRARY} ${IPHLPAPI_LIBRARY} ${CRYPT32_LIBRARY})

# Pour les tests
enable_testing()
add_executable(test_inaritx
    tests/test_main.cpp
    tests/test_bitcoin_client.cpp
    tests/test_pdf_generator.cpp
    tests/test_qr_generator.cpp
    tests/test_json.cpp
    tests/test_curl.cpp
)
target_link_libraries(test_inaritx hpdf qrcodegen curl ${ZLIB_LIBRARY} ${PNG_LIBRARY} ${OPENSSL_SSL_LIBRARY} ${OPENSSL_CRYPTO_LIBRARY} ${WS2_32_LIBRARY} ${IDN2_LIBRARY} ${SSH2_LIBRARY} ${WLDAP32_LIBRARY} ${PSL_LIBRARY} ${BROTLI_LIBRARY} ${ZSTD_LIBRARY} ${NGHTTP2_LIBRARY} ${BCRYPT_LIBRARY} ${IPHLPAPI_LIBRARY} ${CRYPT32_LIBRARY})
add_test(NAME TestInariTx COMMAND test_inaritx)