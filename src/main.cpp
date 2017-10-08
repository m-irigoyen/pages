#include "app.hpp"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */



int main()
{
	/* initialize random seed: */
	srand(time(NULL));

	pages::App app;
	app.init();
	app.run();

	return 0;
}