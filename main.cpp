#include <iostream>
#include <string>
#include "Cping.h"

using namespace std;

int main()
{
	Cping ping(21);
	
	while(1)
	{		
		cout << endl << "distance : " << ping.getDistance() << endl;
		sleep(1);
	}
	

}
