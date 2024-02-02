#include <iostream>
#include "handler_parameters.hxx"
#include "handler_engine.hxx"

int main(int argc, char** argv) {
  HandlerEngine engine;
  
  engine.Run(HandlerParametersBuilder::BuildFromArgs(argc, argv));
  
  return 0;
}