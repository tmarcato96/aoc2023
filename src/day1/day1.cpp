#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

int main(int argc, char* argv[]) {
    std::ifstream inputFile(argv[1]);
    std::string line, output;
    int sum = 0;
    std::string wordDigits[9]={"one", "two", "three",
                               "four", "five", "six", 
                               "seven", "eight", "nine"};

    if (inputFile.is_open()) {
        while (std::getline(inputFile, line)) {
            // This belongs to part 2 and is switched on or off
            // depending whether the macro PART_TWO is defined.
            #ifdef PART_TWO
            size_t wordPos;
            // Find word digit and add corresponding number 
            // so that the code from Part 1 can be used on
            // the modified string (two -> t2wo).
            for (size_t i=0; i<9; ++i) {
                wordPos = line.find(wordDigits[i]);
                if (wordPos!=std::string::npos) {
                    line.insert(wordPos+1, std::to_string(i+1));
                }
            }
            for (size_t i=0; i<9; ++i) {
                wordPos = line.rfind(wordDigits[i]);
                if (wordPos!=std::string::npos) {
                    line.insert(wordPos+1, std::to_string(i+1));
                }
            }
            #endif

            int firstDigit = line.find_first_of("0123456789");
            output += line[firstDigit];

            int secondDigit = line.find_last_of("0123456789");
            output += line[secondDigit];

            sum += std::stoi(output);
            output.clear();
        }
        inputFile.close();
        std::cout << "The result is: " << sum << "\n";
    }
    
    else {
        std::cout << "Unable to open file!\n";
    }
}