#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

struct line {
	int x1;
	int y1;
	int x2;
	int y2;
    char type;
    int count;
};

struct point {
    int value;
    char type;
    int count;
};

using namespace std;

void print(vector <struct line> lines);
vector <struct line> lines;
vector <struct point> partA(vector <struct line> hor, vector <struct line> vert);
int partB (vector <struct line> hor, vector <struct line> vert, int flag);
vector <struct line> originalVert;

int counter;


int main(){

	
	int numOfLines, x1, x2, y1, y2;
	
	cin >> numOfLines;
	
	for (int i = 0; i < numOfLines; i++){
		struct line newLine;
		cin >> newLine.x1 >> newLine.y1 >> newLine.x2 >> newLine.y2;
        newLine.count = 0;
		lines.push_back(newLine);
	}
	
    
    vector <struct line> H;
    vector <struct point> R;
    
    for (int i = 0; i < lines.size(); i++){
		
        if (lines[i].x1 == lines[i].x2){
			lines[i].type = 'v';
            originalVert.push_back(lines[i]);
		}
		
		else if (lines[i].y1 == lines[i].y2){
			lines[i].type = 'h';
			H.push_back(lines[i]);
		}
		
		
	}
   
    partB(H,originalVert, 2);
    
    int a = counter;
    
    counter = 0;
    
    partB(H,originalVert, 1);
    
    int b = counter;
    
    cout << a - b << endl;
      
    
		
}


bool lineY2compare (struct line a, struct line b) {
    return (a.y2 < b.y2);
}

bool lineY1compare (struct line a, struct line b) {
    return (a.y1 < b.y1);
}

int partB (vector <struct line> hor, vector <struct line> vert, int flag){
    
    
    if ((hor.size() + vert.size()) <= 1){
        return 1;
    }
    
    
    vector <struct line> fullSet;
    
    for (int i = 0; i < hor.size(); i++) {
        fullSet.push_back(hor[i]);
    }
    
    for (int i = 0; i < vert.size(); i++) {
        fullSet.push_back(vert[i]);
    }
    
    int yMedian = 0;
    
    if (flag == 2){
        sort (fullSet.begin(), fullSet.end(), lineY2compare);
        yMedian = fullSet[floor(fullSet.size()/2)].y2;

    }
 
    if (flag == 1){
        sort (fullSet.begin(), fullSet.end(), lineY1compare);
        yMedian = fullSet[floor(fullSet.size()/2)].y1;

    }
    
    vector <struct line> HU;
    vector <struct line> HL;
    vector <struct line> RU;
    vector <struct line> RL;
            
    if (flag == 2){
    
        for (int i = 0; i < hor.size(); i++){
            if (hor[i].y2 < yMedian){
                HL.push_back(hor[i]);
            }
            if (hor[i].y2 >= yMedian){
                HU.push_back(hor[i]);
            }
        }
        
        for (int i = 0; i < vert.size(); i++){
            if (vert[i].y2 < yMedian){
                RL.push_back(vert[i]);
            }
            if (vert[i].y2 >= yMedian){
                RU.push_back(vert[i]);
            }
        }
    }
    
    else if (flag == 1){
        
        for (int i = 0; i < hor.size(); i++){
            if (hor[i].y1 < yMedian){
                HL.push_back(hor[i]);
            }
            if (hor[i].y1 >= yMedian){
                HU.push_back(hor[i]);
            }
        }
        
        for (int i = 0; i < vert.size(); i++){
            if (vert[i].y1 < yMedian){
                RL.push_back(vert[i]);
            }
            if (vert[i].y1 >= yMedian){
                RU.push_back(vert[i]);
            }
        }
    }
    
    partB(HU, RU, flag);
    partB(HL, RL, flag);
        
    vector <struct point> R;
    
  
    
    R = partA(HL, RU);
    
    for (int i = 0; i < R.size(); i++) {
        if (R[i].type == 'v'){
            counter += R[i].count;
        }
    }
    
    return 1;
    
    
}

bool compare (struct point a, struct point b) {
    
    if (a.type == 'l' && b.type == 'v' && a.value == b.value){
        return true;
    }
    if (a.type == 'v' && b.type == 'l' && a.value == b.value){
        return false;
    }
    if (a.type == 'r' && b.type == 'v' && a.value == b.value){
        return false;
    }
    if (a.type == 'v' && b.type == 'r' && a.value == b.value){
        return true;
    }
    else return (a.value < b.value);
}

vector <struct point> partA(vector <struct line> hor, vector <struct line> vert){
    
    
    vector <struct point> result;
    
    for (int i = 0; i < hor.size(); i++){
        struct point leftPoint, rightPoint;    
        leftPoint.value = hor[i].x1;
        leftPoint.type = 'l';
        rightPoint.value = hor[i].x2;
        rightPoint.type = 'r';
        result.push_back(leftPoint);
        result.push_back(rightPoint);
    }
    
    for (int i = 0; i < vert.size(); i++){
        struct point vertical;
        vertical.value = vert[i].x1;
        vertical.type = 'v';
        result.push_back(vertical);
    }
    
    sort (result.begin(), result.end(), compare);
        
    int counter = 0;
    
    for (int i = 0; i < result.size(); i++){
                
        if (result[i].type == 'l'){
            
            counter++;
        }
        else if (result[i].type == 'r'){
            
            counter--;
        }
        else if (result[i].type == 'v'){
            
            result[i].count = counter;
        }
    }
    
    return result;
    
}