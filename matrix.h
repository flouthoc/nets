#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <random>

#define COMMA_DELIMIT ","

template <typename T>

class Matrix{

	std::vector<std::vector<T>> matrixinternal;
	unsigned int rowsize;
	unsigned int coloumnsize;

public:
	Matrix(unsigned int x, unsigned int y);
	
	/*Matrix Operations*/
	void changeSize(unsigned int x, unsigned int y);

	/* Member Fn */
	unsigned int getRowSize();
	unsigned int getColoumnSize();

	/* Operations */
	Matrix<T> scale(T factor); /*.Scales a matrix by the given factor*/
	Matrix<T> addScalar(T value);/*.Adds a scaler value to each element of matrix*/
	void dump(); /*.Prints content for a matrix to stdout */
	Matrix<T> apply(T (*f)(T));/*.Applies a transforamtion function to each elemente of matrix*/
	Matrix<T> add(Matrix<T> other);/* Adds a matrix to this one*/
	Matrix<T> dot(Matrix<T> other);/* Product between two given matrices;*/
	Matrix<T> subtract(Matrix<T> other);/*Subtraction between two given matrices*/
	void populateFromArray(T* arr);/*populates the matrix from array*/
	Matrix<T> multiply(Matrix<T> other);
	Matrix<T> returnsample();
	Matrix<T> transpose();
	static Matrix<T> * generateRandom(int rows, int coloumnsize); //works only for integer;


	class matrix_row{

		std::vector<T>& row;

	public:
		matrix_row(std::vector<T> &r);
		T& operator[](unsigned int y);

	};

	matrix_row operator[](unsigned int x);

};

template <typename T>
inline Matrix<T> Matrix<T>::transpose(){

	Matrix<T> * result = new Matrix(this->getColoumnSize(), this->getRowSize());
	
	for(int i=0; i<this->getColoumnSize(); i++){
		
		for(int j=0; j<this->getRowSize(); j++){

			(*result)[i][j] = matrixinternal[j][i];
		}

	}

	return (*result);

}



template <typename T>
inline Matrix<T> * Matrix<T>::generateRandom(int rows, int coloumn){

	Matrix<T> * result = new Matrix<T>(rows, coloumn);

	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(1, 50);

	for(int i=0; i<rows; i++){
		for(int j=0; j<coloumn; j++){

			(*result)[i][j] = distr(eng);
		}
	}

	return result;

}


template <typename T>
inline Matrix<T> Matrix<T>::multiply(Matrix<T> other){


	if((this->getRowSize() == other.getRowSize()) && (this->getColoumnSize() == other.getColoumnSize())){

		Matrix<T> * result = new Matrix<T>(this->getRowSize(), this->getColoumnSize());
		for(int i=0; i<this->getRowSize(); i++){
			for(int j=0; j<this->getColoumnSize(); j++){

				(*result)[i][j] = other[i][j] * matrixinternal[i][j];
			}
		}

		return (*result);

	}else{

		throw std::invalid_argument("multiply: dimensions of primary and secondry matrix should be same");

	}

}


template <typename T>
inline Matrix<T> Matrix<T>::returnsample(){

	Matrix<T> * te = new Matrix<T>(2,2);
	int buffer[2][2] = {{2,2}, {2,2}};
	te->populateFromArray(buffer[0]);

	return (*te);
}


template <typename T>
inline Matrix<T> Matrix<T>::dot(Matrix another){

	/* -------

		MxN1 (dot) N2xP = MxP

		:= where ( N1 == N2 ) must

	 -------*/

	//this->dump();
	//another.dump();


	//std::vector<std::vector<T>> copyInternal = matrixinternal;
	std::cout<<"Dot Product Logs"<<std::endl;
	std::cout<<"this->getColoumnSize()"<<this->getColoumnSize()<<std::endl;
	std::cout<<"another.getRowSize()"<<another.getRowSize()<<std::endl;
	if(this->getColoumnSize() == another.getRowSize()){

		Matrix<T> * result = new Matrix(this->getRowSize(), another.getColoumnSize());

		//this->changeSize(this->getRowSize(), another.getColoumnSize());

		//std::cout<<"Printing Size";
		//std::cout<<this->getRowSize()<<","<<another.getColoumnSize()<<std::endl;


		/*for(int i=0; i<copyInternal.size(); i++){

			for(int j=0; j<another.getColoumnSize(); j++){

				for(int k=0; k<another.getRowSize(); k++){

					matrixinternal[i][j] += copyInternal[i][k] * another[k][j]; 
				
				
				}

				(*result)[i][j] = matrixinternal[i][j];

			}

		}*/

		for(int i=0; i<this->getRowSize(); i++){

			for(int j=0; j<this->getColoumnSize(); j++){

				for(int k=0; k<another.getColoumnSize(); k++){

					(*result)[i][k] += (matrixinternal[i][j] *another[j][k]);

				}
			}


		}

		return (*result);

	}else{

		throw std::invalid_argument( "dot: does not matches to rule MxN1 (dot) N2xP = MxP := where ( N1 == N2 ) must" );
	}


}


