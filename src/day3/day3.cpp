#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

#define toDigit(c) (c - '0')

int main(int argc, char* argv[]) {
    std::ifstream input_file(argv[1]);
    std::string line;
    std::vector<std::string> lines;
    std::string out;
    int lineCount = 0, sum = 0;

    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            lineCount += 1;
            lines.push_back(line);
        }

        for (size_t row=0; row<lines.size(); ++row) {
            for (size_t col=0; col<lines[row].size(); ++col) {
                if (isdigit(lines[row].at(col))) {
                    size_t startIndx = col;
                    int digitLength = 0;
                    bool found = false;
                    while (col < lines[row].size() && isdigit(lines[row].at(col))) {
                        // Here we check the surrounding for a symbol
                        if (row != 0 && row != lines.size()-1 && col != 0 && col != lines[row].size()-1) {
                            for (int i=-1; i<=1; ++i) {
                                for (int j=-1; j<=1; ++j) {
                                    if (!isalnum(lines[row + i].at(col + j)) && lines[row + i].at(col + j) != '.') {
                                        found = true;
                                        break;
                                }
                            }
                            if (found) break;
                        }
                        }
                        else if (row == 0 && col != 0 && col != lines[row].size()-1) {
                            for (int i=0; i<=1; ++i) {
                                for (int j=-1; j<=1; ++j) {
                                    if (!isalnum(lines[row + i].at(col + j)) && lines[row + i].at(col + j) != '.') {
                                        found = true;
                                        break;
                                }
                            }
                            if (found) break;
                        }
                        }
                        else if (row == lines.size()-1 && col != 0 && col != lines[row].size()-1) {
                            for (int i=-1; i<=0; ++i) {
                                for (int j=-1; j<=1; ++j) {
                                    if (!isalnum(lines[row + i].at(col + j)) && lines[row + i].at(col + j) != '.') {
                                        found = true;
                                        break;
                                }
                            }
                            if (found) break;
                        }
                        }
                        else if (col == 0 && row != 0 && row != lines.size()-1) {
                            for (int i=-1; i<=1; ++i) {
                                for (int j=0; j<=1; ++j) {
                                    if (!isalnum(lines[row + i].at(col + j)) && lines[row + i].at(col + j) != '.') {
                                        found = true;
                                        break;
                                }
                            }
                            if (found) break;
                        }
                        }
                        else if (col == lines[row].size()-1 && row != 0 && row != lines.size()-1) {
                            for (int i=-1; i<=1; ++i) {
                                for (int j=-1; j<=0; ++j) {
                                    if (!isalnum(lines[row + i].at(col + j)) && lines[row + i].at(col + j) != '.') {
                                        found = true;
                                        break;
                                }
                            }
                            if (found) break;
                        }
                        }
                        ++digitLength;
                        ++col;
                    }
                    if (found) {
                        out += lines[row].substr(startIndx, digitLength);
                        sum += std::stoi(lines[row].substr(startIndx, digitLength));
                    }
                }
            }
        }
       std::cout << out << "\n";
       std::cout << sum << "\n";
    }   
    else {
        std::cout << "Unable to open input file!\n"; 
    } 
}