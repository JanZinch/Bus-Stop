#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include <math.h>
#include <cassert>

//#include <debugapi.h>

using namespace std;

#define ONE_HOUR 60
#define BAD_DATA "Incorrect original data!"

#define GROTTY "Grotty"
#define POSH "Posh"



class HMTime {

private:

	time_t time;	

public:
	

	time_t get_time_t() {

		return time;
	}

	static time_t to_time_t(int hours, int minutes) {

		return (time_t)(hours * ONE_HOUR) + (time_t)minutes;
	}
	

	HMTime() : time(0) {};

	HMTime(string nm_str) : HMTime() {
	
		const short number_size = 3;
		char buf[number_size] = "";
		int i, j, k = 0;
		int hours, minutes;

		for (i = 0; i < nm_str.size(); i++) {

			if (nm_str[i] == ':') {

				buf[number_size - 1] = '\0';
				hours = atoi(buf);
				k = 0;

				for (j = i + 1; j < nm_str.size(); j++) {

					if (k >= number_size) {
					
						throw out_of_range(BAD_DATA);
					};
					
					buf[k] = nm_str[j];
					k++;
				}

				buf[number_size - 1] = '\0';
				minutes = atoi(buf);

				break;
			}

			if (k >= number_size) {

				throw out_of_range(BAD_DATA);
			};

			buf[k] = nm_str[i];
			k++;
		}

		time = to_time_t(hours, minutes);

		//try {
		
			
		
	/*	}
		catch (exception ex) {
		
			cout << ex.what() << endl;
		
		}*/


		
	
	}


	friend ostream& operator<< (ostream& out, HMTime& hm_time);

	bool operator==(HMTime other) {

		return this->time == other.time;
	}

	bool operator>(HMTime other) {

		return this->time > other.time;
	}

	bool operator<(HMTime other) {

		return this->time < other.time;
	}

	time_t operator-(HMTime other) {

		return abs(this->time - other.time);
	}

	bool operator<=(time_t minutes) {
	
		return this->time <= minutes;	
	}
	

};

ostream& operator<< (ostream& out, HMTime& hm_time)
{
	out << setfill('0') << setw(2) << hm_time.time / ONE_HOUR << ":" << setw(2) << hm_time.time % ONE_HOUR;
	return out;
}



class TravelService
{
private:
	
	string company;
	HMTime departure_time;
	HMTime arrival_time;

public:
	
	TravelService();
	TravelService(string, HMTime, HMTime);
	bool operator<(const TravelService &other);
	friend ostream& operator<< (ostream& out, TravelService& traveling);


	bool operator<=(time_t minutes) {

		return arrival_time - departure_time <= minutes;
	}

	bool operator>(time_t minutes) {

		return arrival_time - departure_time > minutes;
	}

	HMTime GetDepature() {
	
		return departure_time;
	}

	HMTime GetArrival() {
	
		return arrival_time;
	}

	string GetCompany() {
	
		return company;
	}


};

TravelService::TravelService()
{
	company = "";
	departure_time = HMTime();
	arrival_time = HMTime();
}


TravelService::TravelService(string company, HMTime depature, HMTime arrival)
{
	this->company = company;
	departure_time = depature;
	arrival_time = arrival;
}

bool TravelService::operator<(const TravelService &other) {

	return this->departure_time < other.departure_time;
}


ostream& operator<< (ostream& out, TravelService& traveling)
{
	out << traveling.company << " " << traveling.departure_time << " " << traveling.arrival_time;
	return out;
}



