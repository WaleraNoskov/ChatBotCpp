cmake_minimum_required(VERSION 4.0)
project(untitled)

set(CMAKE_CXX_STANDARD 26)

include(FetchContent)

# FTXUI
FetchContent_Declare(ftxui
        GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
        GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)

# GoogleTest
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)
enable_testing()

# SQLite3 (vcpkg)
find_package(unofficial-sqlite3 CONFIG REQUIRED)

# --- Библиотеки ---
add_library(core_lib
        core/Task.cpp
        core/TaskList.cpp
)

target_include_directories(core_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(data_access_lib
        data_access/SqliteService.cpp
        data_access/TaskListRepository.cpp
)

target_include_directories(data_access_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(data_access_lib PUBLIC core_lib unofficial::sqlite3::sqlite3)

# --- Приложение ---
add_executable(untitled
        main.cpp
        controls/chat/ChatViewModel.cpp
        controls/chat/ChatView.cpp
)

target_link_libraries(untitled PRIVATE
        core_lib
        data_access_lib
        ftxui::component
        ftxui::dom
        ftxui::screen
)

# --- Тесты ---
add_executable(tests
        data_access_tests/SqliteServiceTests.cpp
        data_access_tests/TaskListRepositoryTests.cpp
)

target_link_libraries(tests PRIVATE
        core_lib
        data_access_lib
        gtest_main
        unofficial::sqlite3::sqlite3
)

include(GoogleTest)
gtest_discover_tests(tests)