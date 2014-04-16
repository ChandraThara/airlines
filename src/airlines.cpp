/*
 * airlines.cpp
 *
 *  Created on: Mar 23, 2014
 *      Author: 	Chandra Thara Chandrika
 *      Student ID: 82878
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <vector>
#include <math.h>
#include <stdexcept>
#include "HashMap.h"

using namespace std;

class AirportData {
	public:
		long AirportID; //	Unique OpenFlights identifier for this airport.
		string Name;	// Name of airport. May or may not contain the City name.
		string City;	// Main city served by airport. May be spelled differently from Name.
		string Country;	// Country or territory where airport is located.
		string IATA;	//FAA code for USA, ATA code for all other airports. Blank if not assigned.
		string ICAO; //	4-letter ICAO code. Blank if not assigned.
		float Latitude;	//Decimal degrees, usually to six significant digits. Negative is South, positive is North.
		float Longitude;	//Decimal degrees, usually to six significant digits. Negative is West, positive is East.
		long Altitude;	//In feet.
		float Timezone;	//Hours offset from UTC. Fractional hours are expressed as decimals, eg. India is 5.5.
		string DST; //Daylight savings time. One of E (Europe), A (US/Canada), S (South America), O (Australia), Z (New Zealand), N (None) or U (Unknown)
	public:
		friend bool operator== (AirportData &ds1, AirportData &ds2);
		long parseline(string line) {
			stringstream lineStream(line);
			string field;

			try {
				vector<string> all_fields;
				while(getline(lineStream, field, '"')) {
					std::stringstream ss(field);
					while(std::getline(ss, field, ',')) {
						if (field.length() > 0)
							all_fields.push_back(field);
					}
					if(getline(lineStream, field, '"')) {
						all_fields.push_back(field);
					}
				}
				AirportID = stol((string)all_fields[0], NULL);
				Name = all_fields[1];
				City = all_fields[2];
				Country = all_fields[3];
				IATA = all_fields[4];
				ICAO = all_fields[5];
				Latitude = stof((string)all_fields[6], NULL);
				Longitude = stof((string)all_fields[7], NULL);
				Altitude = stol((string)all_fields[8], NULL);
				Timezone = stol((string)all_fields[9], NULL);
				DST = all_fields[10];

				return AirportID;
			} catch (exception &e) {

				cout << e.what();
				return 0;
			}
		}
};

class AirportSlot {
	public:
		long AirportID;
		friend bool operator== (AirportSlot &ds1, AirportSlot &ds2);
		AirportSlot(long ID) {
			AirportID = ID;
		}
		AirportSlot() {
			AirportID = 0;
		}
};

bool operator== (AirportSlot &ds1, AirportSlot &ds2) {
	return (ds1.AirportID == ds2.AirportID);
}

bool operator== (AirportData &d1, AirportData &d2) {
	return (d1.AirportID == d2.AirportID); // ID is unique;
}

/************************class AirlinesData*************************************/
class AirlinesData {
	public:
			long AirlineID;	//Unique OpenFlights identifier for this airline.
			string Name;	//Name of the airline.
			string Alias;	//Alias of the airline. For example, All Nippon Airways is commonly known as "ANA".
			string IATA;	//2-letter IATA code, if available.
			string ICAO;	//3-letter ICAO code, if available.
			string Callsign;	//Airline callsign.
			string Country;	//Country or territory where airline is incorporated.
			string Active;	//"Y" if the airline is or has until recently been operational,
							//"N" if it is defunct. This field is not reliable: in particular, major airlines that stopped flying long ago,
							//but have not had their IATA code reassigned (eg. Ansett/AN), will incorrectly show as "Y".

	public:
		friend bool operator== (AirlinesData &ds1, AirlinesData &ds2);
		long parseline(string line) {
			stringstream lineStream(line);
			string field;

			try {
				vector<string> all_fields;
				while(getline(lineStream, field, '"')) {
					std::stringstream ss(field);
					while(std::getline(ss, field, ',')) {
						if (field.length() > 0)
							all_fields.push_back(field);
					}
					if(getline(lineStream, field, '"')) {
						all_fields.push_back(field);
					}
				}
				AirlineID = stol((string)all_fields[0], NULL);
				Name = all_fields[1];
				Alias = all_fields[2];
				IATA = all_fields[3];
				ICAO = all_fields[4];
				Callsign = all_fields[5];
				Country = all_fields[6];
				Active = all_fields[7];

				return AirlineID;
			} catch (exception &e) {

				cout << e.what();
				return 0;
			}
		}
};
class AirlineSlot {
	public:
		long AirlineID;
		friend bool operator== (AirlineSlot &ds1, AirlineSlot &ds2);
		AirlineSlot(long ID) {
			AirlineID = ID;
		}
		AirlineSlot() {
			AirlineID = 0;
		}
};
bool operator== (AirlineSlot &ds1, AirlineSlot &ds2) {
	return (ds1.AirlineID == ds2.AirlineID);
}

