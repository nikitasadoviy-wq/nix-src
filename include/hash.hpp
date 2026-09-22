#pragma once

#include <string>

std::string sha256File(const std::string& path);

bool verifySha256(
    const std::string& path,
    const std::string& expected
);