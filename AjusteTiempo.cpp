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
#include "AjusteTiempo.h"


AjusteTiempo::AjusteTiempo(){
	std::cout<< "constructor por defecto AjusteTiempo" <<std::endl;
}



void AjusteTiempo::calcularAutocorrelacion(int maxLine, int intervalo,double offset, MatrixXd& A1, MatrixXd& B2)

{
	// offset: define la separación de la segunda serie que sera una serie artificial. La segunda serie S2 = S1 + offset
	// intervalo: define la amplitud de la ventana desde la que buscaremos la correlación
	// maxLine : numero máximo de líneas


    std::cout << std::setprecision(6) << std::fixed;
    std::ofstream outA( "/home/tfm3/workspace/AjusteTiempo/miSalidaA.txt" );
    outA << std::setprecision(6) << std::fixed;

    std::cout << std::setprecision(6) << std::fixed;
    std::ofstream outB( "/home/tfm3/workspace/AjusteTiempo/miSalidaB.txt" );
    outB << std::setprecision(6) << std::fixed;

	std::cout <<"antes de declarar la variable"<<std::endl;
	//int maxLine = 30;
	MatrixXd readingA (maxLine,4);//size is big enough to store an unknown number of data rows from file
	MatrixXd readingB (maxLine,4);
	VectorXd vTiempoA (maxLine), vSerieA (maxLine) ;
	VectorXd vTiempoB (maxLine), vSerieB (maxLine) ;
	//read a file
	int contLin=0;
	double timestamp,rx,ry,rz,q1,q2,q3,q4=0;
	double mediaTiempoA, mediaTiempoB, mediaSerieA, mediaSerieB;
	std::cout <<"antes de leer el archivo"<<std::endl;
	//int miOffset=5;
    double miOffset = offset;
    double newContLin = 0;
    std::cout <<"miOffset="<<miOffset<<std::endl;
	//while ( (infile >> timestamp >> rx >> ry >> rz >> q1 >> q2 >> q3 >> q4) && contLin<maxLine ){
	while (  contLin<maxLine ){
		    //std::cout <<"contLin="<<contLin<<std::endl;

	//while ( infile >> rx >> ry >> rz  ){
			//std::cout << "You said.... contLin"<< contLin << timestamp << " " << rx << " " << ry << " " << rz << " " << q1 << " " << q2 << " " << q3 << " " << q4 << "\n";
			//VectorXd myVector (rx,ry,rz);
			//readingA.row(contLin)= myVector;
		    //create sequence 1, two variables , T (time), X
			//readingA.row(contLin)<< timestamp,rx,ry,rz;
			//readingA.row(contLin)<< contLin,rx,ry,rz;
		    readingA.row(contLin)<< contLin,sin(contLin),ry,rz;
		    vTiempoA.row(contLin) << contLin;
		    vSerieA.row(contLin) << sin(contLin);
			//vTiempoA.row(contLin) << timestamp;
			//create sequence 2, two varialbes,  T+offset , X
			//readingB.row(contLin)<< timestamp+miOffset,rx,ry,rz;
		    newContLin= contLin+miOffset;
		    std::cout <<"newContLin="<<newContLin<<std::endl;
			readingB.row(contLin)<< newContLin,sin(contLin),ry,rz;
			vTiempoB.row(contLin) << newContLin;
			vSerieB.row(contLin) << sin(contLin);

			outA << contLin <<" "<< sin(contLin) <<" "<< ry <<" "<< rz <<" "<< q1 <<" "<< q2 <<" "<<q3 <<" "<< q4<<std::endl;
			outB << newContLin <<" "<< sin(contLin) <<" "<< ry <<" "<< rz <<" "<< q1 <<" "<< q2 <<" "<<q3 <<" "<< q4<<std::endl;
			contLin ++;

	}

	outA.close();
	outB.close();
	contLin=maxLine;
	std::cout <<"contLin="<<contLin<<std::endl;
	//Calcular autoCorrelacion
	MatrixXd A (contLin,3);
	MatrixXd B (contLin,3);
	A = readingA.block(0,0,contLin,3);
	B = readingB.block(0,0,contLin,3);
	mediaTiempoA = vTiempoA.mean();
	std::cout <<"	mediaTiempoA="<<	mediaTiempoA<<std::endl;

	mediaTiempoB = vTiempoB.mean();
	std::cout <<"	mediaTiempoB="<<	mediaTiempoB<<std::endl;
	mediaSerieA = vSerieA.mean();
	std::cout <<"	mediaSerieA="<<	mediaSerieA<<std::endl;

	mediaSerieB = vSerieB.mean();
	std::cout <<"	mediaSerieB="<<	mediaSerieB<<std::endl;

	VectorXd centeredTA,centeredTB,totalCenteredT;
	//for (int i=0; i < contLin ; i++){
		//centeredTA.row(contLin)<< vTiempoA.array() - mediaTiempoA;

	//}
	centeredTA = vTiempoA.array() - mediaTiempoA;
	std::cout <<"	centeredTA="<<	centeredTA<<std::endl;
	centeredTB = vTiempoB.array() - mediaTiempoB;
	std::cout <<"	centeredTB="<<	centeredTB<<std::endl;

	//Serie
	VectorXd centeredSA,centeredSB,totalCenteredS;
		//for (int i=0; i < contLin ; i++){
			//centeredTA.row(contLin)<< vTiempoA.array() - mediaTiempoA;

		//}
	centeredSA = vSerieA.array() - mediaSerieA;
	std::cout <<"	centeredSA="<<	centeredSA<<std::endl;
	centeredSB = vSerieB.array() - mediaSerieB;
	std::cout <<"	centeredSB="<<	centeredSB<<std::endl;

	double denom=0,sx=0,sy=0;
	for ( int i=0; i < contLin; i++){
			//sx += centeredTA(i)*centeredTA(i);
			//sy += centeredTB(i)*centeredTB(i);
			sx += centeredSA(i)*centeredSA(i);
			sy += centeredSB(i)*centeredSB(i);
	}
	//denom = sqrt(sx*sy);
	denom = sqrt(sx*sy);

	/* Calculate the correlation series */
       double sxy=0, rMax=0;
       int j = 0,delayMax=0;

	  for (int delay=-intervalo;delay<=intervalo;delay++) {
		  sxy = 0;
		  for (int i=0;i<contLin;i++) {
			 j = i + delay;
			 if (j < 0 || j >= maxLine)
				continue;
			 else
				//sxy += (vTiempoA[i] - mx) * (vTiempoB[j] - my);
				 //sxy += centeredTA[i] * centeredTB[j];
				 sxy += centeredSA[i] * centeredSB[j];

		  }



		  double r = sxy / denom;
          if ((r < 1 )&& (fabs(r) > rMax)){
        	  rMax=r;
        	  delayMax=delay;
          }
	      /* r is the correlation coefficient at "delay" */
		  std::cout <<"r ="<<fabs(r)<<std::endl;
         std::cout <<"delay ="<<delay<<std::endl;
		  //std::cout <<"i="<<i<<std::endl;
	   }
	  std::cout <<"rMax="<<rMax<<std::endl;
	  std::cout <<"delayMax="<<delayMax<<std::endl;


}

