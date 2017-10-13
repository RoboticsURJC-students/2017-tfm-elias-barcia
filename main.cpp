#include <pangolin/pangolin.h>
#include <pangolin/scene/axis.h>
#include <pangolin/scene/scenehandler.h>
int main( int /*argc*/, char** /*argv*/ )
{  
    pangolin::CreateWindowAndBind("Main Test",640,480);
    glEnable(GL_DEPTH_TEST);

    // Define Projection and initial ModelView matrix
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(640,480,420,420,320,240,0.2,100),
        pangolin::ModelViewLookAt(-2,2,-2, 0,0,0, pangolin::AxisY)
    );

    // Create Interactive View in window
    pangolin::Handler3D handler(s_cam);
    pangolin::Renderable tree;
    tree.Add( std::make_shared<pangolin::Axis>() );
    pangolin::View& d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f/480.0f)
            .SetHandler(&handler);
     glColor3f(0.75f, 0.75f, 0.75f);
     int cont=0;
    while( !pangolin::ShouldQuit() )
    {
        cont ++;
        // Clear screen and activate view to render into
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);

        // Render OpenGL Cube
        glColor3f(.3,.3,.3);
        /*glBegin(GL_QUADS);
        glVertex3f( 0,-0.001, 0);
        glVertex3f( 0,-0.001,10);
        glVertex3f(10,-0.001,10);
        glVertex3f(10,-0.001, 0);
        glEnd();
        */
        // FRAGMENTO QUE DIBUJA UN GRID
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
        // FIN GRID

        // FRAGMENTO QUE DIBUJA UNA CURVA SINUSOIDAL EN TRES DIMENSIONES
        glBegin(GL_POINTS);
        //for(int j=0;j<=2000;j++) {
        for(int j=0;j<=cont;j++) {
            glColor3f(.6,.2,.2);
            //glVertex3f(cos(j*0.02),cos(j*0.01),sin(j*0.05));
            glVertex3f(cos(j*0.002)+3,cos(j*0.01)+3,sin(j*0.05)+3);
        }
        glEnd();
        //pangolin::glDrawColouredCube();
        tree.Render();
        

        // Swap frames and Process Events
        pangolin::FinishFrame();
    }
    
    return 0;
}
