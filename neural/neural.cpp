#include <bits/stdc++.h>
#include <algorithm>
#include <cmath>

using namespace std;

vector<pair<string,vector<string> > > gpvec;
int MAXLEN = 0;
map<char,int> graphMap;
map<string,int> phonMap;
int num_graph=0;
int num_phon=0;
int M, N;

void print_gp(){
	for(int i=0; i<gpvec.size(); i++){
		cout<<gpvec[i].first<<" ";
		for(int j=0; j<(gpvec[i].second).size(); j++){
			cout<<(gpvec[i].second)[j]<<" ";
		}
		cout<<endl;
	}
}

void print_gpMap(){
	cout<<"\nDistinct Graphemes:\n";
	for (map<char,int>::iterator it=graphMap.begin(); it!=graphMap.end(); ++it)
    	cout << it->first << " => " << it->second << '\n';

    cout<<"\nDistinct Phonemes:\n";
    for (map<string,int>::iterator it=phonMap.begin(); it!=phonMap.end(); ++it)
    	cout << it->first << " => " << it->second << '\n';
}

string removeIllegalChars(string s){
	string result;
	int a;
	for(int i=0; i<s.size(); i++){
		a = s[i]-0;
		if(!((a<=90 && a>=65)||(a>=97 && a<=122))) continue;
		else result+=s[i];
	}
	return result;
}

void parse(){
	ifstream infile("cmudict-0.7b");

	string line;
	int count=0;
	while (getline(infile, line))
	{
	    istringstream iss(line);
	    string word;
	    if (!(iss >> word)) break;

		word = removeIllegalChars(word);
		if(word.size()==0) continue;

		string grapheme = word;
		vector<string> phonemes;
		while((iss >> word)){
			phonemes.push_back(word);
		}
		if(phonemes.size()!=grapheme.size()) continue;

		MAXLEN = (MAXLEN > grapheme.size())? MAXLEN : grapheme.size();

		for(int i=0; i<grapheme.size(); i++){
			if(graphMap.find(grapheme[i]) == graphMap.end()){
				graphMap[grapheme[i]] = num_graph;
				num_graph++;
			}

			if(phonMap.find(phonemes[i]) == phonMap.end()){
				phonMap[phonemes[i]] = num_phon;
				num_phon++;
			}
		}

		gpvec.push_back(make_pair(grapheme,phonemes));
		//cout<<line<<endl;
		count++;
	}
	cout<<"No.of valid lines: "<<count<<endl;
}



int main(){
	parse();
	M = ceil(log2(num_graph));
	N = ceil(log2(num_phon));
	cout<<"Max grapheme/phoneme length: "<<MAXLEN<<endl;
	cout<<"No.of distinct graphemes: "<<num_graph<<endl;
	cout<<"No.of distinct phonemes: "<<num_phon<<endl;
	cout<<"M: "<<M<<endl;
	cout<<"N: "<<N<<endl;
	//print_gpMap();
	//print_gp();
}