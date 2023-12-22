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

void make_seed_range(std::vector<long long>& seeds, std::vector<Range>& seed_ranges) {
    for (size_t i=0; i<seeds.size()-1; ++i) {
        if (i%2==0) {
            Range r = {.min=seeds[i], .max=seeds[i] + seeds[i+1]-1};
            seed_ranges.push_back(r);
        }
    }
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

long long map_inverse(long long start, std::vector<Range>& source, std::vector<Range>& destination) {
    long long end;
    bool found = false;
    for (size_t i=0; i<destination.size(); ++i) {
        if (start >= destination[i].min && start <= destination[i].max) {
            found = true;
            end = (start - destination[i].min) + source[i].min;
        }
    }
    if (!found) end = start;

    return end;
}

int main(int argc, char* argv[]) {
    std::ifstream input_file("./input.txt");
    std::string line;
    std::vector<std::string> lines;
    int lineCount = 0;
    std::vector<long long> seeds;
    std::vector<Range> source, destination, seed_ranges;

    if (input_file.is_open()) {
        while (std::getline(input_file, line)) {
            // Parse seeds
            if (lineCount == 0) parse_seeds(line, seeds);
            if (!line.empty()) {
                ++lineCount;
                lines.push_back(line);
            }
        }
    make_seed_range(seeds, seed_ranges);

    long long min_destination = 5600000, res, result;
    bool found = false;
    while (!found) {
        res = min_destination;
        for (size_t i=lines.size()-1; i>0; --i) {
        if (isdigit(lines[i].front())) {
            while (i>0 && isdigit(lines[i].front())) {
                make_range(lines[i], source, destination);
                --i;  
            }
        res = map_inverse(res, source, destination);
        source.clear();
        destination.clear();
        }
        }
        for (auto r: seed_ranges) {
            if (res >= r.min && res <= r.max) {
                found = true;
                result = min_destination;
                break;
            }
        }
        std::cout << min_destination << "\n";
        ++min_destination;
    }
    
    std::cout << result << "\n";
    }
    else {
        std::cout << "Unable to open file\n";
    }
}