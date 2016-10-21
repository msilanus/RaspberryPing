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
	// TIMOUT = 20ms
	#define TIMEOUT 0.02
	
	clock_t t0,t1,t2;
	// Attendre avant la prochaine mesure
	Cgpio::ecrire(0);
	usleep(500);
	// impulsion de commande
	Cgpio::ecrire(1);
	usleep(10);
	Cgpio::ecrire(0);
	
	// Attendre le passage a 1 de l'echo
	t0=clock();		
	while(Cgpio::lire()==0)
	{
		// Pas de passage à 1 avant le timeout
		if((clock() - t0)/CLOCKS_PER_SEC < TIMEOUT) return -1;
	}
	t1=clock();
		
	// Attendre le retour à 0 de l'echo
	while(Cgpio::lire()==1 && (clock() - t1)/CLOCKS_PER_SEC < TIMEOUT) ;
	t2=clock();
	
	// Calcul de la duree aller-retour (CLOCKS_PER_SEC : nb de tick/s)
    unsigned long duration = (((unsigned long)t2)-((unsigned long)t1))/CLOCKS_PER_SEC;
    // Calcul de la distance (340 m/s trajet aller-retour)
    float distance=duration*34000/2;
	
	return distance;
}
