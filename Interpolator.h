#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H
#include <iostream>
#include "Eigen/Dense"
using namespace Eigen;
//using namespace std;

class Interpolator {
private:
	MatrixXd m;

public:
   Interpolator ();
   //void genera2Series(int maxLine, double proporcionFrecuencia,double offset, MatrixXd& A, MatrixXd& B);
   //void calcularAutocorrelacion(int maxLine,int intervalo, double offset, MatrixXd&A, MatrixXd&B);
   //void calcularAutocorrelacion2(int maxLine,int intervalo, double offset, MatrixXd&A, MatrixXd&B);
   //void calcularAutocorrelacion3(char coordinate, int maxLine, int intervalo,double offset, MatrixXd& A1, MatrixXd& B2);
   void interpolate(int maxLine, MatrixXd& A, MatrixXd& B);
   void reduceSequence (int maxLine, MatrixXd& aMatrix, int numberToDelete);
   //MatrixXd insertRowInSequence (MatrixXd& C, VectorXd myVector, int position);
   void insertRowInSequence (MatrixXd& C, VectorXd myVector, int position);
   double interpolateValue (double x,double x2,double y2,double x3,double y3);
   void interpolate2Series(int maxLine, MatrixXd& A, MatrixXd& B);



};
#endif
