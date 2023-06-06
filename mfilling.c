#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

float intcol[3]={0.0,0.0,0.0};
float newcolor[3]={1.0,1.0,0.0};
float floodnew[3] = {1.0,0.0,0.0};
float boundcolor[3]={1.0,1.0,1.0};

int Round1(float a)
{
    return (int)(a+0.5);
}

void DDA(float xa,float ya,float xb,float yb)
{
    float dx=xb - xa;
    float dy=yb - ya;
    float steps;
    
    if(abs(dx)>abs(dy))
    {
        steps=abs(dx);
    }
    else
    {
        steps=abs(dy);
    }
    
    float xin,yin;
    xin = dx/steps;
    yin = dy/steps;
    
    float x,y;
    x=xa;
    y=ya;
    glBegin(GL_POINTS);
    glVertex2d(Round1(x),Round1(y));
    
    for(int i=0;i<steps;i++)
    {
        x = x + xin;
        y = y + yin;
        glVertex2d(Round1(x),Round1(y));
    }
    glEnd();
}

void setpixel(int x,int y,float f[3])
{
  glBegin(GL_POINTS);
  glColor3fv(f);
  glVertex2i(x,y);
  glEnd();
  glFlush();
}

void getpixel(int x,int y,float pixels[3])
{
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,pixels);
}

void floodfill(int x,int y,float  newcolor1[3])
{
    float color[3];
    getpixel(x,y,color);
    
    if(color[0]==intcol[0] && color[1]==intcol[1] && color[2]==intcol[2])
    {
        setpixel(x,y,newcolor1);
        floodfill(x+1,y,newcolor1);
        floodfill(x-1,y,newcolor1);
        floodfill(x,y+1,newcolor1);
        floodfill(x,y-1,newcolor1);
        
    }
} 

void boundryfill(int x,int y,float newcolor[3])
{
    float color[3];
    getpixel(x,y,color);
    
    if(color[0]!=boundcolor[0] || color[1]!=boundcolor[1] || color[2]!=boundcolor[2])
    {
        if(color[0]!=newcolor[0] || color[1]!=newcolor[1] || color[2]!=newcolor[2])
        {
            setpixel(x,y,newcolor);
            boundryfill(x+1,y,newcolor);
            boundryfill(x-1,y,newcolor);
            boundryfill(x,y+1,newcolor);
            boundryfill(x,y-1,newcolor); 
        }
    }
}

void mouse(int button,int state,int x,int y)
{
      if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
      {
          int xi=x;
          int yi=500-y;
          //floodfill(xi,yi,newcolor);
          boundryfill(xi,yi,newcolor);
      }
      if(button==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
      {
          int xi=x;
          int yi=500-y;
          floodfill(xi,yi,floodnew);
      }
}

void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    DDA(100,100,300,100);
    DDA(300,100,300,300);
    DDA(300,300,100,300);
    DDA(100,300,100,100);
    glFlush();
}
void main(int argc , char** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(500,500);
    glutCreateWindow("Flood fill");
    glClearColor(0.0,0.0,0.0,0.0);
    gluOrtho2D(0,500,0,500);
  
    glutDisplayFunc(Draw);
    glutMouseFunc(mouse);
    glutMainLoop();
}
