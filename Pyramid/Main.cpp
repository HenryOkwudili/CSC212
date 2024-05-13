#include "cube.h"
#include "Renderer3D.h"
#include <iostream>
#include <vector>
#include <SDL.h>
#include "Main2.cpp"
using namespace std;

vector<Point3D> points{
	Point3D{-1,-1,-1}, 
}




int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		cout << "SDL initialization succeeded!";
	}

	cin.get();
	return 0;
}