bool operator== (AirlinesData &d1, AirlinesData &d2) {
	return (d1.AirlineID == d2.AirlineID); // ID is unique;
}
/*************************************************************/
/************************class Routes*************************************/
class RoutesDet {
	public:
			long RouteID;
			string Airline	;//2-letter (IATA) or 3-letter (ICAO) code of the airline.
			long AirlineID;//	Unique OpenFlights identifier for airline (see Airline).
			string SourceAirport	;//3-letter (IATA) or 4-letter (ICAO) code of the source airport.
			long SourceAirportID;//	Unique OpenFlights identifier for source airport (see Airport)
			string DestAirport;//	3-letter (IATA) or 4-letter (ICAO) code of the destination airport.
			long DestAirportID;//	Unique OpenFlights identifier for destination airport (see Airport)
			string Codeshare	;//"Y" if this flight is a codeshare (that is, not operated by Airline, but another carrier), empty otherwise.
			long Stops	;//Number of stops on this flight ("0" for direct)
			string Equipment	;//3-letter codes for plane type(s) generally used on this flight, separated by spaces
	public:
		friend bool operator== (RoutesDet &ds1, RoutesDet &ds2);
		long parseline(string line) {
			stringstream lineStream(line);
			string field;vector<string> all_fields;

			try {

				while(getline(lineStream, field, '"')) {
					std::stringstream ss(field);
					while(std::getline(ss, field, ',')) {
						if (field.length() > 0)
							all_fields.push_back(field);
					}
					if(getline(lineStream, field, '"')) {
						all_fields.push_back(field);
					}
				}
				Airline = all_fields[0];
				AirlineID = stol((string)all_fields[1], NULL);
				SourceAirport = all_fields[2];
				SourceAirportID = stol((string)all_fields[3], NULL);
				DestAirport = all_fields[4];
				DestAirportID = stol((string)all_fields[5], NULL);
				if (all_fields.capacity() == 8) {
					Equipment = all_fields[7];
					Stops = stol((string)all_fields[6], NULL);
				} else {
					Codeshare = all_fields[6];
					Equipment = all_fields[8];
					Stops = stol((string)all_fields[7], NULL);
				}

				return 0;
			} catch (exception &e) {

				//cout << e.what();
				//for (int i = 0; i < all_fields.capacity(); i++)
				//	cout << all_fields[i] << endl;
				return 0;
			}
		}
};
class RouteSlot {
	public:
		long RouteID;
		friend bool operator== (RouteSlot &ds1, RouteSlot &ds2);
		RouteSlot(long ID) {
			RouteID = ID;
		}
		RouteSlot() {
			RouteID = 0;
		}
};
bool operator== (RouteSlot &ds1, RouteSlot &ds2) {
	return (ds1.RouteID == ds2.RouteID);
}

