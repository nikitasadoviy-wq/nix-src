#pragma once

#include <string>

struct CpuInfo {
    std::string vendor;
    std::string model;
    std::string architecture;
    std::string profile;
};

CpuInfo detectCpu();