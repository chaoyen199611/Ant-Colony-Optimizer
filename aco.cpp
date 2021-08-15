#include "aco.h"
#include<iostream>
#include <stdlib.h>
#include <time.h> 
#include<vector>
#include<fstream>
#include<cmath>
#include<sstream>
#define vaporRate 0.1
#define initialPhermone 0.5
#define phermoneAmount 100
using namespace std;

void aco(int ants,int ite,int run){
	fstream file,f2;
	file.open("eil51.txt",ios::in);
	f2.open("result.txt",ios::out);
	srand(time(NULL));
	string line;
	vector<pair<int,int> > location;
	while(getline(file,line)&&line!="EOF"){
		stringstream n;
		int x,y;
		n<<line;
		n>>x;n>>x;n>>y;
		location.push_back(make_pair(x,y));
	}
	file.close();
	double distance[51][51],max;
	for(int i=0;i<location.size();i++){
		for(int j=0;j<location.size();j++){
			double x,y,result;
			x=(location[i].first-location[j].first)*(location[i].first-location[j].first);
			y=(location[i].second-location[j].second)*(location[i].second-location[j].second);
			result=sqrt(x+y);
			distance[i][j]=result;
		}
	}
	double result[51][1000];
	for(int i=0;i<run;i++){
		double min=1000;
		double phermone[51][51];
		for(int j=0;j<51;j++){
			for(int k=0;k<51;k++){
				phermone[j][k]=initialPhermone;
			}
		}
		for(int j=0;j<ite;j++){
			double deltaphermone[51][51]={};
			double dis[50]={};
			for(int k=0;k<ants;k++){
				vector<int> route;
				int startCity=rand()%51;
				bool notVisit[51]={true};
				for(int n=0;n<51;n++){
					notVisit[n]=1;
				}
				route.push_back(startCity);
				notVisit[startCity]=0;
				int currentX=startCity,currentY,remainCity=location.size(),select;
				while(--remainCity){
					double total=0,prob[51],range=0;
					vector<int> toCheck;
					for(int n=0;n<51;n++){
						if(notVisit[n]){
							toCheck.push_back(n);
						}
					}
					double a,b,alpha=1,beta=2;
					for(int n=0;n<toCheck.size();n++){
						a=pow((1.0/distance[currentX][toCheck[n]]),alpha);
						b=pow(phermone[currentX][toCheck[n]],beta);
						total+=(a*b);
					}
					for(int n=0;n<toCheck.size();n++){
						a=pow((1.0/distance[currentX][toCheck[n]]),alpha);
						b=pow(phermone[currentX][toCheck[n]],beta);
						range+=(a*b/total);
						prob[n]=range;
					}
					double random=(double)rand()/(RAND_MAX+1.0);
					for(int n=0;n<toCheck.size();n++){
						if(random<=prob[n]){
							dis[k]+=distance[currentX][toCheck[n]];
							notVisit[toCheck[n]]=0;
							currentX=toCheck[n];
							route.push_back(currentX);
							break;
						}
					}
				}
				for(int n=0;n<route.size()-1;n++){
					deltaphermone[route[n]][route[n+1]]+=phermoneAmount/dis[k];
					deltaphermone[route[n+1]][route[n]]+=phermoneAmount/dis[k];
				}
			}
			for(int n=0;n<51;n++){
				for(int k=0;k<51;k++){
					phermone[n][k]=(1-vaporRate)*phermone[n][k]+deltaphermone[n][k];
				}
			}
			double tmp=2000;
			for(int n=0;n<ants;n++){
				if(dis[n]<tmp) tmp=dis[n];
			}
			result[i][j]=tmp;

			if(tmp<min)	min=tmp;
		}
		cout<<min<<endl;
		f2<<min<<endl;
	}
	f2.close();
	double average[1000];
	file.open("output.txt",ios::out);
	for(int j=0;j<ite;j++){
		for(int i=0;i<run;i++){
			average[j]+=result[i][j];
		}
		average[j]/=51.0;
		file<<average[j]<<endl;
	}
	file.close();
}
