#ifndef POINT_HPP
#define POINT_HPP

#include <vector>
#include <iostream>
#include <cmath>

class Point {

private:
    std::vector<double> vect;

public:
    Point()=default;
    Point(const std::vector<double> &v):vect(v){}
    Point(std::size_t size):vect(std::vector<double> (size)) {}
    double operator[](std::size_t i) const;
    double euclidean_norm() const;
    void print_point() const;
    std::size_t get_size() const;
    void set_coo(std::size_t i,double val);
    double get_coo(std::size_t i) const;
    std::vector<double> get_coordinates() const;

};
    
    Point operator-(const Point &p1,const Point &p2);
    Point operator*(const Point &p,double scalar);


#endif //POINT_HPP