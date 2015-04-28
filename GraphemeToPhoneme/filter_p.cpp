#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int found(string s){
	int b = -1;
	for(int i=0; i<s.size(); i++){
		if(!((s[i]<=90 && s[i]>=65)||(s[i]>=97 && s[i]<=122)||s[i]==32||s[i]==10||(s[i]>=48 && s[i]<=57))) b=i; 		
	}
	return b;
}

int found1(string s,char a){
	int b = -1;
	for(int i=0; i<s.size(); i++){
		if(s[i]==a) b=i;
	}
	return b;
}

string rem_braces(string s, char a, char b){
	int p = found1(s,a);
	int q = found1(s,b);
	if(p!=-1 && q!=-1) return s.substr(0,p)+s.substr(q+1);
	else return s; 	
}

vector<string> tokenize(string s){
	int start = 0, end;
	vector<string> out;
	for(int i=0; i<s.size(); i++){
		if(s[i] == ' '){
			end = i -1;
			if(end >= start){
				out.push_back(s.substr(start, end-start+1));
			}
			start = i+1;
		}
	}
	if(start< s.size()) out.push_back(s.substr(start));
	return out;
	
}

void print_vector(vector<string> v){
	for(int i=0; i<v.size(); i++){
		cout << v[i] << ' ' ;
	}
	cout << endl;
}

int main(){
	string line;
	while(getline(cin,line)){
		if(line.size() == 0){
			continue;
		}
		else if(line.substr(0,3)==";;;"){
			continue;
		}
		else{
			int a = line[0];
			if(!((a<=90 && a>=65)||(a>=97 && a<=122))){
				continue;
			}
			else{
				line = rem_braces(line, '(', ')');
				if(found(line) != -1){
					continue;
				}
				else {
					//cout << line << endl;
					string line2 = rem_braces(line, '(', ')');
					vector<string> tokenized = tokenize(line2);
					if((tokenized[0]).size() == (tokenized.size() -1)){
						cout << line2 << endl;
						//print_vector(tokenized);
						//cout << tokenized.size() << endl;
					}
					else{
						continue;
					}
				}
			}
		}
	}
}