bool operator== (RoutesDet &d1, RoutesDet &d2) {
	return (d1.RouteID == d2.RouteID); // ID is unique;
}
/*************************************************************/
/************************class VacationSpot*************************************/
class VacationSpot {
	public:
			long spotID;
			string Airport;	//3-letter (IATA) or 4-letter (ICAO) code of the source airport.
			float Latitude;	//Decimal degrees, usually to six significant digits. Negative is South, positive is North.
			float Longitude;//Decimal degrees, usually to six significant digits. Negative is West, positive is East.
			string Name;	// Name of the vacation spot
	public:
		VacationSpot() {
			spotID = 0;
			Latitude = Longitude = 0;
		}
		VacationSpot(long ID) {
			spotID = ID;
			Latitude = Longitude = 0;
		}
		friend bool operator== (VacationSpot &ds1, VacationSpot &ds2);
		long parseline(string line) {
			stringstream lineStream(line);
			string field;vector<string> all_fields;

			try {

				while(getline(lineStream, field, '"')) {
					std::stringstream ss(field);
					while(std::getline(ss, field, ',')) {
						if (field.length() > 0)
							all_fields.push_back(field);
					}
					if(getline(lineStream, field, '"')) {
						all_fields.push_back(field);
					}
				}
				Airport = all_fields[0];
				Latitude = stof((string)all_fields[1], NULL);
				Longitude = stof((string)all_fields[2], NULL);
				Name = all_fields[3];

				return 0;
			} catch (exception &e) {

				//cout << e.what();
				//for (int i = 0; i < all_fields.capacity(); i++)
				//	cout << all_fields[i] << endl;
				return 0;
			}
		}
};
class VacationSpotSlot {
	public:
		long spotID;
		friend bool operator== (VacationSpotSlot &ds1, VacationSpotSlot &ds2);
		VacationSpotSlot(long ID) {
			spotID = ID;
		}
		VacationSpotSlot() {
			spotID = 0;
		}
};
bool operator== (VacationSpot &ds1, VacationSpot &ds2) {
	return (ds1.spotID == ds2.spotID);
}

bool operator== (VacationSpotSlot &d1, VacationSpotSlot &d2) {
	return (d1.spotID == d2.spotID); // ID is unique;
}
/*************************************************************/
bool iequals(const string& a, const string& b)
{
    unsigned int sz = a.size();
    if (b.size() != sz)
        return false;
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    return true;
}
AirportData * findAirport(HashMap<AirportSlot, AirportData> *airportMap, string IATA) {
	DoublyLinkedListSlotNode<AirportSlot, AirportData> *currentSlot = (DoublyLinkedListSlotNode<AirportSlot, AirportData> *)airportMap->getHeadSlot();
	while (currentSlot != NULL) {
		DoublyLinkedListDataNode<AirportData> *currentData = currentSlot->getHeadData();
		if (currentData->nodedata.IATA.compare(IATA) == 0) {
			airportMap->currSlotNode = currentSlot;
			return &(currentData->nodedata);
		} else {
			currentSlot = (DoublyLinkedListSlotNode<AirportSlot, AirportData> *)currentSlot->next;
		}
	}
	return NULL;
}

int findAirports(HashMap<AirportSlot, AirportData> *airportMap, string cityName, vector<AirportData *>& airports) {
	DoublyLinkedListSlotNode<AirportSlot, AirportData> *currentSlot = (DoublyLinkedListSlotNode<AirportSlot, AirportData> *)airportMap->getHeadSlot();
	while (currentSlot != NULL) {
		DoublyLinkedListDataNode<AirportData> *currentData = currentSlot->getHeadData();
		if (iequals(currentData->nodedata.City, cityName)) {
			airports.push_back(&currentData->nodedata);
			currentSlot = (DoublyLinkedListSlotNode<AirportSlot, AirportData> *)currentSlot->next;
		} else {
			currentSlot = (DoublyLinkedListSlotNode<AirportSlot, AirportData> *)currentSlot->next;
		}
	}
	return airports.size();
}
AirlinesData * findAirline(HashMap<AirlineSlot, AirlinesData> *airlineMap, long ID) {
	DoublyLinkedListSlotNode<AirlineSlot, AirlinesData> *currentSlot = (DoublyLinkedListSlotNode<AirlineSlot, AirlinesData> *)airlineMap->getHeadSlot();
	while (currentSlot != NULL) {
		DoublyLinkedListDataNode<AirlinesData> *currentData = currentSlot->getHeadData();
		if (currentData->nodedata.AirlineID == ID) {
			airlineMap->currSlotNode = currentSlot;
			return &(currentData->nodedata);
		} else {
			currentSlot = (DoublyLinkedListSlotNode<AirlineSlot, AirlinesData> *)currentSlot->next;
		}
	}
	return NULL;
}

