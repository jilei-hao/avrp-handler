#ifndef HANDLER_PARAMETERS_HXX
#define HANDLER_PARAMETERS_HXX

class HandlerParameters {
public:
  HandlerParameters() {}
  ~HandlerParameters() {}
  HandlerParameters(const HandlerParameters&) = default;
  HandlerParameters& operator=(const HandlerParameters&) = delete;

  std::string gatewayUrl;
  std::string username;
  std::string password;
};

class HandlerParametersBuilder {
public:
  HandlerParametersBuilder() {}
  ~HandlerParametersBuilder() {}
  HandlerParametersBuilder(const HandlerParametersBuilder&) = delete;
  HandlerParametersBuilder& operator=(const HandlerParametersBuilder&) = delete;

  static HandlerParameters BuildFromArgs(int argc, char* argv[]) {
    HandlerParameters params;
    for (int i = 1; i < argc; i++) {
      if (std::string(argv[i]) == "-url") {
        if (i + 1 < argc) {
          params.gatewayUrl = argv[i + 1];
        }
      } else if (std::string(argv[i]) == "-un") {
        if (i + 1 < argc) {
          params.username = argv[i + 1];
        }
      } else if (std::string(argv[i]) == "-pw") {
        if (i + 1 < argc) {
          params.password = argv[i + 1];
        }
      }
    }
    return params;
  }
};



#endif // HANDLER_PARAMETERS_HXX