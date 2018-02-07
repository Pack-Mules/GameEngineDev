#include "AFKEngine.h"


int main(int argc, char *argv[]) {
	AFKEngine afkEngine;
	afkEngine.Initialize(argc, argv);
	afkEngine.Start();
	return 0;

}

