#include <iostream>
#include <stdio.h>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstdio>

using namespace std;

struct state{
	int prob;
	string phoneme;
	vector<string> path;
	vector<string> childen;
	vector<int> prob_c;
	
};

int main(){
	map<char, int> graphene_index;
	map<string, int> phoneme_index;
	//vector<vector<int> > freq_gp;
	//vector<vector<int> > freq_gg;
	
	string line;
	ifstream myfile ("testsample.txt");
	if(myfile.is_open()){
		while(getline(myfile, line)){
			string graphene;
			int len=-1;
			for(int i=0; i<line.size();i++){
				if(line[i] == ' ') {
					len = i;
					break;
				}
			}
			if(len == -1){
				cout << "bad input" << endl;
				//break;
				exit(1);
			}
			graphene = line.substr(0,len);
			int j=len+2;
			for(int i=0; i<len; i++){
				string phoneme;
				int p = -1;
				for(int k=j; k<line.size(); k++){
					if(line[k] == ' ') {
						p = k;
						break;
					}
				}
				if(p==-1){
					phoneme = line.substr(j);
				}
				else{
					phoneme = line.substr(j, p-j);
					j = p+1;
				}
				int i1, i2;
				if(graphene_index.find(graphene[i])==graphene_index.end()){
					i1 = graphene_index.size();
					graphene_index[graphene[i]] = i1;
				}
				if(phoneme_index.find(phoneme)==phoneme_index.end()){
					i2 = phoneme_index.size();
					phoneme_index[phoneme] = i2;
				}
			}
		}
		myfile.close();
	}
	else{
		cout << "unable to open file" << endl;
	}
	/*
	cout << graphene_index.size() << endl;
	cout << phoneme_index.size() << endl;
	for(map<char, int>::iterator it=graphene_index.begin(); it != graphene_index.end(); it++){
		int a = it->first;
		cout << a << endl;
	}
	*/
	int l1 = graphene_index.size();
	int l2 = phoneme_index.size();
	
	double freq_gp[l1][l2];
	double freq_pp[l2][l2];
	int prev_p = -1;
	
	for(int i=0; i<graphene_index.size(); i++){
		for(int j=0; j<phoneme_index.size(); j++){
			freq_gp[i][j] = 0;
		}
	}
	for(int i=0; i<phoneme_index.size(); i++){
		for(int j=0; j<phoneme_index.size(); j++){
			freq_pp[i][j] = 0;
		}
	}
	
	ifstream myfile1 ("testsample.txt");
	if(myfile1.is_open()){
		while(getline(myfile1, line)){
			string graphene;
			int len=-1;
			for(int i=0; i<line.size();i++){
				if(line[i] == ' ') {
					len = i;
					break;
				}
			}
			if(len == -1){
				cout << "bad input" << endl;
				//break;
				exit(1);
			}
			graphene = line.substr(0,len);
			int j=len+2;
			for(int i=0; i<len; i++){
				string phoneme;
				int p = -1;
				for(int k=j; k<line.size(); k++){
					if(line[k] == ' ') {
						p = k;
						break;
					}
				}
				if(p==-1){
					phoneme = line.substr(j);
				}
				else{
					phoneme = line.substr(j, p-j);
					j = p+1;
				}
				int i1, i2;
				i1 = graphene_index[graphene[i]];
				i2 = phoneme_index[phoneme];
				if(prev_p != -1){
					freq_gp[i1][i2] += 1;
					freq_pp[prev_p][i2] += 1;
				}
				else{
					freq_gp[i1][i2] += 1;
				}
				prev_p = i2;
			}
		}
		myfile1.close();
	}
	else{
		cout << "unable to open file" << endl;
	}
	
	for(int i=0; i<phoneme_index.size(); i++){
		double total=0;
		for(int j=0; j<phoneme_index.size(); j++){
			total += freq_pp[i][j];
		}
		for(int j=0; j<phoneme_index.size(); j++){
			if(total != 0){
				freq_pp[i][j] = (freq_pp[i][j])/total;
			}
		}
	}
	for(int i=0; i<graphene_index.size(); i++){
		double total=0;
		for(int j=0; j<phoneme_index.size(); j++){
			total += freq_gp[i][j];
		}
		for(int j=0; j<phoneme_index.size(); j++){
			if(total != 0){
				freq_gp[i][j] = (freq_gp[i][j])/total;
			}
		}
	}
	//cout << freq_gp[3][7] << endl;
}
