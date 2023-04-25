add_library (Tape tape_impl.cpp tape_impl.h tape.h)
add_executable (tape main.cpp)
target_link_libraries (tape Tape)
