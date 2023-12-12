#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <cctype>

int main(int argc, char* argv[]) {
    std::string line, output;
    std::ifstream input_file(argv[1]);
    std::regex spaceRegex(" ");
    std::string colors[3] = {"red", "blue", "green"};
    std::vector<int> balls;
    int lineCount = 0, sum=0;

    if (input_file.is_open()) {
        while(std::getline(input_file, line)) {
            lineCount += 1;
            // Remove spaces
            line = std::regex_replace(line, spaceRegex, "");
            size_t posColor = 0;
            std::string ballCount;
            int ballCountInt = 0;
            for (size_t i=0; i<3; ++i) {
                while(posColor!=std::string::npos) {
                    posColor = line.find(colors[i], posColor+1);
                    for (size_t j=2; j>=1; --j) {
                    if (isdigit(line[posColor-j])) ballCount += line[posColor-j];
                }
                if (posColor!=std::string::npos) {
                    int t = std::stoi(ballCount);
                    if (t > ballCountInt) ballCountInt = t;
                }
                ballCount.clear();
                
                }
                posColor = 0;
                balls.push_back(ballCountInt);
                ballCountInt = 0;
            }
            int power = 1;
            for (auto x: balls) {
                power *= x;
            }
            sum += power;
            balls.clear();
        }
        std::cout << "The result is: " << sum << "\n";
    }
    else {
        std::cout << "Unable to open file!\n"; 
    }
}