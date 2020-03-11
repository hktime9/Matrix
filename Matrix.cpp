#include <iostream>
#include <tuple>
#include <stdio.h> 
#include <stdlib.h> 
#include <string>
#include <math.h>
#include <time.h> 
#include <random>

using namespace std;



class Matrix{
	private:
		int rows, cols;
		double** matrix;
		void init(){
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					matrix[i][j]= 0.0;
				}
			}
		}
		void clear(){
			for(int i=0;i<rows;i++){
				delete matrix[i];
			}
			delete matrix;			
		}
		double sigmoid(double num){
			return (1)/(1+exp(-1*num));
		}
		double randomNumber(double lowerB, double upperB){
			return (lowerB + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(upperB))));
		}
		friend ostream & operator << (ostream &out, Matrix const &m);
	public:
		Matrix(int r, int c){
			rows= r;
			cols= c;
			matrix= new double*[rows];
			for(int i=0;i<rows;i++){
				matrix[i]= new double[cols];
			}
			this->init();
		}
		Matrix(double** original, int r, int c){
			rows= r;
			cols= c;
			matrix= new double*[rows];
			for(int i=0;i<rows;i++){
				matrix[i]= new double[cols];
			}
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					matrix[i][j]= original[i][j];
				}
			}
		}
		Matrix(double* original, int r, int c){
			rows= r;
			cols= c;
			int originalSize= r*c;
			matrix= new double*[rows];
			for(int i=0;i<rows;i++){
				matrix[i]= new double[cols];
			}
			int index= 0;
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					matrix[i][j]= original[index];
					index++;
				}
			}
		}
		Matrix(int r, int c, double lowerB, double upperB){
			rows= r;
			cols= c;
			matrix= new double*[rows];
			for(int i=0;i<rows;i++){
				matrix[i]= new double[cols];
			}
			srand((unsigned)time(NULL));
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){

					matrix[i][j]= this->randomNumber(lowerB, upperB);
				}
			}

		}
		Matrix(const Matrix &m){
			rows= m.rows;
			cols= m.cols;
			matrix= new double*[rows];
			for(int i=0;i<rows;i++){
				matrix[i]= new double[cols];
			}
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					matrix[i][j]= m.matrix[i][j];
				}
			}
		}
		~Matrix(){
			this->clear();
		}
		int getRows(){
			return rows;
		}
		int getCols(){
			return cols;
		}
		tuple<int,int> shape(){
			return make_tuple(rows, cols);
		}

		void reShape(int newRow, int newCol){
			this->clear();
			rows= newRow;
			cols= newCol;
			matrix= new double*[rows];
			for(int i=0;i<rows;i++){
				matrix[i]= new double[cols];
			}
			this->init();
		}
		void zeros(){
			this->init();
		}
		Matrix multiply(int num){
			double cast= double(num);
			Matrix result(rows, cols);
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					result.matrix[i][j]= matrix[i][j]*cast;
				}
			}
			return result;
		}
    	Matrix operator * (int num){ 
         	return this->multiply(num);
    	}
		Matrix multiply(double num){
			Matrix result(rows, cols);
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					result.matrix[i][j]= matrix[i][j]*num;
				}
			}
			return result;
		}
    	Matrix operator * (double num){ 
         	return this->multiply(num);
    	}
		Matrix add(int num){
			double cast= double(num);
			Matrix result(rows, cols);
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					result.matrix[i][j]= matrix[i][j]+cast;
				}
			}
			return result;
		}
    	Matrix operator + (int num){ 
         	return this->add(num);
    	}
		Matrix subtract(int num){
			return this->add(-1*num);
		}
    	Matrix operator - (int num){ 
         	return this->subtract(num);
    	}
		Matrix divide(int num){
			double cast= double(num);
			cast= 1/cast;
			return this->multiply(cast);
		}
    	Matrix operator / (int num){ 
         	return this->divide(num);
    	}
		Matrix add(Matrix toAdd){
			try{
				if((toAdd.getRows()!=rows)||(toAdd.getCols()!=cols)){
					string rowStr= to_string(toAdd.getRows());
					string colStr= to_string(toAdd.getCols());
					string error= "Error:: Shapes ("+to_string(rows)+", "+to_string(cols)+") and ("+rowStr+", "+colStr+") mismatch";
					throw(error);
				}
				Matrix added(rows, cols);
				for(int i=0;i<rows;i++){
					for(int j=0;j<cols;j++){
						added.matrix[i][j]= matrix[i][j]+toAdd.matrix[i][j];
					}
				}
				return added;
			}
			catch(string errorMessage){
				cout << errorMessage << endl;
				_Exit(10);
			}
		}
    	Matrix operator + (Matrix const &toAdd){ 
         	return this->add(toAdd);
    	}
    	Matrix subtract(Matrix toSubtr){
    		return this->add(toSubtr*-1);
    	}
    	Matrix operator - (Matrix const &toSubtr){ 
         	return this->subtract(toSubtr);
    	}
		Matrix dot(Matrix toDot){
			try{
				if(toDot.getRows()!=cols){
					string rowStr= to_string(toDot.getRows());
					string colStr= to_string(toDot.getCols());
					string error= "Error:: Shapes ("+to_string(rows)+", "+to_string(cols)+") and ("+rowStr+", "+colStr+") do not align";
					throw(error);
				}
				Matrix dotProd(rows, toDot.cols);
				for(int i= 0;i<rows;++i){
			        for(int j= 0;j<toDot.getCols();++j){
			            for(int k = 0;k<cols;++k){
			            	dotProd.matrix[i][j]+= matrix[i][k]*toDot.matrix[k][j];
			            }
			        }
				}
				return dotProd;
			}
			catch(string errorMessage){
				cout << errorMessage << endl;
				_Exit(10);
			}
		}
    	Matrix operator * (Matrix toDot){ 
         	return this->dot(toDot);
    	}
		Matrix T(){
			Matrix transposed(cols, rows);
		    for(int i= 0;i<rows;++i){
        		for(int j= 0; j<cols;++j){
        			transposed.matrix[j][i]= matrix[i][j];
        		}
		    }
		    return transposed;
		}
		Matrix sigmoid(){
			Matrix copied(rows,cols);
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					copied.matrix[i][j]= sigmoid(matrix[i][j]);
				}
			}
			return copied;
		}
};

ostream & operator << (ostream &out, Matrix const &m){
	out << "[";
	for(int i=0;i<m.rows;i++){
		if(i==0){
			out << "[ ";
		}
		else{
			out << " [ ";
		}
		for(int j=0;j<m.cols;j++){
			out << m.matrix[i][j] << " ";
		}
		if(i==m.rows-1){
			out << "]";
		}
		else{
			out << "]" << endl;
		}
	}
	out << "]" << endl;
	return out;
}

// int main(){
// 	double test[18]= {1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9};
// 	double i[18]= {1.0,0.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0};
// 	Matrix A(test,3,3);
// 	Matrix B(i,3,3);
// 	cout << A;
// 	cout << B;
// 	cout << A*B;
// }