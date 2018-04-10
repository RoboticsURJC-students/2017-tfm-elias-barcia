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

	std::cout<< "constructor por defecto Interpolator" <<std::endl;

}



void Interpolator::insertRowInSequence (MatrixXd& m, VectorXd myVector, int position){
   /*
	MatrixXd myNewMatrix ( m.rows()+1,m.cols());
	std::cout <<"myNewMatrix="<<myNewMatrix<<std::endl;
	std::cout<< "insertRowInSequence"<<std::endl;
	std::cout <<"m="<<m<<std::endl;


	//myNewMatrix << m.block(position-1,m.cols(),0,0);
	//myNewMatrix = m.block(0,0,position-1,3);
	std::cout <<"myNewMatrix="<<myNewMatrix<<std::endl;
	//myNewMatrix.row(position) << myVector(0),myVector(1),myVector(2);
	//myNewMatrix.row(position) = myVector.transpose();

	//myNewMatrix << m.block(position,m.cols(),position,0);
	//myNewMatrix << m.block(0,0,position,3);

	//return myNewMatrix;

	for (int i=0; i< m.rows(); i++){
		if (i<position){
			std::cout <<"1"<<std::endl;
			myNewMatrix.row(i)<<m.row(i);
		} else if (i>position){
			std::cout <<"2"<<std::endl;
			myNewMatrix.row(i+1) <<m.row(i);
		} else if (i==position){
			std::cout <<"3"<<std::endl;
			myNewMatrix.row(position) << myVector.transpose();
			myNewMatrix.row(i+1) << m.row(i);
		}
		std::cout <<"myNewMatrix="<<myNewMatrix<<std::endl;
	}
	std::cout<< "insertRowInSequence2"<<std::endl;
	m=myNewMatrix.block(0,0,myNewMatrix.rows(),4);
	//return;
	*/
}




double Interpolator::interpolateValue (double x,double x2,double y2,double x3,double y3) {

	double y;
	y= y2 + (x-x2)*((y3-y2)/(x3-x2));

	return y;
}

void Interpolator::interpolate2Series(int maxLine, MatrixXd& A, MatrixXd& B){

	// Supposed B less values than A
	int Bsize= B.rows();
	std::cout<< "Bsize="<<Bsize<<std::endl;
	int Asize= A.rows();
	std::cout<< "Asize="<<Asize<<std::endl;
	int i =1;
	int j , contAddedValues= 0;
	MatrixXd newBMatrix (A.rows(),A.cols());
    int contNewMatrix =0;
	while (i < Bsize){
		//std::cout<< "i="<<i<<std::endl;
		newBMatrix.row(contNewMatrix)<< B.row(i-1);
		contNewMatrix++;
		//std::cout<< "contNewMatrix="<<contNewMatrix<<std::endl;
		//std::cout<< "B.row(i-1)(0)="<<B.row(i-1)(0)<<std::endl;
		contAddedValues = 0;
		//j=i-1;
		while (j< Asize  && (A.row(j)(0) < B.row(i)(0))){

			//std::cout<< "i="<<i<< "j="<<j<<" (A.row(j)(0)="<<(A.row(j))(0)<<" B.row(i)(0)="<<(B.row(i))(0)<<std::endl;

			if ((A.row(j)(0) > B.row(i-1)(0)) ) {

				//interpolate X coordinate
				double y2= (B.row(i-1))(1);
				double x = (A.row(j))(0);
				double x2= (B.row(i-1))(0);
				double y3= (B.row(i))(1);
				double x3= (B.row(i))(0);
				double xCoordinate = this->interpolateValue(x,x2,y2,x3,y3);

				//interpolate Y coordinate
				y2= (B.row(i-1))(2);
				x = (A.row(j))(0);
				x2= (B.row(i-1))(0);
				y3= (B.row(i))(2);
				x3= (B.row(i))(0);
				double yCoordinate = this->interpolateValue(x,x2,y2,x3,y3);

				//interpolate Z coordinate
				y2= (B.row(i-1))(3);
				x = (A.row(j))(0);
				x2= (B.row(i-1))(0);
				y3= (B.row(i))(3);
				x3= (B.row(i))(0);
				double zCoordinate = this->interpolateValue(x,x2,y2,x3,y3);
				Vector4d myNewVector(x,xCoordinate,yCoordinate,zCoordinate);
				//contAddedValues++;

				newBMatrix.row(contNewMatrix) << myNewVector.transpose();
				contNewMatrix++;
				//std::cout<< "contNewMatrix="<<contNewMatrix<<std::endl;
			}
			j++;
		}
		i++;

	}
	//std::cout<< "contNewMatrix="<<contNewMatrix<<std::endl;


	//std::cout<< "A="<<A<<std::endl;
	//std::cout<< "B="<<B<<std::endl;

	newBMatrix.row(contNewMatrix)<<B.row(i-1);
	contNewMatrix ++;
	//std::cout<< "newBMatrix="<<newBMatrix<<std::endl;

	B= newBMatrix.block(0,0,contNewMatrix,4);
	//std::cout<< "new B Matrix="<<B<<std::endl;


}

