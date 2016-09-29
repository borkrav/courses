#include <uC++.h>
#include <dirent.h>
#include <iostream>
#include <vector>
#include <uSemaphore.h>
#include "q1mapper.h"
#include "q1reducer.h"
#include "q1sortmapper.h"
#include "q1sortreducer.h"

using namespace std;



void uMain::main() {

	//set up all the needed variables
	string pathName = argv[0];
	string dirName;
	vector<string> filesToProcess = vector<string>();
	int numReducers = 4;
	int queueLength = 16;
	int sortBufferSize = 0;

	vector<Mapper*> mappers;
	vector<Reducer*> reducers;

	//get all the input

	try {
	
		//wrong number of parameteres
		if (argc == 1 || argc > 5) throw -1;
	
		else if (argc > 1) {
		
			dirName = argv[1];
			//copy all file names from the given directory
			DIR *directory;
			struct dirent *ent;
			if ((directory = opendir (dirName.c_str())) != NULL) {
		
				while ((ent = readdir (directory)) != NULL) {
					
					//stat to see file type
					struct stat s;
					stat((dirName + "/" + ent->d_name).c_str(),&s);
					if (s.st_mode & S_IFREG){
						//this name refers to a file, therefore we need to process it
						filesToProcess.push_back(ent->d_name);
					}
									
				}

				closedir (directory);
			} 

			else {
				cerr << "Error! Cannot open directory \"" + dirName + "\"" << endl;
				throw -1;
			}

			//get all the other input
			if (argc > 2){
				if (atoi(argv[2]) <= 0) throw -1;
				numReducers = atoi(argv[2]);
				if (argc > 3){
					if (atoi(argv[3]) <= 0) throw -1;
					queueLength = atoi(argv[3]);
					if (argc > 4){
						if  (atoi(argv[4]) < 0) throw -1;
						sortBufferSize = atoi(argv[4]);	
					}	
				}
			}
		}

	} catch (int i) {

		if (i == -1) {
			cerr << "Usage: " + pathName + " input-directory [ num-reducers ( > 0 ) [ queue-length ( > 				0 ) [ sort-buffer-size ( >= 0 ) ] ] ]" << endl;
			exit(0);
		}
	}

	//done getting all the input


	uSemaphore signal(0);

	//using regular mappers and reducers
	if (sortBufferSize == 0){

		//create my mappers
		for (int i = 0; i< filesToProcess.size(); i++){

			mappers.push_back(new Mapper(dirName + "/" + filesToProcess[i], 
																	 queueLength,
																	 &signal));
		}

		//create my reducers
		for (int i = 0; i< numReducers; i++){

			reducers.push_back(new Reducer(i, numReducers, &signal,mappers));
		}
	

		//delete my reducers
		for (int i = 0; i< numReducers; i++){
			delete reducers[i];
		}

		//delete my mappers
		for (int i = 0; i< mappers.size(); i++){
			delete mappers[i];
		}

	}

	//using sorted mappers and reducers
	else {

		//create my mappers
		for (int i = 0; i< filesToProcess.size(); i++){

			mappers.push_back(new SortMapper(dirName + "/" + filesToProcess[i], 
																	 queueLength, sortBufferSize,
																	 &signal));
		}

		//create my reducers
		for (int i = 0; i< numReducers; i++){

			reducers.push_back(new SortReducer(i, numReducers, &signal,mappers));
		}
	

		//delete my reducers
		for (int i = 0; i< numReducers; i++){
			delete reducers[i];
		}


		//delete my mappers
		for (int i = 0; i< mappers.size(); i++){
			delete mappers[i];
		}




	}

	cout << "Finished! Semaphore counter: " << signal.counter() << endl;

}
