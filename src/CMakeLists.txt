add_executable(Grapes main.cpp Scanner.cpp Parser.cpp)

target_link_libraries(Grapes svm)

install(TARGETS Grapes DESTINATION bin)