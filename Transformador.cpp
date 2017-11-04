#include <iostream>
#include <ctime>
#include <unistd.h>
#include <fstream>
#include <sys/time.h>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <limits>

#include "Point3D.h"
#include "Transformador.h"




void Transformador::displayMatriz (double matriz [4][4], int matriz_rows, int matriz_cols){

	std::cout<<"-----------------------------------------------display Matriz Rotacion-traslacion\n\n";
	for(int i=0;i<matriz_rows;i++)
            {
                for(int j=0;j<matriz_cols;j++)
                {
                    std::cout<<"\t"<<matriz[i][j];
                }
                std::cout<<"\n\n";
            }

}

void Transformador::displayMatrizRotTrasla (){
	displayMatriz(matRotTrasla,4,4);
}
void Transformador::createMatRotTrasla ( char eje , float angulo, Point3D aPoint3D){
	createMatRot( eje, angulo);
	setTraslacion( aPoint3D);

}
void Transformador::createMatRot ( char eje , float angulo) {
	float anguloRad = angulo * (float)M_PI / 180.0f;

	    if (eje == 'X'){

	        matRotTrasla[0][0]=1.0;
	        matRotTrasla[0][1]=0.0;
	        matRotTrasla[0][2]=0.0;
	        matRotTrasla[0][3]=0.0;

	        matRotTrasla[1][0]=0.0;
	        matRotTrasla[1][1]=cosf(anguloRad);
	        matRotTrasla[1][2]=sinf(anguloRad);
	        matRotTrasla[1][3]=0.0;

	        matRotTrasla[2][0]=0.0;
	        matRotTrasla[2][1]=-sinf(anguloRad);
	        matRotTrasla[2][2]=cosf(anguloRad);
	        matRotTrasla[2][3]=0.0;

	        matRotTrasla[3][0]=0.0;
	        matRotTrasla[3][1]=0.0;
	        matRotTrasla[3][2]=0.0;
	        matRotTrasla[3][3]=1.0;

	    }if (eje == 'Y'){

	    	matRotTrasla[0][0]=cosf(anguloRad);
	    	matRotTrasla[0][1]=0.0;
	    	matRotTrasla[0][2]=-sinf(anguloRad);
	    	matRotTrasla[0][3]=0.0;

	    	matRotTrasla[1][0]=0.0;
	    	matRotTrasla[1][1]=1.0;
	    	matRotTrasla[1][2]=0.0;
	    	matRotTrasla[1][3]=0.0;

	    	matRotTrasla[2][0]=sinf(anguloRad);
	    	matRotTrasla[2][1]=0.0;
	    	matRotTrasla[2][2]=cosf(anguloRad);
	    	matRotTrasla[2][3]=0.0;

	    	matRotTrasla[3][0]=0.0;
	    	matRotTrasla[3][1]=0.0;
	    	matRotTrasla[3][2]=0.0;
	    	matRotTrasla[3][3]=1.0;

	    } else if (eje == 'Z') {

	    	matRotTrasla[0][0]=cosf(anguloRad);
	    	matRotTrasla[0][1]=sinf(anguloRad);
	    	matRotTrasla[0][2]=0.0;
	    	matRotTrasla[0][3]=0.0;

	    	matRotTrasla[1][0]=-sinf(anguloRad);
	    	matRotTrasla[1][1]=cosf(anguloRad);
	    	matRotTrasla[1][2]=0.0;
	    	matRotTrasla[1][3]=0.0;

	    	matRotTrasla[2][0]=0.0;
	    	matRotTrasla[2][1]=0.0;
	    	matRotTrasla[2][2]=1.0;
	    	matRotTrasla[2][3]=0.0;

	    	matRotTrasla[3][0]=0.0;
	    	matRotTrasla[3][1]=0.0;
	    	matRotTrasla[3][2]=0.0;
	    	matRotTrasla[3][3]=1.0;

	    }

}

