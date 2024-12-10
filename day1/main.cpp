#include <iostream>
#include <strings.hpp>

#include "fmt/xchar.h"

auto filename = "input.txt";

int main() {

    auto&& [lines, ok] = get_file_lines(filename);

    if (!ok) {
        fmt::println(stderr, "Error reading file {}", filename);
    }

    std::vector<int> leftColumn;
    std::vector<int> rightColumn;

    for(auto &line : *lines) {
        auto&& [tokens, splited] = split(line, ' ');
        if (!splited) {
            fmt::println(stderr, "Cannot split the line: {}", line);
            return EXIT_FAILURE;
        }
        if(tokens->size() != 2) {
            fmt::println(stderr, "Wrong number of tokens: {}", tokens->size());
            return EXIT_FAILURE;
        }

        int left = std::stoi(tokens->at(0));
        int right = std::stoi(tokens->at(1));

        leftColumn.push_back(left);
        rightColumn.push_back(right);
    }

    std::ranges::sort(leftColumn);
    std::ranges::sort(rightColumn);

    int similarity = 0;
    for(const auto &left : leftColumn) {
        int count = 0;
        for(const auto &right : rightColumn) {
            if(right > left) break;
            if(right == left) count++;
        }
        similarity += (left * count);
    }

    fmt::println("Similarity: {}", similarity);
    return EXIT_SUCCESS;
}