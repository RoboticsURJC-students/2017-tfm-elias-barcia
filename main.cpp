#include <iostream>
#include <ctime>
#include <unistd.h>
#include <sys/time.h>
#include <iomanip>
#include <pangolin/pangolin.h>
#include <pangolin/scene/axis.h>
#include <pangolin/scene/scenehandler.h>
#include <fstream>



double arx[15000]= {0.0};
double ary[15000]= {0.0};
double arz[15000]= {0.0};
double brx[15000]= {0.0};
double bry[15000]= {0.0};
double brz[15000]= {0.0};
double a2rx[15000]= {0.0};
double a2ry[15000]= {0.0};
double a2rz[15000]= {0.0};
int contLin1=0,contLin2=0,contLin3=0; 
double c1x=0,c1y=0,c1z=0;//centroids for dataset1
double c2x=0,c2y=0,c2z=0;//centroids for dataset2
double c3x=0,c3y=0,c3z=0;//centroids for dataset2


void readFileAndDraw ( char* fileName, double &cx, double &cy, double &cz, double (&parx) [15000],double (&pary) [15000],double (&parz) [15000],int &contLin){
/* this function reads a file and set data into x,y,z arrays  and also calculate centroid of data */   

    std::cout << "Inside readFileAndDraw."  << std::endl;
    std::ifstream infile(fileName);
    std::string line;
    infile >> std::setprecision(6) >> std::fixed;
    double timestamp,rx,ry,rz,q1,q2,q3,q4;
    
    while (infile >> timestamp >> rx >> ry >> rz >> q1 >> q2 >> q3 >> q4 )
    {
                parx[contLin]=rx;
                pary[contLin]=ry;
                parz[contLin]=rz;
                cx+=rx;
                cy+=ry;
                cz+=rz;
                // if (line == "Path") { continue; }

                // std::istringstream iss(line);
                // int a, b;

                // if (!(iss >> a >> b) || iss.get() != EOF) { /* error! die? */ }

                //std::cout << "You said contLin"<< contLin << timestamp << " " << arx[contLin] << " " << ary[contLin] << " " << arz[contLin] << " " << q1 << " " << q2 << " " << q3 << " " << q4 << "\n";
                contLin++;
    }
    cx=cx/contLin;
    cy=cy/contLin;
    cz=cz/contLin;
    std::cout<< "cx="<<cx <<"cy="<<cy<<"cz="<<cz<<"\n";
    //parx=px;
    //pary=py;
    //parz=pz;
    infile.close();
};



