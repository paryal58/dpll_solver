/*
    CS463G : Assignment 3
    SAT Solver - Using DPLL, WalkSAT, and GSAT
*/

#include "solver.h"
#include "solver.cpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <sstream>
#include <filesystem>

std::vector<std::vector<int>> readClause (const std::string &filename);

int main() {
    std::string folderPath[2] = {".\\CNF Formulas", ".\\HARD CNF Formulas"};
    int choice;
    choice = 1;
    for (int i = 0; i < 2; i++) {
        for (const auto& entry : std::filesystem::directory_iterator(folderPath[i])) {
                std::string filePath = entry.path().string();
                std::cout << "Reading file: " << filePath << std::endl;
                std::vector<std::vector<int>> formula = readClause(filePath);
                auto begin = std::chrono::high_resolution_clock::now(); // Begin time
                SAT solver(formula);
                if (solver.solve(choice)) {
                    auto end = std::chrono::high_resolution_clock::now(); // End Time
                    std::chrono::duration<double> elapsed = end - begin;  // Elapsed Time
                    std::cout << "The CNF is satisfiable!" << std::endl;
                    std::cout << "Time elapsed = " << elapsed.count() << std::endl;
                }
                else {
                    auto end = std::chrono::high_resolution_clock::now(); // End Time
                    std::chrono::duration<double> elapsed = end - begin;  // Elapsed Time
                    std::cout << "The CNF is not satisfiable!" << std::endl;
                    std::cout << "Time elapsed = " << elapsed.count() << std::endl;
                }
        }
    }
    return 0;
}


// Function to import data from cnf 
std::vector<std::vector<int>> readClause (const std::string &filename) {
    std::vector<std::vector<int>> formula;
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
    std::string line;
    while (getline(infile, line)) {
        if (line[0] == 'c' || line[0] == 'p') {
            continue;
        }
        // Store clauses
        std::stringstream ss(line);
        std::vector<int> clause;
        int literal;
        while (ss >> literal) {
            if (literal == 0)
                break;
            clause.push_back(literal);
        }
        formula.push_back(clause);
    }
    infile.close();
    return formula;
}
