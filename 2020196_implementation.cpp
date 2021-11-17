#include <Windows.h> // for using SetPixel and GetConsoleWindow functions
#include <math.h>
#include "2020196_class.h"
using namespace std;

Donut::Donut(double r) //constructor to initialize the radius
	{
		r1 = r;
		r2 = 1.2*r;
	}

void Donut::draw()
{
	HDC hdc = GetDC(GetConsoleWindow()); // gets the console screen. Used as paramter in SetPixel function
	
	double xC, yC, x, y, z;                   // xC and yC are coordinates of the single circle. x, y, z are coordinates after its rotation
	double tSpacing = 0.09, phiSpacing = 0.1; // increments in theta and phi angles for running of the loop
	double A=0, B=0;                          // angles for tilting with respect to x and y axes respectively
	double h = 0;	                          // used inside sine function to make the radius values oscillate between lower and higher
	
	int buffer[5000][3];					  // to store all calculated coordinates of a single donut for displaying later
	
	while(1) // keeps showing the donut, never stops
	{
		int i=0;                         // used to keep track of index where the next coordinate is to be stored in the buffer array
		h+=0.1;
		r1 = abs(10+r1*sin(h));              // radius changes in every loop so it looks like donut is coming towards the screen and going away from it.
		r2 = 1.2*r1;
		A += 3*tSpacing, B+= 3*tSpacing; // every time next donut is created, A and B are slightly incremented so that donut keeps tilting
		double cosA=cos(A), sinA=sin(A); // used so that values of cos and sin should not be computed again and again
		double cosB=cos(B), sinB=sin(B);
		
		for(double phi=0; phi<2.2*M_PI; phi+=phiSpacing) // rotates the circle to create a torus (this is solid of revolution)
		{				
			double sinphi=sin(phi), cosphi=cos(phi);

			for(double t=0; t<2*M_PI; t+=tSpacing) //creates a single circle
			{
				double cost=cos(t), sint=sin(t);
				
				// coordinates of the circle for each theta (each iteration of the loop)
				xC = r2+r1*cost + 50; 
				yC = r1*sint + 50;
				
				
				//coordinates of circle rotated about x, y, and z axis (obtained after multiplication with appropriate rotation matrices)
				x = xC*(cosphi*cosB + sinA*sinB*sinphi)-yC*cosA*sinB + 250 + abs(200*sin(h));  // phi, A, and B control how circle behaves, that is, it rotates differently every time, creating a tilting effect
				y = xC*(cosphi*sinB - cosB*sinA*sinphi)+ yC*cosA*cosB + 200 +  + abs(80*cos(h)); // h -> moves the coordinates between two fixed points so the donut seems like dancing between those coordinates
				
				//Luminance or Shading
				double L = cosphi*cost*sinB - cosA*cost*sinphi - sinA*sint + cosB*(cosA*sint - cost*sinA*sinphi);
				
				//stores x and y coordinates along with their luminance value in the array for printing them later all at once
				buffer[i][0] = x;
				buffer[i][1] = y;
				buffer[i][2] = L;
				i++;
			}
		}
		
		//Drawing the pixels on the console screen
		for(int a=0; a<i; a++)
		{
			double L = buffer[a][2];
			if(L > 0)    // L moves from 0 to sqrt(2) -> Setting the color of the point(pixel) based on its luminance value. If luminance is higher, it is more bright
				SetPixel(hdc, buffer[a][0], buffer[a][1], RGB(L*100+100, L*100+100, L*100+100));
			else         // luminance is lower so it is dim
				SetPixel(hdc, buffer[a][0], buffer[a][1], RGB(50, 50, 50));
		}
		
		//clear the screen so that next donut does not overlaps the previous one
		system("cls");
	} // while loop
} //draw function
