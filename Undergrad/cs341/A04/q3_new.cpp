//TODO Clean up code, remove all debugging statements, write a random test generator

#include <iostream>
#include <vector>
#include <math.h>
#include <limits>
#include <set>
#include <algorithm>

using namespace std;

typedef struct {
	int number;
	int x;
	int y;
} point;

typedef struct {
	int v;
	float weight;
	int u;
} edge;


vector <point> points;
point source;
point destination;

vector < vector < pair <int, float> > > adjMatrix;

 
void prims (vector < vector < pair <int, float> > > adjMatrix);
float distance (int x1, int x2, int y1, int y2);

bool myfunction(edge a, edge b) {
	return a.weight < b.weight;
}

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

	vector <pair <int, float> > newRow;    

        for (int j = 0; j < points.size(); j++){

		if (i == j){
			newRow.push_back(make_pair(0, 0));
		}

		else {

			float dist = distance(points[i].x, points[j].x, points[i].y, points[j].y);
		    	newRow.push_back(make_pair(1, dist));
		}

        }
	adjMatrix.push_back(newRow);
    }

	vector <edge> test;
	
	for (int i = 0; i < points.size(); i++){
		for (int j = 0; j < points.size(); j++){
			if (adjMatrix[i][j].first == 1){
				edge newEdge;
				newEdge.v = j+1;
				newEdge.u = i+1;
				newEdge.weight = adjMatrix[i][j].second;
				test.push_back (newEdge);
        	}
    		
    	}
	}
		
	sort(test.begin(), test.end(), myfunction);
	
	for (int i = 0; i < test.size(); i++){
		//cout << "(" << test[i].u << "," <<test[i].v << "," << test[i].weight << ")" << endl;
	}
	
	prims(adjMatrix);
 
}


float distance (int x1, int x2, int y1, int y2){
    return (pow((x2-x1),2) + pow((y2-y1),2));
}


void prims (vector < vector < pair <int, float> > > adjMatrix){
   	
    	//cout << "Adjacency Matrix" << endl; 

    	for (int i = 0; i < points.size(); i++){
		for (int j = 0; j < points.size(); j++){
			cout << "(" << adjMatrix[i][j].first << " " << adjMatrix[i][j].second << ")";
            
        	}
    		cout << endl;
    	}
	

	int numOfVertices = adjMatrix.size();

	vector <edge> key;	
	set <int> Q;
    set <int>::iterator qIt;
    
	for (int i = 1; i <= numOfVertices; i++){
        edge newEdge;
		newEdge.v = -1;
		newEdge.weight = numeric_limits<float>::max();
		newEdge.u = -1;
		Q.insert(i + 1);
		key.push_back(newEdge);
	}
	
	 float smallestWeight =  numeric_limits<float>::max();
    	for (int j = 0; j < numOfVertices; j++){
    		if (adjMatrix[0][j].first == 1){
    			if(adjMatrix[0][j].second < smallestWeight){
                    smallestWeight = adjMatrix[0][j].second;
                    key[0].v = j+1;
        			key[0].weight = adjMatrix[0][j].second;
        			key[0].u = 1;
        			
                }	
    		}
    	}
	
	for (int i = 0; i < key.size(); i++){
		      cout << key[i].v << " " << key[i].weight << " " << key[i].u << endl;
    } 

    vector <pair <int, int> > result;
	
	while (Q.size() > 1){
          
 	      for (int i = 0; i < key.size(); i++){
                      cout << key[i].v << " " << key[i].weight << " " << key[i].u << endl;
          	}
          
        edge minKey;
        int indexOfMinKey = -1;
        float smallestWeight =  numeric_limits<float>::max();
        for (int i = 0; i < key.size(); i++){
            if (key[i].weight < smallestWeight){
                smallestWeight = key[i].weight;
                minKey = key[i];
                indexOfMinKey = i;
            }
        }
          
        key[indexOfMinKey].weight = numeric_limits<float>::max();
         
          
        cout << "Selected: (" << minKey.u << "," << minKey.v << ")" << endl;
        result.push_back(make_pair(minKey.u, minKey.v));
          
        vector <int> values;
	/*          
        if (minKey.v == 2){
			values.push_back(minKey.v);
            int target = minKey.u;
            values.push_back(target);
            //cout << "size:" << result.size() << endl;
			 
			if (result.size() == 1){
				cout << result[0].first << endl;
				cout << result[0].second << endl;
			}
			
			else {
				for (int i = result.size(); i > 0; i--){
					 
					if (result[i].second == target){

						//cout << result[i].second << endl;
						values.push_back(result[i].first);
						target = result[i].first; 
					}
				} 
				values.push_back(1);
            
				for (int i = values.size()-1; i>=0; i--){
				 
					cout << values[i] << endl;    
					 
				}
			}			
             
            break;
        }   
        */  
        Q.erase(Q.find(minKey.v));

          
        for (int j = 0; j < numOfVertices; j++){
            if (adjMatrix[minKey.v-1][j].first == 1){
				if (Q.find(j+1) != Q.end() && adjMatrix[minKey.v-1][j].second < key[j].weight){
					key[j].v = j+1;
                    key[j].weight = adjMatrix[minKey.v-1][j].second;
                    key[j].u = minKey.v;
                }
            } 
        }
          
        for (int j = 0; j < numOfVertices; j++){
            if (adjMatrix[minKey.u-1][j].first == 1){
				if (Q.find(j+1) != Q.end() && adjMatrix[minKey.u-1][j].second < key[j].weight){
                    key[j].v = j+1;
                    key[j].weight = adjMatrix[minKey.v-1][j].second;
                    key[j].u = minKey.u;
                }
            }
        }
        /*       
          for (int i = 0; i < key.size(); i++){
		      cout << key[i].v << " " << key[i].weight << " " << key[i].u << endl;
          }      
          */
          
                 
    }
 
 


	
	

     
}
