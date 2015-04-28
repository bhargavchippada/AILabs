#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

vector<pair<string,vector<string> > > gpvec;
int MAXLEN = 0;
map<char,int> graphMap;
map<string,int> phonMap;
int num_graph=0;
int num_phon=0;

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

bool illegalChars(string &s){
	int a;
	for(int i=0; i<s.size(); i++){
		a = s[i]-0;
		// 
		if(!((a<=90 && a>=65)||(a>=97 && a<=122) || (a>=48 && a<=57) || a==32 || a==40 || a==41)) return true;
	}
	/*
	int leftbrac = s.find('(');
	int rightbrac = s.find(')');
	if(leftbrac==-1 && rightbrac==-1) return false;
	else if(leftbrac!=-1 && rightbrac!=-1){
		s = s.substr(0,leftbrac) + s.substr(rightbrac+1);
		return false;
	}else return true;
	*/
	return false;
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
	    if(illegalChars(line)){
			continue;
		}

		int leftbrac = word.find('(');
		int rightbrac = word.find(')');
		if(leftbrac==-1 && rightbrac==-1);
		else if(leftbrac!=-1 && rightbrac!=-1){
			word = word.substr(0,leftbrac);
		}else continue;

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
	cout<<"Max grapheme/phoneme length: "<<MAXLEN<<endl;
	cout<<"No.of distinct graphemes: "<<num_graph<<endl;
	cout<<"No.of distinct phonemes: "<<num_phon<<endl;
}


int main(){
	parse();
	print_gpMap();
	//print_gp();
}