#include "solver.h"

// Constructor to set name and truthValue for variable
Variable::Variable() {
    name = "";
    truthValue = -1;  // Initially set truth value for every variables to -1
}

Variable::Variable(std::string name, int truthValue) {
    this->name = name;
    this->truthValue = truthValue;
}

// Set variable with truthValue value
void Variable::setTruthValue(int value) {
    if (value == 1 || value == 0)
        truthValue = value;
}

// Constructor mapping string with Variable
SAT::SAT(std::vector<std::vector<int>> cnf) {
    clauses = std::move(cnf);
    for (const auto& clause : clauses) {
        for (int literal : clause) {
            std::string varName = std::to_string(std::abs(literal));
            if (vars.find(varName) == vars.end()) {
                vars[varName] = Variable(varName, -1);
            }
        }
    }
}

// Helper function to check if clause is satisfied
bool SAT::isClauseSatisfied(const std::vector<int>& clause) {
    for (int literal : clause) {
        std::string varName = std::to_string(std::abs(literal));
        int truthValue = vars[varName].truthValue;;
        if ((literal > 0 && truthValue == 1) || (literal < 0 && truthValue == 0)) {
            return true; 
        }
    }
    return false;
}

// Function to calculate fitness
int SAT::countSatisfiedClauses() {
    fitness = 0;
    for (const auto& clause : clauses) {
        if (isClauseSatisfied(clause)) {
            fitness++;
        }
    }
    return fitness;
}

// Check if the CNF function is satisfied
bool SAT::isFormulaSatisfied() {
    for (const auto& clause : clauses) {
        if (!isClauseSatisfied(clause)) {
            return false;
        }
    }
    return true;
}

// Assign value to a variable
void SAT::assignVariable(std::string name, int value) {
    if (vars.find(name) != vars.end()) {
        vars[name].setTruthValue(value);
        assignedVars.insert(name);
    }
}

// Helper function for DPLL
std::string SAT::findUnassignedVariable() {
    for (const auto& varPair : vars) {
        // Return the first unassigned variable
        if (varPair.second.truthValue == -1) {
            return varPair.first; 
        }
    }
    return "";  // Return empty clause
}


// Remove from the set of assigned variables
void SAT::unassignVariable(std::string name) {
    if (vars.find(name) != vars.end()) {
        vars[name].setTruthValue(-1); // Reset truthValue
        assignedVars.erase(name);  
    }
}

// Function to print the satisfiable assignments
void SAT::printAssignments() {
    std::cout << "Satisfiable assignments:" << std::endl;
    for (const auto& varPair : vars) {
        std::cout << "x" << varPair.first << " = " << varPair.second.truthValue << std::endl;
    }
    std::cout << std::endl;
}


// Solver function
bool SAT::solve(int choice) {
    switch(choice) {
    case 1:
        return dpll();
        break;
    // Only DPLL cause it is more accurate
    default:
        std::cout << "Invalid" << std::endl;
        return false;
    }
}

// DPLL algorithm implementation
bool SAT::dpll() {
    if (isFormulaSatisfied()) {
        printAssignments();
        return true; 
    }
    // Unit propagation
    bool unitClauseFound = true;
    while (unitClauseFound) {
        unitClauseFound = false;
        for (const auto& clause : clauses) {
            // Check for unit clause
            if (clause.size() == 1) {
                int literal = clause[0];
                std::string varName = std::to_string(std::abs(literal));
                int value = (literal > 0) ? 1 : 0;
                assignVariable(varName, value);
                unitClauseFound = true;
                break; 
            }
        }
    }
    // Find unassigned variable
    std::string unassignedVar = findUnassignedVariable();
    if (unassignedVar.empty()) { 
        return isFormulaSatisfied();
    }
    // Assigning the variable to true(1)
    assignVariable(unassignedVar, 1);
    auto originalClauses = clauses;
    for (const auto& clause : originalClauses) {
        if (isClauseSatisfied(clause)) {
            continue;
        }
        clauses.push_back(clause);
    }
    if (dpll())
        return true;
    // Backtrack and assign the variable to false(0)
    assignVariable(unassignedVar, 0);
    // Remove satisfied clauses again
    clauses.clear();
    std::vector<std::vector<int>> unsatisfiedClauses;
    for (const auto& clause : clauses) {
        if (!isClauseSatisfied(clause)) {
            unsatisfiedClauses.push_back(clause); 
        }
    }
    clauses = std::move(unsatisfiedClauses);
    if (dpll())
        return true;
    // Unassign the variable 
    unassignVariable(unassignedVar);
    return false; 
}

