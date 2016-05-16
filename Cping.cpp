#include "Cping.h"
#include <string>

using namespace std;


Cping::Cping(int gpio) : Cgpio(gpio)
{
}
	
Cping::~Cping()
{};

int Cping::getDistance()
{
	clock_t t1,t2;
	// Attendre avant la prochaine mesure
	Cgpio::ecrire(0);
	usleep(500);
	// impulsion de commande
	Cgpio::ecrire(1);
	usleep(10);
	Cgpio::ecrire(0);
	
	// Attendre le passage a 1 de l'echo			
	while(Cgpio::lire()==0) ;
	t1=clock();
		
	// Attendre le retour à 0 de l'echo
	while(Cgpio::lire()==1) ;
	t2=clock();
	
	// Calclu de la duree aller-retour
	unsigned long duration = (((unsigned long)t2)-((unsigned long)t1));
	// Calcul de la distance
	float distance=duration*34/2000;
	
	return distance;
}
