#include <iostream>
#define MAX_ROWS 45
#define MAX_COLUMNS 45

using namespace std;

/*
*	栅格类
*/
struct Grid{
	int distence; //到站点距离
	int walk_probability; //出行率或发生率
	int weght; //土地和密度的和权重
	int weight_upper_limit; //权重范围上限
	int weight_lower_limit; //权重范围下限
};


/*
*	轨道交通站点类
*
*
*/
class Station{
public:
	Station();
	~Station(){}

	string getName();
	void setName(string _name);

	int getRealNumber();
	void setRealNumber(int _number);

	int getPredictedNumber();
	void setPredictedNumber(int _number);
	
	Grid getGrid();
	void setGrid(Grid _grid);

	//读距离和权重数据
	void readDate(); 
private:
	string station_name; //站点名字

	//早高峰7:30-8:29一小时的客流发送量
	int real_passenger_number; //实际发生客流量
	int predicted_passenger_number; //预测客流发生量

	//栅格数据
	int rows; //栅格行数
	int grids_each_row[MAX_ROWS]; //每行的栅格数
	Grid grids[MAX_ROWS][MAX_COLUMNS]; //栅格数据
};

