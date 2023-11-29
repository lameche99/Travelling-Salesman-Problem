# Travelling-Salesman-Problem
A series of algorithms to solve TSP

# General framework
An abstract class "TspSolver" has been created to group all the data processing functions such as read/write, and common variables. There is a virtual function "solve" that needs to be implemented in the specific solvers. 

This generic interface allows every team member to work separately effectively while ensuring compatibility of the solvers. Three solvers have been implemented:

1) BfSolver: a brute force approach that terminates after a given time cutoff.
2) ApproxSolver: an approximation to the solution with some quality boundaries.
3) LsSolver: a local search that uses heuristics.

4) 

