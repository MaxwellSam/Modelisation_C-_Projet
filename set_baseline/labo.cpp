#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "myToolBox.h"
using namespace std; // utilisation de l'espace de nom de std

int main (){
	string channel_2 = extractChannel(2, "data_mcs.txt");
	cout << channel_2 << endl; 
}