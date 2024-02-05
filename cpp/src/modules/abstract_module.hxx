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
  virtual void set_study_config(const StudyConfig& config) 
  {
    m_config = config;
  }

  // download data from the gateway
  virtual void download_data() = 0;

  // after downloading data, run the module
  virtual void run() = 0;

  // upload result to the gateway
  virtual void upload_result() = 0;

protected:
  StudyConfig m_config;
};

#endif