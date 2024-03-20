#include "Point.hpp"

double Point::operator[](std::size_t i) const{
        
        return vect[i];
    }

double Point::euclidean_norm() const{
    double quad=0;
      for(std::size_t i=0;i<vect.size();++i)
        quad+=std::pow(vect[i],2);

    return std::sqrt(quad);
    }
     
void Point::print_point() const {
    for(std::size_t i = 0; i < vect.size(); ++i) {
        std::cout << vect[i];
        if (i != vect.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
}


std::size_t Point::get_size() const{
      return vect.size();
    }

void Point::set_coo(std::size_t i,double val){
      vect[i]=val;
    }

double Point::get_coo(std::size_t i) const{
  return vect[i];
}

std::vector<double> Point::get_coordinates() const{
      return vect;
    }

Point operator-(const Point &p1,const Point &p2){
    std::vector<double> vect(p1.get_size());
    Point result(vect);

      for(std::size_t i=0;i<p1.get_size();++i){
        result.set_coo(i,p1[i]-p2[i]);
      }
     return result;
    }
    
Point operator*(const Point &p,double scalar){
    std::vector<double> vect(p.get_size());
    Point result(vect);

      for(std::size_t i=0;i<p.get_size();++i){
        result.set_coo(i,p[i]*scalar);
      }
     return result;
    }