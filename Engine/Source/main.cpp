#include <iostream>

#include "Frame/HdrRectFrame.h"

int main(int argc, char* argv[])
{
	using namespace ph;

	std::cout << "Hello World!" << std::endl;

	HdrRectFrame hdrFrame(1280, 720);

	return 0;
}