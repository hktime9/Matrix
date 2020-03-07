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
		friend ostream& operator <<(ostream& os, const Matrix &mat);
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
			// To be continued...
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
};

ostream & operator << (ostream &out, const Matrix &matrix)
{
	out << "[";
	for(int i=0;i<matrix.rows;i++){
		if(i==0){
			out << "[ ";
		}
		else{
			out << " [ ";
		}
		for(int j=0;j<matrix.cols;j++){
			out << matrix.matrix[i][j] << " ";
		}
		if(i==matrix.rows-1){
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

}