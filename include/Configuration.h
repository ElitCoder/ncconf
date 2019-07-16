#pragma once

#include <string>
#include <map>

// This is perhaps done better some other way
const std::string CONFIGURATION_DEFAULT_FILE    = "settings.conf";
const std::string CONFIGURATION_INCLUDE         = "include";

// Configuration will live as a static singleton throughout the program
class Configuration {
public:
    // Parse configuration
    static bool parse(const std::string &filename = CONFIGURATION_DEFAULT_FILE);
    // Return last error
    static const std::string& error();

private:
    static void flush_errors();

    static std::map<std::string, std::string> config_; // Key-value pairs
    static std::string error_; // Last error
};