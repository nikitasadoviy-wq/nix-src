#pragma once

#include <string>

struct FetchResult {
    std::string path;
    std::string hash;
};

FetchResult fetchSource(const std::string& url);