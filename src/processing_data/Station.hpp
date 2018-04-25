#include <iostream>
#include <vector> 
#include <string> 
#include <fstream>  
#include<cmath>
#include <cstdlib>


#define MAX_ROWS 45
#define MAX_COLUMNS 45
//#define MAX_GRIDS 1609
#define MAX_GRIDS 2000
using namespace std;

/*
*	栅格类
*/
struct Grid{
	int distance; //到站点距离
	double walk_probability; //出行率或发生率
	int weight; //土地和密度的和权重
	int weight_upper_limit; //权重范围上限
	int weight_lower_limit; //权重范围下限
	int population; //the number of population in each little grid
};


/*
*	轨道交通站点类
*	
*
*/ 
class Station{
public:
	Station();
	~Station();


	/* return the name of the station */
	string getName();
	/* set or change the name of the station with the @param _name */
	void setName(string _name);


	/* return the real passager number at a station between 7:30am to 8:29am */
	int getRealNumber();

	/* set or change the real passager number of the station with the @param _number  */
	void setRealNumber(int _number);


	/* return the predicted passager number at a station between 7:30am to 8:29am  */
	int getPredictedNumber();

	/* cannot set or change the real passager number of the station with the @param _number 
	 * the variable predicted_passenger_number cannot change or set out of the class
	 * the value of the variable predicted_passenger_number just can be get by computing
	 ** void setPredictedNumber(int _number);
	*/


	/* return the number of population */
	int gePopulation();
	/* set or change the value of population around the station
	 * @param _population
	 */
	void setPopulation(int _number);
            

	/* functions about the Grid array */
	//Grid** getGrid();
	//void setGrid(Grid _grid);

	/* compute the predicted number by using negative logistic function
	 * @param a, b are the corresponding parameter in the negative logistic function
	 * the result of predicted passagers number will not return 
	 * the result will store at the variable predicted_number
	 * call the getPredictedNumber() could get the result
	 * this function will call 
	 */
	void computePredictedNumber(double a, double b);


	/* compute the walk probability from the distance
	 * @param a, b are the corresponding parameter in the negative logistic function
	 * be called in computePredictedNumber function
	 */
	void computeWalkProbability(double a, double b);


	/* disperse the population into each grid 
	 * the method is about the weight and the total population number
	 */
	void computeDiscretePopulation();


	/* read the data of the weights
	 * it will set the weight of Grid
	 * the files of the weight data are in the data/weights begining with "weight_line_*_*"
	 * the first * is a positive integer which means the number of the line
	 * the second * is a positive integer which means the number of the station
	 * the Huangchun station is line 4 station 1
	 * so the filename is "weight_line_4_1"
	 * @param _path is the path of the file needed to be read
	 */
	void readWeightsData(string _path); 


	/* read the data of the weights
	 * it will set the distance of Grid
	 * the files of the distance data are in the data/weights begining with "line_*_*"
	 * the first * is a positive integer which means the number of the line
	 * the second * is a positive integer which means the number of the station
	 * the Huangchun station is line 4 station 1
	 * so the filename is "line_4_1"
	 * @param _path is the path of the file needed to be read
	 */
	void readDistancesData(string _path);




	/* write the result of data after processing 
	 * the data contains:
	 * the line name and each station name
	 * the real passagers number and the predicted value
	 * the parameter 'a' and 'b' of negative logistic function
	** void writeAnalysedData();
	*/


private:
	string station_name; //站点名字

	/* 早高峰7:30-8:29一小时的客流发送量 */
	int real_number; //实际发生客流量
	int predicted_number; //预测客流发生量

	/* population */
	int population_number; //the population around the station in a circle(r = 700m) 

	/* 栅格数据 */
	int rows; //栅格行数
	int total_grids; //the sum number of grid
	int grids_each_row[MAX_ROWS]; //每行的栅格数
	Grid grids[MAX_ROWS][MAX_COLUMNS]; //栅格数据
};



