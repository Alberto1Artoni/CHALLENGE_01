#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include "Point.hpp"
#include "json.hpp"
#include "parameters.hpp"
#include "muparser_fun.hpp"
#include "Gradient_method.hpp"


using json = nlohmann::json;

int main(int argc, char **argv)
{
  std::ifstream f("parameters.json");
  json data = json::parse(f);

  parameters param;
  param.fun=data.value("fun","");
  param.dim=data.value("dim",2);
  std::vector<std::string> grad_temp=data[("gradient")];
  param.gradient=grad_temp;
  std::vector<double> temp=data[("initial_guess")];
  param.initial_guess=temp;
  param.toler_s=data.value("toler_s",1e-6);
  param.toler_r=data.value("toler_r",1e-6);
  param.max_iteration=data.value("max_iteration",10000);
  param.alpha_init=data.value("alpha_init",0.1);
  param.mu=data.value("mu",0.1);
  param.sigma=data.value("sigma",0.2);
  param.h=data.value("h",0.0001);
  param.neta=data.value("neta",0.9);

    std::vector<std::string> variableNames;
    for (unsigned i = 1; i <= param.dim; ++i) {
        variableNames.push_back("x" + std::to_string(i));
    }
    
    MuparserFun fun(param.fun, variableNames);
    Gradient_method pb(param);
    
    std::string grad_choice;
    std::cout<<"choose between analitical or numerical gradient:"<<std::endl;
    std::cin>>grad_choice;
    std::cout<<std::endl;

    Point min(param.dim);

    if(grad_choice=="analitical"){

      std::vector<MuparserFun> grad;
        for(std::size_t i = 0; i < param.dim; ++i) {
           grad.emplace_back(MuparserFun(param.gradient[i], variableNames));
           }


       for(auto& fun:grad) {
           fun = MuparserFun(fun.getExpression(), variableNames);
          }
    
    std::string analitical_choice;
    std::cout<<std::endl;
    std::cout<<"choose between Gradient or Momentum method,write grad or mom:"<<std::endl;
    std::cin>>analitical_choice;
    std::cout<<std::endl;

    if(analitical_choice=="grad")
         min=pb.gradient_solve(fun,grad);
    else
         min=pb.momentum_solve(fun,grad);
    }

    else min=pb.gradient_solve_finite(fun,param.h);


    if(min.get_coordinates()==std::vector<double> (param.dim,std::numeric_limits<double>::quiet_NaN())){
       std::cout<<"GRADIENT METHOD DOES NOT CONVERGE"<<std::endl;
       min.print_point();
      }
    else {
      std::cout<<"GRADIENT METHOD CONVERGES"<<"\n"<<std::endl;
      std::cout<<"the minimum is reached at: "<<std::endl;
      min.print_point();
      std::cout<<"\n"<<"the value of the function evaluated in the minimum is: "<<fun(min.get_coordinates())<<std::endl;
    }

  return 0;
}
