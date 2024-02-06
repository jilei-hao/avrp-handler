#ifndef MODULE_STUDYGEN_HXX
#define MODULE_STUDYGEN_HXX

#include <iostream>
#include "abstract_module.hxx"

class StudyGenModule : public AbstractModule
{
public:
  StudyGenModule() {}
  ~StudyGenModule() {}
  StudyGenModule(const StudyGenModule&) = delete;
  StudyGenModule& operator=(const StudyGenModule&) = delete;

  void DownloadData() override
  {
    std::cout << "Downloading data..." << std::endl;
  }

  void Run() override
  {
    std::cout << "Running module..." << std::endl;
  }

  void UploadResult() override
  {
    std::cout << "Uploading result..." << std::endl;
  }
};

#endif