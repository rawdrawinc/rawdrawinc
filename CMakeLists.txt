cmake_minimum_required(VERSION 3.20)
project(DigitalBrainSim VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(DBS_BUILD_TESTS "Build tests" ON)

add_library(brain_core
    src/core/Neuron.cpp
    src/core/BrainRegion.cpp
    src/core/Connectome.cpp
    src/core/SimulationEngine.cpp
    src/core/SpikeQueue.cpp
)

target_include_directories(brain_core PUBLIC include)

if (MSVC)
  target_compile_options(brain_core PRIVATE /W4 /permissive-)
else()
  target_compile_options(brain_core PRIVATE -Wall -Wextra -Wpedantic -O3)
endif()

add_library(brain_cognitive
    src/cognitive/Agent.cpp
    src/cognitive/Planner.cpp
)

add_library(brain_communication
    src/communication/DialogBrain.cpp
    src/communication/AuditTrail.cpp
)

target_include_directories(brain_communication PUBLIC include)

target_include_directories(brain_cognitive PUBLIC include)

target_link_libraries(brain_cognitive PUBLIC brain_core)

add_executable(digital_brain src/app/main.cpp)
target_link_libraries(digital_brain PRIVATE brain_core brain_cognitive brain_communication)

if (DBS_BUILD_TESTS)
  include(CTest)
  enable_testing()
  add_executable(unit_tests
      tests/test_engine.cpp
  )
  target_link_libraries(unit_tests PRIVATE brain_core brain_cognitive brain_communication)
  add_test(NAME unit_tests COMMAND unit_tests)
endif()
