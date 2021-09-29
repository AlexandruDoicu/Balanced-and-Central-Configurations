# Balanced-and-Central-Configurations
Numerical analysis of balanced and central configurations

The files in the directories "BalancedConfig" and "CentralConfig" contain the
balanced and central configurations, respectively, computed by a stochastic 
optimization algorithm described in the paper (arXiv):
"A stochastic optimization algorithm for analyzing planar central and balanced 
configurations in the n-body problem" by Alexandru Doicu, Lei Zhao, and Adrian
Doicu. 

The output file for each balanced configuration contains: 
-  the value of the objective function, 
-  the Cartesian coordinates of the point masses, 
-  the residual of the normalization condition for the moment of inertia, 
-  the Cartesian coordinates of the center of mass, 
-  the RMS of the relative quadratic approximation error and the maximum 
   quadratic approximation error, 
-  a logical flag indicating if global minima of F exist in a small box 
   around the solution, as well as, a logical flag indicating if there is a 
   unique stationary point of F in the same box, and 
-  the number of degenerate solutions and the corresponding Cartesian 
   coordinates of the point masses. 
For central configurations, the output file contains in addition 
-  the residual of the Albouy-Chenciner equations, 
-  the Morse and isotropy indices, and 
.  the residual of the Morse equation. 

In the directory "BalancedConfig", the file "BCNMASxSYyz.dat" corresponds to a
a balanced configuration with x masses and an SY-value of 0.yz. In the directory,
"CentralConfig", the file "CCNMASx.dat" corresponds to a central configuration 
with x masses.

The folder ""
