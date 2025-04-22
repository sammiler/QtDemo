find_package(Qt5 COMPONENTS Core Gui Concurrent REQUIRED)

add_executable(WordCount WIN32
        main.cpp)

target_link_libraries(WordCount PRIVATE Qt5::Core Qt5::Gui     Qt5::Widgets  Qt5::Concurrent )