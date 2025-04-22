
add_executable(IPCWindows
        WIN32
        main.cpp
        senderwindow.cpp
        senderwindow.h     # 包含 Q_OBJECT，需要 moc 处理
        receiverwindow.cpp
        receiverwindow.h   # 包含 Q_OBJECT，需要 moc 处理
        # ipc_defs.h 不包含 Q_OBJECT，不需要列在这里
)

# 链接库
# target_link_libraries 用于指定目标需要链接的库
# PRIVATE 关键字表示这些库只供该目标内部使用
# 明确列出需要的 Qt 模块库
target_link_libraries(IPCWindows
        PRIVATE
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

