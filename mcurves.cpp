#include <iostream>
#include <GL/glut.h>
#include <math.h>
using namespace std;
int choice,n;
int xa,ya,xb,yb;
int input[2][4];
#define R (3.14/180)

int Round(float a){
	return (int)(a+0.5);
}

void DDA(float xa,float ya,float xb,float yb){
	int dx,dy,P;
	dx=xb-xa;
	dy=yb-ya;
	
	if(abs(dx)>abs(dy)){
		P=abs(dx);
	}
	else{
		P=abs(dy);
	}
	
	float delx=dx/(float)(P);
	float dely=dy/(float)(P);
	
	float x=xa;
	float y=ya;
	glVertex2d(Round(x),Round(y));
	
	for(int i=0;i<P;i++){
		x+=delx;
		y+=dely;
		glVertex2d(Round(x),Round(y));
	}
	
}

void Bezier(){
	int dx,dy;
	for(float i=0;i<=1;i+=0.001){
		dx= (1-i)*(1-i)*(1-i)*input[0][0] + 3*(1-i)*(1-i)*(i)*input[0][1] + 3*(1-i)*(i)*(i)*input[0][2] + (i)*(i)*(i)*input[0][3];
		
		dy= (1-i)*(1-i)*(1-i)*input[1][0] + 3*(1-i)*(1-i)*(i)*input[1][1] + 3*(1-i)*(i)*(i)*input[1][2] + (i)*(i)*(i)*input[1][3];
		
		glVertex2d(dx,dy);
	}
}


void Koch(float xa,float ya,float xb,float yb,int n){
	float xc,yc,xd,yd,midx,midy;
	
	xc=(2*xa+xb)/3;
	yc=(2*ya+yb)/3;
	xd=(2*xb+xa)/3;
	yd=(2*yb+ya)/3;
	
	midx=xc+((xd-xc)*cos(60*R))+( (yd-yc)*(sin(60*R)));
	midy=yc-((xd-xc)*sin(60*R))+( (yd-yc)*(cos(60*R)));
	
	if(n>0){
		Koch(xa,ya,xc,yc,n-1);
		Koch(xc,yc,midx,midy,n-1);
		Koch(midx,midy,xd,yd,n-1);
		Koch(xd,yd,xb,yb,n-1);
	}else{
		DDA(xa,ya,xc,yc);
		DDA(xc,yc,midx,midy);
		
		DDA(midx,midy,xd,yd);
		DDA(xd,yd,xb,yb);
		
	}
	
}
void draw(){
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
	if(choice==1){
		for(int q=0;q<4;q++){
			glColor3f(1.0,0.0,0.0);
			glVertex2d(input[0][q],input[1][q]);
		}
		glColor3f(0.0,0.0,1.0);
		Bezier();
	}else{
		Koch(600,100,800,400,n);
		Koch(800,400,400,400,n);
		Koch(400,400,600,100,n);
	}
	glEnd();
	glFlush();
}

int main(int argc,char** argv){

	cout<<"Which curve : "<<endl;
	cout<<"1.Bezier"<<endl;
	cout<<"2.Koch"<<endl;
	cin>>choice;
	switch(choice){
		case 1:
			cout<<"Enter the 4 Points : "<<endl;
			for(int i=0;i<4;i++){
				cout<<"X : ";
				cin>>input[0][i];
				cout<<"Y : ";
				cin>>input[1][i];
			}
			break;
			
		case 2: 
			cout<<"Enter the Number of iterations : "<<endl;
			cin>>n;
			break;
	}
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE||GLUT_RGB);
	glutInitWindowSize(1400,900);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Koch");
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	gluOrtho2D(0,1400,0,900);
	glutDisplayFunc(draw);
	//glutMouseFunc(myMouse);
	glutMainLoop();
	return 0;
}

