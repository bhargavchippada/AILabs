#include <bits/stdc++.h>

using namespace std;

int main(){
	ifstream infile("cmudict-0.7b");

	string line;
	while (getline(infile, line))
	{
	    istringstream iss(line);
	    string word;
	    if (!(iss >> word)) { break; }
	    if(word==";;;") continue;
	    cout<<word;
	}
	return 0;
}