#pragma once

#include <filesystem>
#include <fstream>

class Logger {
    std::filesystem::path filepath;
    std::ofstream output_file;

public:
    Logger(char** argv) {
        filepath = std::string(argv[0]) + "/../../out/log.txt";
        output_file.open(filepath, std::ios::out | std::ios::trunc);
        output_file.close();
    }

    ~Logger() {
        output_file.close();

        // TODO: research if a crash will prevent this from being called, and if so, how to fix it.
    }

    template<typename... Args>
    void LogMessage(const std::string& format, Args... args) {
        output_file.open(filepath, std::ios::app);

        char buffer[1024];
        snprintf(buffer, sizeof(buffer), format.c_str(), args...);
        output_file << buffer;

        output_file.flush();
        output_file.close();
    }
};