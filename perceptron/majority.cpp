#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > truth;
int n;
vector<int> w;

bool dot(vector<int> b) {
	int prod=0;
	for(int i=0;i<=n;i++) {
		//cout<<b[i]<<" ";
		prod+=w[i]*b[i];
	}
	//cout<<prod<<" "<<endl;
	return (prod>0);
}

void add(vector<int> a) {
	for(int i=0;i<=n;i++) {
		w[i]+=a[i];
	}
}

void check() {
	bool flag=true;
	while(true) {
		flag=true;
		for(int i=0;i<pow(2,n);i++) {
			if(!dot(truth[i])) {
				add(truth[i]);
				flag=false;
				break;
			}
		}
		if(flag){
			for(int i=0;i<=n;i++) {
				cout<<w[i]<<" ";
			}
			cout<<endl;
			return;
		}
	}
}


int main() {
	int value;
	int temp;
	cin>>n;
	for(int i=0;i<pow(2,n);i++) {
		cin>>value;
		if(value==0) value=-1;
		truth.push_back(*(new vector<int> ()));
		for(int j=0;j<n;j++) {
			cin>>temp;
			truth[i].push_back(temp*value);
		}
		truth[i].push_back(-1*value);
	}
	/*for(int i=0;i<pow(2,n);i++) {
		for(int j=0;j<n+1;j++) {
			cout<<truth[i][j]<<" ";
		}
		cout<<endl;
	}*/
	for(int i=0;i<n+1;i++) {
		w.push_back(0);
	}
	check();
}