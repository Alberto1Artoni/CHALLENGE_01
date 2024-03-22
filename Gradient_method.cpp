#include "Gradient_method.hpp"
#include <limits>


template <Gradient_method::step_alpha step>
double Gradient_method::alpha_compute(int cont,const Point &x_old,MuparserFun fun,Point grad_eval){
   if constexpr (step==step_alpha::exponential_decay)  
       return param.alpha_init*std::exp(-param.mu*cont);
   else if constexpr (step==step_alpha::inverse_decay)
       return param.alpha_init/(1+param.mu*cont);
   else if constexpr (step==step_alpha::linear_search)
      return Gradient_method::Armijo_rule(x_old,fun,grad_eval);
}


double Gradient_method::Armijo_rule(const Point &p,MuparserFun fun,Point grad_eval){

    bool stop=false;
    unsigned cont=0;
          
    std::vector<std::string> variableNames;
       for (unsigned i = 1; i <= param.dim; ++i) {
        variableNames.push_back("x" + std::to_string(i));
    }
    fun = MuparserFun(fun.getExpression(), variableNames);
          

    while(!stop || cont>param.max_iteration){
       ++cont; 
        if((fun(p.get_coordinates())-fun((p-grad_eval*param.alpha_init).get_coordinates())) >=
                param.sigma*param.alpha_init*std::pow(grad_eval.euclidean_norm(),2))
            
             stop=true;
        
        else
            param.alpha_init=param.alpha_init/2;
    }
    
    return param.alpha_init;
}

Point Gradient_method::finite_diff_grad(MuparserFun fun,double h,const Point &p){
    
    Point grad(param.dim);
    
    std::vector<std::string> variableNames;
       for (unsigned i = 1; i <= param.dim; ++i) {
        variableNames.push_back("x" + std::to_string(i));
    }
    fun = MuparserFun(fun.getExpression(), variableNames);

    for(std::size_t i=0;i<param.dim;++i){
        Point p1(p);
        Point p2(p);

        p1.set_coo(i,p.get_coo(i)+h);
        p2.set_coo(i,p.get_coo(i)-h);
        grad.set_coo(i,(fun(p1.get_coordinates())-fun(p2.get_coordinates()))/(2*h));
    }
   return grad; 
}



Point Gradient_method::gradient_solve(MuparserFun fun,std::vector<MuparserFun> gradient){

    Point init(param.initial_guess);
    Point x_new(init);
    Point x_old(init);
    bool stop=false;
    unsigned cont=0;
    double alpha(param.alpha_init);
    
    constexpr step_alpha choice=step_alpha::exponential_decay;

    std::vector<std::string> variableNames;
       for (unsigned i = 1; i <= param.dim; ++i) {
        variableNames.push_back("x" + std::to_string(i));
    }
    fun = MuparserFun(fun.getExpression(), variableNames);

    for(auto& fun:gradient) {
        fun = MuparserFun(fun.getExpression(), variableNames);
        }
    

    while(!stop){
    
       for(std::size_t i=0;i<param.dim;++i)
            x_new.set_coo(i,x_old[i]-alpha*gradient[i](x_old.get_coordinates()));

        std::vector<double> vect(param.dim);
        Point grad_eval(vect);
        
        for(std::size_t i=0;i<param.dim;++i){
             grad_eval.set_coo(i,gradient[i](x_old.get_coordinates()));
        }

    if(cont>param.max_iteration || (x_new-x_old).euclidean_norm() <param.toler_s
        || grad_eval.euclidean_norm()<param.toler_r)
            stop=true;
      
        x_old=x_new;
        ++cont;
        alpha=Gradient_method::alpha_compute<choice>(cont,x_old,fun,grad_eval);
        
    }

    if(cont>param.max_iteration)
      return std::vector<double> (param.dim,std::numeric_limits<double>::quiet_NaN());
   return x_new;
}

Point Gradient_method::gradient_solve_finite(MuparserFun fun, double h){

    Point init(param.initial_guess);
    Point x_new(init);
    Point x_old(init);
    bool stop=false;
    unsigned cont=0;
    double alpha(param.alpha_init);
    
    constexpr step_alpha choice=step_alpha::exponential_decay;

    std::vector<std::string> variableNames;
       for (unsigned i = 1; i <= param.dim; ++i) {
          variableNames.push_back("x" + std::to_string(i));
    }
    fun = MuparserFun(fun.getExpression(), variableNames);

    while(!stop){
    
       for(std::size_t i=0;i<param.dim;++i)
            x_new.set_coo(i,x_old[i]-alpha*(finite_diff_grad(fun,h,x_old)).get_coo(i));

        std::vector<double> vect(param.dim);
        Point grad_eval(vect);
        for(std::size_t i=0;i<param.dim;++i)
            grad_eval.set_coo(i,(finite_diff_grad(fun,h,x_old)).get_coo(i));
            
          
      if(cont>param.max_iteration || (x_new-x_old).euclidean_norm() <param.toler_s
        || grad_eval.euclidean_norm()<param.toler_r)
            stop=true;
      
        x_old=x_new;
        ++cont;
        alpha=Gradient_method::alpha_compute<choice>(cont,x_old,fun,grad_eval);
        
    }

    if(cont>param.max_iteration)
      return std::vector<double> (param.dim,std::numeric_limits<double>::quiet_NaN());
   return x_new;
}


Point Gradient_method::momentum_solve(MuparserFun fun,std::vector<MuparserFun> gradient){

    Point init(param.initial_guess);
    Point x_new(init);
    Point x_old(init);
    bool stop=false;
    unsigned cont=0;
   
    std::vector<std::string> variableNames;
       for (unsigned i = 1; i <= param.dim; ++i) {
        variableNames.push_back("x" + std::to_string(i));
    }
    fun = MuparserFun(fun.getExpression(), variableNames);

    for(auto& fun:gradient) {
        fun = MuparserFun(fun.getExpression(), variableNames);
        }
    Point d_grad(param.dim);

            for(std::size_t i=0;i<param.dim;++i)
            d_grad.set_coo(i,-param.alpha_init*gradient[i](param.initial_guess));
      
    while(!stop){
    
       for(std::size_t i=0;i<param.dim;++i){
            x_new.set_coo(i,x_old[i]+d_grad[i]);
            d_grad.set_coo(i,param.neta*d_grad.get_coo(i)-param.alpha_init*gradient[i](x_new.get_coordinates()));
       }

        std::vector<double> vect(param.dim);
        Point grad_eval(vect);
       
        for(std::size_t i=0;i<param.dim;++i)
          grad_eval.set_coo(i,gradient[i](x_old.get_coordinates()));
          

    if(cont>param.max_iteration || (x_new-x_old).euclidean_norm() <param.toler_s
        || grad_eval.euclidean_norm()<param.toler_r)
            stop=true;
      
        x_old=x_new;
        ++cont;
        
        
    }

    if(cont>param.max_iteration)
      return std::vector<double> (param.dim,std::numeric_limits<double>::quiet_NaN());
   return x_new;
}


