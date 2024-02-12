#include <iostream>
#include "handler_parameters.hxx"
#include "handler_engine.hxx"

int main(int argc, char** argv) {
  HandlerParametersBuilder::BuildFromConfigFile(argc, argv);
  HandlerEngine engine;
  engine.Run();
  
  return 0;
}