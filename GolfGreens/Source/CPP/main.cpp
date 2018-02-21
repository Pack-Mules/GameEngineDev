#include "AFKEngine.h"
#include "GameObject.h"


int main(int argc, char *argv[]) {
	AFKEngine engine;

	//If failed system requirements
	if (!engine.Initialize(argc, argv))
		return 1;

	engine.Start();

	return 0;

}

