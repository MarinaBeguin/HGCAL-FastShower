#include <iostream>
#include <string>
#include <Python.h>
#include "Generator.h"
#include "Parameters.h"


int main(int argc, char** argv) {

  if(argc!=2)
  {
    std::cout<<"Usage:\n";
    std::cout<<" shower_simulation.exe config_file_name\n";
    return 1;
  }

  std::string config_file(argv[1]);
  Parameters params;
  try
  {
    params.read(config_file);
  }
  catch(...)
  {
    std::cout<<"Error reading python config file:\n";
    PyErr_Print();
    PyErr_Clear();
    return 2;
  }

  params.print();

  //Generator generator;
  //generator.simulate(nevents);
  return 0;
}
