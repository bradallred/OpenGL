#ifdef __APPLE__ 
#include<GLUT/glut.h> 
#include<openGL/openGL.h> 
#else 
#include<GL/glut.h> 
#endif 
#include<math.h>
#include<unistd.h>
#include<stdlib.h>
float x=3.0,y=0.0,angle=0.0,var=0.01; 
static int flag=1; 
void initRendering() 
{ 
    glEnable(GL_DEPTH_TEST); 
} 

void reshape(int w,int h) 
{ 
    glViewport(0,0,w,h); 
    
    glMatrixMode(GL_PROJECTION); 
    
    glLoadIdentity(); 
    
    gluPerspective(45,w/h,1,200); 
    
} 
//if escape key is pressed then it closes the window
void keyPressed(int key,int x,int y) 
{ 
    if(key==27) 
    {
        exit(1);
    } 
} 
//small white ball is drawn by this function
void drawBall1() 
{ 
    glColor3f(0.0,1.0,1.0); 
    
    glPushMatrix(); 
    
    glTranslatef(0.0,0.0,-5.0); 
    
    glutSolidSphere(0.6,40,40); 
    
    glPopMatrix(); 
    
} 
//big ball is drawn by this function
void drawBall2() 
{ 
    glColor3f(1.0,1.0,1.0); 
    
    glPushMatrix(); 
    
    glTranslatef(x,y,-20.0); 
    
    glutSolidSphere(0.6,20,20); 
    
    glPopMatrix(); 
    
} 
//ball rotates according to this variance of x and y
void update() 
{
    angle+=var;
    if(angle>=6.28 || angle<=0)
    {
        var=-var;
    }
    x=3*sin(angle);
    y=3*cos(angle);
} 
void display() 
{ 
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); 
    glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity(); 
    drawBall1(); 
    drawBall2(); 
    update(); 
    glutSwapBuffers(); 
} 


int main(int argc,char **argv) 
{ 
    glutInit(&argc,argv); 
    
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH); 
    
    glutInitWindowSize(600,600); 
    
    glutCreateWindow("Rotating Ball Around Circle !"); 
    
    initRendering(); 
    
    glutDisplayFunc(display); 
    
    glutIdleFunc(display); 
    
    glutReshapeFunc(reshape); 
    
    glutSpecialFunc(keyPressed); 
    
    glutMainLoop(); 
    
    return(0); 
}
