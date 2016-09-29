#include <iostream>
#include "scene_lua.hpp"

int threads = 1;

int main(int argc, char** argv)
{
  std::string filename = "scene.lua";
  if (argc >= 2) {
    filename = argv[1];
		if (argc >= 3) threads = atoi(argv[2]);
  }

  if (!run_lua(filename)) {
    std::cerr << "Could not open " << filename << std::endl;
    return 1;
  }
}

