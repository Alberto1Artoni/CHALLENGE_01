here a brief presentation of all the files and useful hints to understand better the implementation of the code:

1. Point.hpp/Point.cpp --> this is a class for vector of doubles, there are overloaded operators,some utlities and the euclidean norm

2. parameters.hpp/parameters.json --> the first one is a struct with the collection of all the input data e parameters neededed for the method, including th exact analitical gradient
   for the test function; the second one instead is a json file to collect all the data of the struct, to give the option to the user of apport some modifications.

3. Gradient_method.hpp/Gradient.cpp --> this is the class that collects the three different method used to minimize the function:
   -analitical:
      - gradient method: to refresh alpha is present a template with three different choice to prooced, notice that to choose one of them the user is forced to go inside the function and 
        tipe one of the method listed in enumerator defined inside the class, this was necessary to solve the choice of alpha at compile time (the default one in the code is 
        exponential_decay).
      - Momentum_method: here I use a fixed alpha value, for semplicity the alpha_init of the struct, that previously was needed as first input for the parameter, and for neta the fixed 
        value 0.9
   -numerical: finite gradient method: the same as the continuos one, but with a numerical computation of the gradient using the centred formula

4. muparser_fun --> this is a class that implement a generalization of the muparser functions, for functions that go from R^n to R.
   In particulary this type of function can evaluate a vector, and in the constructor asks for a vector of string with the correct name for each variable, here in this problem i suppose 
   be x1,x2....
   
5 main.cpp --> here i simply read all the input data from the json file and compute the minimum giving the choice to the user to use is favourite method

6. Makefile --> to have a correct behaviour in the compilation pheraps this command is needed (with your specified path): LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/lucadalessandro/pacs-examples/Examples/lib

        
