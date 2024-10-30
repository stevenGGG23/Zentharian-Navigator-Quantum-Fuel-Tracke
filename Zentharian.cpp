* Filename: zentharian.cpp.cpp 
Discription: program that will process a ledger file to pinpoint the Zentharian navigator carrying the most
quantum fuel and calculate the total quantum fuel they are transporting. The ledger files will have no more than 1000 groups
of data aka 1000 Zentharians with mutiple crystals (but no more than 20) of fuel. 
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

const int MAX_ZENTHARIANS = 1000;  // Maximum number of Zentharians
const int MAX_CRYSTALS = 20;       // Maximum number of Crystals per Zentharian

struct Zentharian {
    std::array<int, MAX_CRYSTALS> crystals;
    int crystal_count = 0;
    int total_fuel = 0;
};

// Function prototypes
bool readFile(const std::string& file_path, std::vector<Zentharian>& zentharians);
void calculateFuelTotals(std::vector<Zentharian>& zentharians);
int findMaxFuelNavigator(const std::vector<Zentharian>& zentharians);


int main() {
    std::string file_path;
    std::cout << "Enter ledger file: ";
    std::cin >> file_path; 
    std::cout << std::endl; //formating empty space 

    std::vector<Zentharian> zentharians(MAX_ZENTHARIANS);

    if (!readFile(file_path, zentharians)) {
        std::cout << "You entered an invalid ledger..." << file_path << std::endl;
        return 1;
    }

    calculateFuelTotals(zentharians);

    int max_index = findMaxFuelNavigator(zentharians);
    if (max_index != -1) {
        const Zentharian& max_zentharian = zentharians[max_index];
        std::cout << "Zentharian " << (max_index + 1) 
                  << " has " << max_zentharian.crystal_count << " crystals worth" << std::endl;

        // Print each crystal's fuel content
        for (int i = 0; i < max_zentharian.crystal_count; ++i) {
            std::cout << max_zentharian.crystals[i] << std::endl;
        }

        std::cout << "fuel each. Totaling " 
                  << max_zentharian.total_fuel << " units." << std::endl;
    }

    return 0;
}


bool readFile(const std::string& file_path, std::vector<Zentharian>& zentharians) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    int zenth_index = 0;
    while (std::getline(file, line)) {
        if (line.empty()) {  // Moves to next Zentharian if line is empty
            zenth_index++;
            if (zenth_index >= MAX_ZENTHARIANS) break;
            continue;
        }
        if (zentharians[zenth_index].crystal_count < MAX_CRYSTALS) {
            zentharians[zenth_index].crystals[zentharians[zenth_index].crystal_count++] = std::stoi(line);
        }
    }
    file.close();
    return true;
}
//calculates their total fuel based on the fuel stored in their crystals.
void calculateFuelTotals(std::vector<Zentharian>& zentharians) {
    for (auto& zenth : zentharians) {
        zenth.total_fuel = 0;
        for (int i = 0; i < zenth.crystal_count; ++i) {
            zenth.total_fuel += zenth.crystals[i];
        }
    }
}
// find the index of the one with the highest total_fuel value.
int findMaxFuelNavigator(const std::vector<Zentharian>& zentharians) {
    int max_index = -1;
    int max_fuel = 0;

    for (size_t i = 0; i < zentharians.size(); ++i) {
        if (zentharians[i].total_fuel > max_fuel) {
            max_fuel = zentharians[i].total_fuel;
            max_index = i;
        }
    }
    return max_index;
}
