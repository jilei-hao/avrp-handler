#ifndef DATA_SERVER_HELPER_HXX
#define DATA_SERVER_HELPER_HXX

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

class DataServerHelper
{
public:
  DataServerHelper(std::string url): m_Url(url) {}
  ~DataServerHelper() {}
  DataServerHelper(const DataServerHelper&) = default;
  DataServerHelper& operator=(const DataServerHelper&) = default;

  nlohmann::json GetData(uint64_t dsid)
  {
    std::cout << "[DataServerHelper] Getting data, dsid: " << dsid << std::endl;
    return nlohmann::json();
  }

private:
  std::string m_Url;
};

#endif