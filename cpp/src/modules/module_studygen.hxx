#ifndef MODULE_STUDYGEN_HXX
#define MODULE_STUDYGEN_HXX

#include <iostream>
#include <chrono>
#include <thread>
#include <filesystem>
#include "abstract_module.hxx"
#include "study_generator.h"
#include "configurations.hxx"
#include "handler_parameters.hxx"

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
    RunStudyGennerator();
    Finalize();
  }

  void RunStudyGennerator()
  {
    std::cout << "[StudyGenModule] Running Study Generator..." << std::endl;
    auto taskConfig = m_Task.m_Config;
    studygen::StudyGenConfig sgConfig;
    sgConfig.fnImage4D = m_fnMainImage;
    sgConfig.nT =taskConfig.m_TPEnd - taskConfig.m_TPStart + 1;
    sgConfig.dirOut = m_dirOutput;

    // systolic config
    studygen::SegmentationConfig sysSegConfig;
    sysSegConfig.fnRefSeg = m_fnSysSegref;
    sysSegConfig.refTP = taskConfig.m_SysTPRef;
    for (int i = taskConfig.m_SysTPStart; i <= taskConfig.m_SysTPEnd; i++)
    {
      if (i == taskConfig.m_SysTPRef)
        continue;
      
      sysSegConfig.targetTPList.push_back(i);
    }
    sgConfig.segConfigList.push_back(sysSegConfig);

    // diasolic config
    studygen::SegmentationConfig diasSegConfig;
    diasSegConfig.fnRefSeg = m_fnDiasSegref;
    diasSegConfig.refTP = taskConfig.m_DiasTPRef;
    for (int i = taskConfig.m_DiasTPStart; i <= taskConfig.m_DiasTPEnd; i++)
    {
      if (i == taskConfig.m_DiasTPRef)
        continue;
      
      diasSegConfig.targetTPList.push_back(i);
    }
    sgConfig.segConfigList.push_back(diasSegConfig);

    // run study generator
    studygen::StudyGenerator sg;
    sg.SetStudyGenConfig(sgConfig);
    sg.Run();
  }

protected:
  void Initialize() override
  {
    std::cout << "[StudyGenModule] Initializing module..." << std::endl;
    std::cout << "-- study_id: " << m_Task.m_StudyID << std::endl;
    std::cout << "-- main_dsid: " << m_Task.m_Config.m_MainImageDSID << std::endl;
    std::cout << "-- sys_segref_dsid: " << m_Task.m_Config.m_SysSegrefDSID << std::endl;
    std::cout << "-- dias_segref_dsid: " << m_Task.m_Config.m_DiasSegrefDSID << std::endl;

    m_GatewayHelper->UpdateTaskStatus(m_Task.m_StudyID, "processing", m_Task.m_ModuleStatus | 0x00000001);

    m_fnMainImage = m_DataServerHelper->GetData(m_Task.m_Config.m_MainImageDSID, "nii.gz");
    m_fnSysSegref = m_DataServerHelper->GetData(m_Task.m_Config.m_SysSegrefDSID, "nii.gz");
    m_fnDiasSegref = m_DataServerHelper->GetData(m_Task.m_Config.m_DiasSegrefDSID, "nii.gz");

    // create a directory for the study
    HandlerParameters params = HandlerParameters::getInstance();
    m_dirOutput = params.getUploadDir() + "/" + std::to_string(m_Task.m_StudyID);
    std::filesystem::create_directory(std::to_string(m_Task.m_StudyID));

    std::cout << "-- data downloaded." << std::endl;
  }

  void Finalize() override
  {
    std::cout << "[StudyGenModule] Finalizing module..." << std::endl;
  }

private:
  std::string m_fnMainImage;
  std::string m_fnSysSegref;
  std::string m_fnDiasSegref;
  std::string m_dirOutput;
  
};

#endif