#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "FCavesGenerator.h"
#include "FMetrics.h"

int main()
{
	FCavesGenerator CavesGenerator{};
	CavesGenerator.GenerateCaves();

	return NULL;
}
