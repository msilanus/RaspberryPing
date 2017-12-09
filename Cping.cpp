#include "Cping.h"
#include <string>
#include <chrono>

using namespace std;
typedef std::chrono::high_resolution_clock Clock;

Cping::Cping(int gpio) : Cgpio(gpio)
{
}
	
Cping::~Cping()
{};

float Cping::getDistance()
{
	// TIMOUT = 20ms
	#define TIMEOUT 0.02
	
	
	// Attendre avant la prochaine mesure
	Cgpio::ecrire(0);
	usleep(500);
	// impulsion de commande
	Cgpio::ecrire(1);
	usleep(10);
	Cgpio::ecrire(0);
	
	// Attendre le passage a 1 de l'echo
	auto t0 = Clock::now();		
	while(Cgpio::lire()==0)
	{
		// Pas de passage à 1 avant le timeout
		//if((clock() - t0)/CLOCKS_PER_SEC > TIMEOUT) return -1;
	}
	auto t1 = Clock::now();
	//cout << "t1="<<t1<<endl;	
	// Attendre le retour à 0 de l'echo
	while(Cgpio::lire()==1 /*&& (clock() - t1)/CLOCKS_PER_SEC < TIMEOUT*/);
	auto t2 = Clock::now();
	//cout << "t2="<<t2<<endl;
	// Calcul de la duree aller-retour (CLOCKS_PER_SEC : nb de tick/s)
    float duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
	
    // Calcul de la distance (340 m/s trajet aller-retour)
    float distance=duration*34/2000;
	
	return distance;
}
