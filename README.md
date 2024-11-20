DPLL description in program: 

The algorithm starts by applying unit propagation, which simplifies the CNF (Conjunctive Normal Form) formula by deducing assignments for variables that appear in unit clauses (clauses containing only a single literal). After this, the algorithm searches for unassigned variables within the formula and then recursively assigns truth values (either true or false) to these variables. If an assignment leads to a conflict where no clauses can be satisfied, the algorithm backtracks by unassigning the last variable and exploring other potential assignments. This recursive process continues until a satisfying assignment is found or all possibilities have been exhausted.


To run the program enter the following command on terminal in the directory where all files are present:
g++ main.cpp -o solver
./solver

