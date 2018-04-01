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
#include "GeneratorPCA.h"




GeneratorPCA::GeneratorPCA(){
	std::cout<< "constructor por defecto AjusteTiempo" <<std::endl;
}

void GeneratorPCA::calculatePCA(int maxLine, MatrixXd& A){

	std::cout << std::setprecision(6) << std::fixed;
	std::ifstream infile( "/home/tfm3/workspace/GeneratorPCA/miEntradaA.txt" );
	//inputFile >> std::setprecision(6) >> std::fixed;

    std::cout << std::setprecision(6) << std::fixed;
    std::ofstream outA( "/home/tfm3/workspace/GeneratorPCA/miSalidaA.txt" );
    outA << std::setprecision(6) << std::fixed;


	std::cout <<"antes de declarar la variable"<<std::endl;
	//int maxLine = 30;
	MatrixXd readingA (maxLine,3);//size is big enough to store an unknown number of data rows from file

	VectorXd vTiempoA (maxLine), vSerieA (maxLine) ;
	//read a file
	int contLin=0;
	double timestamp,rx,ry,rz,q1,q2,q3,q4=0;
	double mediaTiempoA, mediaTiempoB, mediaSerieA, mediaSerieB;
	std::cout <<"antes de leer el archivo"<<std::endl;
	//int miOffset=5;
    //double miOffset = offset;
    double newContLin = 0;
    //std::cout <<"miOffset="<<miOffset<<std::endl;

    //Read the input file
	while ( (infile >> timestamp >> rx >> ry >> rz >> q1 >> q2 >> q3 >> q4) && contLin<maxLine ){
		    readingA.row(contLin)<< rx,ry,rz;

			contLin ++;

	}
	infile.close();

	// Calculate PCA ,
	//MatrixXd A (contLin,3);

	A = readingA.block(0,0,contLin,3);

	// Mean centering data.
	Eigen::VectorXd myMeans = A.colwise().mean();

	std::cout <<"myMeans="<<myMeans<<std::endl;

	Eigen::MatrixXd centered = A.rowwise() + myMeans.transpose();

    	// Compute the covariance matrix.
	Eigen::MatrixXd cov = centered.adjoint() * centered;
	cov = cov / (A.rows() - 1);

	Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eig(cov);
	// Normalize eigenvalues to make them represent percentages.

	Eigen::VectorXd normalizedEigenValues =  eig.eigenvalues() / eig.eigenvalues().sum();


	// Get the two major eigenvectors and omit the others.
	Eigen::MatrixXd evecs = eig.eigenvectors();
	Eigen::MatrixXd pcaTransform = evecs.rightCols(3);


	// Map the dataset in the new two dimensional space.
	centered = centered * pcaTransform;

	for (int i= 0; i< contLin; i++){
		std::cout <<"i="<<i<<std::endl;
		std::cout <<"centered.row(i)="<<centered.row(i)<<std::endl;
		VectorXd aRow = centered.row(i);
		outA << aRow(0)<<" "<<aRow(1)<<" "<<aRow(2)<<"\n";
		std::cout <<"aRow="<<aRow<<std::endl;
		//outA << centered.row(i).[1], centered.row(i).[2],centered.row(i).[3];
		//outA << centered.row(i,1), centered.row(i,2),centered.row(i,3);

	}

    outA.close();



}

int main( int argc, char** argv )
{
	//std::cout << std::setprecision(6) << std::fixed;




		std::cout <<"	ESTOY EN BLOQUE 2="<<std::endl;
        GeneratorPCA miGeneratorPCA;
		MatrixXd A;
		double offset = 28;
		int maxLine = 2500;
		int intervalo = 200;		//micorrelador.calcularAutocorrelacion( maxLine,intervalo, offset, A,  B);
		//micorrelador.calcularAutocorrelacion2( maxLine,intervalo, offset, A,  B);

		miGeneratorPCA.calculatePCA(maxLine, A);
		//micorrelador.calcularAutocorrelacion3( 'y',maxLine,intervalo, offset, A,  B);
		//micorrelador.calcularAutocorrelacion3( 'z',maxLine,intervalo, offset, A,  B);




}

