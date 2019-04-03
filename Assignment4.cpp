// Author: Jacob Christiansen
// Class: CSCI 2270
// Course Instructor: Rhonda Hoenigman
// Recitation: 105
//
// Assignment 4

#include <fstream>
#include <sstream>
#include "CommunicationNetwork.h"
#include <iostream>

int main(int argc, char *argv[]){
	int menu = 0;
	bool quit = 0;
	CommunicationNetwork *netPtr;
	CommunicationNetwork net;
	netPtr = &net;
	while(!quit){

		std::cout << "======Main Menu======" << std::endl;
		std::cout << "1. Build Network" << std::endl;
		std::cout << "2. Print Network Path" << std::endl;
		std::cout << "3. Transmit Message Coast-To-Coast-To-Coast" << std::endl;
		std::cout << "4. Add City" << std::endl;
		std::cout << "5. Delete City" << std::endl;
		std::cout << "6. Clear Network" << std::endl;
		std::cout << "7. Quit" << std::endl;

		std::cin >> menu;

		if(menu==1){
			net.buildNetwork();
			net.printNetwork();
		}

		else if(menu==2){
			net.printNetwork();
		}

		else if(menu==3){
			net.transmitMsg(argv[1]);
		}

		else if(menu==4){
			std::string add, before;
			std::cout << "Enter a city name: " << std::endl;
			std::cin >> add;
			std::cout << "Enter a previous city name: " << std::endl;
            std::cin >> before;
			net.addCity(add, before);
		}

		else if(menu==5){
			std::string del;
			std::cout << "Enter a city name: " << std::endl;
			std::cin >> del;
			net.deleteCity(del);
		}

		else if(menu==6){
			net.deleteNetwork();
		}

		else if(menu==7){
			quit = true;
		}
	}
	std::cout << "Goodbye!" << std::endl;
}