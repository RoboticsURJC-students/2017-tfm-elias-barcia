#include <iostream>
#include <ctime>
#include <unistd.h>
#include <fstream>
#include <sys/time.h>
#include <iomanip>
#include <cmath>

#include "Point3D.h"
#include "Transformador.h"
//float traslacion [4] [4] = {0.0};

Point3D myPoint3D (3.0,3.0,3.0);
//Point3D myPoint3D ;

double timestamp,rx,ry,rz,q1,q2,q3,q4;

double matRot [4] [4] = {
    {0.0}
};

double matRotTrasla [4][4] = {

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
double newPunto [4]  [1] = {0.0};

void createMatRot ( char eje , float angulo) {

    float anguloRad = angulo * (float)M_PI / 180.0f;
    if (eje == 'X'){
        
        matRot[0][0]=1.0;
        matRot[0][1]=0.0;
        matRot[0][2]=0.0;
        matRot[0][3]=0.0;

        matRot[1][0]=0.0;
        matRot[1][1]=cosf(anguloRad);
        matRot[1][2]=sinf(anguloRad);
        matRot[1][3]=0.0;

        matRot[2][0]=0.0;
        matRot[2][1]=-sinf(anguloRad);
        matRot[2][2]=cosf(anguloRad);
        matRot[2][3]=0.0;

        matRot[3][0]=0.0;
        matRot[3][1]=0.0;
        matRot[3][2]=0.0;
        matRot[3][3]=1.0;




    }if (eje == 'Y'){
        
        matRot[0][0]=cosf(anguloRad);
        matRot[0][1]=0.0;
        matRot[0][2]=-sinf(anguloRad);
        matRot[0][3]=0.0;

        matRot[1][0]=0.0;
        matRot[1][1]=1.0;
        matRot[1][2]=0.0;
        matRot[1][3]=0.0;

        matRot[2][0]=sinf(anguloRad);
        matRot[2][1]=0.0;
        matRot[2][2]=cosf(anguloRad);
        matRot[2][3]=0.0;

        matRot[3][0]=0.0;
        matRot[3][1]=0.0;
        matRot[3][2]=0.0;
        matRot[3][3]=1.0;

    } else if (eje == 'Z') {

        matRot[0][0]=cosf(anguloRad);
        matRot[0][1]=sinf(anguloRad);
        matRot[0][2]=0.0;
        matRot[0][3]=0.0;

        matRot[1][0]=-sinf(anguloRad);
        matRot[1][1]=cosf(anguloRad);
        matRot[1][2]=0.0;
        matRot[1][3]=0.0;

        matRot[2][0]=0.0;
        matRot[2][1]=0.0;
        matRot[2][2]=1.0;
        matRot[2][3]=0.0;

        matRot[3][0]=0.0;
        matRot[3][1]=0.0;
        matRot[3][2]=0.0;
        matRot[3][3]=1.0;

    }
};

void displayPunto (double unPunto [4][1]) {
    std::cout<<"displayPunto\n";
    std::cout<<"\n"<<unPunto[0][0];
    std::cout<<"\n"<<unPunto[1][0];
    std::cout<<"\n"<<unPunto[2][0];
    std::cout<<"\n"<<unPunto[3][0];
};

void displayMatriz (double unaMatriz [4] [4] ) {
    std::cout<<"displayMatriz\n";


};

void multiplicaMatrizPunto (double matriz [4][4], double unPunto[4][1], int colsMatriz, int rowsMatriz, int colsUnPunto , int rowsUnPunto){

        
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

};

void multiplicaMatrizPorMatriz (double matrizA [4][4], double matrizB[4][4], int colsMatrizA, int rowsMatrizA, int colsMatrizB , int rowsMatrizB){
    
    
    int a_cols=colsMatrizA;
    int b_rows=rowsMatrizB;
    int a_rows=rowsMatrizA;
    int b_cols=colsMatrizB;

    if (a_cols == b_rows){
       // std::cout << "\nThe number of cols in the first array is same as the number of rows in the second array, \nThe multiplication is possible\n";
        //initialize the final array
        //int c[a_rows][b_cols];
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

};


int main( int argc, char** argv )
{  
   
        
    std::cout << std::setprecision(6) << std::fixed;
    std::ofstream out( "miEntradaModificada.txt" );
    out << std::setprecision(6) << std::fixed;



    int contLin=0;
    Transformador myTransformador;
    for (contLin=0;contLin <50; contLin++  ){
    // FOR READING FILE AND DRAW CURVE
    std::ifstream infile("mientrada.txt");
    std::string line;
    infile >> std::setprecision(6) >> std::fixed;

    //createMatRot('Z',10*contLin);
    //multiplicaMatrizPorMatriz (matRot,traslacion,4,4,4,4);// el resultado quedara en matRotTrasla
    Point3D traslacion(0,0,0.2*contLin);
    myTransformador.createMatRotTrasla('Z',10*contLin,traslacion);
    myTransformador.displayMatrizRotTrasla();
    std::cout << "beFORE WHILE";
    while ( infile >> timestamp >> rx >> ry >> rz >> q1 >> q2 >> q3 >> q4 ){
        std::cout << "You said.... contLin"<< contLin << timestamp << " " << rx << " " << ry << " " << rz << " " << q1 << " " << q2 << " " << q3 << " " << q4 << "\n";
    	myPoint3D.setX(rx);
    	myPoint3D.setY(ry);
    	myPoint3D.setZ(rz);

    	myTransformador.setPoint3D(myPoint3D);

        punto[0][0]=myPoint3D.getX();
        punto[1][0]=myPoint3D.getY();
        punto[2][0]=myPoint3D.getZ();
        punto[3][0]=1;
        
        //multiplicaMatrizPunto (traslacion,punto,4,4,1,4);
        //myPoint3D=myTransformador.multiplicaMatrizPunto(matRotTrasla,punto,4,4,1,4);
        myPoint3D=myTransformador.multiplicaMatrizPunto(punto,1,4);
        //multiplicaMatrizPunto (matRotTrasla,punto,4,4,1,4);
        //contLin++;
        //out <<  timestamp <<" "<< rx <<" "<< ry <<" "<<rz<<"\n"<<std::endl;

        //out <<timestamp <<" "<< newPunto[0][0] <<" "<< newPunto[1][0] <<" "<< newPunto[2][0] << q1 << q2 << q3 << q4<<std::endl;
        out <<timestamp <<" "<< myPoint3D.getX() <<" "<< myPoint3D.getY() <<" "<< myPoint3D.getZ() << q1 << q2 << q3 << q4<<std::endl;

    }
    infile.close();
    std::cout << ">>>>>>>CIERROR INFILE\n";
    }

    //multiplicaMatrizPunto (traslacion,punto,4,4,1,4);
    //displayPunto(newPunto);
    
    //multiplicaMatrizPorMatriz (matRot,traslacion,4,4,4,4);
    out.close();
    //infile.close();

    return 0;
}
