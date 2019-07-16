#include "Configuration.h"
#include "Log.h"

#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

string Configuration::error_;
map<string, string> Configuration::config_;

static vector<string> tokenize(const string &line, char delim) {
    istringstream words(line);
    vector<string> tokens;

    string word;
    while (getline(words, word, delim)) {
        tokens.push_back(word);
    }

    return tokens;
}

void Configuration::flush_errors() {
    error_ = "";
}

bool Configuration::parse(const string &filename) {
    flush_errors();

    ifstream file(filename);
    if (!file) {
        error_ = "File not found";
        return false;
    }

    // Parse line by line
    string line;
    while (getline(file, line)) {
        // Follow syntax
        // If first character is '#' it's a comment
        if (line.front() == '#') {
            continue;
        }

        // Ignore empty lines
        if (line.empty()) {
            continue;
        }

        // If first word is include, include another file
        auto tokens = tokenize(line, ' ');
        if (tokens.front() == CONFIGURATION_INCLUDE) {
            tokens.erase(tokens.begin());
            if (tokens.empty()) {
                // Missing filename, print warning
                Log(WARN) << "Missing include filename in " << filename;
                continue;
            }

            for (auto &include : tokens) {
                if (!Configuration::parse(include)) {
                    Log(WARN) << "Failed to parse include configuration " << include;
                }
            }
            continue;
        }

        // Add key-value pair if correct syntax "key = value"
        if (tokens.size() >= 3) {
            auto values = tokenize(line, '=');
            // Remove key
            values.erase(values.begin());
            // Remove trailing whitespace
            if (values.front().front() != ' ') {
                Log(WARN) << "Missing whitespace between = and value at line \"" << line << "\"";
                continue;
            }
            values.front().erase(values.front().begin());
            Log(DEBUG) << "Found " << values.front();

            // Everything well, add to configuration
            config_[tokens.front()] = values.front();
            Log(DEBUG) << "Add key \"" << tokens.front() << "\" with values \"" << values.front() << "\"";
        } else {
            Log(WARN) << "Line \"" << line << "\" is invalid syntax";
        }
    }

    file.close();
    return true;
}

const string& Configuration::error() {
    return error_;
}