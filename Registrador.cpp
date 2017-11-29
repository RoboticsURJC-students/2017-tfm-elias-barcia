#include "Registrador.h"
#include <iostream>
#include "Eigen/SVD"
//#include "Eigen/Dense"
//using namespace Eigen;
//using namespace std;

Registrador::Registrador(){
	std::cout<< "constructor por defecto" <<std::endl;
}//

 void Registrador::rigid_transform_3D(MatrixXd A, MatrixXd B , MatrixXd& R, MatrixXd& t){
	// comparar tamaño de Matrices A y B
    int N=0;
    Matrix3d AA, BB , mCentroidA, mCentroidB;
    MatrixXd H,  U , V ,S;

    std::cout<<"rigid_transform_3D 1"<<std::endl;
    if (A.cols()*A.rows() == B.cols()* B.rows()) { // the 2 arrays have similar size
    	MatrixXd AA(A.rows(),A.cols()), BB (B.rows(),B.cols()) , mCentroidA(A.rows(),A.cols()), mCentroidB(B.rows(),B.cols());

		N = A.rows(); // total points

		double centroidAX= VectorXd(A.col(0)).mean();
		double centroidAY= VectorXd(A.col(1)).mean();
		double centroidAZ= VectorXd(A.col(2)).mean();

		Vector3d centroidA(centroidAX,centroidAY,centroidAZ);

		double centroidBX= VectorXd(B.col(0)).mean();
		double centroidBY= VectorXd(B.col(1)).mean();
		double centroidBZ= VectorXd(B.col(2)).mean();

		Vector3d centroidB(centroidBX,centroidBY,centroidBZ);

		for (int i=0; i< N; i++ ) {
			//AA.row(i) = Vector3d(A.row(i)) - centroidA ;
			mCentroidA.row(i) << centroidAX ,centroidAY,centroidAZ ;

		}

		for (int j=0; j< N; j++ ) {
			//BB.row(j) = Vector3d(B.row(j)) - centroidB ;
			mCentroidB.row(j) << centroidBX ,centroidBY,centroidBZ ;

		}
        AA= A - mCentroidA;
        BB= B - mCentroidB;
		std::cout << "A "<< A <<std:: endl;

		std::cout <<centroidA <<std::endl;
		std::cout << "AA "<< AA << std::endl;

		std::cout << "B "<< B << std::endl;

		std::cout <<centroidB <<std::endl;
		std::cout << "BB "<< BB << std::endl;

		H= AA.transpose() * BB;



		std::cout << "H "<< H << std::endl;

		//JacobiSVD<MatrixXd> svd(H, ComputeFullU | ComputeFullV);
		BDCSVD<MatrixXd> svd(H, ComputeFullU | ComputeFullV);
		U=svd.matrixU();
		V=svd.matrixV();
		S=svd.singularValues();
		std::cout << "U: " << U << std::endl;;
		std::cout << "V: " << V << std::endl;;
		std::cout << "S: " << S << std::endl;

		R = V.transpose() * U.transpose();
		std::cout << "R: " << R <<std::endl;
		std::cout << "centroidA: " << centroidA <<std::endl;
		std::cout << "centroidB: " << centroidB <<std::endl;
		if (R.determinant() < 0){
			std::cout << "Detectadas reflections-------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>><"<<std::endl;
		       //Vt[2,:] *= -1
			    V.row(2) *= -1;
			    R = V.transpose() * U.transpose();
		}
		//t = -R * mCentroidA.transpose() + mCentroidB.transpose();
		//t = -R * centroidA.transpose() + centroidB.transpose();
		//t = -R * centroidA.transpose();
		t = -R * centroidA + centroidB;
		std::cout <<"t "<< t <<std:: endl;

		//return R, t

		//Hallar los centroides de A y  B
		//centroid_A = mean(A, axis=0)
		//centroid_B = mean(B, axis=0)

		// Diferencia de los centroides
		//AA = A - tile(centroid_A, (N, 1))
		//BB = B - tile(centroid_B, (N, 1))

		//print "AA shape";
		//print  AA.shape;
		//print BB.shape;

		//# dot is matrix multiplication for array

		//H = transpose(AA)* BB

		//Hallar SVD
		//U, S, Vt = linalg.svd(H)

		//R = Vt.T * U.T

		//# special reflection case
		//if linalg.det(R) < 0:
		  // print "Reflection detected"
		  //Vt[2,:] *= -1
		  // R = Vt.T * U.T

		//t = -R*centroid_A.T + centroid_B.T

		//print t

		//return R, t
    }
}


void Registrador::demoPresentaMatriz() {

  MatrixXd m = MatrixXd::Random(3,3);
  //m = (m + MatrixXd::Constant(3,3,1.2)) * 50;
  std::cout << "m =" <<  m <<std::endl;
  VectorXd v(3);
  v << 1, 2, 3;
  std::cout << "m * v =" <<  m * v <<std::endl;

}

