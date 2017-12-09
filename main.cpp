#include <iostream>
#include <string>
#include "Cping.h"

using namespace std;

int main()
{
	Cping ping(21);
	
	while(1)
	{		
		cout << endl << "distance : " << (int)ping.getDistance() << " cm" ;
		sleep(1);
	}
	

}
