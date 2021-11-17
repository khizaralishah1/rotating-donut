//Khizar Ali Shah
//2020196	BCS
//Assignment 1 of CS112
//-----------------------------------------!!!!!!!IMPORTANT!!!!!!!!!----------------------------------------
//NOTE: PLEASE ADD '-lgdi32' to linker options WITHOUT quotes by
//going to Tools->Compiler Options->and typing this under 'add the following commands when calling linker'
//-----------------------------------------!!!!!!!!!!!!!!!!!!!!!!!!!----------------------------------------
//#include "2020196_implementation.cpp"
#include "2020196_class.h"

int main()
{
	Donut myNewDonut(40); // creates and instance of class Donut and its constructor is called which takes radius as a parameter
	myNewDonut.draw();    // draws the donut on the screen by calling the public member function of donut class
	
	return 0;
}