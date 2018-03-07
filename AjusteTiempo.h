#ifndef AJUSTETIEMPO_H
#define AJUSTETIEMPO_H
#include <iostream>
#include "Eigen/Dense"
using namespace Eigen;
//using namespace std;

class AjusteTiempo {
private:
	MatrixXd m;

public:
   AjusteTiempo () ;
   void demoPresentaMatriz(); // Constructor with default arguments
   void rigid_transform_3D (MatrixXd A, MatrixXd B, MatrixXd& R, MatrixXd& t);
   void getScalaRansac(MatrixXd AA, MatrixXd BB, int ContLin);
   void genera2Series(double proporcionFrecuencia,double offset, MatrixXd& A, MatrixXd& B);
   Vector3d getScalaEigenValues(MatrixXd AA, MatrixXd BB);
   Vector3d getScalaSVD(MatrixXd AA, MatrixXd BB);

};
#endif