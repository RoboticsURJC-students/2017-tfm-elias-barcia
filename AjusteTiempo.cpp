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
#include "AjusteTiempo.h"


AjusteTiempo::AjusteTiempo(){
	std::cout<< "constructor por defecto AjusteTiempo" <<std::endl;
}

AjusteTiempo::genera2Series(int maxLine,double proporcionFrecuencia,double offset, MatrixXd& A, MatrixXd& B){
	// por desarrollar
	/*int contLin=0;
	MatrixXd readingA (maxLine,4);//size is big enough to store an unknown number of data rows from file
	MatrixXd readingB (maxLine,4);
	VectorXd vTiempoA (maxLine) ;
	VectorXd vTiempoB (maxLine) ;
	for (int i=0;i< maxLine; i++){
		readingA.row(contLin)<< contLin,sin(contLin),ry,rz;
		vTiempoA.row(contLin) << contLin;
		//vTiempoA.row(contLin) << timestamp;
		//create sequence 2, two varialbes,  T+offset , X
		//readingB.row(contLin)<< timestamp+miOffset,rx,ry,rz;
		readingB.row(contLin)<< contLin+miOffset,sin(contLin),ry,rz;
		vTiempoB.row(contLin) << contLin+miOffset;

		outA <<contLin <<" "<< sin(contLin) <<" "<< ry <<" "<< rz <<" "<< q1 <<" "<< q2 <<" "<<q3 <<" "<< q4<<std::endl;
		outB <<contLin+miOffset <<" "<< sin(contLin) <<" "<< ry <<" "<< rz <<" "<< q1 <<" "<< q2 <<" "<<q3 <<" "<< q4<<std::endl;
		contLin ++;
	}*/
}

int main( int argc, char** argv )
{
	//std::cout << std::setprecision(6) << std::fixed;

    std::ifstream infile( "/home/tfm3/workspace/AjusteTiempo/miEntradaA.txt" );
    infile >> std::setprecision(6) >> std::fixed;

    std::cout << std::setprecision(6) << std::fixed;
    std::ofstream outA( "/home/tfm3/workspace/AjusteTiempo/miSalidaA.txt" );
    outA << std::setprecision(6) << std::fixed;

    std::cout << std::setprecision(6) << std::fixed;
    std::ofstream outB( "/home/tfm3/workspace/AjusteTiempo/miSalidaB.txt" );
    outB << std::setprecision(6) << std::fixed;

	std::cout <<"antes de declarar la variable"<<std::endl;
	int maxLine = 30;
	MatrixXd readingA (maxLine,4);//size is big enough to store an unknown number of data rows from file
	MatrixXd readingB (maxLine,4);
	VectorXd vTiempoA (maxLine) ;
	VectorXd vTiempoB (maxLine) ;
	//read a file
	int contLin=0;
	double timestamp,rx,ry,rz,q1,q2,q3,q4=0;
	double mediaTiempoA, mediaTiempoB;
	std::cout <<"antes de leer el archivo"<<std::endl;
	int miOffset=5;

	while ( (infile >> timestamp >> rx >> ry >> rz >> q1 >> q2 >> q3 >> q4) && contLin<maxLine ){
		    std::cout <<"contLin="<<contLin<<std::endl;

	//while ( infile >> rx >> ry >> rz  ){
			//std::cout << "You said.... contLin"<< contLin << timestamp << " " << rx << " " << ry << " " << rz << " " << q1 << " " << q2 << " " << q3 << " " << q4 << "\n";
			//VectorXd myVector (rx,ry,rz);
			//readingA.row(contLin)= myVector;
		    //create sequence 1, two variables , T (time), X
			//readingA.row(contLin)<< timestamp,rx,ry,rz;
			//readingA.row(contLin)<< contLin,rx,ry,rz;
		    readingA.row(contLin)<< contLin,sin(contLin),ry,rz;
		    vTiempoA.row(contLin) << contLin;
			//vTiempoA.row(contLin) << timestamp;
			//create sequence 2, two varialbes,  T+offset , X
			//readingB.row(contLin)<< timestamp+miOffset,rx,ry,rz;
			readingB.row(contLin)<< contLin+miOffset,sin(contLin),ry,rz;
			vTiempoB.row(contLin) << contLin+miOffset;

			outA <<contLin <<" "<< sin(contLin) <<" "<< ry <<" "<< rz <<" "<< q1 <<" "<< q2 <<" "<<q3 <<" "<< q4<<std::endl;
			outB <<contLin+miOffset <<" "<< sin(contLin) <<" "<< ry <<" "<< rz <<" "<< q1 <<" "<< q2 <<" "<<q3 <<" "<< q4<<std::endl;
			contLin ++;

	}
	infile.close();
	outA.close();
	outB.close();
	contLin=maxLine;// OJO aqui cambio el numero de lineas
	std::cout <<"contLin="<<contLin<<std::endl;
	MatrixXd A (contLin,3);
	MatrixXd B (contLin,3);
	A = readingA.block(0,0,contLin,3);
	B = readingB.block(0,0,contLin,3);

	mediaTiempoA = vTiempoA.mean();
	std::cout <<"	mediaTiempoA="<<	mediaTiempoA<<std::endl;

	mediaTiempoB = vTiempoB.mean();
	std::cout <<"	mediaTiempoB="<<	mediaTiempoB<<std::endl;

	VectorXd centeredTA,centeredTB,totalCenteredT;
	//for (int i=0; i < contLin ; i++){
		//centeredTA.row(contLin)<< vTiempoA.array() - mediaTiempoA;

	//}
	centeredTA = vTiempoA.array() - mediaTiempoA;
	std::cout <<"	centeredTA="<<	centeredTA<<std::endl;
	centeredTB = vTiempoB.array() - mediaTiempoB;
	std::cout <<"	centeredTB="<<	centeredTB<<std::endl;
	double totalTime,miCov;
    totalTime=0;
	for ( int i=0; i < contLin; i++){
		totalTime += centeredTA(i)*centeredTB(i);
	}
	miCov=totalTime/contLin;
	std::cout <<"	miCov="<<	miCov<<std::endl;

    // ahora calculamos la desviacion tipica
	double desviacionA,desviacionB,miCorrelation;
	for ( int i=0; i < contLin; i++){
			desviacionA += centeredTA(i)*centeredTA(i);
			desviacionB += centeredTB(i)*centeredTB(i);

		}
	desviacionA = sqrt(desviacionA/contLin);
	desviacionB = sqrt(desviacionB/contLin);
	std::cout <<"	desviacionA="<<	desviacionA<<std::endl;
	std::cout <<"	desviacionB="<<	desviacionB<<std::endl;

	miCorrelation = miCov/(desviacionA*desviacionB);
	std::cout <<"	miCorrelation="<<	miCorrelation<<std::endl;


}

//create sequence 1, two variables , T (time), X

