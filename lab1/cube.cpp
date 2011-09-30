#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include "cube.h"
#include "Matrix4.h"
#include <math.h>
#include <vector>

using namespace std;

static Cube cube;

int Window::width  = 512;   // set window width in pixels here
int Window::height = 512;   // set window height in pixels here
int resolution=20;
int moon_rotation=0;
//----------------------------------------------------------------------------
// Callback method called when system is idle.
void Window::idleCallback(void)
{
 //cube.spin(1.0);       // rotate cube by 1 degree
  displayCallback();    // call display routine to redraw cube
}
	
//----------------------------------------------------------------------------
// Callback method called when window is resized.
void Window::reshapeCallback(int w, int h)
{
  width = w;
  height = h;
  glViewport(0, 0, w, h);  // set new viewport size
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-10.0, 10.0, -10.0, 10.0, 10, 1000.0); // set perspective projection viewing frustum
  glTranslatef(0, 0, -20);
  glMatrixMode(GL_MODELVIEW);
}

//----------------------------------------------------------------------------
// Callback method called when window readraw is necessary or
// when glutPostRedisplay() was called.
//same as display()
void Window::displayCallback(void)
{
  //cout<<"begin draw"<<endl;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear color and depth buffers
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(cube.getMatrix().getPointer());
  glBegin(GL_QUADS);
/*******************************DIFFERENT SPHERE RADII**********************************/
  float radius =1;	//eart radius
  float sunradius = 2;	//sun radius
  float moonradius = .5;	//moon radius
/*******************************SPHERE CONSTANTS****************************************/
  const float pi = acos(-1.0);
  float v1x,v2y,v3y,phi,theta;
  int counter,counter2;
  vector<vector<Vector3> >Earth;
  vector<vector<Vector3> >Sun;
  vector<vector<Vector3> >Moon;
  float dt=pi/resolution;
  float dp=2*pi/resolution;
  Matrix4 tmatrix = Matrix4();
  Matrix4 tmatrix2=Matrix4();
/************************************SUN************************************************/ 
  
	for (theta=0, counter=0; counter<resolution+1; theta+=dt, counter++){
	//cout<<"phi:"<<phi<<endl;
		Sun.push_back(vector<Vector3>());
		for (phi=0, counter2=0; counter2<resolution+1 ; phi+=dp, counter2++){
			v1x=sunradius*sin(theta)*cos(phi);
			v2y=sunradius*sin(theta)*sin(phi);
			v3y=sunradius*cos(theta);
			Sun[counter].push_back(Vector3(v1x,v2y,v3y));
		}
	}
	vector<vector<Vector3> >SunTransform;
	tmatrix.shear(0,1,1,0,0,0);
	for (int i =0;i<Sun.size();i++){
		SunTransform.push_back(vector<Vector3>());
		for(int j =0;j<Sun[i].size();j++)
		{
			//multiply each vector by the transformation
			tmatrix.multiply(Sun[i][j]);
			SunTransform[i].push_back(Sun[i][j]);
		}
	}

	//cout<<"START draw sun"<<endl;
	for(int j = 0; j<counter-1;j++)
		for(int i = 0;i<counter2-1 ;i++)
		{
			glColor3f(1,1,0);
			glVertex3f(SunTransform[j][i][0],SunTransform[j][i][1],SunTransform[j][i][2]);
			glVertex3f(SunTransform[j][i+1][0],SunTransform[j][i+1][1],SunTransform[j][i+1][2]);
				//cout <<Sun[j][i+1]<<endl;
			glVertex3f(SunTransform[j+1][i+1][0],SunTransform[j+1][i+1][1],SunTransform[j+1][i+1][2]);
				//cout <<Sun[j+1][i+1]<<endl;
			glVertex3f(SunTransform[j+1][i][0],SunTransform[j+1][i][1],SunTransform[j+1][i][2]);
				//cout <<Sun[j+1][i]<<endl;
		}

/************************************EARTH**********************************************/ 

  for (theta=0, counter=0; counter<resolution+1; theta+=dt, counter++){
		//cout<<"phi:"<<phi<<endl;
		Earth.push_back(vector<Vector3>());
		for (phi=0, counter2=0; counter2<resolution+1 ; phi+=dp, counter2++){
			v1x=radius*sin(theta)*cos(phi);
			v2y=radius*sin(theta)*sin(phi);
			v3y=radius*cos(theta);
			Earth[counter].push_back(Vector3(v1x,v2y,v3y));
		}
	}
	vector<vector<Vector3> >EarthTransform;
	tmatrix.translate(Vector3(7,0,0));
	tmatrix2.rotatez(pi/4*moon_rotation);
	tmatrix.multiply(tmatrix2);

	for (int i =0;i<Earth.size();i++){
		EarthTransform.push_back(vector<Vector3>());
		for(int j =0;j<Earth[i].size();j++)
		{
			//multiply each vector by the transformation
			tmatrix.multiply(Earth[i][j]);
			EarthTransform[i].push_back(Earth[i][j]);
		}
	}
	for(int j = 0; j<counter-1;j++)
		for(int i = 0;i<counter2-1 ;i++)
		{
			glColor3f(0,0,1);
			glVertex3f(EarthTransform[j][i][0],EarthTransform[j][i][1],EarthTransform[j][i][2]);
			glVertex3f(EarthTransform[j][i+1][0],EarthTransform[j][i+1][1],EarthTransform[j][i+1][2]);
			glVertex3f(EarthTransform[j+1][i+1][0],EarthTransform[j+1][i+1][1],EarthTransform[j+1][i+1][2]);
			glVertex3f(EarthTransform[j+1][i][0],EarthTransform[j+1][i][1],EarthTransform[j+1][i][2]);
		}

/************************************MOON***********************************************/
	for (theta=0, counter=0; counter<resolution+1; theta+=dt, counter++){
	//cout<<"phi:"<<phi<<endl;
		Moon.push_back(vector<Vector3>());
		for (phi=0, counter2=0; counter2<resolution+1 ; phi+=dp, counter2++){
			v1x=moonradius*sin(theta)*cos(phi);
			v2y=moonradius*sin(theta)*sin(phi);
			v3y=moonradius*cos(theta);
			Moon[counter].push_back(Vector3(v1x,v2y,v3y));
		}
	}
	vector<vector<Vector3> >MoonTransform;
	moon_rotation++;

	tmatrix.translate(Vector3(2,0,0));
	tmatrix2.rotatez(pi/3*moon_rotation);
	tmatrix.multiply(tmatrix2);

	tmatrix2.translate(Vector3(7,0,0));
	tmatrix.multiply(tmatrix2);

	tmatrix2.rotatez(pi/4*moon_rotation);
	tmatrix.multiply(tmatrix2);





	for (int i =0;i<Moon.size();i++){
		MoonTransform.push_back(vector<Vector3>());
		for(int j =0;j<Moon[i].size();j++)
		{
			//multiply each vector by the transformation
			
			tmatrix.multiply(Moon[i][j]);
			if(i==0 && j==0)
			{
				cout<<Moon[i][j]<<endl;
			}
			MoonTransform[i].push_back(Moon[i][j]);
		}
	}
	for(int j = 0; j<counter-1;j++)
		for(int i = 0;i<counter2-1 ;i++)
		{
			glColor3f(1,0,0);
			glVertex3f(MoonTransform[j][i][0],MoonTransform[j][i][1],MoonTransform[j][i][2]);
			glVertex3f(MoonTransform[j][i+1][0],MoonTransform[j][i+1][1],MoonTransform[j][i+1][2]);
			glVertex3f(MoonTransform[j+1][i+1][0],MoonTransform[j+1][i+1][1],MoonTransform[j+1][i+1][2]);
			glVertex3f(MoonTransform[j+1][i][0],MoonTransform[j+1][i][1],MoonTransform[j+1][i][2]);
		}
/***************************************************************************************/
  glEnd();
  //cout<<"end draw"<<endl;
 // cout<<resolution<<endl;
  glFlush();  
  //glFinish();
  glutSwapBuffers();
}

