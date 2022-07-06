#pragma once
using namespace std;
#include<vector>
#include<fstream>
#include<sstream>
#include<string>

enum Caseh {
	frame,
	ToolSysToWorldSys,
	Direction,
	Location
};



bool CSVAnalysis_HMK(char *&pFileName, vector<vector<double>> &matrix, vector<vector<double>> &direction, vector<vector<double>> &cutInf, vector<int>&amount) {
	ifstream csvfile(pFileName, ios::in);
	if (!csvfile)
	{
		return false;
	}
	string lines;
	Caseh caseh;
	int i = -1, j = 0, total = 0;
	while (getline(csvfile, lines))
	{
		string strtemp = lines.substr(0, 4);
		if (!strtemp.compare("Tool")) {
			caseh = ToolSysToWorldSys;
			j = 0;
		}
		else if (!strtemp.compare("Feed")) {
			caseh = Direction;
			i = -1;
		}
		else if (!strtemp.compare("fram"))
		{
			caseh = frame;
			if (i)
			{
				amount.push_back(i);
				total += i;
			}
		}
		else {
			i++;
			if (caseh == ToolSysToWorldSys)
			{
				string num;
				istringstream readstr(lines);
				vector<double> tempm;
				for (int m = 1; m < 5; m++) {
					getline(readstr, num, ',');
					tempm.push_back(atof(num.c_str()));
				}
				matrix.push_back(tempm);
			}
			else if (caseh == Direction) {
				string num;
				istringstream readstr(lines);
				vector<double> tempd;
				for (int m = 1; m < 4; m++) {
					getline(readstr, num, ',');
					tempd.push_back(atof(num.c_str()));
				}
				direction.push_back(tempd);
				caseh = Location;
			}
			else if (caseh == Location)
			{
				string num;
				istringstream readstr(lines);
				vector<double> temp;

				for (int m = 1; m < 17; m++) {
					getline(readstr, num, ',');
					temp.push_back(atof(num.c_str()));
				}
				cutInf.push_back(temp);
			}
			continue;
		}
	}
	amount.push_back(cutInf.size() - total);
	return true;
}