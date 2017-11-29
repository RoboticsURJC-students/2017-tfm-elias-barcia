#ifndef REGISTRADOR_H
#define REGISTRADOR_H
#include <iostream>
#include "Eigen/Dense"
using namespace Eigen;
//using namespace std;

class Registrador {
private:
	MatrixXd m;

public:
   Registrador () ;
   void demoPresentaMatriz(); // Constructor with default arguments
   void rigid_transform_3D (MatrixXd A, MatrixXd B, MatrixXd& R, MatrixXd& t);

};
#endif
