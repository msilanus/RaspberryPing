#include<time.h> // for clock
#include "Cgpio.h"


class Cping : Cgpio
{
	private :
	
	public :
	
	Cping(int gpio);
	~Cping();	
	float getDistance();
};
