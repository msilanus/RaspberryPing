#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "Cping.h"
#include "rgb_lcd.h"

using namespace std;

int dist;
string log;
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
	cout << "wait please ..." << endl;
	sleep(5);
	
	while(1)
	{	
		dist =  ping->getDistance();
	
		now = time(0);
		nowinfo = localtime(&now);
		// push info to standard output quickly
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
		
		// write info into log file
		ofstream flog("/var/www/html/distance.log", ios::out);
		if(flog)
        	{
			if(nowinfo->tm_mday<10) log="0" + to_string(nowinfo->tm_mday) + "/";
			else log += to_string(nowinfo->tm_mday) +"/";
			if(nowinfo->tm_mon<9) log += "0" + to_string(nowinfo->tm_mon + 1) + "/";
			else log += to_string(nowinfo->tm_mon + 1) + "/";
			log += to_string(nowinfo->tm_year + 1900) + " - ";
			if(nowinfo->tm_hour<10) log += "0" + to_string(nowinfo->tm_hour) + ":";
			else log += to_string(nowinfo->tm_hour) + ":";
			if(nowinfo->tm_min<10) log += "0" +to_string(nowinfo->tm_min) + ":";
			else log += to_string(nowinfo->tm_min) + ":";
			if(nowinfo->tm_sec<10) log += "0" + to_string(nowinfo->tm_sec);
			else log += to_string(nowinfo->tm_sec); 		
			log += "   |   ";
			log += to_string(dist) + " cm\n";			
			flog << log ;
			flog.close();
        	}
		
		// Write info on LCD display
		if(dist<10) myLcd->setColor(RED);
		else if(dist<50) myLcd->setRGB(255,127,0);
		else myLcd->setColor(WHITE);

		myLcd->clear();		
		myLcd->setCursor(5, 0);
    		myLcd->write(to_string(dist) + " cm");
		sleep(1);
		
	}
	

}
