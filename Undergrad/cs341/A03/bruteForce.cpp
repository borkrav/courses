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



using namespace std;

vector <struct line> lines;
int bruteForce (vector <struct line> hor, vector <struct line> vert);
vector <struct line> originalVert;

int counter;


void print(vector <struct line> lines){
    
	char map[10][10];
	
	for(int i = 0; i < 10; i++){
		for (int j = 0; j < 10; j++){
			map[i][j] = ' ';
		}
	}
	
	
	for (int i = 0; i < lines.size(); i++){
		if (lines[i].x1 == lines[i].x2){
			
			for (int j = 0; j <= lines[i].y2 - lines[i].y1; j++){
				map[lines[i].x1][lines[i].y1 + j] = '|';
			}
		}
		
		if (lines[i].y1 == lines[i].y2){
			
			for (int j = 0; j <= lines[i].x2 - lines[i].x1; j++){
				map[lines[i].x1 + j][lines[i].y1] = '-';
			}
		}
		
		
	}
    
    
	
	for(int i = 0; i < 10; i++){
        
		if (i == 0){
			cout << " ";
			for (int j = 0; j < 10; j++){
				cout << j; 
			}
			cout << endl;
		}
        
		for (int j = 0; j < 10; j++){
			if (j == 0){
				cout << i;
			}
			
			cout << map[j][i];
		}
		cout << endl;
	}
	
}





int main(){
    
	
	int numOfLines, x1, x2, y1, y2;
	
	cin >> numOfLines;
	
	for (int i = 0; i < numOfLines; i++){
		struct line newLine;
		cin >> newLine.x1 >> newLine.y1 >> newLine.x2 >> newLine.y2;
        newLine.count = 0;
		lines.push_back(newLine);
	}
	
    
    
	//print(lines);
    
    
    vector <struct line> H;
    
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
    
    
    int result = bruteForce(H,originalVert);
    

    //for (int i = 0; i < originalVert.size(); i++) {
    //    cout << originalVert[i].count << " ";
    //}
    cout << result << endl;
    

    
}



int bruteForce (vector <struct line> hor, vector <struct line> vert){
        
    
    int result = 0;
    
    for (int i = 0; i < vert.size(); i++){
        for (int j = 0; j < hor.size(); j++){
            
            //cout << hor[j].x1 << vert[i].x1 << hor[j].x2 << vert[i].y2 << hor[j].y1 << vert[i].y1 << endl;
            
            if((hor[j].x1 < vert[i].x1) && (vert[i].x1< hor[j].x2) && (vert[i].y2 > hor[j].y1) && (hor[j].y1 > vert[i].y1)) {
                result++;
            }
        }
    }
    
    
    return result;
    
    
}




