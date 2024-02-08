cmake_minimum_required(VERSION 3.12)
project(handlercpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add your source files here
set(SOURCES
  src/main.cxx
)

# Add your header files here
#set(HEADERS)

include(FetchContent)

# Download and build cpr
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 3b15fa82ea74739b574d705fea44959b58142eb8)
FetchContent_MakeAvailable(cpr)

# Download and build nlohmann_json
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)



# Add any additional include directories here
set(INCLUDE_DIRS
  include
  src
  src/modules
  studygen/src
)

# Add any additional compiler flags here
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Add studyGen project
add_subdirectory(studygen)

set(LIBRARIES 
  cpr
  nlohmann_json::nlohmann_json
  StudyGenAPI
)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link any additional libraries
target_link_libraries(${PROJECT_NAME} ${LIBRARIES})

# Add any additional include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRS})
