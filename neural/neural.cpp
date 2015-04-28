#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

vector<pair<string,vector<string> > > gpvec;
int MAXLEN = 0;

void print_gp(){
	for(int i=0; i<gpvec.size(); i++){
		cout<<gpvec[i].first<<" ";
		for(int j=0; j<(gpvec[i].second).size(); j++){
			cout<<(gpvec[i].second)[j]<<" ";
		}
		cout<<endl;
	}
}

bool illegalChars(string &s){
	int a;
	for(int i=0; i<s.size(); i++){
		a = s[i]-0;
		// || a==40 || a==41
		if(!((a<=90 && a>=65)||(a>=97 && a<=122) || (a>=48 && a<=57) || a==32 || a==40 || a==41)) return true;
	}
	
	int leftbrac = s.find('(');
	int rightbrac = s.find(')');
	if(leftbrac==-1 && rightbrac==-1) return false;
	else if(leftbrac!=-1 && rightbrac!=-1){
		s = s.substr(0,leftbrac) + s.substr(rightbrac+1);
		return false;
	}else return true;
	
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
		string grapheme = word;
		vector<string> phonemes;
		while((iss >> word)){
			phonemes.push_back(word);
		}
		if(phonemes.size()!=grapheme.size()) continue;

		MAXLEN = (MAXLEN > grapheme.size())? MAXLEN : grapheme.size();
		gpvec.push_back(make_pair(grapheme,phonemes));
		//cout<<line<<endl;
		count++;
	}
	cout<<"No.of valid lines: "<<count<<endl;
	cout<<"Max grapheme/phoneme length: "<<MAXLEN<<endl;
}


int main(){
	parse();
	//print_gp();
}