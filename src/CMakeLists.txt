add_library (Tape tape_impl.cpp tape_impl.h tape.h tape_exception.cpp tape_exception.h)
add_executable (tape main.cpp)
target_link_libraries (tape Tape)
