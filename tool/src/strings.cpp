#include "strings.h"

#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <tuple>

std::tuple<std::unique_ptr<std::vector<std::string>>, bool> get_file_lines(const char *filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        return std::make_tuple(nullptr, false);
    }
    auto lines = std::make_unique<std::vector<std::string>>();

    std::string line;
    while (std::getline(file, line)) lines->push_back(line);
    file.close();

    return std::make_tuple(std::move(lines), true);
}

std::tuple<std::unique_ptr<std::vector<std::string>>, bool> split(const std::string &s, char delim) {
    if (s.empty()) {
        return std::make_tuple(nullptr, false);
    }

    auto tokens = std::make_unique<std::vector<std::string>>();

    size_t start = 0, end = 0;

    std::string token;
    while ((end = s.find(delim, start)) != std::string::npos) {
        token = s.substr(start, end - start);
        start = end + 1;
        if (token.empty() || (token.size() == 1 && token[0] == delim)) {
            continue;
        }
        tokens->push_back(token);
    }

    if (start < s.length() && end == std::string::npos) {
        token = s.substr(start);
        tokens->push_back(token);
    }

    return std::make_tuple(std::move(tokens), true);
}