#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
#include <array>
#include <algorithm>
#include <iterator>

struct Range {
     long long min, max;
};

void parse_seeds(std::string& line, std::vector<long long>& seeds) {
    size_t colonPos;
    colonPos = line.find(':');
    for (size_t i=colonPos; i<line.size(); ++i) {
        if (isdigit(line[i])) {
            size_t digitPos = i;
            long digitLength = 0;
            while (i<line.size() && isdigit(line[i])) {
                ++i;
                ++digitLength;
            }
            seeds.push_back(std::stoll(line.substr(digitPos, digitLength)));
        }
    }
    
}

std::vector<long long> create_seeds_pt2(std::vector<long long>& seeds) {
    std::vector<long long> s;
    for (int i=0; i<seeds.size()-1; ++i) {
        if (i % 2 == 0) {
            long long j = 0;
            while (j<seeds[i+1]) {
                s.push_back(seeds[i] + j);
                ++j;
            }
        }
    }
    return s;
}

void parse_numbers(std::vector<long long>& numbers, std::string& line) {
    std::stringstream stream(line);
    for (long long n; stream >> n;) numbers.push_back(n);
}

void make_range(std::string& line, std::vector<Range>& source, std::vector<Range>& destination) {
    std::vector<long long> numbers;
    parse_numbers(numbers, line);
    Range s = {.min = numbers[1], .max = numbers[1] + numbers[2] - 1};
    Range d = {.min = numbers[0], .max = numbers[0] + numbers[2] - 1};
    source.push_back(s);
    destination.push_back(d);
}

long long map(long long start, std::vector<Range>& source, std::vector<Range>& destination) {
    long long end;
    bool found = false;
    for (size_t i=0; i<source.size(); ++i) {
        if (start >= source[i].min && start <= source[i].max) {
            found = true;
            end = (start - source[i].min) + destination[i].min;
        }
    }
    if (!found) end = start;

    return end;
}

int main(int argc, char* argv[]) {
    std::ifstream input_file(argv[1]);
    std::string line;
    std::vector<std::string> lines;
    int lineCount = 0;
    std::vector<long long> seeds;
    std::vector<Range> source, destination;

    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            // Parse seeds
            if (lineCount == 0) parse_seeds(line, seeds);
            if (!line.empty()) {
                ++lineCount;
                lines.push_back(line);
            }
        }
    std::vector<long long> seeds_pt2 = create_seeds_pt2(seeds);
    for (size_t i=0; i<lines.size(); ++i) {
        if (isdigit(lines[i].front())) {
            while (i<lines.size() && isdigit(lines[i].front())) {
                make_range(lines[i], source, destination);
                ++i;  
            }
        for (size_t i=0; i<seeds_pt2.size(); ++i) {
            seeds_pt2[i] = map(seeds_pt2[i], source, destination);
        }
        source.clear();
        destination.clear();
        }
    }
    std::cout << *std::min_element(seeds_pt2.begin(), seeds_pt2.end()) << "\n";
    }
    else {
        std::cout << "Unable to open file\n";
    }
}