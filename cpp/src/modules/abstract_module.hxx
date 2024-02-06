#ifndef ABSTRACT_MODULE_HXX
#define ABSTRACT_MODULE_HXX

#include "models.hxx"

class AbstractModule {
public:
  virtual ~AbstractModule() = default;
  AbstractModule(const AbstractModule&) = delete;
  AbstractModule& operator=(const AbstractModule&) = delete;
  AbstractModule(AbstractModule&&) = delete;
  AbstractModule& operator=(AbstractModule&&) = delete;
  AbstractModule() {};

  // set study config
  virtual void SetStudyConfig(const StudyConfig& config) 
  {
    m_config = config;
  }

  // download data from the gateway
  virtual void DownloadData() = 0;

  // after downloading data, run the module
  virtual void Run() = 0;

  // upload result to the gateway
  virtual void UploadResult() = 0;

protected:
  StudyConfig m_config;
};

#endif