void AjusteTiempo::calcularAutocorrelacion2(int maxLine, int intervalo,double offset, MatrixXd& A1, MatrixXd& B2)

{
	// offset: define la separación de la segunda serie que sera una serie artificial. La segunda serie S2 = S1 + offset
	// intervalo: define la amplitud de la ventana desde la que buscaremos la correlación
	// maxLine : numero máximo de líneas


    std::cout << std::setprecision(6) << std::fixed;
    std::ofstream outA( "/home/tfm3/workspace/AjusteTiempo/miSalidaA.txt" );
    outA << std::setprecision(6) << std::fixed;

    std::cout << std::setprecision(6) << std::fixed;
    std::ofstream outB( "/home/tfm3/workspace/AjusteTiempo/miSalidaB.txt" );
    outB << std::setprecision(6) << std::fixed;

    std::cout << std::setprecision(6) << std::fixed;
    std::ofstream outRegresion( "/home/tfm3/workspace/AjusteTiempo/miSalidaRegresion.txt" );
    outRegresion << std::setprecision(6) << std::fixed;

	std::cout <<"antes de declarar la variable"<<std::endl;
	//int maxLine = 30;
	maxLine=maxLine;
	MatrixXd readingA (maxLine,4);//size is big enough to store an unknown number of data rows from file
	MatrixXd readingB (int(maxLine+offset),4);
	VectorXd vTiempoA (maxLine), vSerieA (maxLine) ;
	VectorXd vTiempoB (int(maxLine+offset)), vSerieB (int(maxLine+offset)) ;
	//read a file
	int contLin=0;
	double timestamp,rx,ry,rz,q1,q2,q3,q4=0;
	double mediaTiempoA, mediaTiempoB, mediaSerieA, mediaSerieB;
	std::cout <<"antes de leer el archivo"<<std::endl;
	//int miOffset=5;
    double miOffset = offset;
    double newContLin = 0;
    std::cout <<"miOffset="<<miOffset<<std::endl;
    /* initialize random seed: */
    srand (time(NULL));
	//while ( (infile >> timestamp >> rx >> ry >> rz >> q1 >> q2 >> q3 >> q4) && contLin<maxLine ){
    double aleatorio =0, valueToB=0;
	while (  contLin<maxLine ){
		   std::cout <<"contLin="<<contLin<<std::endl;

	//while ( infile >> rx >> ry >> rz  ){
			//std::cout << "You said.... contLin"<< contLin << timestamp << " " << rx << " " << ry << " " << rz << " " << q1 << " " << q2 << " " << q3 << " " << q4 << "\n";
			//VectorXd myVector (rx,ry,rz);
			//readingA.row(contLin)= myVector;
		    //create sequence 1, two variables , T (time), X
			//readingA.row(contLin)<< timestamp,rx,ry,rz;
			//readingA.row(contLin)<< contLin,rx,ry,rz;
		    //readingA.row(contLin)<< contLin,sin(contLin),ry,rz;
		    //vTiempoA.row(contLin) << contLin;
		    vSerieA.row(contLin) << sin(contLin);
			//vTiempoA.row(contLin) << timestamp;
			//create sequence 2, two varialbes,  T+offset , X
			//readingB.row(contLin)<< timestamp+miOffset,rx,ry,rz;
		    //double num =  rand() % 2 + 1;
		    //double num = (float) rand()/RAND_MAX +0.5;
		    //std::cout <<"num="<<num<<std::endl;

		    //std::cout <<"newContLin="<<newContLin<<std::endl;
			//readingB.row(contLin)<< newContLin,sin(contLin),ry,rz;
			//vTiempoB.row(contLin) << newContLin;
			//vSerieB.row(contLin) << sin(contLin)+num;
			//vSerieB.row(contLin) << sin(contLin)+sqrt(contLin/50);


			outA << contLin <<" "<< sin(contLin) <<std::endl;

			newContLin= contLin + miOffset;
			//if (contLin < 65) {
			if (newContLin < 80) {
				 //aleatorio = cos((double) rand()/RAND_MAX +0.5);
				//aleatorio = cos((double) rand()/RAND_MAX +1);
                //valueToB = newContLin/(aleatorio + 1);
				aleatorio = ((double) rand()/RAND_MAX +0.5);
                //valueToB = (newContLin/9)+ 1/(aleatorio);
				valueToB = (newContLin*newContLin)/37 - 2*(newContLin+aleatorio);
			} else {
				aleatorio = 0;
				valueToB = sin(contLin);
			}

			//valueToB=sin(contLin);
		    vSerieB.row(newContLin)<<valueToB;
			outB << newContLin <<" "<< valueToB <<std::endl;
			contLin ++;

	}
	std::cout <<"fin de bucle"<<contLin<<std::endl;
	outA.close();
	outB.close();
	contLin=maxLine;
	std::cout <<"contLin="<<contLin<<std::endl;
	//Calcular autoCorrelacion
	MatrixXd A (contLin,3);
	MatrixXd B (contLin,3);
	A = readingA.block(0,0,contLin,3);
	B = readingB.block(0,0,contLin,3);

	mediaSerieA = vSerieA.mean();
	std::cout <<"	mediaSerieA="<<	mediaSerieA<<std::endl;

	mediaSerieB = vSerieB.mean();
	std::cout <<"	mediaSerieB="<<	mediaSerieB<<std::endl;


	//Serie
	VectorXd centeredSA,centeredSB,totalCenteredS;
		//for (int i=0; i < contLin ; i++){
			//centeredTA.row(contLin)<< vTiempoA.array() - mediaTiempoA;

		//}
	centeredSA = vSerieA.array() - mediaSerieA;
	std::cout <<"	centeredSA="<<	centeredSA<<std::endl;
	centeredSB = vSerieB.array() - mediaSerieB;
	std::cout <<"	centeredSB="<<	centeredSB<<std::endl;

	double denom=0,sx=0,sy=0;
	for ( int i=0; i < contLin; i++){
			//sx += centeredTA(i)*centeredTA(i);
			//sy += centeredTB(i)*centeredTB(i);
			sx += centeredSA(i)*centeredSA(i);
			sy += centeredSB(i)*centeredSB(i);
	}

	denom = sqrt(sx*sy);

	/* Calculate the correlation series */
       double sxy=0, rMax=0;
       int j = 0,delayMax=0;

	  for (int delay=-intervalo;delay<intervalo;delay++) {
		  sxy = 0;
		  sx=0;
		  sy=0;
		  for (int i=0;i<contLin;i++) {
			 j = i + delay;
			 if (j < 0 || j >= maxLine)
				continue;
			 else
				//sxy += (vTiempoA[i] - mx) * (vTiempoB[j] - my);
				 //sxy += centeredTA[i] * centeredTB[j];
				 //sxy += centeredSA[i] * centeredSB[j];
				 sxy += (vSerieA[i] - mediaSerieA) * (vSerieB[j] - mediaSerieB);
                 //sx += centeredSA(i)*centeredSA(i);
			     //sy += centeredSB(j)*centeredSB(j);
		  }



		  double r = sxy / denom;
		  //double r = sxy / sqrt(sx*sy);
          if ((fabs(r) < 1 )&& (fabs(r) > rMax)){
        	  rMax=r;
        	  delayMax=delay;
          }
	      /* r is the correlation coefficient at "delay" */
		  std::cout <<"r ="<<fabs(r)<<std::endl;
         std::cout <<"delay ="<<delay<<std::endl;
         outRegresion<< r << " " << delay << std::endl;
		  //std::cout <<"i="<<i<<std::endl;
	   }
	  std::cout <<"rMax="<<rMax<<std::endl;
	  std::cout <<"delayMax="<<delayMax<<std::endl;
	  outRegresion.close();


}
int main( int argc, char** argv )
{
	//std::cout << std::setprecision(6) << std::fixed;




		std::cout <<"	ESTOY EN BLOQUE 2="<<std::endl;
        AjusteTiempo micorrelador;
		MatrixXd A,B;
		double offset = 20;
		int maxLine = 200;
		int intervalo = 100;		//micorrelador.calcularAutocorrelacion( maxLine,intervalo, offset, A,  B);
		micorrelador.calcularAutocorrelacion2( maxLine,intervalo, offset, A,  B);




}

//create sequence 1, two variables , T (time), X