Cube::Cube()
{
  angle = 0.0;
}

Matrix4& Cube::getMatrix()
{
  return matrix;
}

void Cube::spin(double deg)
{
  angle += deg;
  if (angle > 360.0 || angle < -360.0) angle = 0.0;
  matrix.rotateY(angle);
}

int main(int argc, char *argv[])
{
  float specular[]  = {1.0, 1.0, 1.0, 1.0};
  float shininess[] = {100.0};
  float position[]  = {0.0, 10.0, 1.0, 0.0};	// lightsource position
  //get resolution from commandline if available
  if(argc==2)
	{  char*s=argv[1];
	resolution=atoi(s);
  }
	 // resolution = argv[1];
  cout << "\nCommand-line arguments:\n";
    for(int count = 0; count < argc; count++ )
         cout << "  argv[" << count << "]   "
                << argv[count] << "\n";
  
  cout<<resolution<<endl;
  //finish command line reading
  glutInit(&argc, argv);      	      	      // initialize GLUT
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // open an OpenGL context with double buffering, RGB colors, and depth buffering
  glutInitWindowSize(Window::width, Window::height);      // set initial window size
  glutCreateWindow("OpenGL Cube");    	      // open window and set window title
  if (glutGet(GLUT_WINDOW_COLORMAP_SIZE) != 0) 
  {
    cerr << "Fatal Error: bad RGBA colormap size\n" << endl;
    exit(1);
  }
  glEnable(GL_DEPTH_TEST);            	      // enable depth buffering
  glClear(GL_DEPTH_BUFFER_BIT);       	      // clear depth buffer
  glClearColor(1,1,1,1);   	      // set clear color to black
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // set polygon drawing mode to fill front and back of each polygon
  glShadeModel(GL_SMOOTH);             	      // set shading to smooth
  glMatrixMode(GL_PROJECTION); 
  
  // Generate material properties:
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  
  // Generate light source:
  glLightfv(GL_LIGHT0, GL_POSITION, position);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  
  // Install callback functions:
  glutDisplayFunc(Window::displayCallback);
  glutReshapeFunc(Window::reshapeCallback);
  glutIdleFunc(Window::idleCallback);
    
  // Initialize cube matrix:
  cube.getMatrix().identity();
    
  glutMainLoop();
  return 0;
}