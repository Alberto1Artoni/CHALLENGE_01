#ifndef Parameters_HPP
#define Parameters_HPP
#include <string>
#include <vector>

struct parameters
{
  
  //! function to minimize 
  std::string fun="x1*x2+4*x1^4+x2^2+3*x1";
  //! dimension of the space 
  unsigned dim=2;
  //! exact gradient of the function
  std::vector<std::string> gradient={"x2+16*x1^3+3","x1+2x2"};
  //! initial guess x0
  std::vector<double> initial_guess={0,0};
  //! Tolerance for stopping criteria on step length
  double toler_s = 1e-6;
  //! Tolerance for stopping criteria on residual
  double toler_r = 1e-6;
  //! max iterazion admissible for the while loop
  unsigned max_iteration = 1000;
  //! starting guess for alpha 
  double alpha_init = 0.1;
  //! parameter used in exponential/inverse decay for alpha
  double mu = 0.1;
  //! parameter used in approximation linear search for alpha 
  double sigma = 0.1;
  //! step length for the computation of the numerical gradient 
  double h=0.0001;
  //! parameter used to refresh d in the momentum method
  double neta=0.9;

};

#endif