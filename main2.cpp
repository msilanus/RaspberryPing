#include <iostream>
#include <string>
#include <time.h>
#include "Cping.h"
#include "rgb_lcd.h"

using namespace std;

int dist;
time_t now;
tm *nowinfo; 

int main()
{
	Cping *ping;
	ping = new Cping(21);
	rgb_lcd *myLcd;
	myLcd = new rgb_lcd();
    	myLcd->begin(16,2);
    	myLcd->setRGB(0,0,255);
	myLcd->setCursor(5, 0);
    	myLcd->write("Mesure");
	myLcd->setCursor(2, 1); 
    	myLcd->write("de distance");
	sleep(5);
	
	
	
	while(1)
	{	
		dist =  ping->getDistance();
	
		now = time(0);
		nowinfo = localtime(&now);
		if(nowinfo->tm_mday<10) cout << "0" << nowinfo->tm_mday <<"/";
		else cout << nowinfo->tm_mday <<"/";
		if(nowinfo->tm_mon<9) cout << "0" << nowinfo->tm_mon + 1 <<"/";
		else cout << nowinfo->tm_mon + 1 <<"/";
		cout << nowinfo->tm_year + 1900 <<" - ";
		if(nowinfo->tm_hour<10) cout << "0" << nowinfo->tm_hour <<":";
		else cout << nowinfo->tm_hour <<":";
		if(nowinfo->tm_min<10) cout << "0" << nowinfo->tm_min <<":";
		else cout << nowinfo->tm_min <<":";
		if(nowinfo->tm_sec<10) cout << "0" << nowinfo->tm_sec;
		else cout << nowinfo->tm_sec; 		
		cout << "   |   ";
		cout << dist << " cm" << endl;
		
		if(dist<10) myLcd->setColor(RED);
		else if(dist<50) myLcd->setRGB(255,127,0);
		else myLcd->setColor(WHITE);

		myLcd->clear();		
		myLcd->setCursor(5, 0);
    		myLcd->write(to_string(dist) + " cm");
		usleep(500000);
		
	}
	

}
