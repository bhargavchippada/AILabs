#include <bits/stdc++.h>
#include <algorithm>
#include <cmath>

using namespace std;

vector<pair<string,vector<string> > > gpvec;

int MAXLEN = 0;
map<char,vector<double> > graphMap;
map<string,vector<double> > phonMap;
int num_graph=0;
int num_phon=0;
int M, N;
double eff = 0.8;

int num_hiddenNodes = 0;

vector<double> neuralInput;
vector<double> neuralTarget;

void print_gp(){
	for(int i=0; i<gpvec.size(); i++){
		cout<<gpvec[i].first<<" ";
		for(int j=0; j<(gpvec[i].second).size(); j++){
			cout<<(gpvec[i].second)[j]<<" ";
		}
		cout<<endl;
	}
}

void printVec(vector<double> vec){
	for(int i=0; i<vec.size(); i++) cout<<vec[i]<<" ";
}

void print_gpMap(){
	cout<<"\nDistinct Graphemes:\n";
	for (map<char,vector<double> >::iterator it=graphMap.begin(); it!=graphMap.end(); ++it){
    	cout << it->first << " => ";
    	printVec(it->second);
    	cout<<endl;
	}

    cout<<"\nDistinct Phonemes:\n";
    for (map<string,vector<double> >::iterator it=phonMap.begin(); it!=phonMap.end(); ++it){
    	cout << it->first << " => ";
    	printVec(it->second);
    	cout<<endl;
    }
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
				vector<double> binary;
				int q = num_graph,r;
				do{
					r=q%2;
					q=q/2;
					binary.push_back(r);
				}while(q);

				graphMap[grapheme[i]] = binary;
				num_graph++;
			}

			if(phonMap.find(phonemes[i]) == phonMap.end()){
				vector<double> binary;
				int q = num_phon,r;
				do{
					r=q%2;
					q=q/2;
					binary.push_back(r);
				}while(q);

				phonMap[phonemes[i]] = binary;
				num_phon++;
			}
		}

		gpvec.push_back(make_pair(grapheme,phonemes));
		//cout<<line<<endl;
		count++;
	}
	cout<<"No.of valid lines: "<<count<<endl;
}

void paddVector(){
	for (map<char,vector<double> >::iterator it=graphMap.begin(); it!=graphMap.end(); ++it){
    	for(int i=(it->second).size(); i<M; i++){
    		(it->second).push_back(0);
    	}
    	reverse((it->second).begin(),(it->second).end());
	}

    cout<<"\nDistinct Phonemes:\n";
    for (map<string,vector<double> >::iterator it=phonMap.begin(); it!=phonMap.end(); ++it){
    	for(int i=(it->second).size(); i<N; i++){
    		(it->second).push_back(0);
    	}
    	reverse((it->second).begin(),(it->second).end());
    }
}

void computeGPBinary(int ind){
	string grapheme = (gpvec[ind].first);
	int gsize = grapheme.size();
	for(int i=0; i<(MAXLEN-gsize); i++){
		for(int j=0; j<M; j++) neuralInput[i*M+j] = 0; //padding to left
	}

	for(int i=(MAXLEN-gsize); i<MAXLEN; i++){
		for(int j=0; j<M; j++) {
			neuralInput[i*M+j] = (graphMap[grapheme[i-(MAXLEN-gsize)]])[j]; //padding to left
		}
	}

	vector<string> phonemes = (gpvec[ind].second);
	int psize = phonemes.size();
	for(int i=0; i<(MAXLEN-psize); i++){
		for(int j=0; j<N; j++) neuralTarget[i*N+j] = 0; //padding to left
	}

	for(int i=(MAXLEN-psize); i<MAXLEN; i++){
		for(int j=0; j<N; j++) {
			neuralTarget[i*N+j] = (phonMap[phonemes[i-(MAXLEN-psize)]])[j]; //padding to left
		}
	}
}

struct layer{
	layer* nextLayer; // NULL for output layer
	layer* previousLayer; //NULL for input layer
	int numNodes;
	vector<vector<double> > weights;
	vector<double> output;

	layer(layer* prev, layer* next, int n){
		numNodes = n;
		nextLayer = next;
		previousLayer = prev;

		for(int i=0; i< numNodes; i++){
			output.push_back(0.0);
		}

		if(nextLayer!=NULL){
			for(int i=0; i<numNodes; i++){
				weights.push_back(*(new vector<double>()));
				for(int j=0; j<nextLayer->numNodes; j++){
					weights[i].push_back(1.0);
				}
			}	
		}
	}

	void computeOutput(){
		if(previousLayer==NULL){
			nextLayer->computeOutput();
		}else{
			for(int i=0; i<numNodes; i++){
				double val = 0.0;
				for(int j=0; j<previousLayer->numNodes; j++){
					val += (previousLayer->weights[j][i])*(previousLayer->output[j]);
				}
				output[i] = val;
			}
			if(nextLayer!=NULL) nextLayer->computeOutput();
		}
	}

	void print_weights(){
		if(nextLayer!=NULL){
			cout<<endl;
			for(int i=0; i<numNodes; i++){
				for(int j=0; j<nextLayer->numNodes; j++){
					cout<<weights[i][j]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
			nextLayer->print_weights();
		}
		
	}

	void print_output(){
		for(int i=0; i<numNodes; i++){
			cout<<output[i]<<" ";
		}
		cout<<endl;
		if(nextLayer!=NULL) nextLayer->print_output();
	}

};

layer* outputLayer;
layer* inputLayer;


int main(){
	parse();
	M = ceil(log2(num_graph));
	N = ceil(log2(num_phon));
	paddVector();
	num_hiddenNodes = ceil((M+N)/2);
	for(int i=0; i<M*MAXLEN; i++) neuralInput.push_back(0.0);
	for(int i=0; i<N*MAXLEN; i++) neuralTarget.push_back(0.0);

	cout<<"Max grapheme/phoneme length: "<<MAXLEN<<endl;
	cout<<"No.of distinct graphemes: "<<num_graph<<endl;
	cout<<"No.of distinct phonemes: "<<num_phon<<endl;
	cout<<"M: "<<M<<endl;
	cout<<"N: "<<N<<endl;
	cout<<"Num of hidden nodes: "<<num_hiddenNodes<<endl;

	outputLayer = new layer(NULL,NULL,N);
	layer* hiddenLayer = new layer(NULL, outputLayer, num_hiddenNodes);
	outputLayer->previousLayer = hiddenLayer;
	inputLayer = new layer(NULL,hiddenLayer,M);
	inputLayer->nextLayer = hiddenLayer;
	hiddenLayer->previousLayer = inputLayer;
	inputLayer->print_weights();
	inputLayer->output[0] = 0;
	inputLayer->output[1] = 1;
	inputLayer->output[2] = 0;
	inputLayer->output[3] = 1;
	inputLayer->output[4] = 1;
	inputLayer->computeOutput();
	//inputLayer->print_output();
	//computeGPBinary(3);
	//printVec(neuralInput);
	//cout<<endl;
	//printVec(neuralTarget);
	//cout<<endl;
	//print_gpMap();
	//print_gp();

}