
#include "Hrac.h"
#include "Lopta.h"
#include "Hra.h"
#include "Klient.h"
#include <random>
#include <time.h>
#include <cstdio>

int main(){	
	
	initHeapMonitor();
	Klient* klient = new Klient();
	if (!klient->getZlyhanie())
	{
		klient->hra();
	}
	delete klient;
		
	return 0;

}