int findAirlines(HashMap<AirlineSlot, AirlinesData> *airlineMap, string airlineName, vector<AirlinesData *>& airlines) {
	DoublyLinkedListSlotNode<AirlineSlot, AirlinesData> *currentSlot = (DoublyLinkedListSlotNode<AirlineSlot, AirlinesData> *)airlineMap->getHeadSlot();
	while (currentSlot != NULL) {
		DoublyLinkedListDataNode<AirlinesData> *currentData = currentSlot->getHeadData();
		if (currentData->nodedata.Name.find(airlineName) != string::npos) {
			airlines.push_back(&currentData->nodedata);
			currentSlot = (DoublyLinkedListSlotNode<AirlineSlot, AirlinesData> *)currentSlot->next;
		} else {
			currentSlot = (DoublyLinkedListSlotNode<AirlineSlot, AirlinesData> *)currentSlot->next;
		}
	}
	return airlines.size();
}

RoutesDet * findRoute(HashMap<RouteSlot, RoutesDet> *routeMap, long sourceID, long destID) {
	DoublyLinkedListSlotNode<RouteSlot, RoutesDet> *currentSlot = (DoublyLinkedListSlotNode<RouteSlot, RoutesDet> *)routeMap->getHeadSlot();
	DoublyLinkedListDataNode<RoutesDet> *currentData = currentSlot->getHeadData();
	while (currentData != NULL) {
		if ((currentData->nodedata.SourceAirportID == sourceID) && (currentData->nodedata.DestAirportID == destID)) {
			routeMap->currDataNode = currentData;
			return &(currentData->nodedata);
		} else {
			currentData = (DoublyLinkedListDataNode<RoutesDet> *)currentData->next;
		}
	}
	return NULL;
}

RoutesDet * findNextRoute(HashMap<RouteSlot, RoutesDet> *routeMap, long sourceID, long destID) {
	DoublyLinkedListDataNode<RoutesDet> *currentData = (DoublyLinkedListDataNode<RoutesDet> *)routeMap->currDataNode->next;
	while (currentData != NULL) {
		if ((currentData->nodedata.SourceAirportID == sourceID) && (currentData->nodedata.DestAirportID == destID)) {
			routeMap->currDataNode = currentData;
			return &(currentData->nodedata);
		} else {
			currentData = (DoublyLinkedListDataNode<RoutesDet> *)currentData->next;
		}
	}
	return NULL;
}

