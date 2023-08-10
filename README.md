# Monte-Carlo-Intro

Theses are introductionary models for monte carlo simulation.

1. Sailor(Drunkard) model
Description for graph and results: The graph above shows the dependence on a logarithmic scale of the standard deviation of sigma position on the number of simulated steps . In the simulation, these values were counted for N from 10 to 10000. The number of sailors in the simulation is 250. The graph also estimates the exponent using linear regression.
Slope meaning slope corresponds to the value of a in Eq. Straight y=ax+b. It is 0.49983±0.0005126 or approximately 0.5 , as we assumed in the theory of this task

2. Diffusion of N atoms in 2D
  Description for graph and results: The graph above shows a plot of the dependence of the diffusion coefficient D on the number of MCS steps - K (system transitions). It can be seen that the coefficient D is higher for very small K~(0.3) , which quickly decreases and for the rest of K oscillates around a constant value.
These results were developed from simulations based on the following code. The number of independent realizations for each K is 30 , while the density of the layout C=0.5 . The size of the system is 20x20 sites , and the number of atoms simulated is 200. 

3.Spin Model - Metropolis algorithm
In the graph above, the results of the monte-carlo simulation of the spin model in a magnetic field are shown as red dots . The simulation result is almost identical to the predicted results.  According to the theory of this model, the dependence of the average spin (magnetization) on the reduced temperature should be mi(T*)=tanh(1/T*), and as can be seen in the graph, the curve of the theoretical result almost coincides with the simulation result.
(simulation parameters : reduced temperature from 0.1 to 15 ; 500 spins ; 100,000 MCS steps - analysis every 100th step without considering the MCS(0-10000) range )
