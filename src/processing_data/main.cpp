
#include <iostream>
#include <vector> 
#include <string> 
#include <fstream>  
#include<cmath>
#include <cstdlib>

//#include "Station.hpp"

using namespace std;

int main(){
	
	cout << "hello world" << endl;
/*	
	cout << "hello world" << endl;
	Station s1;
	s1.readWeightsData("../../data/weights/weight_line_1_1.txt");
	s1.readDistancesData("../../data/distances/line_1_1.txt");
	s1.setPopulation(30000);
	s1.computePredictedNumber(1.4, 0.007);
	cout << s1.getPredictedNumber() << endl;
	
*/
	/*string w_path = "../../data/weights/weight_line_1_";
	string d_path = "../../data/distances/line_1_";
	Station station[16];
	int population[16] = {24759, 26537, 26340, 74636, 52352, 109716, 47455, 47333,
						 42052, 80428, 83254, 32251, 32995, 18466, 10118, 6225};

	string temp[16] = {"1", "2", "3", "4", "5", "6", "7", "8",
					 "9", "10", "11", "12", "13", "14", "15", "16"};

	for (int i = 0; i < 15; ++i){
		
		station[i].readWeightsData("../../data/weights/weight_line_1_"+temp[i]+".txt");
		station[i].readDistancesData("../../data/distances/line_1_"+temp[i]+".txt");
		station[i].setPopulation(population[i]);
		station[i].computePredictedNumber(1.4, 0.007);
		cout << i << ": " << station[i].getPredictedNumber() << endl;


	}

*/
	return 0;
}