/**
 * Interperpolated from:
 * \author Sergey Kosarevsky, 2014-2019
 * \author support@linderdaum.com   http://www.linderdaum.com   http://blog.linderdaum.com
 */

/*
	To compile:
		gcc Poisson.cpp -std=c++11 -lstdc++
*/

#include <vector>
#include <iostream>
#include <fstream>
#include <memory.h>
//#include "../General/asteriod.cpp"
//#include "../General/planet.cpp"
//#include "../General/star,pp

#define POISSON_PROGRESS_INDICATOR 1
#include "PoissonGenerator.h"

///////////////// User selectable parameters ///////////////////////////////

const int   NumPoints   = 18;	// minimal number of points to generate
const int   ImageSize   = 720;	// generate RGB image [ImageSize x ImageSize]

////////////////////////////////////////////////////////////////////////////


void mPoissonGenerator( int argc, char** argv )
{
	//vector<float> solarSystemObjects;

	PoissonGenerator::DefaultPRNG PRNG;

	const auto Points = PoissonGenerator::generatePoissonPoints( NumPoints, PRNG );

	// dump points to a text file
	std::ofstream File( "Poisson.txt", std::ios::out );	

	File << "NumPoints = " << Points.size() << std::endl;

	for ( const auto& p : Points )
	{
		//will pull in a vector of planets, asteriods, and stars
		//below returns the cooridinates of the Poisson algorithm
		File << "X = " << p.x << "; Y = " << p.y << std::endl;
	}

}