/*
void Interpolator::interpolate2Series(int maxLine, MatrixXd& A, MatrixXd& B){

 //testing inserting row
  std::cout <<"interpolate"<<std::endl;
  int sizeB = B.rows();
  double timeBPrevious = 0;
  MatrixXd myNewBMatrix (A.rows(),A.cols());
  int cont=0;
  std::cout <<"cont="<<cont<<std::endl;
  myNewBMatrix.row(0)<< B.row(0);
  std::cout <<"cont="<<cont<<std::endl;
  for (int i=1;i< sizeB ;i++){
	  //std::cout <<"i="<<i<<std::endl;
	  if ((B.row(i))(0) > (A.row(i))(0)){

		  //for x coordinate
		  double y2= (B.row(i-1))(1);
		  double x = (A.row(i))(0);
		  double x2= (B.row(i-1))(0);
		  double y3= (B.row(i))(1);
		  double x3= (B.row(i))(0);
		  double y = this->interpolateValue(x,x2,y2,x3,y3);
		  Vector4d myNewVector(x,y,y,y);
		  //this->insertRowInSequence(B,myNewVector,i);
          myNewBMatrix.row(i)<< myNewVector.transpose();
          myNewBMatrix.row(i+1)<< B.row(i);
          cont++;
          //std::cout <<"iSecret="<<iSecret<<std::endl;
		  //double newTimeB= (B.row(i-1).(0) + B.row(i).(0))/2;
		  //double newX = (B.row(i-1).(1) + B.row(i).(1))/2;
		  //double newY = (B.row(i-1).(2) + B.row(i).(2))/2;
		  //double newZ = (B.row(i-1).(3) + B.row(i).(3))/2;
		  //VectorX4d myNewVector(newTimeB,newX,newY,newZ);
		  //this.insertRowInSequence(B,myNewVector,i);


	  } else {
		  //myNewBMatrix.row(cont)<< B.row(i);
		  myNewBMatrix.row(i+cont)<< B.row(i);
	  }
	  //cont++;
  }
  std::cout <<"cont="<<cont<<std::endl;
  B = myNewBMatrix.block(0,0,myNewBMatrix.rows(),4);


}
*/
void Interpolator::reduceSequence(int maxLine, MatrixXd& aMatrix , int numberToDelete){
	/*This method deletes a number of lines of a matrix
	 * The lines are selected randomly
	 * The shrunk matrix,  is returned.
	 */

	int iSecret;
    const double MaxValue=99999999999;
	/* initialize random seed: */
	srand (time(NULL));
    for (int i=0;i<numberToDelete;i++) {
		/* generate secret number between 1 and 10: */
		iSecret = rand() % aMatrix.rows() ;
		std::cout <<"iSecret="<<iSecret<<std::endl;
		aMatrix(iSecret,0)=MaxValue;
		std::cout <<"aMatrix(iSecret,0)="<<aMatrix(iSecret,0)<<std::endl;
    }
    MatrixXd myNewMatrix (aMatrix.rows(),4);
    int cont=0;
    for (int i=0;i<aMatrix.rows();i++){
    	std::cout <<"aMatrix(i,0)="<<aMatrix(i,0)<<std::endl;
    	if (aMatrix(i,0)< MaxValue){
    		std::cout <<"encontrado="<<aMatrix(i,0)<<std::endl;
    		myNewMatrix.row(cont) <<  aMatrix.row(i);
    		cont++;
    	}

    }


    std::cout <<"cont="<<cont<<std::endl;
    aMatrix = myNewMatrix.block(0,0,cont,4);
    //std::cout <<"aMatrix="<<aMatrix<<std::endl;



}


