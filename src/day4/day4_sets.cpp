#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <set>
#include <algorithm>

void parse_numbers(std::string line, std::set<int>& wNums, std::set<int>& cNums) {
    size_t colonPos = 0, barPos = 0;
    colonPos = line.find(':');
    barPos = line.find('|');
    for (size_t i=colonPos; i<barPos; ++i) {
        if (isdigit(line[i])) {
            size_t startIndex = i;
            int digitLength = 0;
            while (i<line.size() && isdigit(line[i])) {
                ++digitLength;
                ++i;
            }
            wNums.insert(std::stoi(line.substr(startIndex, digitLength)));
        }
    }

    for (size_t i=barPos; i<line.size(); ++i) {
        if (isdigit(line[i])) {
            size_t startIndex = i;
            int digitLength = 0;
            while (i<line.size() && isdigit(line[i])) {
                ++digitLength;
                ++i;
            }
            cNums.insert(std::stoi(line.substr(startIndex, digitLength)));
        }
    }

}

size_t find_matches(std::set<int>& wNums, std::set<int>& cNums) {
    std::vector<int> intersection(wNums.size() + cNums.size());
    std::vector<int>::iterator it;
    size_t matches;
    it = std::set_intersection(wNums.begin(), wNums.end(), cNums.begin(), cNums.end(), intersection.begin());
    intersection.resize(it - intersection.begin());
    matches = intersection.size();
    wNums.clear();
    cNums.clear();
    return matches;
}

int main(int argc, char* argv[]) {
    std::ifstream input_file(argv[1]);
    std::string line;
    int sum = 0, match;
    std::set<int> winningNums, currNums;
    std::vector<int> matches;

    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            parse_numbers(line, winningNums, currNums);
            match = find_matches(winningNums, currNums);
            if (match > 0) sum += (1<<(match -1));
            matches.push_back(match);
        }

    // Part 1
    std::cout << "The result of part 1 is: " << sum << "\n";
    sum = 0;
    // Part 2
    std::vector<int> counts(matches.size(), 1);
    for (size_t i=0; i<counts.size(); ++i) {
        for (size_t j=0; j<matches[i]; ++j) {
            counts[i + 1 + j] += counts[i];
        }
    }    
    
    for (auto x: counts) sum += x;
    std::cout << "The result of part 2 is: " << sum << "\n";
    }
    else {
        std::cout << "Unable to open file!\n";
    }
}