int main( int argc, char** argv )
{  
    pangolin::CreateWindowAndBind("2 CURVAS",640,480);
    glEnable(GL_DEPTH_TEST);
    int readAndDraw=1;
    //readFileAndDraw("salidaCurva1.txt");
    // Define Projection and initial ModelView matrix
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(640,480,420,420,320,240,0.2,100),
        //pangolin::ModelViewLookAt(-2,2,-2, 0,0,0, pangolin::AxisY)
        pangolin::ModelViewLookAt(-5,1.25,-5, 0,0,0, pangolin::AxisY)
    );

    // Create Interactive View in window
    pangolin::Handler3D handler(s_cam);
    pangolin::Renderable tree;
    tree.Add( std::make_shared<pangolin::Axis>() ); 
    pangolin::View& d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f/480.0f)
            .SetHandler(&handler);
     //glColor3f(0.75f, 0.75f, 0.75f);
     glColor3f(1, 1, 1);
     int cont=0;
     float x,y,z=0;
     timeval a; //Para leer el tiempo del reloj de la maquina
     
     double myMilliseconds;
     gettimeofday(&a, 0);

     //
     std::cout << "Numero parametros="  << argc <<  std::endl;
     if ( argc > 1) {
        std::cout << "parametro ="  << argv[argc-1] <<  std::endl;
     }
     //Format decimal point for timestamp precision (SECONDS AND MILLISECONDS)
     std::cout << std::setprecision(6) << std::fixed;
     std::ofstream out( "salidaCurva1.txt" );
     out << std::setprecision(6) << std::fixed;

     // FOR READING FILE AND DRAW CURVE
     std::ifstream infile("misalida.txt");
     //std::ifstream infile("miEntradaModificada.txt");
     std::string line;
     infile >> std::setprecision(6) >> std::fixed;
     double timestamp,rx,ry,rz,q1,q2,q3,q4;
     
     //double arx[15000]= {0.0};
     //double ary[15000]= {0.0};
     //double arz[15000]= {0.0};
     //int contLin=0;
     if( !out )
     {
       std::cout << "Couldn't open file."  << std::endl;
       return 1;
     }
    contLin1=0;
    readFileAndDraw("miEntrada.txt",c1x,c1y,c1z,arx,ary,arz,contLin1);
    std::cout<< "cx="<<c1x <<"cy="<<c1y<<"cz="<<c1z<<"\n";

    contLin2=0;
    readFileAndDraw("miEntradaModificada.txt",c2x,c2y,c2z,brx,bry,brz,contLin2);
    std::cout<< "c2x="<<c2x <<"c2y="<<c2y<<"c2z="<<c2z<<"\n";

    contLin3=0;
    readFileAndDraw("miSalidaRegistro.txt",c3x,c3y,c3z,a2rx,a2ry,a2rz,contLin3);
    std::cout<< "c3x="<<c3x <<"c3y="<<c3y<<"c2z="<<c3z<<"\n";


   
    while( !pangolin::ShouldQuit() )
    {
        cont ++;
        // Clear screen and activate view to render into
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        //glClearColor(0.1f, 1.0f, 0.0f, 1.0f);
        glClearColor(1, 1, 1,1);
        
        d_cam.Activate(s_cam);

        if (readAndDraw == 1) {
            //while (infile >> timestamp >> rx >> ry >> rz >> q1 >> q2 >> q3 >> q4 )
            /*if (infile >> timestamp >> rx >> ry >> rz >> q1 >> q2 >> q3 >> q4 )
                {
                arx[contLin]=rx;
                ary[contLin]=ry;
                arz[contLin]=rz;
                
                // if (line == "Path") { continue; }

                // std::istringstream iss(line);
                // int a, b;

                // if (!(iss >> a >> b) || iss.get() != EOF) {  error! die?  }

                std::cout << "You said, cont"<< cont << timestamp << " " << arx[contLin] << " " << ary[contLin] << " " << arz[contLin] << " " << q1 << " " << q2 << " " << q3 << " " << q4 << "\n";
                glBegin(GL_POINTS);
                    for (int h=0; h<= contLin; h++){
                       
                        glColor3f(0,1,1);//cyan
                        
                        glVertex3f(arx[h],ary[h],arz[h]); // LINEA QUE DIBUJA UNA CURVA 
                    
                    }
                    glColor3f(0,1,1);//cyan
                        
                    glVertex3f(rx,ry,rz); // LINEA QUE DIBUJA UNA CURVA 
                glEnd();    
                contLin++;
              */
            //} else if (contLin > 0 ) {// After reading all coordinates from file. Only have to paint the content of the arrays.
               
                glBegin(GL_POINTS);
                    glColor3f(0,0,0);//white, original curve, ground trouth
                    for (int h=0; h < contLin1; h++){// Bucle for, important the < simbol instead of <=
                       
                        glVertex3f(arx[h],ary[h],arz[h]); // LINEA QUE DIBUJA UNA CURVA 
                    
                    }
                    glColor3f(0,0,1);//BLUE, artificial data
                    for (int j=0; j < contLin2; j++){// Bucle for, important the < simbol instead of <=
                       
                        glVertex3f(brx[j],bry[j],brz[j]); // LINEA QUE DIBUJA UNA CURVA 
                    
                    }
                    glColor3f(0,1,0);//GREEN, Estimated data using Rotation and Traslation calculated with SVD
                    for (int k=0; k < contLin3; k++){// Bucle for, important the < simbol instead of <=
                       
                        glVertex3f(a2rx[k],a2ry[k],a2rz[k]); // LINEA QUE DIBUJA UNA CURVA 
                    
                    }



                    glColor3f(1,0,0);//RED, to display centroids
                    glVertex3f(c1x,c1y,c1z); 
                    glVertex3f(c2x,c2y,c2z); 
                    glVertex3f(c3x,c3y,c3z); 
                glEnd(); 

                glLineWidth(2.5);
                glColor3f(1.0, 0.0, 0.0);
                glBegin(GL_LINES);
                for (int l=0; l < contLin2; l++){// Bucle for, important the < simbol instead of <=
                       
                        glVertex3f(a2rx[l],a2ry[l],a2rz[l]); // LINEA QUE DIBUJA UNA CURVA 
                        glVertex3f(brx[l],bry[l],brz[l]); // LINEA QUE DIBUJA UNA CURVA 
                        
                    
                    }
                
                glEnd();
               
            //}
        } else { // Draw and Write


        
            // Render OpenGL Cube
            glColor3f(.3,.3,.3);
            /*glBegin(GL_QUADS);
            glVertex3f( 0,-0.001, 0);
            glVertex3f( 0,-0.001,10);
            glVertex3f(10,-0.001,10);
            glVertex3f(10,-0.001, 0);
            glEnd();
            */
            

            // DRAW 2 SINUSOIDAL CURVES IN 3D
            glBegin(GL_POINTS);
            //for(int j=0;j<=2000;j++) {
            for(int j=0;j<=cont;j++) {
                
                //glColor3f(.6,.2,.2);
                //glColor3f(0,1,0);//GREEN           
                glColor3f(1,0,0);//RED           
                //glVertex3f(cos(j*0.02),cos(j*0.01),sin(j*0.05));
                //x=cos(j*0.001)+1;
                x=cos(j*0.013)+1;
                //y=cos(j*0.01)+1;
                y=cos(j*0.006)+1;
                //z=sin(j*0.05)+1;
                z=sin(j*0.007)+1;
                //glVertex3f(x,y,z);
                glVertex3f(x,y+x,z+y+x); // LINEA QUE DIBUJA UNA CURVA 

                //glColor3f(.2,.2,.5);
                glColor3f(1,1,0);//YELLOW
                glVertex3f(x+3,y+1+x,z+3+x+y); // LINE THAT DRAWS A CURVE USGIN COORDINATES FROM THE FIRST CURVE
                // GET TIME (SECONDS AND MILISECONDS)
                gettimeofday(&a, 0);
                myMilliseconds = double( double(a.tv_sec)+  double( double(a.tv_usec)/1000000.0)); 
                //printf("misalida %.2f",double(a.tv_usec)/double(1000000.0));
                //std::cout << "misalida %.2f" <<double(a.tv_sec)+ double(a.tv_usec)/double(1000000.0) << std::endl;
                std::cout << "timeStamp = " << myMilliseconds << "X="<<x<<"Y="<<y<<"Z="<<z<<std::endl;
                out << "timeStamp = " << myMilliseconds << "X="<<x<<"Y="<<y<<"Z="<<z<<"\n"<<std::endl;
                // END GET TIME MILISECONDS

                //glVertex3f(cos(j*0.002)+3,cos(j*0.01)+3,sin(j*0.05)+3);
            }
            glEnd();

        }
        //pangolin::glDrawColouredCube();
        
        // DRAW A  GRID
        glBegin(GL_LINES);
        for(int i=0;i<=10;i++) {
            if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
            glVertex3f(i,0,0);
            glVertex3f(i,0,10);
            if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
            glVertex3f(0,0,i);
            glVertex3f(10,0,i);
           
        };
        glEnd();
        // END DRAW GRID

        tree.Render();

        

        // Swap frames and Process Events
        pangolin::FinishFrame();

        
    }
    out.close();
    return 0;
}
