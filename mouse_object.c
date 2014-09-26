
#include <GLUT/glut.h>
#include <string.h>
#define WIDTH 600
#define HEIGHT 600

//using namespace std;

double arr[5000][4];
int z=0;
int flag=0;
float radius=0.03;
int ptr=0;
int faltu_bit=1;
float color[3][3]={{1.0,1.0,1.0},{1.0,1.0,0.0},{0.0,1.0,0.0}};

void drawText(char *str,float x,float y,int id) 
{
    int i;
    int len=strlen(str);
    //glLoadIdentity();
    glColor3f(color[id][0],color[id][1],color[id][2]);
    glRasterPos2f(x,y);
    for(i=0;i<len;i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
}


void init()
{
    glClearColor( 0.0, 0.0, 0.0, 1.0);
    glMatrixMode( GL_PROJECTION);
    gluOrtho2D(0.0,WIDTH,0.0,HEIGHT);
    memset(arr,0,5000);
    glPointSize(20.0);
}

void resetAll()
{ 
    memset(arr,0,5000);
    z=0;
} 

///OPENGL MAPPING///
float getOpenGLX(int x)
{
    double ox = x/ (double)WIDTH*(WIDTH);
    return ox;
}

float getOpenGLY(int y)
{
    double oy = (1 - y/ (double) HEIGHT)*HEIGHT;
    return oy;
}

void drawPoints()
{ 
    int i;
    glBegin( GL_POINTS );
    glColor3f( 0.0,1.0,0.0 );
    for ( i = 0; i < z; i++ )
    {
        glVertex2f( arr[i][0],arr[i][1]);
    }
    glEnd();
}

void drawBall(float x,float y)
{
    glBegin( GL_POINTS);
    glColor3f( 0.0,1.0,1.0 );
//    glPushMatrix(); 
  //  glTranslatef(0.0,0.0,-5.0); 
   // glutSolidSphere(0.6,40,40); 
   
     glVertex2f(x,y);
    glEnd();
}

/*void drawBall1() 
{ 
    glColor3f(0.0,1.0,1.0); 
    
    glPushMatrix(); 
    
    glTranslatef(0.0,0.0,-5.0); 
    
    glutSolidSphere(0.6,40,40); 
    
    glPopMatrix(); 
    
} */

void drawLines()
{
    int i;
    glBegin(GL_LINES);
    glColor3f(1.0,1.0,1.0);
    for(i=0;i<z;i++)
    {
        glVertex2f(arr[i][0],arr[i][1]);
    }
    glEnd();
}



void addValue(int x,int y)
{
    arr[z][0]=getOpenGLX(x);
    arr[z++][1]=getOpenGLY(y);
} 

void trackBall()
{
    drawPoints();
}


void myDisplay()
{
    glClear( GL_COLOR_BUFFER_BIT);
    if(!flag)
    {
        drawLines();
        if(!faltu_bit)
            drawBall(arr[ptr][0],arr[ptr][1]);
    }
    /*if(faltu_bit)
    {
        drawText("Project by: Adil Ansar [10 CSS-32]",50.0,500.0,0);
        drawText("Welcome",250.0,300.0,1);
        drawText("Drag the Mouse Any Where in the Window to see the Path",10.0,200.0,2);
    }*/
    glutSwapBuffers();
    glutPostRedisplay();
    glFlush();
}


void myMouseStat(int button,int state,int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(!flag)
        {
            if(faltu_bit)
            {
                faltu_bit=0;
            }
            resetAll();
            flag=1;
        }
    }
    else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if(flag)
        { 
            ptr=0;
            flag=0;
        }
    }
}


void myPressedMove(int x,int y)
{
    if(flag)
    {
        addValue(x,y);
    }
}



void myTimer(int t)
{
    if(ptr!=z)
    {
        ptr++;
    }
    else
    {
        ptr=0;
    }
    glutTimerFunc(100,myTimer,0);
}

int main( int argc, char ** argv)
{
    glutInit( &argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowPosition( 100, 100);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow( "Testing");
    init();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouseStat);
    glutMotionFunc(myPressedMove);
    glutTimerFunc(100,myTimer,0);
    glutMainLoop();
    return 0;
}