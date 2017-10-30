#include "Point3D.h"

class Transformador {
private:

	double timestamp,rx,ry,rz,q1,q2,q3,q4;
	//Point3D myPoint3D (3.0,3.0,3.0);
	Point3D myPoint3D;
	double matRot [4] [4] = {
	    {0.0}
	};

	double matRotTrasla [4][4] = {
		{1.0, 0.0 , 0.0, 0.0},
		{0.0, 1.0 , 0.0, 0.0},
		{0.0, 0.0 , 1.0, 0.0},
		{0.0, 0.0 , 0.0, 1.0}

	};

	double traslacion [4] [4] = {

	    {1.0, 0.0 , 0.0, 0.0},
	    {0.0, 1.0 , 0.0, 0.0},
	    {0.0, 0.0 , 1.0, 0.0},
	    {0.0, 0.0 , 0.0, 1.0}

	};

	double identidad [4] [4] = {

	    {1.0, 0.0 , 0.0, 0.0},
	    {0.0, 1.0 , 0.0, 0.0},
	    {0.0, 0.0 , 1.0, 0.0},
	    {0.0, 0.0 , 0.0, 1.0}

	};

	double punto [4] [1] = {
	    {10.0},
	    {10.0},
	    {10.0},
	    {1.0}
	};
	//float punto [4] [1] = {0.0};
	double newPunto [4]  [1] = { {0.0},
		    {0.0},
		    {0.0},
		    {0.0} };

public:
	void createMatRotTrasla ( char eje , float angulo, Point3D trasla) ;
	void createMatRot ( char eje , float angulo) ;
	Point3D multiplicaMatrizPunto (double matriz [4][4], double unPunto[4][1], int colsMatriz, int rowsMatriz, int colsUnPunto , int rowsUnPunto);
	Point3D multiplicaMatrizPunto (double unPunto[4][1], int colsUnPunto , int rowsUnPunto);
	void multiplicaMatrizPorMatriz (double matrizA [4][4], double matrizB[4][4], int colsMatrizA, int rowsMatrizA, int colsMatrizB , int rowsMatrizB);
	void setPoint3D (Point3D aPoint3D);
	void setTraslacion (Point3D aPoint3D);
	void displayMatriz (double matriz [4][4], int matriz_rows, int matriz_cols);
	void displayMatrizRotTrasla ();



};
