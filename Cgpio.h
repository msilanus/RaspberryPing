#include <unistd.h>				
#include <fcntl.h>				
#include <iostream>
#include <time.h>
#include <sys/select.h> 
#include <string.h>
#include <stdio.h>
#include <cstdlib>



class Cgpio
{
	private :
	char filename[50];
		
	public :
	
	Cgpio(int addr);
	~Cgpio();
 
	int lire();
	int ecrire(int value);
};
