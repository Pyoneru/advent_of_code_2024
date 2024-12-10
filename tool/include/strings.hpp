//
// Created by piotr on 01/12/2024.
//

#ifndef STRINGS_HPP
#define STRINGS_HPP
#include <memory>
#include <vector>

std::tuple<std::unique_ptr<std::vector<std::string>>, bool> get_file_lines(const char *filename);

std::tuple<std::unique_ptr<std::vector<std::string>>, bool> split(const std::string &s, char delim);

#endif //STRINGS_HPP
