#include "Registrador.h"
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <fstream>
#include <sys/time.h>
#include <iomanip>
#include <cmath>
#include <cstdlib>

#include <limits>


//#include "Eigen/Dense"

int main( int argc, char** argv )
{
	//std::cout << std::setprecision(6) << std::fixed;
    std::ofstream out( "miSalida.txt" );
    //out << std::setprecision(6) << std::fixed;


	std::ifstream infile("/home/tfm3/workspace/Registrador/mientrada.txt");
	//std::string line;
    //infile >> std::setprecision(6) >> std::fixed;
	MatrixXd A (4,3);
	int contLin=0;
	double timestamp,rx,ry,rz,q1,q2,q3,q4=0;
	std::cout <<"antes de leer el archivo"<<std::endl;
	while ( infile >> timestamp >> rx >> ry >> rz >> q1 >> q2 >> q3 >> q4 ){
	        std::cout << "You said.... contLin"<< contLin << timestamp << " " << rx << " " << ry << " " << rz << " " << q1 << " " << q2 << " " << q3 << " " << q4 << "\n";
	        //VectorXd myVector (rx,ry,rz);
	        //A.row(contLin)= myVector;
	        A.row(contLin)<< rx,ry,rz;
	        contLin ++;

	}
	infile.close();


	std::cout << ">>>>>>>CIERRO INFILE\n";

	std::ifstream infileB("/home/tfm3/workspace/Registrador/miEntradaModificada.txt");

	    //infileB >> std::setprecision(6) >> std::fixed;
		MatrixXd B (4,3);
		int contLinB=0;
		//double timestamp,rx,ry,rz,q1,q2,q3,q4=0;
		std::cout <<"antes de leer el archivo"<<std::endl;
		timestamp=0,rx=0,ry=0,rz=0,q1,q2,q3,q4=0;
		while ( infileB >> timestamp >> rx >> ry >> rz >> q1 >> q2 >> q3 >> q4 ){
		        std::cout << "You said.... contLinB"<< contLinB << timestamp << " " << rx << " " << ry << " " << rz << " " << q1 << " " << q2 << " " << q3 << " " << q4 << "\n";
		        //VectorXd myVector (rx,ry,rz);
		        //A.row(contLin)= myVector;
		        B.row(contLinB)<< rx,ry,rz;
		        contLinB ++;

		}
		infileB.close();

	Registrador miRegistrador;
	//miRegistrador.demoPresentaMatriz();
	//MatrixXd A = MatrixXd::Random(3,3);
	std::cout << "A "<<A<<std::endl;

	//MatrixXd B = MatrixXd::Random(3,3);
	//MatrixXd B (3000,3);
	std::cout << "B "<<B<<std::endl;
	MatrixXd ret_R,ret_t;

	miRegistrador.rigid_transform_3D( A, B, ret_R,ret_t);

	std::cout << "ret_R"<<ret_R << std::endl;
	std::cout << "ret_t "<<ret_t << std::endl;

	MatrixXd A2 = (ret_R * A.transpose());
	std::cout << "A2"<<A2<< std::endl;
	int N = A2.cols();
	MatrixXd A3 (A2.rows(),A2.cols());
	std::cout << "2- "<<std::endl;
	for (int i=0; i< N; i++ ) {
		std::cout << "3- "<<std::endl;
				//A3.row(i) = VectorXd(A2.row(i)) + VectorXd( ret_t );
		        //A3.row(i) = Vector3d( A2.row(i)) + Vector3d(ret_t);
			    A3.col(i) =  A2.col(i) + ret_t ;

		        std::cout << "4- "<<std::endl;

			}

	//MatrixXd A3	= A2.rowwise()	+ ret_t;
	std::cout << "A3 "<<A3<<std::endl;
	MatrixXd A4 = A3.transpose();
	std::cout << "A4 "<<A4<<std::endl;

	// Find the error
	MatrixXd err = A4 - B;
	std::cout << "err "<<std::endl<< err <<std::endl;
	MatrixXd err2 = err.array().pow(2);
	double errorNumber = sqrt(err2.sum()/err2.rows());

	std::cout << "err2 "<< err2 <<std::endl;
	std::cout << "RMSE= "<< errorNumber <<std::endl;


}
