#include "fetch.hpp"
#include "hash.hpp"

#include <curl/curl.h>

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>

static size_t writeData(
    void* data,
    size_t size,
    size_t count,
    void* userdata
)
{
    auto* file = static_cast<std::ofstream*>(userdata);

    const size_t totalSize = size * count;

    file->write(
        static_cast<const char*>(data),
        static_cast<std::streamsize>(totalSize)
    );

    return file->good() ? totalSize : 0;
}

FetchResult fetchSource(const std::string& url)
{
    const auto slash = url.find_last_of('/');

    if (slash == std::string::npos || slash + 1 >= url.size()) {
        throw std::runtime_error("Cannot determine filename from URL");
    }

    std::string filename = url.substr(slash + 1);

    const auto query = filename.find_first_of("?#");

    if (query != std::string::npos) {
        filename.erase(query);
    }

    if (filename.empty()) {
        throw std::runtime_error("URL does not contain a filename");
    }

    const std::filesystem::path outputDirectory = "sources";
    const std::filesystem::path outputPath =
        outputDirectory / filename;

    std::filesystem::create_directories(outputDirectory);

    std::ofstream file(outputPath, std::ios::binary);

    if (!file) {
        throw std::runtime_error(
            "Cannot create output file: " + outputPath.string()
        );
    }

    CURL* curl = curl_easy_init();

    if (!curl) {
        throw std::runtime_error("Failed to initialize libcurl");
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "nix-src/0.1.0");
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 30L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &file);

    const CURLcode result = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    file.close();

    if (result != CURLE_OK) {
        std::filesystem::remove(outputPath);

        throw std::runtime_error(
            std::string("Download failed: ") +
            curl_easy_strerror(result)
        );
    }

    FetchResult fetchResult;
    fetchResult.path = outputPath.string();
    fetchResult.hash = sha256File(fetchResult.path);

    return fetchResult;
}