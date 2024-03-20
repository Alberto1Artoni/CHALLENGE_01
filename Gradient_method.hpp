#ifndef GRADIENT_METHOD_HPP
#define GRADIENT_METHOD_HPP

#include "parameters.hpp"
#include "iostream"
#include "Point.hpp"
#include "muparser_fun.hpp"
#include <random>

class Gradient_method
{
  
  enum class step_alpha{
    exponential_decay,
    inverse_decay,
    linear_search,
    };

public:
  Gradient_method(const parameters &p): param(p) {}
  
  Point gradient_solve(MuparserFun fun,std::vector<MuparserFun> gradient);
  Point gradient_solve_finite(MuparserFun fun, double h);
  Point momentum_solve(MuparserFun fun,std::vector<MuparserFun> gradient);

private:
    parameters param;
    
    double Armijo_rule(const Point &p,MuparserFun fun,Point grad_eval);

    Point finite_diff_grad(MuparserFun fun,double h,const Point &p);

    template <step_alpha step>
         double alpha_compute(int cont,const Point &x_old,MuparserFun fun,Point grad_eval); 

 

};

#endif /* GRADIENT_METHOD_HPP */
