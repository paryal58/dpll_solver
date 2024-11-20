#ifndef SOLVER_H
#define SOLVER_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <random>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <set>
#include <unordered_set>

// Class defining each variable
// Each variable has a name and truth value
class Variable {

public:
    std::string name;
    int truthValue;
    Variable();
    Variable(std::string name, int truthValue); // Set variable name and truthValue
    void setTruthValue(int value);  // Set truth value with value
};

// Class containing all the Solver methods
class SAT {

private:
    std::unordered_map<std::string, Variable> vars;  // Map of variables used in the boolean formula
    std::set<std::string> assignedVars;    // All the assigned variables
    std::vector<std::vector<int>> clauses;  // CNF formula
    int fitness = 0;  // Fitness: Number of satisfied clauses
    bool isClauseSatisfied(const std::vector<int>& clause);  // Check if a clause is satisfied
    bool isFormulaSatisfied();  // Check if formula is satisfied
    std::string findUnassignedVariable();  // Check for unassigned variables

public:
    SAT(std::vector<std::vector<int>> cnf); // Constructor
    bool dpll();  // DPLL algorithm
    int countSatisfiedClauses();  // Count satisfied clauses
    void assignVariable(std::string name, int value);  // Assignment to a variable
    void unassignVariable(std::string name);  // Unassign assigned variables
    void printAssignments(); // Print satisfiable assignment
    bool solve(int choice);  // SAT Solver function

};

#endif
