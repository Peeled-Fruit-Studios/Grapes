add_library(svm SHARED Value.cpp Program.cpp)

target_include_directories(svm PUBLIC "${PROJECT_SOURCE_DIR}/svm/include")

install(TARGETS svm DESTINATION share)