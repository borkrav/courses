#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
#include <set>
using namespace std;


typedef struct {
	int number;
	int x;
	int y;
} point;

typedef struct {
	int v;
	int weight;
	int u;
} edge;


vector <point> points;
point source;
point destination;

vector < vector < pair <int, int> > > adjMatrix;

 
void prims (vector < vector < pair <int, int> > > adjMatrix);
int distance (int x1, int x2, int y1, int y2);

int main(){
    
	int numOfPoints;
	
	cin >> numOfPoints;
	
	for (int i = 0; i < numOfPoints; i++){
		point newPoint;
		cin >> newPoint.x >> newPoint.y;
        	newPoint.number = i+1;
		points.push_back(newPoint);
    }
    
    source = points[0];
    destination = points[1];
    
    
    
    for (int i = 0; i < points.size(); i++) {

	vector <pair <int, int> > newRow;    

        for (int j = 0; j < points.size(); j++){

		if (i == j){
			newRow.push_back(make_pair(0, 0));
		}

		else {

			int dist = distance(points[i].x, points[j].x, points[i].y, points[j].y);
		    	newRow.push_back(make_pair(1, dist));
		}

        }
	adjMatrix.push_back(newRow);
    }

	prims(adjMatrix);

}


int distance (int x1, int x2, int y1, int y2){
    return (pow((x2-x1),2) + pow((y2-y1),2));
}


void prims (vector < vector < pair <int, int> > > adjMatrix){
   	
    	cout << "Adjacency Matrix" << endl; 

    	for (int i = 0; i < points.size(); i++){
		for (int j = 0; j < points.size(); j++){
			cout << "(" << adjMatrix[i][j].first << " " << adjMatrix[i][j].second << ")";
            
        	}
    		cout << endl;
    	}
	

	int numOfVertices = adjMatrix.size();

	vector <edge> key;	
	set <int> Q;

	for (int i = 1; i <= numOfVertices; i++){
		edge newEdge{-1, numeric_limits<int>::max(), -1};
			
		Q.insert(i + 1);
		key.push_back(newEdge);
	}
	
	int l = 0;
	for (int j = 0; j < numOfVertices; j++){
		if (adjMatrix[0][j].first == 1){
			key[l].v = j+1;
			key[l].weight = adjMatrix[0][j].second;
			key[l].u = 1;
			l++;	
		}
	}
	
e
	for (int i = 0; i < key.size(); i++){
		cout << key[i].v << " " << key[i].weight << " " << key[i].u << endl;
	} 


	//need to write the actual agorithm here
	

     
}




















