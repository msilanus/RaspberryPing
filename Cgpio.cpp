#include "Cgpio.h"
#include <string>

using namespace std;

#define EXPORT 		"export"
#define DIRECTION 	"direction"
#define VALUE 		"value"
#define IN 			"in"
#define OUT 		"out"


Cgpio::Cgpio(int addr)
{
	int fd;
	char buffer[3];
	
	sprintf(filename,"/sys/class/gpio/%s",EXPORT);
	fd = open(filename, O_WRONLY);
	
	snprintf(buffer, 3, "%d", addr);
	if(write(fd, buffer, 3)==-1)
	{
			cout << "Erreur ou existe deja" << endl;
	}
	else cout << "Cgpio::Cgpio : Export de " << addr << " reussi " << endl;
	close(fd);
	sprintf(filename,"/sys/class/gpio/gpio%d/",addr);
	usleep(50000);
}
	
Cgpio::~Cgpio()
{}


int Cgpio::lire()
{
	int fd;
	char value_str[1];
	char gpioPath[50];	
	
	sprintf(gpioPath,filename);
	strcat(gpioPath,DIRECTION);
	char dir[2];
	sprintf(dir,IN);
	fd = open(gpioPath, O_WRONLY);
	write(fd, dir,sizeof(dir));
	close(fd);
	
	sprintf(gpioPath,filename);
	strcat(gpioPath,VALUE);;
	fd = open(gpioPath, O_RDONLY);
	if (read(fd, value_str, 1)==-1) 
	{
		cout << "Cgpio::lire : Erreur de lecture" << endl;
		return(-1);
	}
 
	close(fd);
 
	return(atoi(value_str));
}
	
int Cgpio::ecrire(int value)
{
	int fd;
	char gpioPath[50];
	sprintf(gpioPath,filename);
	strcat(gpioPath,DIRECTION);
	//cout << gpioPath << endl;
	char dir[3];
	sprintf(dir,OUT);
	//cout << dir << endl;
	
	fd = open(gpioPath, O_WRONLY);
	write(fd, dir,sizeof(dir));
	close(fd);
	
	sprintf(gpioPath,filename);
	strcat(gpioPath,VALUE);
	//cout << gpioPath << endl;
	
	fd = open(gpioPath, O_WRONLY);
	
	char value_str[1];
	if(value==0) value_str[0]='0';
	else value_str[0]='1';

	if (write(fd, value_str,1)!=1)
	{
		cout << "Cgpio::ecrire : Erreur d'ecriture sur " << gpioPath << " : " << value_str << endl;
		return(-1);
	}
 
	close(fd);
	return(0);
}	