Station::Station(){
	station_name = "";
	real_number = 0;
	predicted_number = 0;
	population_number = 0;
	rows = MAX_ROWS;
	total_grids = MAX_GRIDS;

	int temp_grids_each_row[rows] = {11,17,21,25,27,29,33,35,35,37,39,39,41,41,
									43,43,43,43,45,45,45,45,45,45,45,45,45,43,
									43,43,43,41,41,39,39,37,35,35,33,29,27,25,
									21,17,11};

	for (int i = 0; i < rows; ++i){
		grids_each_row[i] = temp_grids_each_row[i];
	}

	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < grids_each_row[i]; ++j){
			grids[i][j].distance = 0;
			grids[i][j].walk_probability = 0;
			grids[i][j].weight = 0;
			grids[i][j].weight_lower_limit = 0;
			grids[i][j].weight_upper_limit = 0;
			grids[i][j].population = 0;
		}	
	}
}


Station::~Station(){
}


string Station::getName(){
	return station_name;
}


void Station::setName(string _name){
	station_name = _name;
}


int Station::getRealNumber(){
	return real_number;
}


void Station::setRealNumber(int _number){
	real_number = _number;
}


int Station::getPredictedNumber(){
	return predicted_number;
}


int Station::gePopulation(){
	return population_number;
}


void Station::setPopulation(int _number){
	population_number = _number;
}
            

void Station::computePredictedNumber(double a, double b){
	//call the following two functions
	computeWalkProbability(a,b);
	computeDiscretePopulation();
	int counter = 0;

	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < grids_each_row[i]; ++j){
			counter += (grids[i][j].walk_probability*grids[i][j].population );
		}
	}
	predicted_number = counter;
}

void Station::computeWalkProbability(double a, double b){
	int e = exp(1); //自然数e
	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < grids_each_row[i]; ++j){
			grids[i][j].walk_probability = (pow(e,a-b*grids[i][j].distance))/(1+pow(e,a-b*grids[i][j].distance));
		}
	}
}



void Station::computeDiscretePopulation(){
	int counter = 0; //the count of the population, counter cannot be more than the population

	int sum_weight = 0;

	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < grids_each_row[i]; ++j){
			grids[i][j].weight_lower_limit = sum_weight;
			sum_weight += grids[i][j].weight;
			grids[i][j].weight_upper_limit = sum_weight;
		}
	}

	while (counter <= population_number){
		bool isFounded = false;
		int randomNumber = rand()%sum_weight;


		for (int i = 0; i < rows; ++i){
			isFounded = false;
			for (int j = 0; j < grids_each_row[i]; ++j){
				if (randomNumber >= grids[i][j].weight_lower_limit 
					&& randomNumber < grids[i][j].weight_upper_limit
					&& grids[i][j].weight_lower_limit != grids[i][j].weight_upper_limit){

					++grids[i][j].population;
					isFounded = true;
					break;
				}
			}

			if (isFounded){
				break;
			}
		}
		++counter;
	}
}



void Station::readWeightsData(string _path){

	string str = "";
	int weight_grid = 0;
	int weight_arr[MAX_GRIDS] = {};
	int counter = 0;

	ifstream myfile;
	myfile.open(_path, ios::in);  

	if (!myfile.is_open()){
		cout << "Error: Can't open the file: " << _path << endl;
		return;
	}

	while (myfile.good()){
		getline(myfile, str);
		weight_grid =  atoi(str.c_str());

		weight_arr[counter++] = weight_grid;
	}

	counter = 0;
	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < grids_each_row[i]; ++j){
			grids[i][j].weight =  weight_arr[counter++];
		}
	}

	myfile.close();
}


void Station::readDistancesData(string _path){
	string str = "";
	int distance_grid = 0;
	int distance_arr[MAX_GRIDS] = {};
	int counter = 0;
	ifstream myfile;
	myfile.open(_path, ios::in);  

	if (!myfile.is_open()){
		cout << "Error: Can't open the file: " << _path << endl;
		return;
	}

	while (myfile.good()){
		getline(myfile, str);
		distance_grid =  atoi(str.c_str());

		distance_arr[counter++] = distance_grid;
	}

	counter = 0;
	for (int i = 0; i < rows; ++i){
		for (int j = 0; j < grids_each_row[i]; ++j){
			grids[i][j].distance =  distance_arr[counter++];
		}
	}

	myfile.close();
}
