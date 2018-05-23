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
#include "SLAMTestBed.h"
#include "GeneratorPCA.h"
//#include "../AjusteTiempo/AjusteTiempo.h"
#include "FindScala.h"

SLAMTestBed::SLAMTestBed(){
	std::cout<< "constructor por defecto Interpolator" <<std::endl;
}

int main(){

	int maxLine = 2500;
	MatrixXd readingA (maxLine,3);
	MatrixXd readingB (maxLine,3);
	std::cout <<"1="<<std::endl;
	std::cout << std::setprecision(4) << std::fixed;
	std::ifstream infileA( "/home/tfm3/workspace/SLAMTestBed/miEntradaA.txt" );
	//inputFile >> std::setprecision(6) >> std::fixed;
	std::cout << std::setprecision(4) << std::fixed;
	std::ifstream infileB( "/home/tfm3/workspace/SLAMTestBed/miEntradaA.txt" );
	//inputFile >> std::setprecision(6) >> std::fixed;
	std::cout <<"2="<<std::endl;
	std::cout << std::setprecision(4) << std::fixed;
	std::ofstream outA( "/home/tfm3/workspace/SLAMTestBed/miSalidaA.txt" );
	outA << std::setprecision(4) << std::fixed;
	std::cout << std::setprecision(4) << std::fixed;

	std::ofstream outB( "/home/tfm3/workspace/SLAMTestBed/miSalidaB.txt" );
	outB << std::setprecision(4) << std::fixed;

	double timestamp,rx,ry,rz,q1,q2,q3,q4=0;
	int contLin=0;
	std::cout <<"4="<<std::endl;
	while ( (infileA >> timestamp >> rx >> ry >> rz >> q1 >> q2 >> q3 >> q4) && contLin<maxLine ){
				std::cout <<"contLin="<<contLin<<std::endl;
				readingA.row(contLin)<< rx,ry,rz;
				//std::cout <<"contLin="<<contLin<<std::endl;
				contLin ++;


	}
	infileA.close();
	MatrixXd A (contLin,3);
	A = readingA.block(0,0,contLin,3);

	contLin=0;

	while ( (infileB >> timestamp >> rx >> ry >> rz >> q1 >> q2 >> q3 >> q4) && contLin<maxLine ){
					readingB.row(contLin)<<rx,ry,rz;

					contLin ++;

	}
	infileB.close();
	MatrixXd B (contLin,3);
	B = readingB.block(0,0,contLin,3);

    GeneratorPCA myGeneratorPCA;
    myGeneratorPCA.calculatePCAbySVD(A);
    myGeneratorPCA.calculatePCAbySVD(B);

    FindScala myFindScala;
    myFindScala.getScalaSVD(A,B);









}
