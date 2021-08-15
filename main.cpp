#include<iostream>
#include<string>
#include "aco.h"
using namespace std;

int main(int argc, char *argv[]){
	int ants=stoi(argv[1]),iteration=stoi(argv[2]),run=stoi(argv[3]);
	aco(ants,iteration,run);
}
