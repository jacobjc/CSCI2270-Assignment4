#include "CommunicationNetwork.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

CommunicationNetwork::CommunicationNetwork(){
    head = NULL;
    tail = NULL;
}

CommunicationNetwork::~CommunicationNetwork(){
    head = NULL;
    tail = NULL;
    deleteNetwork();
}

void CommunicationNetwork::addCity(std::string newCityName, std::string previousCityName){
    City *newCity, *temp;
    temp = head;
    bool foundPos = false;
    
    if(head == NULL){
        foundPos = true;
        newCity = new City(newCityName, NULL, NULL, "");
        head = newCity;
        tail = newCity;
    }else if(previousCityName == "First"){
        foundPos = true;
        newCity = new City(newCityName, head, NULL, "");
        head->previous = newCity;
        head = newCity;
    }else{
        newCity = new City(newCityName, NULL, NULL, "");
     }
    
    while(!foundPos && temp->next != NULL){
        if(temp->cityName==previousCityName){
            newCity->next = temp->next;
            newCity->previous = temp;
            temp->next = newCity;
            newCity->next->previous = newCity;
            foundPos = true;
            if(newCity->next==NULL){
                tail = newCity;
            }
        }
        temp = temp->next;
    }
    if(!foundPos){
        foundPos = true;
        newCity->previous = tail;
        tail->next = newCity;
        tail = newCity;
    }
}

void CommunicationNetwork::transmitMsg(char* filename){
    ifstream fr;
    string msg;
    string line;
    fr.open(filename);
    while(!fr.eof()){
        getline(fr, line);
        stringstream ss(line);
        while(getline(ss, msg, ' ')){
                City *temp = head;
                while(temp->next != NULL){
                    temp->message = msg;
                    cout << temp->cityName << " received " << temp->message << endl;
                    temp = temp->next;
                }
    
                while(temp->previous != NULL){
                    temp->message = msg;
                    cout << temp->cityName << " received " << temp->message << endl;
                    temp = temp->previous;
                }
                temp->message = msg;
                cout << temp->cityName << " received " << temp->message << endl;
                temp = temp->previous;
        }
    }
    fr.close();
}

void CommunicationNetwork::printNetwork(){
    cout<<"===CURRENT PATH==="<<endl;
    City *temp = new City("", NULL, NULL, "");
    temp = head;
    cout << "NULL <- " << head->cityName;
    while(temp->next!=NULL){
        temp = temp->next;
        cout<< " <-> " << temp->cityName;
    }
    cout << " -> NULL" << endl << "==================" << endl;
}

void CommunicationNetwork::buildNetwork(){
	string cities[10] = {"Los Angeles","Phoenix","Denver","Dallas","St. Louis","Chicago","Atlanta","Washington, D.C.","New York","Boston"};
    head = new City(cities[0], NULL, NULL, "");
    City *tempPrev = head;
    for(int i=1; i<10; i++){
    	City *temp = new City(cities[i], NULL, tempPrev, "");
    	tempPrev->next = temp;
    	tempPrev = temp;
    	if(i==9){
    		tail = temp;
    	}
    }
}

void CommunicationNetwork::deleteCity(std::string removeCity){
	City *temp = new City;
	temp = head;
	bool isFound = false;
	
	if(temp==tail){
	    isFound = true;
		delete temp;
	}

	if(temp->cityName==removeCity && !isFound){
		isFound = true;
		temp->next->previous = NULL;
		head = temp->next;
		delete temp;
	}

	while(!isFound && temp->next!=NULL){
		temp = temp->next;
		if(temp == tail && temp->cityName == removeCity){
		    isFound = true;
		    temp->previous->next = NULL;
		    tail = temp->previous;
		    delete temp;
		    break;
		}
		if(temp->cityName == removeCity && !isFound){
		    isFound = true;
		    temp->next->previous = temp->previous;
		    temp->previous->next = temp->next;
		    delete temp;
		    break;
		}
	}
	if(!isFound){
	    cout << removeCity << " not found" << endl;
	}
}

void CommunicationNetwork::deleteNetwork(){
    City *temp = new City;
    temp = head->next;
    while(temp != NULL){
        cout << "deleting " << temp->previous->cityName << endl;
        delete temp->previous;
        temp = temp->next;
    }
    cout << "deleting " << tail->cityName << endl;
    delete temp;
    head = NULL;
}