#include "cpu.hpp"

#include <fstream>
#include <string>

static std::string detectProfile(
    const std::string& vendor,
    const std::string& family,
    const std::string& model
)
{
    if (vendor == "AuthenticAMD" && family == "23") {
        if (model == "1" || model == "8" || model == "17" ||
            model == "24" || model == "25" || model == "31" ||
            model == "33" || model == "47" || model == "49" ||
            model == "50" || model == "51" || model == "56" ||
            model == "57" || model == "58" || model == "68") {
            return "zen2";
        }
    }

    if (vendor == "AuthenticAMD" && family == "25") {
        return "zen3";
    }

    return "generic";
}

CpuInfo detectCpu()
{
    CpuInfo cpu;

    std::ifstream file("/proc/cpuinfo");
    std::string line;

    std::string family;
    std::string modelNumber;

    while (std::getline(file, line)) {
        if (line.rfind("vendor_id", 0) == 0) {
            cpu.vendor = line.substr(line.find(':') + 2);
        }
        else if (line.rfind("model name", 0) == 0) {
            cpu.model = line.substr(line.find(':') + 2);
        }
        else if (line.rfind("cpu family", 0) == 0) {
            family = line.substr(line.find(':') + 2);
        }
        else if (line.rfind("model", 0) == 0 &&
                 line.rfind("model name", 0) != 0) {
            modelNumber = line.substr(line.find(':') + 2);
        }

        if (!cpu.vendor.empty() &&
            !cpu.model.empty() &&
            !family.empty() &&
            !modelNumber.empty()) {
            break;
        }
    }

#if defined(__x86_64__)
    cpu.architecture = "x86_64";
#elif defined(__aarch64__)
    cpu.architecture = "aarch64";
#else
    cpu.architecture = "unknown";
#endif

    cpu.profile = detectProfile(cpu.vendor, family, modelNumber);

    return cpu;
}