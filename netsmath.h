#ifndef NETSMATH_H
#define NETSMATH_H

#include <iostream>
#include <cmath>
#include "matrix.h"

template <typename T>
class Netsmath{

public:
	static int sigmod(int a);
	static Matrix<T> sigmodprime(Matrix<T> m);
};

template <typename T>
inline int Netsmath<T>::sigmod(int a){
	return (1.0/(1+exp(-1*a)));
}

template <typename T>
inline Matrix<T> Netsmath<T>::sigmodprime(Matrix<T> m){

	Matrix<T> ones(m.getRowSize(), 1);
	Matrix<T> subtracted = ones.subtract(m);
	return m.multiply(subtracted);

}

#endif 