template <typename T>
inline void Matrix<T>::populateFromArray(T*arr){

	//std::cout<<matrixinternal.size()<<std::endl;
	//std::cout<<matrixinternal.at(0).size()<<std::endl

	for(int i=0; i<this->getRowSize(); i++){
		for(int j=0; j<this->getColoumnSize(); j++){

			matrixinternal[i][j] = *(arr+i*matrixinternal.at(i).size()+j); //(arr[i][j];
		}


	}

}


template <typename T>
inline Matrix<T> Matrix<T>::subtract(Matrix another){

	if((this->getRowSize() == another.getRowSize()) && 
		(this->getColoumnSize() == another.getColoumnSize())){

		Matrix<T> * result = new Matrix<T>(this->getRowSize(), this->getColoumnSize());

		for(int i=0; i<this->getRowSize(); i++){
			for(int j=0; j<this->getColoumnSize(); j++){
				//matrixinternal[i][j] -= another[i][j];

				(*result)[i][j] = matrixinternal[i][j] - another[i][j];

			}
		}

		return (*result);

	}else{

		throw std::invalid_argument( "subtract: Dimensions of primary and argument matrix must be equivalent" );
	}

}


template <typename T>
inline Matrix<T> Matrix<T>::add(Matrix another){

	if((this->getRowSize() == another.getRowSize()) && 
		(this->getColoumnSize() == another.getColoumnSize())){

		Matrix<T> * result = new Matrix<T>(this->getRowSize(), this->getColoumnSize());

		for(int i=0; i<this->getRowSize(); i++){
			for(int j=0; j<this->getColoumnSize(); j++){
				//matrixinternal[i][j] += another[i][j];
				(*result)[i][j] = matrixinternal[i][j] + another[i][j];		
			}
		}

		return (*result);

	}else{

		throw std::invalid_argument( "add: Dimensions of primary and argument matrix must be equivalent" );
	}

}

template <typename T>
inline Matrix<T> Matrix<T>::addScalar(T value){
	
	/*

		To-do:
		Replace Logic with : Matrix = this.Matrix + value * IdentityMatrix;

	*/

	Matrix<T> * result = new Matrix<T>(this->getRowSize(), this->getColoumnSize());

	for(int i=0; i<this->getRowSize(); i++){
		for(int j=0; j<this->getColoumnSize(); j++){
			//matrixinternal[i][j] += value;
			(*result)[i][j] = matrixinternal[i][j] + value;
		}
	}

	return (*result);

}

template <typename T>
inline Matrix<T> Matrix<T>::apply(T (*f)(T)){

	Matrix<T> *result = new Matrix<T>(this->getRowSize(), this->getColoumnSize());


	for(int i=0; i<this->getRowSize(); i++){
		for(int j=0; j<this->getColoumnSize(); j++){
			
			(*result)[i][j] = (*f)(matrixinternal[i][j]);

			//result[i][j] = callbackfunction(this.matrixinternal)

			//matrixinternal[i][j] = (*f)(matrixinternal[i][j]);
		}
	}

	return (*result);

}

template <typename T>
inline Matrix<T> Matrix<T>::scale(T factor){

	Matrix<T> *result = new Matrix<T>(this->getRowSize(), this->getColoumnSize());

	for(int i=0; i<this->getRowSize(); i++){
		for(int j=0; j<this->getColoumnSize(); j++){
			//matrixinternal[i][j] *= factor;
			(*result)[i][j] = matrixinternal[i][j] * factor;
		}
	}

	return (*result);
}

template <typename T>
inline void Matrix<T>::dump(){

	std::cout<<"Printing Size"<<this->getRowSize();
	std::cout<<"Printing Size"<<this->getColoumnSize()<<std::endl;


	for(int i=0; i<this->getRowSize(); i++){
		for(int j=0; j<this->getColoumnSize(); j++){

			std::cout<<matrixinternal[i][j];
			if(j != (this->getColoumnSize()-1))
				std::cout<<COMMA_DELIMIT;

		}

		std::cout<<std::endl;
	}
}


template <typename T>
inline void Matrix<T>::changeSize(unsigned int x, unsigned int y){
	rowsize = x;
	coloumnsize = y;
	matrixinternal.resize(x, std::vector<T>(y));
}


template <typename T>
inline Matrix<T>::Matrix(unsigned int x, unsigned int y){
	rowsize = x;
	coloumnsize = y;
	matrixinternal.resize(x, std::vector<T>(y));
}

template <typename T>
inline Matrix<T>::matrix_row::matrix_row(std::vector<T>& r): row(r){

}

template <typename T>
inline T& Matrix<T>::matrix_row::operator[](unsigned int y){
	return row.at(y);
}

template <typename T>
inline unsigned int Matrix<T>::getRowSize(){
	return rowsize;
}

template <typename T>
inline unsigned int Matrix<T>::getColoumnSize(){
	return coloumnsize;
}


template <typename T>
inline typename Matrix<T>::matrix_row Matrix<T>::operator[](unsigned int x){
	return matrix_row(matrixinternal.at(x));
}

#endif
