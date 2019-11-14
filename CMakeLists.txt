cmake_minimum_required(VERSION 3.5)
project(PolitoceanAnalytics)

set(CMAKE_CXX_STANDARD 11)

if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
	In-source builds are not allowed.
	Please, create a separate directory for build files (e.g. build/).
	Delete CMakeCache.txt, make a separate dir and try again.
	")
endif()

add_subdirectory(politocean_common)
include_directories(politocean_common/include)

include_directories(include)

add_executable(PolitoceanSensors src/PolitoceanSensors.cpp)

target_link_libraries(PolitoceanSensors
    PolitoceanCommon::Sensor
    PolitoceanCommon::mqttLogger
    PolitoceanCommon::logger
    PolitoceanCommon::MqttClient
)

set(CMAKE_INSTALL_PREFIX:PATH /usr)
include(GNUInstallDirs)

install (   TARGETS PolitoceanSensors
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
            PERMISSIONS WORLD_READ WORLD_EXECUTE    )