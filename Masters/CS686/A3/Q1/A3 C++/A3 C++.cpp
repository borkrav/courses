// A3 C++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;



vector <string> words;
vector < pair<int,vector<string>*>> dataset;
vector <int> labels;

vector < pair<int, vector<string>*>> dataset2;
vector <int> labels2;

int depth = 4;

struct node{
	string data;
	float IG;
	node *left;
	node *right;
};


void deleteTree(node *root){
	if (root->left != NULL) deleteTree(root->left);
	if (root->right != NULL) deleteTree(root->right);
	delete root;
}

void printTree(node *root){
	queue < node* > q;
	q.push(root);

	while (q.size() != 0){
		node* n = q.front();
		q.pop();

		cout << n->data << endl;
		cout << n->IG << endl;
		cout << endl;

		if (n->left != NULL) q.push(n->left);
		if (n->right != NULL) q.push(n->right);


	}

}


int classify(node *root, pair<int, vector<string>*> article){

	if (root->left == NULL && root->right == NULL){
		return atoi(root->data.c_str());
	}


	bool inList = std::find(article.second->begin(), article.second->end(), root->data) != article.second->end();

	if (inList){
		return classify(root->right, article);
	}

	else{
		return classify(root->left, article);
	}


}


float I(float f1, float f2) {

	if (f1 == 0 || f2 == 0) {
		return 0;
	}

	return -f1*(log2(f1)) - f2*(log2(f2));

}

bool comp(pair<float, string> a, pair<float, string> b) {

	if (a.first > b.first) return true;
	else return false;

}




void chooseAttribute(vector<string*> attributes, vector < pair<int, vector<string>*>> examples, string *r_best, float *r_max){

	string best = "";
	float max = 0;


	for (int i = 0; i < attributes.size(); i++){
		float c1yesAttr = 0;
		float c2yesAttr = 0;
		float c1noAttr = 0;
		float c2noAttr = 0;

		for (int j = 0; j < examples.size(); j++){


			bool inList = std::find(examples[j].second->begin(), examples[j].second->end(), *attributes[i]) != examples[j].second->end();

			if (examples[j].first == 1){


				if (inList) {

					c1yesAttr += 1;

				}

				else {

					c1noAttr += 1;

				}

			}

			if (examples[j].first == 2){

				if (inList) {

					c2yesAttr += 1;

				}

				else {

					c2noAttr += 1;

				}

			}



		}


		float noAttr = c1noAttr + c2noAttr;
		float yesAttr = c1yesAttr + c2yesAttr;
		float IG = 0;

		if (noAttr > 0 && yesAttr > 0){
			IG = 1 - (noAttr / dataset.size())*I(c1noAttr / (noAttr), c2noAttr / (noAttr)) - (yesAttr / dataset.size())*I(c1yesAttr / (yesAttr), c2yesAttr / (yesAttr));
		}
		
		
		else if (noAttr > 0 && yesAttr == 0){
			IG = 1 - (noAttr / dataset.size())*I(c1noAttr / (noAttr), c2noAttr / (noAttr));
		}

		else if (noAttr == 0 && yesAttr > 0){
			IG = 1 - (yesAttr / dataset.size())*I(c1yesAttr / (yesAttr), c2yesAttr / (yesAttr));
		}


		if (IG > max){
			max = IG;
			best = *attributes[i];
		}


			


	}

	*r_best = best;
	*r_max = max;
}



pair<string, float> MTchooseAttribute(vector<string> attributes, vector < pair<int, vector<string>*>> examples){


	vector<string*> w1;
	vector<string*> w2;
	vector<string*> w3;
	vector<string*> w4;

	for (int i = 0; i < attributes.size(); i++){
		if (i % 4 == 0) w1.push_back(&attributes[i]);
		if (i % 4 == 1) w2.push_back(&attributes[i]);
		if (i % 4 == 2) w3.push_back(&attributes[i]);
		if (i % 4 == 3) w4.push_back(&attributes[i]);

	}

	string best1, best2, best3, best4;
	float max1, max2, max3, max4;

	std::thread t1(chooseAttribute, w1, examples, &best1, &max1);
	std::thread t2(chooseAttribute, w2, examples, &best2, &max2);
	std::thread t3(chooseAttribute, w3, examples, &best3, &max3);
	std::thread t4(chooseAttribute, w4, examples, &best4, &max4);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	vector<pair<float, string>>max = { { max1, best1 }, { max2, best2 }, { max3, best3 }, { max4, best4 } };

	sort(max.begin(), max.end(), comp);

	return pair<string,float>{max[0].second, max[0].first};


}


