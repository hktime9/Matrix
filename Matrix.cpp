#include <iostream>

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
		~Matrix(){
			this->clear();
		}
		int getRows(){
			return rows;
		}
		int getCols(){
			return cols;
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
		void multiply(int num){
			double cast= double(num);
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					matrix[i][j]*= cast;
				}
			}
		}
		void multiply(double num){
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					matrix[i][j]*= num;
				}
			}	
		}
		void add(int num){
			double cast= double(num);
			for(int i=0;i<rows;i++){
				for(int j=0;j<cols;j++){
					matrix[i][j]+= cast;
				}
			}
		}
		void subtract(int num){
			this->add(-1*num);
		}
		void divide(int num){
			double cast= double(num);
			cast= 1/cast;
			this->multiply(cast);
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



int main(){
	double test[18]= {1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9};
	Matrix m(test,2,9);
	m.subtract(3);
	cout << m;
}