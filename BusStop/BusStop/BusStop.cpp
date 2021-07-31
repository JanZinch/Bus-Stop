#include <iostream>
#include <fstream>
#include <string>

#include<vector>
#include <list>
//#include <debugapi.h>

#include "Service.h"




using namespace std;



bool first_condition(const list<TravelService>::iterator &it, TravelService &current) {

	return it->GetDepature() == current.GetDepature() && it->GetArrival() > current.GetArrival();
}

bool second_condition(const list<TravelService>::iterator &it, TravelService &current) {

	return it->GetArrival() == current.GetArrival() && it->GetDepature() < current.GetDepature();
}

bool third_condition(const list<TravelService>::iterator &it, TravelService &current) {

	return it->GetDepature() < current.GetDepature() && it->GetArrival() > current.GetArrival();
}

bool fourth_condition(const list<TravelService>::iterator &it, TravelService &current) {

	return it->GetDepature() == current.GetDepature() && it->GetArrival() == current.GetArrival() && it->GetCompany() == GROTTY;
}




void CheckForEfficient(list<TravelService>& timetable) {

	int i, j = 0;

	bool* selected_values_mask = new bool[timetable.size()];
	
	for (i = 0; i < timetable.size(); i++) {
	
		selected_values_mask[i] = false;
	}
	
	TravelService current;
	auto i_iter = timetable.begin(), j_iter = timetable.begin();

	for (i = 0; i < timetable.size(); i++) {

		current = TravelService(POSH, i_iter->GetDepature(), i_iter->GetArrival());
		//i_iter++;

		j = 0;

		for (j_iter = timetable.begin(); j_iter != timetable.end(); j_iter++) {

			if (j_iter == i_iter) { j++; continue; }

			if (first_condition(j_iter, current) || second_condition(j_iter, current)
				|| third_condition(j_iter, current) || fourth_condition(j_iter, current)) {
			
				selected_values_mask[j] = true;
			
			}


			//if ((*j_iter).GetDepature() == current.GetDepature()
			//	&& (*j_iter).GetArrival() > current.GetArrival()) {

			//	//cout << (*j_iter).second.GetArrival().ToString() << " > " << current.ToString() << endl;

			//	selected_values_mask[j] = true;
			//}

			//if ((*j_iter).GetArrival() == current.GetArrival()
			//	&& (*j_iter).GetDepature() < current.GetDepature()) {

			//	selected_values_mask[j] = true;
			//}

			//if ((*j_iter).GetDepature() < current.GetDepature()
			//	&& (*j_iter).GetArrival() > current.GetArrival()) {


			//	selected_values_mask[j] = true;

			//}

			//if ((*j_iter).GetDepature() == current.GetDepature()
			//	&& (*j_iter).GetArrival() == current.GetArrival() && (*j_iter).GetCompany() == Company::GROTTY) {

			//	selected_values_mask[j] = true;

			//}

			j++;
		}

		++i_iter;
	}

	i_iter = timetable.begin();
	i = 0;

	while (i_iter != timetable.end()) {
	
		if (selected_values_mask[i]) {
		
			i_iter = timetable.erase(i_iter);
			i++;
		}
		else { ++i_iter; i++; }
	}

	delete[] selected_values_mask;
}


int main()
{

	const string original_timetable_path = "OriginalTimetableTest.txt";
	const string resulting_timetable_path = "ResultingTimetable.txt";

	list<TravelService> timetable;

	ifstream file;
	file.open(original_timetable_path);

	try {
	
		if (!file.is_open()) {

			cout << "File " + original_timetable_path + " is not found!";
			exit(EXIT_FAILURE);
		}
		else
		{
			string company, depature, arrival = "";

			while (!file.eof()) {

				file >> company;
				file >> depature;
				file >> arrival;

				if (company == "") break;

				if (company != GROTTY && company != POSH) {

					throw exception(BAD_DATA);
				}

				timetable.emplace_back(TravelService(company, HMTime(depature), HMTime(arrival)));
				company = "";
			}


			for (auto it : timetable)
			{
				cout << it << endl;
			}
			cout << " - - - " << endl;

			timetable.sort();

			for (auto it : timetable)
			{
				cout << it << endl;
			}
			cout << " - - - " << endl;

			timetable.remove_if([](TravelService value) { return value > ONE_HOUR; });

			for (auto it : timetable)
			{
				cout << it << endl;
			}
			cout << " - - - " << endl;

			CheckForEfficient(timetable);

			for (auto it : timetable)
			{
				cout << it << endl;
			}
			cout << " - - - " << endl;
		
		}
	
		exit(EXIT_SUCCESS);

	}
	catch (exception ex) {
	
		cout << ex.what() << endl;
		exit(EXIT_FAILURE);	
	}
	

}


