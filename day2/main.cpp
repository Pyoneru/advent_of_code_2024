#include <strings.hpp>
#include <iostream>
#include <fmt/core.h>

#include "fmt/xchar.h"

auto filename = "input.txt";

enum Direction {
    NONE,
    INCREASING,
    DECREASING
};

bool inTolerateRange(int first, int second);
bool isKeepingDirection(int first, int second, int & direction);
bool canIgnoreBadLevel(const std::vector<int> &levels, int level, int & direction);
bool isSafeReport(std::vector<int> & levels, bool checkSingleBadLevel);
std::vector<int> createNewLevels(const std::vector<int> &levels, size_t skip);


int main() {
    auto &&[lines, linesOk] = get_file_lines(filename);

    if (!linesOk) {
        fmt::println(stderr, "Failed to read input file");
        return EXIT_FAILURE;
    }

    int safeReportCounter = 0;
    for (auto &line: *lines) {
        auto &&[tokens, tokensOK] = split(line, ' ');
        if (!tokensOK) {
            fmt::println(stderr, "failed to split line : {}", line);
            return EXIT_FAILURE;
        }

        std::vector<int> levels;
        for (auto &token: *tokens) {
            levels.push_back(std::stoi(token));
        }
        if (isSafeReport(levels, true)) {
            safeReportCounter++;
        }
    }

    fmt::println("Safe report counter: {}", safeReportCounter);
    return EXIT_SUCCESS;
}

bool inTolerateRange(const int first, const int second) {
    const int diff = first > second ? first - second : second - first;
    return diff >= 1 && diff <= 3;
}

bool isKeepingDirection(const int first, const int second, int & direction) {
    if (direction == NONE) {
        direction = first > second ? INCREASING : DECREASING;
        return true;
    }

    if (const int nextDirection = first > second ? INCREASING : DECREASING; nextDirection == direction) {
        return true;
    }

    return false;
}

bool canIgnoreBadLevel(const std::vector<int> &levels, int level, int & direction) {
    // skip first (f)

    // if (level == 0) {
    //     const int first = levels[level];
    //     const int second = levels[level + 1];
    //     const int third = levels[level + 2];
    //     if(inTolerateRange(second, third)) {
    //         const int nextDirection = second > third ? INCREASING : DECREASING;
    //         const int currentDirection = first > second ? INCREASING : DECREASING;
    //
    //     }
    // }

    if (level > 0) {
        const int first = levels[level - 1];
        const int second = levels[level + 1];
        if (inTolerateRange(first, second)) {
            return isKeepingDirection(first, second, direction);
        }
    }

    if(level + 2 < levels.size()) {
        const int first = levels[level + 1];
        const int second = levels[level + 2];
        if (inTolerateRange(first, second)) {
            return isKeepingDirection(first, second, direction);
        }
    }

    return false;
}

bool isSafeReport(std::vector<int> & levels, bool checkSingleBadLevel) {
    int direction = NONE;
    for (int i = 0; i < levels.size() - 1; i++) {
        const int first = levels[i];
        const int second = levels[i + 1];

        if (!inTolerateRange(first, second)) {
            if (checkSingleBadLevel) {
                for( int x = 0; x < levels.size(); x++) {
                    std::vector<int> newLevels = createNewLevels(levels, x);
                    if (isSafeReport(newLevels, false)) {
                        fmt::println("{}", fmt::join(levels, " "));
                        return true;
                    }
                }
                return false;
            }
            return false;
        }

        if (!isKeepingDirection(first, second, direction)) {
            if (checkSingleBadLevel) {
                for( int x = 0; x < levels.size(); x++) {
                    std::vector<int> newLevels = createNewLevels(levels, x);
                    if (isSafeReport(newLevels, false)) {
                        fmt::println("{}", fmt::join(levels, " "));
                        return true;
                    }
                }
                return false;
            }
            return false;
        }
    }
    fmt::println("{}", fmt::join(levels, " "));
    return true;
}

std::vector<int> createNewLevels(const std::vector<int> &levels, const size_t skip) {
    std::vector<int> newLevels;

    for(size_t i = 0; i < levels.size(); i++) {
        if( i != skip) {
            newLevels.push_back( levels[i] );
        }
    }

    return newLevels;
}