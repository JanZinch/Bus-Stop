#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

#include "Service.h"

using namespace std;


bool first_condition(const list<TravelService>::iterator &it, TravelService &current) {   

	return it->depature() == current.depature() && it->arrival() > current.arrival();
}

bool second_condition(const list<TravelService>::iterator &it, TravelService &current) {

	return it->arrival() == current.arrival() && it->depature() < current.depature();
}

bool third_condition(const list<TravelService>::iterator &it, TravelService &current) {

	if (it->midnightСrossing() && !current.midnightСrossing() || !it->midnightСrossing() && current.midnightСrossing()) {
	
		return it->depature() > current.depature() && it->arrival() > current.arrival();
	}
	else {
	
		return it->depature() < current.depature() && it->arrival() > current.arrival();	
	}	
}

bool fourth_condition(const list<TravelService>::iterator &it, TravelService &current) {			

	return it->depature() == current.depature() && it->arrival() == current.arrival() && it->company() == GROTTY && current.company() == POSH;
}


void checkForEfficient(list<TravelService>& timetable) {
	
	TravelService selected_entry;
	list<TravelService>::iterator i_iter, j_iter;
	i_iter = j_iter = timetable.begin();

	for (int i = 0; i < timetable.size(); i++) {

		selected_entry = TravelService(i_iter->company(), i_iter->depature(), i_iter->arrival());

		for (j_iter = timetable.begin(); j_iter != timetable.end(); j_iter++) {		

			if (j_iter == i_iter) continue;
		
			if (first_condition(j_iter, selected_entry) || second_condition(j_iter, selected_entry) || third_condition(j_iter, selected_entry)
				|| fourth_condition(j_iter, selected_entry)) {

				j_iter->Select();
			}
		}

		++i_iter;
	}

	i_iter = timetable.begin();

	while (i_iter != timetable.end()) {
	
		if (i_iter->isSelected()) {
		
			i_iter = timetable.erase(i_iter);
		}
		else  ++i_iter; 
	}		
}

bool compareCompanies(TravelService left, TravelService right) {

	return left.company() == POSH && right.company() == GROTTY;
}

void consolePrint(list<TravelService> &timetable) {

	cout << " - - - " << endl;
	for (auto var : timetable)
	{
		cout << var << endl;
	}
	cout << " - - - " << endl;
}


int main()
{
	const string original_timetable_path = "OriginalTimetable.txt";
	const string resulting_timetable_path = "ResultingTimetable.txt";

	list<TravelService> timetable;

	fstream file;
	file.open(original_timetable_path, fstream::in);

	try {
	
		if (!file.is_open()) {

			cout << "File " + original_timetable_path + " is not found!";
			exit(EXIT_FAILURE);
		}
		else
		{
			TravelService buffer;

			while (!file.eof()) {

				file >> buffer;

				if (buffer.company() != GROTTY && buffer.company() != POSH) {
				
					throw exception(BAD_DATA);
				}

				timetable.emplace_back(buffer);
			}

			file.close();

			consolePrint(timetable);

			timetable.unique();
			timetable.remove_if([](TravelService value) { return value > ONE_HOUR; });			
			timetable.sort();			

			consolePrint(timetable);

			checkForEfficient(timetable);	
			timetable.sort(compareCompanies);

			consolePrint(timetable);
		
			file.open(resulting_timetable_path, fstream::out, fstream::trunc);

			if (!file.is_open()) {

				cout << "File " + resulting_timetable_path + " is not found!";
				exit(EXIT_FAILURE);
			}
			else {
			
				bool blank_line_setted = false;

				for (TravelService var : timetable)
				{
					if (!blank_line_setted && var.company() == GROTTY) { 
						
						file << endl;
						blank_line_setted = true;						
					}

					file << var << endl;
				}
			
				file.close();			
			}	
		}
	
		exit(EXIT_SUCCESS);

	}
	catch (exception ex) {
	
		cout << ex.what() << endl;
		file.close();
		exit(EXIT_FAILURE);	
	}
	catch (...) {
	
		file.close();
		exit(EXIT_FAILURE);
	}
	

}


