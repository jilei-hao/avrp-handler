#ifndef HANDLER_ENGINE_HXX
#define HANDLER_ENGINE_HXX

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <filesystem>
#include "handler_parameters.hxx"
#include "gateway_helper.hxx"
#include "data_server_helper.hxx"
#include "module_studygen.hxx"
#include "task_processor.hxx"


class HandlerEngine {
public: 
  HandlerEngine() {}
  ~HandlerEngine() {}
  HandlerEngine(const HandlerEngine&) = delete;
  HandlerEngine& operator=(const HandlerEngine&) = delete;

  void CheckWorkDirectories() const {
    std::cout << "[HandlerEngine] Checking work directories..." << std::endl;
    HandlerParameters& params = HandlerParameters::getInstance();
    std::string workDir = params.getWorkDir();
    std::string downloadDir = params.getDownloadDir();
    std::string uploadDir = params.getUploadDir();
    std::string logDir = params.getLogDir();

    // check if directories exist, if not, create them
    if (!std::filesystem::exists(downloadDir)) {
      std::filesystem::create_directory(downloadDir);
      std::cout << "[HandlerEngine] Created download directory." << std::endl;
    } else {
      std::cout << "[HandlerEngine] Download directory already exists." << std::endl;
    }
    if (!std::filesystem::exists(uploadDir)) {
      std::filesystem::create_directory(uploadDir);
      std::cout << "[HandlerEngine] Created upload directory." << std::endl;
    } else {
      std::cout << "[HandlerEngine] Upload directory already exists." << std::endl;
    }

    if (!std::filesystem::exists(logDir)) {
      std::filesystem::create_directory(logDir);
      std::cout << "[HandlerEngine] Created log directory." << std::endl;
    } else {
      std::cout << "[HandlerEngine] Log directory already exists." << std::endl;
    }
  }

  int Run() {
    HandlerParameters params = HandlerParameters::getInstance();
    GatewayHelper gw(GatewayConfig(
      params.getGatewayURL(), params.getGatewayUsername(), params.getGatewayPassword()));
    DataServerHelper ds(params.getDataServerURL());
    TaskProcessor processor(&gw, &ds);

    CheckWorkDirectories();

    while (true) {
      processor.FetchTasks();

      processor.Process();

      // Sleep for 10 seconds
      std::this_thread::sleep_for(std::chrono::seconds(10));
    }
    return 0;
  }
};

#endif // HANDLER_ENGINE_HXX