#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

int main(int argc, char* argv[]) {
    std::ifstream inputFile(argv[1]);
    std::string s;
    int sum = 0;

    if (inputFile.is_open()) {
        while (std::getline(inputFile, s)) {
            //std::cout << s << "\n";
            std::string out = "";
            for (size_t i=0; i<s.size(); ++i) {
                if (isdigit(s[i])) {
                    out.push_back(s[i]);
                    break;
                }
            }
            for (size_t i=s.size()-1; i>=0; --i) {
                if (isdigit(s[i])) {
                    out.push_back(s[i]);
                    break;
                }
            }
            sum += std::stoi(out);
        }
        inputFile.close();
        std::cout << sum << "\n";
    }
    
    else {
        std::cout << "Unable to open file!\n";
    }
}