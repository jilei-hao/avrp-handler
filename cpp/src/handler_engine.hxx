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

class HandlerEngine {
public: 
  HandlerEngine() {}
  ~HandlerEngine() {}
  HandlerEngine(const HandlerEngine&) = delete;
  HandlerEngine& operator=(const HandlerEngine&) = delete;

  int Run(HandlerParameters params) {
    GatewayHelper gw(GatewayConfig(params.gatewayUrl, params.username, params.password));

    while (true) {
      // Print heartbeat
      std::cout << "-- Check available tasks..." << std::endl;

      std::vector<HandlerTask> tasks = gw.GetTasks();

      StudyGenModule module;
      module.set_study_config(tasks[0].m_Config);
      module.download_data();
      module.run();
      module.upload_result();

      // Sleep for 10 seconds
      std::this_thread::sleep_for(std::chrono::seconds(10));
    }
    return 0;
  }
};

#endif // HANDLER_ENGINE_HXX