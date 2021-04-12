#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "myToolBox.h"
using namespace std; // utilisation de l'espace de nom de std

int main (){
	string fileContent = read_data("datasetTest.txt");
	string channel_2 = extractChannel(2, fileContent);
	string contentAvg = movingAverage(channel_2, 2);
	cout << channel_2 << endl; 
}