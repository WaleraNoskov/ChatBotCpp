cmake_minimum_required(VERSION 4.0)
project(untitled)

set(CMAKE_CXX_STANDARD 26)

include(FetchContent)
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

add_executable(untitled main.cpp
        controls/chat/ChatViewModel.cpp
        controls/chat/ChatViewModel.h
        controls/chat/ChatView.cpp
        controls/chat/ChatView.h)

target_link_libraries(untitled PRIVATE
        ftxui::component
        ftxui::dom
        ftxui::screen
)