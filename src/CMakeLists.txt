add_library (Tape tape_impl.cpp tape_impl.h tape.h tape_exception.cpp tape_exception.h tape_sorter.h tape_sorter_impl.cpp tape_sorter_impl.h)
add_executable (tape main.cpp)
target_link_libraries (tape Tape)
