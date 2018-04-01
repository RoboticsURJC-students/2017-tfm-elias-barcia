#include <iostream>
#include <ctime>
#include <unistd.h>
#include <fstream>
#include <sys/time.h>
#include <iomanip>
#include <cmath>
#include <math.h>
#include <cstdlib>
#include "Eigen/Dense"
#include "Eigen/SVD"
using namespace Eigen;
#include <limits>
#include <stdbool.h>
#include "Interpolator.h"

/* This class interpolates 2 data of series
 * Reads 2 files with format " Time X Y Z"
 *
 */


Interpolator::Interpolator(){

	std::cout<< "constructor por defecto AjusteTiempo" <<std::endl;

}

MatrixXd insertRowInSequence (MatrixXd& m, VectorXd myVector, int position){

	MatrixXd myNewMatrix;
	myNewMatrix << m.block< position-1,m.cols()>(0,0);
	myNewMatrix << myVector;
	mynewMatrix << m.block<position,m.cols()>(position,0);

	return myNewMatrix;
}

void Interpolator::interpolate(int maxLine, MatrixXd& A, MatrixXd& B){

 //testing inserting row


}

void Interpolator::reduceSequence(int maxLine, MatrixXd& aMatrix ){



}


int main(){

	std::cout <<"	Starting main of  Interpolator="<<std::endl;
	Interpolator myInterpolator;
	MatrixXd A;
	double offset = 28;
	int maxLine = 2500;
	int intervalo = 200;
    //Read Files for sequence A and Sequence B

	std::cout << std::setprecision(6) << std::fixed;
	std::ifstream infileA( "/home/tfm3/workspace/Interpolator/miEntradaA.txt" );
	//inputFile >> std::setprecision(6) >> std::fixed;
	std::cout << std::setprecision(6) << std::fixed;
	std::ifstream infileB( "/home/tfm3/workspace/Interpolator/miEntradaB.txt" );
	//inputFile >> std::setprecision(6) >> std::fixed;

	std::cout << std::setprecision(6) << std::fixed;
	std::ofstream outA( "/home/tfm3/workspace/Interpolator/miSalidaA.txt" );
	outA << std::setprecision(6) << std::fixed;
	std::cout << std::setprecision(6) << std::fixed;
	std::ofstream outB( "/home/tfm3/workspace/Interpolator/miSalidaB.txt" );
	outB << std::setprecision(6) << std::fixed;

	while ( (infileA >> timestamp >> rx >> ry >> rz >> q1 >> q2 >> q3 >> q4) && contLin<maxLine ){
			    readingA.row(contLin)<< rx,ry,rz;

				contLin ++;

	}
    infileA.close();
	MatrixXd A (contLin,3);
	A = readingA.block(0,0,contLin,3);


	while ( (infileB >> timestamp >> rx >> ry >> rz >> q1 >> q2 >> q3 >> q4) && contLin<maxLine ){
				    readingB.row(contLin)<< rx,ry,rz;

					contLin ++;

	}
	infileB.close();
	MatrixXd B (contLin,3);
	B = readingB.block(0,0,contLin,3);




	Interpolator.interpolate(maxLine, A,B);

	for (int i= 0; i< contLin; i++){
			std::cout <<"i="<<i<<std::endl;
			std::cout <<"centered.row(i)="<<centered.row(i)<<std::endl;

			VectorXd aRow = A.row(i);
			outA << aRow(0)<<" "<<aRow(1)<<" "<<aRow(2)<<"\n";

			VectorXd bRow = B.row(i);
			outB << bRow(0)<<" "<<bRow(1)<<" "<<bRow(2)<<"\n";

	}

	outA.close();
	outB.close();


}


