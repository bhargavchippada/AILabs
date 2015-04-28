#include <bits/stdc++.h>

using namespace std;


bool illegalChars(string &s){
	int a;
	for(int i=0; i<s.size(); i++){
		a = s[i]-0;
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
		//cout<<line<<endl;
		count++;
	}
	cout<<"No.of valid lines: "<<count<<endl;
}


int main(){
	parse();	
}