#define pi 3.14159265358979323846

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts decimal degrees to radians             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double deg2rad(double deg) {
  return (deg * pi / 180);
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts radians to decimal degrees             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double rad2deg(double rad) {
  return (rad * 180 / pi);
}//		if (route->Codeshare.compare("Y") == 0)
//			cout << " (codeshare)"<< endl;
//		else


double distance(double lat1, double lon1, double lat2, double lon2, char unit) {
  double theta, dist;
  theta = lon1 - lon2;
  dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
  dist = acos(dist);
  dist = rad2deg(dist);
  dist = dist * 60 * 1.1515;
  switch(unit) {
    case 'M':
      break;
    case 'K':
      dist = dist * 1.609344;
      break;
    case 'N':
      dist = dist * 0.8684;
      break;
  }
  return (dist);
}

int findAlternateSourceAirports(HashMap<AirportSlot, AirportData> *airportMap, HashMap<RouteSlot, RoutesDet> *routesMap, AirportData * airport1, AirportData * destAirport,  vector<AirportData*>& airports, vector<AirportData*>& nearby) {
	DoublyLinkedListSlotNode<AirportSlot, AirportData> *currentSlot = (DoublyLinkedListSlotNode<AirportSlot, AirportData> *)airportMap->getHeadSlot();
	airports.clear();
	while (currentSlot != NULL) {
		DoublyLinkedListDataNode<AirportData> *currentData = currentSlot->getHeadData();
		AirportData airport2 = currentData->nodedata;
		if (distance(airport1->Latitude, airport1->Longitude, airport2.Latitude, airport2.Longitude, 'M') < (double)200.0f) {
			nearby.push_back(&currentData->nodedata);
			if (findRoute(routesMap, airport2.AirportID, destAirport->AirportID)) {
				airports.push_back(&currentData->nodedata);
			}
			currentSlot = (DoublyLinkedListSlotNode<AirportSlot, AirportData> *)currentSlot->next;
		} else {
			currentSlot = (DoublyLinkedListSlotNode<AirportSlot, AirportData> *)currentSlot->next;
		}
	}
	return airports.size();
}
int findAlternateDestAirports(HashMap<AirportSlot, AirportData> *airportMap, HashMap<RouteSlot, RoutesDet> *routesMap, AirportData * airport1, AirportData * sourceAirport,  vector<AirportData*>& airports, vector<AirportData*>& nearby) {
	DoublyLinkedListSlotNode<AirportSlot, AirportData> *currentSlot = (DoublyLinkedListSlotNode<AirportSlot, AirportData> *)airportMap->getHeadSlot();
	airports.clear();
	while (currentSlot != NULL) {
		DoublyLinkedListDataNode<AirportData> *currentData = currentSlot->getHeadData();
		AirportData airport2 = currentData->nodedata;
		if (distance(airport1->Latitude, airport1->Longitude, airport2.Latitude, airport2.Longitude, 'M') < (double)200.0f) {
			nearby.push_back(&currentData->nodedata);
			if (findRoute(routesMap, sourceAirport->AirportID, airport2.AirportID))
				airports.push_back(&currentData->nodedata);
			currentSlot = (DoublyLinkedListSlotNode<AirportSlot, AirportData> *)currentSlot->next;
		} else {
			currentSlot = (DoublyLinkedListSlotNode<AirportSlot, AirportData> *)currentSlot->next;
		}
	}
	return airports.size();
}


/*************************************************************/
//Function declarations
void Travel(HashMap<AirportSlot, AirportData>& airportMap, HashMap<AirlineSlot, AirlinesData>& airlineMap, HashMap<RouteSlot, RoutesDet>& routesMap, HashMap<VacationSpotSlot, VacationSpot>& vacationMap, bool vacation);
/*************************************************************/
int main(int argc, char*argv[]) {
	HashMap<AirportSlot, AirportData> airportMap;
	HashMap<AirlineSlot, AirlinesData> airlineMap;
	HashMap<RouteSlot, RoutesDet> routesMap;
	HashMap<VacationSpotSlot, VacationSpot> vacationMap;


	ifstream airportfile("data/airports.dat");
	for (string line; getline(airportfile, line); )
	{
		AirportData *data = new AirportData();
		AirportSlot *slot= new AirportSlot(data->parseline(line));
		airportMap.insert(*slot);
		airportMap.insert(*slot, *data);
	}
	airportfile.close();

	ifstream airlinefile("data/airlines.dat");
	for (string line; getline(airlinefile, line); )
	{
		AirlinesData *data = new AirlinesData();
		AirlineSlot *slot= new AirlineSlot(data->parseline(line));
		airlineMap.insert(*slot);
		airlineMap.insert(*slot, *data);
	}
	airlinefile.close();

	ifstream routesfile("data/routes.dat");
	RouteSlot *slot= new RouteSlot();
	routesMap.insert(*slot);
	for (string line; getline(routesfile, line); )
	{
		RoutesDet *data = new RoutesDet();
		data->parseline(line);
		routesMap.insert(*slot, *data);
	}
	routesfile.close();

	ifstream vacationfile("data/vacationspots.dat");
	VacationSpotSlot *vcslot= new VacationSpotSlot();
	vacationMap.insert(*vcslot);
	int i = 1;

	for (string line; getline(vacationfile, line); )
	{
		VacationSpot *data = new VacationSpot(i++);
		data->parseline(line);
		vacationMap.insert(*vcslot, *data);
	}
	vacationfile.close();
	cout << "\n************************************************" << endl;
	cout << "\tWELCOME TO AIRLINE TRACKING SYSTEM!!!\n";
	cout << "\n************************************************" << endl;
	char c = 'y';
	int opt;
	do{
		cout << "------------------------------------------------" << endl;
		cout << "\t\tMAIN MENU\n";
		cout << "------------------------------------------------" << endl;
		cout << "\n1. SEARCH FOR AIRPORTS.\n2. SEARCH FOR AIRLINES.\n3. PLAN TRAVEL.\n4. GO FOR VACATION.\n\n";
		cout << "\nPlease enter your choice :";
		cin >> opt;
		string startCity;
		vector<AirportData *> airports;
		vector<AirlinesData *> airlines;
		switch(opt){
			case 1:
				cout << "\nSearch for Airport based on City : ";
				cin.ignore(1, '\n');
				getline(cin, startCity);
				airports.clear();
				if (findAirports(&airportMap, startCity, airports)) {
					cout << "\nAirport(s) found:" << endl;
					for (i = 0; (unsigned)i < airports.size(); i++) {
						cout << i+1 << ": " << airports.at(i)->Name << ", " << airports.at(i)->City << ", " << airports.at(i)->Country << endl;
					}
				} else
					cerr << "\nOops!!! Airport Not found.Exiting!!" << endl;
				break;
			case 2:
				cout << "\nSearch for Airline: ";
				cin.ignore(1, '\n');
				getline(cin, startCity);
				airlines.clear();
				if (findAirlines(&airlineMap, startCity, airlines)) {
					cout << "\nAirline(s) found:" << endl;
					for (i = 0; (unsigned)i < airlines.size(); i++) {
						cout << i+1 << ": " << airlines.at(i)->Name;
						if (airlines.at(i)->IATA.size() > 0)
							cout << "(" << airlines.at(i)->IATA << ")";
						else if (airlines.at(i)->ICAO.size() > 0)
							cout << "(" << airlines.at(i)->ICAO << ")";
						cout << " head-quartered at " << airlines.at(i)->Country << ". " << endl;
					}
				} else
					cerr << "\nOops!!! Airline Not found.Exiting!!" << endl;
				break;
			case 3:
				Travel(airportMap,airlineMap, routesMap, vacationMap, false);
				break;
			case 4:
				Travel(airportMap,airlineMap, routesMap, vacationMap, true);
				break;
			default :
				cout << "\nInvalid choice!";
				break;
		}
		cout << "\nDo you want to continue(y/n)?:";
		cin >> c;
	} while( c != 'n' );

	return 0;
}



void Travel(HashMap<AirportSlot, AirportData>& airportMap, HashMap<AirlineSlot, AirlinesData>& airlineMap, HashMap<RouteSlot, RoutesDet>& routesMap, HashMap<VacationSpotSlot, VacationSpot>& vacationMap, bool vacation) {
	int i;
	DoublyLinkedListDataNode<VacationSpot> *vacspot;
	vector<AirportData *> airports;
	vector<AirportData *> nearbySourceAirports;
	vector<AirportData *> nearbyDestAirports;
	if (vacation) {
		vacspot = vacationMap.getHeadSlot()->getHeadData();
		cout << "\nPlease find  below the Vacation Spots" << endl;
		cout << "---------------------------------------" << endl;
		for (i = 0; i < vacationMap.getHeadSlot()->getSize(); i++) {
			cout << vacspot->nodedata.spotID << ". " << vacspot->nodedata.Name << endl;
			vacspot = (DoublyLinkedListDataNode<VacationSpot> *)vacspot->next;
		}
		do {
			cout << "\nSelect a vacation spot:  ";
			cin >> i;
			if ((i > 0) && (i <= vacationMap.getHeadSlot()->getSize())) {
				break;
			} else {
				cout << "\nInvalid selection...please select again..." << endl;
			}
		} while (true);
		vacspot = vacationMap.getHeadSlot()->getHeadData();
		for (; i > 1; i--) {
			vacspot = (DoublyLinkedListDataNode<VacationSpot> *)vacspot->next;
		}
		cout << "\nTraveling to " << vacspot->nodedata.Name << endl;
	}
	cout << "\nEnter Start City: ";
	string startCity;
	cin.ignore(1, '\n');
	getline(cin, startCity);

	if (findAirports(&airportMap, startCity, airports) > 1) {
		cout << "\nMultiple airports found, choose the correct one..." << endl;
		for (i = 0; (unsigned)i < airports.size(); i++) {
			cout << i+1 << ": " << airports.at(i)->Name << ", " << airports.at(i)->City << ", " << airports.at(i)->Country << endl;
		}
		cout << "\nEnter selection: ";
		cin >> i;
	} else
		i = 1;

	AirportData * airport1;
	try {
		airport1 = airports.at(i-1);
	} catch (out_of_range &e) {
		cerr << "\nOops!!!City Not found.Exiting!!" << endl;
		return;
	}
	AirportData * airport2;
	if (vacation) {
		airport2 = findAirport(&airportMap, vacspot->nodedata.Airport);
		if (airport2 == NULL) {
			cerr <<  "\nNo airport found!!!" << vacspot->nodedata.Airport;
			return;
		}
	} else {
		cout << "\nEnter Destination City: ";
		string startCity;
		cin.ignore(1, '\n');
		getline(cin, startCity);
		airports.clear();
		if (findAirports(&airportMap, startCity, airports) > 1) {
			cout << "\nMultiple airports found, choose the correct one..." << endl;
			for (i = 0; (unsigned)i < airports.size(); i++) {
				cout << i+1 << ": " << airports.at(i)->Name << ", " << airports.at(i)->City << ", " << airports.at(i)->Country << endl;
			}
			cout << "\nEnter selection: ";
			cin >> i;
		} else
			i = 1;
		try {
			airport2 = airports.at(i-1);
		} catch (out_of_range &e) {
			cerr << "\nOops!!!City Not found.Exiting!!" << endl;
			return;
		}
	}
	RoutesDet *route = findRoute(&routesMap, airport1->AirportID, airport2->AirportID);
	if (route) {
		cout << "\nTotal distance by air from " << airport1->City << " to " << airport2->City << ": " << distance(airport1->Latitude, airport1->Longitude, airport2->Latitude, airport2->Longitude, 'M') << " miles"<< endl;
		cout <<"*************************************************************************************************************\n";
		cout << "\t\t\tITINERARY DETAILS!!!\n";
		cout <<"*************************************************************************************************************\n";
		cout << "Flight From \t\t\t\t Flight To\t\t\t\t\t\tOperated By\n";
		cout << "---------------------------------------------------------------------------------------------------------\n";
		while (route != NULL) {
			AirlinesData *airline = findAirline(&airlineMap, route->AirlineID);
			//cout << "\nFlight from " << airport1->Name << ", " << airport1->City << " to ";
			//cout << vacspot->nodedata.Name << " via "<< airport2->Name << ", " << airport2->City << ": Operated by " << airline->Name;

			cout <<airport1->Name << "," << airport1->City;
			cout <<"\t";
			if (vacation)
				cout << vacspot->nodedata.Name << " via ";
			cout << airport2->Name << ", " << airport2->City;
			cout <<"\t" << airline->Name;
			cout << endl;
			route = findNextRoute(&routesMap, airport1->AirportID, airport2->AirportID);
		}
	} else {
		cout << "\nNo direct flights found." << endl;
		vector<AirportData *> airports;
		if (findAlternateSourceAirports(&airportMap, &routesMap, airport1, airport2, airports, nearbySourceAirports)) {
			cout << "However, there are flights from neighboring airports..." << endl;
			for (i = 0; (unsigned)i < airports.size(); i++) {
				cout << i+1 << ": " << airports.at(i)->Name << ", " << airports.at(i)->City << ", " << airports.at(i)->Country;
				cout << " (" << distance(airport1->Latitude, airport1->Longitude, airports.at(i)->Latitude, airports.at(i)->Longitude, 'M');
				cout <<  " miles from " << airport1->City << ")" << endl;
			}
			if (airports.size() > 1) {
				cout << "Choose an airport: ";
				cin >> i;
			} else {
				i = 1;
			}
			airport1 = airports.at(i-1);
			RoutesDet *route = findRoute(&routesMap, airport1->AirportID, airport2->AirportID);
			if (route) {
				cout << "\nTotal distance by air from " << airport1->City << " to " << airport2->City << ": " << distance(airport1->Latitude, airport1->Longitude, airport2->Latitude, airport2->Longitude, 'M') << " miles"<< endl;
				cout <<"*************************************************************************************************************\n";
				cout << "\t\t\tITINERARY DETAILS!!!\n";
				cout <<"*************************************************************************************************************\n";
				cout << "Flight From \t\t\t\t Flight To\t\t\t\t\t\tOperated By\n";
				cout << "---------------------------------------------------------------------------------------------------------\n";
				while (route != NULL) {
					AirlinesData *airline = findAirline(&airlineMap, route->AirlineID);
					cout <<airport1->Name << "," << airport1->City;
					cout <<"\t";

					if (vacation)
						cout << vacspot->nodedata.Name << " via ";
					cout << airport2->Name << ", " << airport2->City;
					cout <<"\t" << airline->Name;
					cout << endl;
					route = findNextRoute(&routesMap, airport1->AirportID, airport2->AirportID);
				}
			}
		} else if (findAlternateDestAirports(&airportMap, &routesMap, airport2, airport1, airports, nearbyDestAirports)) {
			cout << "However, there are flights to neighboring airports..." << endl;
			for (i = 0; (unsigned)i < airports.size(); i++) {
				cout << i+1 << ": " << airports.at(i)->Name << ", " << airports.at(i)->City << ", " << airports.at(i)->Country;
				cout << " (" << distance(airport2->Latitude, airport2->Longitude, airports.at(i)->Latitude, airports.at(i)->Longitude, 'M');
				cout <<  " miles from " << airport2->City << ")" << endl;
			}
			if (airports.size() > 1) {
				cout << "Choose an airport: ";
				cin >> i;
			} else {
				i = 1;
			}
			AirportData * airport2 = airports.at(i-1);
			RoutesDet *route = findRoute(&routesMap, airport1->AirportID, airport2->AirportID);
			if (route) {
				cout << "Total distance by air from " << airport1->City << " to " << airport2->City << ": " << distance(airport1->Latitude, airport1->Longitude, airport2->Latitude, airport2->Longitude, 'M') << " miles"<< endl;
				cout <<"*************************************************************************************************************\n";
				cout << "\t\t\tITINERARY DETAILS!!!\n";
				cout <<"*************************************************************************************************************\n";
				cout << "Flight From \t\t\t\t Flight To\t\t\t\t\t\tOperated By\n";
				cout << "---------------------------------------------------------------------------------------------------------\n";

				while (route != NULL) {
					AirlinesData *airline = findAirline(&airlineMap, route->AirlineID);
					//cout << "Flight from " << airport1->Name << ", " << airport1->City << " to ";
					//cout << vacspot->nodedata.Name << " via "<< airport2->Name << ", " << airport2->City << ": Operated by " << airline->Name;
					cout <<airport1->Name << "," << airport1->City;
					cout <<"\t";
					if (vacation)
						cout << vacspot->nodedata.Name << " via ";
					cout << airport2->Name << ", " << airport2->City;
					cout <<"\t" << airline->Name;
					cout << endl;
					route = findNextRoute(&routesMap, airport1->AirportID, airport2->AirportID);
				}
			}
		} else {
			AirportData *originalSource = airport1;
			AirportData *originalDest = airport2;
			RoutesDet *route;
			for (i = 0; (unsigned)i < nearbySourceAirports.size(); i++) {
				for (int j = 0; (unsigned)j < nearbyDestAirports.size(); j++) {
					//cout << nearbySourceAirports[i].City << "----->" << nearbyDestAirports[j].City << endl;
					route = findRoute(&routesMap, nearbySourceAirports[i]->AirportID, nearbyDestAirports[j]->AirportID);
					if (route) {
						airport1 = nearbySourceAirports[i];
						airport2 = nearbyDestAirports[j];
						cout << "-------------------------------------------------------------------------------------------------------------" << endl;
						cout << "Suggested alternate route from " << airport1->City << " (";
						cout << distance(airport1->Latitude, airport1->Longitude, originalSource->Latitude, originalSource->Longitude, 'M');
						cout <<  " miles from " << originalSource->City << ") to " << airport2->City << " (";
						cout << distance(airport2->Latitude, airport2->Longitude, originalDest->Latitude, originalDest->Longitude, 'M');
						cout <<  " miles from " << originalDest->City << ")" << endl;
						cout << "\nTotal distance by air from " << airport1->City << " to " << airport2->City << ": " << distance(airport1->Latitude, airport1->Longitude, airport2->Latitude, airport2->Longitude, 'M') << " miles"<< endl;
						cout <<"*************************************************************************************************************\n";
						cout << "\t\t\tITINERARY DETAILS!!!\n";
						cout <<"*************************************************************************************************************\n";
						cout << "Flight From \t\t\t\t Flight To\t\t\t\t\t\t\tOperated By\n";
						cout << "---------------------------------------------------------------------------------------------------------\n";
						while (route != NULL) {
							AirlinesData *airline = findAirline(&airlineMap, route->AirlineID);
							//cout << "\nFlight from " << airport1->Name << ", " << airport1->City << " to ";
							//cout << vacspot->nodedata.Name << " via "<< airport2->Name << ", " << airport2->City << ": Operated by " << airline->Name;
							cout <<airport1->Name << "," << airport1->City;
							cout <<"\t";
							if (vacation)
								cout << vacspot->nodedata.Name << " via ";
							cout << airport2->Name << ", " << airport2->City;
							cout <<"\t" << airline->Name;
							cout << endl;
							route = findNextRoute(&routesMap, airport1->AirportID, airport2->AirportID);
						}
						cout << "-------------------------------------------------------------------------------------------------------------" << endl;
					}
				}
			}
		}
	}
}