int main(){

	std::cout <<"	Starting main of  Interpolator="<<std::endl;
	Interpolator myInterpolator;

	double offset = 28;
	int maxLine = 2500;
	int intervalo = 200;
	MatrixXd readingA (maxLine,4);
	MatrixXd readingB (maxLine,4);
    //Read Files for sequence A and Sequence B

	std::cout <<"1="<<std::endl;
	std::cout << std::setprecision(6) << std::fixed;
	std::ifstream infileA( "/home/tfm3/workspace/Interpolator/miEntradaA.txt" );
	//inputFile >> std::setprecision(6) >> std::fixed;
	std::cout << std::setprecision(6) << std::fixed;
	std::ifstream infileB( "/home/tfm3/workspace/Interpolator/miEntradaB.txt" );
	//inputFile >> std::setprecision(6) >> std::fixed;
	std::cout <<"2="<<std::endl;
	std::cout << std::setprecision(6) << std::fixed;
	std::ofstream outA( "/home/tfm3/workspace/Interpolator/miSalidaA.txt" );
	outA << std::setprecision(6) << std::fixed;
	std::cout << std::setprecision(6) << std::fixed;
	std::ofstream outB( "/home/tfm3/workspace/Interpolator/miSalidaB.txt" );
	outB << std::setprecision(6) << std::fixed;
	std::ofstream outBbeforeInterpolate( "/home/tfm3/workspace/Interpolator/myOutputBbeforeInterpolate.txt" );
	outBbeforeInterpolate << std::setprecision(6) << std::fixed;
	std::cout <<"3="<<std::endl;

	double timestamp,rx,ry,rz,q1,q2,q3,q4=0;
	int contLin=0;
	std::cout <<"4="<<std::endl;
	while ( (infileA >> timestamp >> rx >> ry >> rz >> q1 >> q2 >> q3 >> q4) && contLin<maxLine ){
		        std::cout <<"contLin="<<contLin<<std::endl;
			    readingA.row(contLin)<<timestamp, rx,ry,rz;
			    //std::cout <<"contLin="<<contLin<<std::endl;
				contLin ++;


	}
    infileA.close();
	MatrixXd A (contLin,4);
	A = readingA.block(0,0,contLin,4);

	contLin=0;

	while ( (infileB >> timestamp >> rx >> ry >> rz >> q1 >> q2 >> q3 >> q4) && contLin<maxLine ){
				    readingB.row(contLin)<<timestamp, rx,ry,rz;

					contLin ++;

	}
	infileB.close();
	MatrixXd B (contLin,4);
	B = readingB.block(0,0,contLin,4);



	/*MatrixXd m(4,4);
    m <<  1, 2, 3, 4,
	      5, 6, 7, 8,
	      9,10,11, 8,
          12,13,14, 15;
    Vector4d v(4,4,4,4);
    */

    //MatrixXd newMatrix (5,3);

    //std::cout <<"newMatrix="<<newMatrix<<std::endl;

	//myInterpolator.interpolate(maxLine, A,B);
	//std::cout <<"B="<<B<<std::endl;




    //myInterpolator.insertRowInSequence(m,v,2);
    //std::cout <<"m="<<m<<std::endl;
    int valuesToReduce = 2450;
	myInterpolator.reduceSequence(maxLine,B, valuesToReduce);

	valuesToReduce = 2450;
	myInterpolator.reduceSequence(maxLine,A, valuesToReduce);

    std::cout <<"before interpolate"<<std::endl;

    // Save Serie B into a file , before interpolate.  Later compare graphically
    for (int i= 0; i< B.rows(); i++){
    					//std::cout <<"i="<<i<<std::endl;
    					//std::cout <<"centered.row(i)="<<B.row(i)<<std::endl;


    					VectorXd bRow = B.row(i);
    					outBbeforeInterpolate << bRow(0)<<" "<<bRow(1)<<" "<<bRow(2)<<" "<<bRow(3)<<"\n";

    }
    outBbeforeInterpolate.close();

	myInterpolator.interpolate2Series(maxLine, A,B);
	std::cout <<"after interpolate"<<std::endl;
	std::cout <<"B has"<<B.rows()<<"rows"<<std::endl;

    //Save data A
	for (int i= 0; i< A.rows(); i++){
				//std::cout <<"i="<<i<<std::endl;
				//std::cout <<"centered.row(i)="<<A.row(i)<<std::endl;

				VectorXd aRow = A.row(i);
				outA << aRow(0)<<" "<<aRow(1)<<" "<<aRow(2)<<" "<<aRow(3)<<"\n";



		}
	// Save data B
	for (int i= 0; i< B.rows(); i++){
					//std::cout <<"i="<<i<<std::endl;
					//std::cout <<"centered.row(i)="<<B.row(i)<<std::endl;


					VectorXd bRow = B.row(i);
					outB << bRow(0)<<" "<<bRow(1)<<" "<<bRow(2)<<" "<<bRow(3)<<"\n";

			}
	outA.close();
	outB.close();



}


