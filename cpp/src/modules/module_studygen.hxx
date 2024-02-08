#ifndef MODULE_STUDYGEN_HXX
#define MODULE_STUDYGEN_HXX

#include <iostream>
#include <chrono>
#include <thread>
#include "abstract_module.hxx"
#include "study_generator.h"

class StudyGenModule : public AbstractModule
{
public:
  StudyGenModule() {}
  ~StudyGenModule() {}
  StudyGenModule(const StudyGenModule&) = delete;
  StudyGenModule& operator=(const StudyGenModule&) = delete;

  void Run() override
  {
    std::cout << "[StudyGenModule] Start Running Module..." << std::endl;
    Initialize();
    std::this_thread::sleep_for(std::chrono::seconds(21));
    Finalize();
  }

protected:
  void Initialize() override
  {
    std::cout << "[StudyGenModule] Initializing module..." << std::endl;
    std::cout << "-- study_id: " << m_Task.m_StudyID << std::endl;
    std::cout << "-- main_dsid: " << m_Task.m_Config.m_MainImageDSID << std::endl;
    std::cout << "-- sys_segref_dsid: " << m_Task.m_Config.m_SysSegrefDSID << std::endl;
    std::cout << "-- dias_segref_dsid: " << m_Task.m_Config.m_DiasSegrefDSID << std::endl;
  }

  void Finalize() override
  {
    std::cout << "[StudyGenModule] Finalizing module..." << std::endl;
  }

private:

  
};

#endif