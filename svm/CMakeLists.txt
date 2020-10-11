add_library(svm STATIC Value.cpp Program.cpp ExecutionEngine.cpp)

target_include_directories(svm PUBLIC "${PROJECT_SOURCE_DIR}/svm/include")

install(TARGETS svm DESTINATION share)