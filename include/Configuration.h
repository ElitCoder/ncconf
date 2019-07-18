#pragma once

#include <string>
#include <map>
#include <vector>

#include "Log.h"

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
    // Return generic value
    template<class T>
    static T get(const std::string &key, const T &default_value) {
        if (!has(key)) {
            Log(DEBUG) << "Key " << key << " missing, returning default value";
            return default_value;
        }

        std::istringstream stream(config_[key]);
        T value;
        stream >> value;
        return value;
    }
    // Return generic list
    template<class T>
    static std::vector<T> get_all(const std::string &key) {
        if (!has(key)) {
            Log(DEBUG) << "Key " << key << " missing, returning empty list";
            return std::vector<T>();
        }

        std::istringstream stream(config_[key]);
        std::vector<T> values;
        for (T &value : stream) {
            values.push_back(value);
        }
        return values;
    }

private:
    static bool has(const std::string &key);
    static void flush_errors();

    static std::map<std::string, std::string> config_; // Key-value pairs
    static std::string error_; // Last error
};