#include <iostream>
#include "scene_lua.hpp"

int threads;

int main(int argc, char** argv)
{
  std::string filename = "scene.lua";
	threads = sysconf( _SC_NPROCESSORS_ONLN );
	
	time_t start = time(0);


	try { 

		switch (argc){
		
			case 3:
				if (atoi(argv[2]) < 0) throw -1;
				threads = atoi(argv[2]);
			case 2:
				filename = argv[1];
			case 1:
				break;
			default:
				throw -1;
		}
	
	} catch (int i){
		if (i == -1) {
			std::cerr << "Usage: rt [ scene.lua [ SSAA (0,1) [ threads (>0)] ] ]" << std::endl; 
			exit(0);
		}
	}

  if (!run_lua(filename)) {
    std::cerr << "Could not open " << filename << std::endl;
    return 1;
  }

	time_t finish = time(0);

	int timeItTook = finish - start;

	int hours = timeItTook / 3600;
	timeItTook = timeItTook % 3600;
	int minutes = timeItTook/60;
	timeItTook = timeItTook % 60;
	int seconds = timeItTook;

	
	std::cout << "FINISHED IN " 
						<< hours << "h " 
						<< minutes << "m " 
						<< seconds << "s"
					 	<< std::endl;



}

