

# Add the executable
add_executable(GraphicsItemInteraction
        WIN32
        main.cpp
        custom_item.cpp
        custom_item.h
        custom_scene.cpp
        custom_scene.h # Use WIN32 for a standard Windows GUI application
)

# Link Qt libraries to the executable
target_link_libraries(GraphicsItemInteraction
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

# Optional: Add compiler flags for UTF-8 source files if needed
# target_compile_options(${PROJECT_NAME} PRIVATE
#     $<$<CXX_COMPILER_ID:MSVC>:/utf-8>
#     $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-finput-charset=UTF-8>
# )