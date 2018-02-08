#include "AFKEngine.h"


int main(int argc, char *argv[]) {
	AFKEngine engine;
	engine.Initialize(argc, argv);
	engine.Start();
	return 0;

}