node* DTL(vector<pair<int,vector<string>*>> examples, vector<string> attributes, string default, int depth){

	//base cases


	if (examples.size() == 0){
		return new node{ default, 0, NULL, NULL};
	}

	int c1 = 0;
	int c2 = 0;
	int mode = 0;

	for (int i = 0; i < examples.size(); i++){
			if (examples[i].first == 1) c1 += 1;
			else c2 += 1;
		
	}

	if (c1 > c2) mode = 1;
	else mode = 2;

	if (c1 == 0 || c2 == 0 || attributes.size() == 0 || depth == 0) return new node{ to_string(mode), 0, NULL, NULL };

	//recursive case

	pair<string,float> best = MTchooseAttribute(attributes, examples);

	node *tree = new node{ best.first, best.second, NULL, NULL };

	vector<pair<int,vector<string>*>> dataWithout;
	vector<pair<int, vector<string>*>> dataWith;

	for (int i = 0; i < examples.size(); i++){

		bool inList = std::find(examples[i].second->begin(), examples[i].second->end(), best.first) != examples[i].second->end();

		if (inList){
			dataWith.push_back(examples[i]);
		}

		else{
			dataWithout.push_back(examples[i]);
		}
		

	}

	attributes.erase(std::find(attributes.begin(), attributes.end(), best.first));

	node *left = DTL(dataWithout, attributes, to_string(mode), depth-1);
	node *right = DTL(dataWith, attributes, to_string(mode), depth-1);

	tree->left = left;
	tree->right = right;


	return tree;










}


int _tmain(int argc, _TCHAR* argv[]){


	ifstream inputFile("..\\A3 C++\\Input\\words.txt");

	string line;
	int a, b;

	while (getline(inputFile, line)){

		istringstream iss(line);
		words.push_back(line);
	}

	inputFile = ifstream("..\\A3 C++\\Input\\trainLabel.txt");

	while (getline(inputFile, line)){

		istringstream iss(line);
		iss >> a;

		labels.push_back(a);


	}


	inputFile = ifstream("..\\A3 C++\\Input\\testLabel.txt");

	while (getline(inputFile, line)){

		istringstream iss(line);
		iss >> a;

		labels2.push_back(a);


	}

	inputFile = ifstream("..\\A3 C++\\Input\\trainData.txt");

	int currentDocument = 1;

	vector<string>* wordList = new vector < string > ;


	while (getline(inputFile, line)){

		istringstream iss(line);
		iss >> a >> b;

		if (a != currentDocument){
			dataset.push_back(pair < int, vector<string>* > { labels[currentDocument], wordList });
			currentDocument += 1;
			wordList = new vector < string > ;

		}

		wordList->push_back(words[b - 1]);

	}


	inputFile = ifstream("..\\A3 C++\\Input\\testData.txt");

	currentDocument = 1;

	wordList = new vector < string > ;


	while (getline(inputFile, line)){

		istringstream iss(line);
		iss >> a >> b;

		if (a != currentDocument){
			dataset2.push_back(pair < int, vector<string>* > { labels2[currentDocument], wordList });
			currentDocument += 1;
			wordList = new vector < string > ;

		}

		wordList->push_back(words[b - 1]);

	}



	//cout << "tes1t" << endl;

	//cout << MTchooseAttribute(words, dataset) << endl;



	//cout << "DONE" << endl;

	//for (int d = 20; d < 21; d++){

		//build tree
		node *tree = DTL(dataset, words, "0", depth);


		int hits = 0;
		int misses = 0;

		for (int i = 0; i < dataset.size(); i++){
			int result = classify(tree, dataset[i]);

			if (result != dataset[i].first){
				misses += 1;
			}

			else hits += 1;

		}

		float percent = float(hits) * 100 / float(misses + hits);

		cout << "TRAINING Depth: " << depth << " hits: " << hits << " misses: " << misses << " accuracy: " << percent << endl;


		hits = 0;
		misses = 0;

		for (int i = 0; i < dataset2.size(); i++){
			int result = classify(tree, dataset2[i]);

			if (result != dataset2[i].first){
				misses += 1;
			}

			else hits += 1;

		}

		percent = float(hits) * 100 / float(misses + hits);

		cout << "TESTING Depth: " << depth << " hits: " << hits << " misses: " << misses << " accuracy: " << percent << endl;

		printTree(tree);
		

		deleteTree(tree);
	//}

	getchar();

	for (int i = 0; i < dataset.size(); i++){
		delete dataset[i].second;
	}

	for (int i = 0; i < dataset2.size(); i++){
		delete dataset2[i].second;
	}

	//need to clean up whole tree recursively


	//deleteTree(tree);



	return 0;
}

