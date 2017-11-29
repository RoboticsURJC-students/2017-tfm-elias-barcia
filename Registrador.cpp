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
		std::cout << "A \n"<< A <<std:: endl;

		std::cout <<centroidA <<std::endl;
		std::cout << "AA \n"<< AA << std::endl;

		std::cout << "B \n"<< B << std::endl;

		std::cout <<centroidB <<std::endl;
		std::cout << "BB \n"<< BB << std::endl;

		H= AA.transpose() * BB;



		std::cout << "H \n"<< H << std::endl;

		//JacobiSVD<MatrixXd> svd(H, ComputeFullU | ComputeFullV);
		JacobiSVD<MatrixXd> svd(H, ComputeFullU | ComputeFullV);
		//BDCSVD<MatrixXd> svd(H, ComputeFullU | ComputeFullV);
		U=svd.matrixU();
		V=svd.matrixV();
		S=svd.singularValues();
		MatrixXd neoA = U*S.asDiagonal()*V.transpose();
		//MatrixXd neoA = neoA * V;
				//*V.transpose();
		//MatrixXd neoA = U*S*V.transpose();
		std::cout << "neoA: \n" << neoA << std::endl;
		MatrixXd Vt = V.transpose();
		std::cout << "U: \n" << U << std::endl;;
		std::cout << "V: \n" << V << std::endl;;
		std::cout << "Vt: \n" << Vt << std::endl;
		std::cout << "S: \n" << S << std::endl;

		//R = V.transpose() * U.transpose();
		R = Vt.transpose() * U.transpose();
		std::cout << "R1: \n" << R <<std::endl;
		std::cout << "centroidA: " << centroidA <<std::endl;
		std::cout << "centroidB: " << centroidB <<std::endl;
		if (R.determinant() < 0){
			std::cout << "Detectadas reflections-------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>><"<<std::endl;
		       //Vt[2,:] *= -1
			    Vt.row(2) *= -1;
			    R = Vt.transpose() * U.transpose();
			    std::cout << "R2: \n" << R <<std::endl;
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

