#ifndef HANDLER_ENGINE_HXX
#define HANDLER_ENGINE_HXX

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include "handler_parameters.hxx"
#include "gateway_helper.hxx"
#include "models.hxx"
#include "module_studygen.hxx"
#include "task_processor.hxx"

class HandlerEngine {
public: 
  HandlerEngine() {}
  ~HandlerEngine() {}
  HandlerEngine(const HandlerEngine&) = delete;
  HandlerEngine& operator=(const HandlerEngine&) = delete;

  int Run(HandlerParameters params) {
    GatewayHelper gw(GatewayConfig(params.gatewayUrl, params.username, params.password));
    TaskProcessor processor(&gw);

    while (true) {
      processor.FetchTasks();

      // Sleep for 10 seconds
      std::this_thread::sleep_for(std::chrono::seconds(10));
    }
    return 0;
  }
};

#endif // HANDLER_ENGINE_HXX