#include "hash.hpp"

#include <openssl/evp.h>

#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>

std::string sha256File(const std::string& path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file) {
        throw std::runtime_error("Cannot open file: " + path);
    }

    EVP_MD_CTX* context = EVP_MD_CTX_new();

    if (!context) {
        throw std::runtime_error("Failed to create SHA-256 context");
    }

    if (EVP_DigestInit_ex(context, EVP_sha256(), nullptr) != 1) {
        EVP_MD_CTX_free(context);
        throw std::runtime_error("Failed to initialize SHA-256");
    }

    char buffer[8192];

    while (file.read(buffer, sizeof(buffer)) || file.gcount() > 0) {
        if (EVP_DigestUpdate(
                context,
                buffer,
                static_cast<std::size_t>(file.gcount())) != 1) {

            EVP_MD_CTX_free(context);
            throw std::runtime_error("Failed to update SHA-256");
        }
    }

    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int digestLength = 0;

    if (EVP_DigestFinal_ex(
            context,
            digest,
            &digestLength) != 1) {

        EVP_MD_CTX_free(context);
        throw std::runtime_error("Failed to finalize SHA-256");
    }

    EVP_MD_CTX_free(context);

    std::ostringstream result;
    result << std::hex << std::setfill('0');

    for (unsigned int i = 0; i < digestLength; ++i) {
        result << std::setw(2)
               << static_cast<unsigned int>(digest[i]);
    }

    return result.str();
}

bool verifySha256(
    const std::string& path,
    const std::string& expected
)
{
    return sha256File(path) == expected;
}