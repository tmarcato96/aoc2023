#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>

void pad_with_periods(std::vector<std::string>& grid_padded, std::vector<std::string>& grid) {
    std::string pad(grid[0].size() + 2, '.');
    grid_padded.push_back(pad);
    for (auto x: grid) {
        grid_padded.push_back("." + x + ".");
    }
    grid_padded.push_back(pad);

}

int main(int arcg, char* argv[]) {
    std::ifstream input_file(argv[1]);
    std::string line;
    std::vector<std::string> grid;
    std::string out;
    int lineCount = 0, sum = 0;

    if (input_file.is_open()) {
        while(std::getline(input_file, line)) {

            grid.push_back(line);
        }
        input_file.close();

        // Pad with periods
        std::vector<std::string> grid_padded;
        pad_with_periods(grid_padded, grid);
        
        for (size_t row=1; row<grid_padded.size()-1; ++row) {
            for (size_t col=1; col<grid_padded[row].size()-1; ++col) {
                if (isdigit(grid_padded[row].at(col))) {
                    size_t startIndex = col;
                    int digitLength = 0;
                    bool found = false;
                    while (col<grid_padded[row].size() && isdigit(grid_padded[row].at(col))) {
                        for (int i=-1; i<=1; ++i) {
                                for (int j=-1; j<=1; ++j) {
                                    if (!isalnum(grid_padded[row + i].at(col + j)) && grid_padded[row + i].at(col + j) != '.') {
                                        found = true;
                                        break;
                                }
                            }
                            if (found) break;
                        }
                        ++digitLength;
                        ++col;
                    }
                    if (found) {
                        //out += grid_padded[row].substr(startIndex, digitLength);
                        sum += std::stoi(grid_padded[row].substr(startIndex, digitLength));
                    }
                }
            }
        }
        
    std::cout << sum << "\n";
        
    }
    else {
        std::cout << "Unable to open file!\n";
    }
}