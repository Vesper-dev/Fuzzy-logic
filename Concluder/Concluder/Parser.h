#pragma once
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

struct Arguments {
        std::string arg1, arg2, outcome;
    };

class Parser {
    std::vector<Arguments> args;
    std::fstream file;
    std::string text;
public:
    Parser(std::string fileName) {
        file.open(fileName, std::ios::in);
        if (file.is_open()) {
            while (!file.eof()) {
                text = "";
                args.push_back({});
                file >> args.back().arg1;
                file >> text;
                if (text == "and") {
                    text = "";
                    file >> args.back().arg2;
                    file >> text;
                    if (text == "=") {
                        text = "";
                        file >> args.back().outcome;
                    }
                    else {
                        std::cout << "Parse Fail !!!\n";
                        return;
                    }
                }
                else {
                    std::cout << "Parse Fail !!!\n";
                    return;
                }
            }
            file.close();
        }
        else {
            std::cout << "Error: Nie mo¿na odnaleŸæ pliku\n";
        }
    }

    Arguments get(size_t index) {
        return args[index];
    }

    size_t size() {
        return args.size();
    }
};