Point3D Transformador::multiplicaMatrizPunto (double unPunto[4][1], int colsUnPunto , int rowsUnPunto){
//void Transformador::multiplicaMatrizPunto (double matriz [4][4], Point3D unPunto3D, int colsMatriz, int rowsMatriz, int colsUnPunto , int rowsUnPunto){


	       Point3D aPoint3D;

	       int matriz_cols = 4;
	       int unPunto_rows = rowsUnPunto;
	       int matriz_rows  = 4;
	       int unPunto_cols = colsUnPunto;

	        if (matriz_cols == unPunto_rows){
	            std::cout << "\nThe number of cols in the first array is same as the number of rows in the second array, \nThe multiplication is possible\n";
	            //initialize the final array
	            matriz_rows=4;
	            unPunto_cols=1;
	            //float c[][1]={0.0};

	            int i, j , k;
	            for (i=0;i<matriz_rows; i++) {

	                for (j=0;j<unPunto_cols;j++) {

	                    newPunto[i][j]=0;

	                    for (k=0;k<unPunto_rows;k++) {

	                        newPunto[i][j] += matRotTrasla[i][k]*unPunto[k][j];

	                    }
	                }
	            }
                aPoint3D.setXYZ(newPunto[0][0],newPunto[1][0],newPunto[2][0]);
	            std::cout << "\nthe final array has been created\n\n";
	            std::cout << "time to see the results \n";


	           /*for(i=0;i<matriz_rows;i++)
	            {
	                for(j=0;j<unPunto_cols;j++)
	                {
	                    std::cout<<"\t"<<c[i][j];
	                }
	                std::cout<<"\n\n";
	            }
	            */
	        }
	        else{
	            std::cout << "Multiplication of the two array is not possible";
	        }
	        return aPoint3D;

}
Point3D Transformador::multiplicaMatrizPunto (double matriz [4][4], double unPunto[4][1], int colsMatriz, int rowsMatriz, int colsUnPunto , int rowsUnPunto){
//void Transformador::multiplicaMatrizPunto (double matriz [4][4], Point3D unPunto3D, int colsMatriz, int rowsMatriz, int colsUnPunto , int rowsUnPunto){


	       Point3D aPoint3D;

	       int matriz_cols = colsMatriz;
	       int unPunto_rows = rowsUnPunto;
	       int matriz_rows  = rowsMatriz;
	       int unPunto_cols = colsUnPunto;

	        if (matriz_cols == unPunto_rows){
	            std::cout << "\nThe number of cols in the first array is same as the number of rows in the second array, \nThe multiplication is possible\n";
	            //initialize the final array
	            matriz_rows=4;
	            unPunto_cols=1;
	            //float c[][1]={0.0};

	            int i, j , k;
	            for (i=0;i<matriz_rows; i++) {

	                for (j=0;j<unPunto_cols;j++) {

	                    newPunto[i][j]=0;

	                    for (k=0;k<unPunto_rows;k++) {

	                        newPunto[i][j] += matriz[i][k]*unPunto[k][j];

	                    }
	                }
	            }
                aPoint3D.setXYZ(newPunto[0][0],newPunto[1][0],newPunto[2][0]);
	            std::cout << "\nthe final array has been created\n\n";
	            std::cout << "time to see the results \n";


	           /*for(i=0;i<matriz_rows;i++)
	            {
	                for(j=0;j<unPunto_cols;j++)
	                {
	                    std::cout<<"\t"<<c[i][j];
	                }
	                std::cout<<"\n\n";
	            }
	            */
	        }
	        else{
	            std::cout << "Multiplication of the two array is not possible";
	        }
	        return aPoint3D;

}

void Transformador::multiplicaMatrizPorMatriz (double matrizA [4][4], double matrizB[4][4], int colsMatrizA, int rowsMatrizA, int colsMatrizB , int rowsMatrizB){
	    int a_cols=colsMatrizA;
	    int b_rows=rowsMatrizB;
	    int a_rows=rowsMatrizA;
	    int b_cols=colsMatrizB;

	    if (a_cols == b_rows){
	       // std::cout << "\nThe number of cols in the first array is same as the number of rows in the second array, \nThe multiplication is possible\n";
	        //initialize the final array
	        int c[a_rows][b_cols];
	        int i, j,k;
	        for (i=0;i<a_rows; i++){
	            for (j=0;j<b_cols;j++){
	                //c[i][j]=0;
	                matRotTrasla[i][j]=0;
	                for (k=0;k<b_rows;k++){
	                    matRotTrasla[i][j] += matrizA[i][k]*matrizB[k][j];
	                }
	            }
	        }
	        //std::cout << "\nthe final array has been created\n\n";
	        //std::cout << "time to see the results \n";

	       for(i=0;i<a_rows;i++)
	        {
	            for(j=0;j<b_cols;j++)
	            {
	                std::cout<<"\t"<<matRotTrasla[i][j];
	            }
	            std::cout<<"\n\n";
	        }
	    }
	    else{
	        std::cout << "Multiplication of the two array is not possible";
	    }




}

void Transformador::setTraslacion (Point3D aPoint3D){
	matRotTrasla[0][3]= aPoint3D.getX();
	matRotTrasla[1][3]= aPoint3D.getY();
	matRotTrasla[2][3]= aPoint3D.getZ();
}
void Transformador::setPoint3D (Point3D aPoint3D){
	this->myPoint3D.setXYZ(aPoint3D.getX(),aPoint3D.getY(),aPoint3D.getZ());

}

double Transformador::generateGaussianNoise(double mu, double sigma)
{
	static const double epsilon = std::numeric_limits<double>::min();
	static const double two_pi = 2.0*3.14159265358979323846;

	double z1;
	bool generate;
	generate = !generate;

	if (!generate)
	   return z1 * sigma + mu;

	double u1, u2;
	do
	 {
	   u1 = rand() * (1.0 / RAND_MAX);
	   u2 = rand() * (1.0 / RAND_MAX);
	 }
	while ( u1 <= epsilon );

	double z0;
	z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
	return z0 * sigma + mu;
}

