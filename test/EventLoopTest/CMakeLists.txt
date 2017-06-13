cmake_minimum_required(VERSION 3.5)
PROJECT(EventLoopTest)
set(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++11)
set(SRC_LIST_1 ../../net/EventLoop.h ../../net/EventLoop.cpp test1.cpp )
set(SRC_LIST_2 ../../net/EventLoop.h ../../net/EventLoop.cpp test2.cpp )
set(SRC_LIST_3 ../../net/EventLoop.h ../../net/EventLoop.cpp test3.cpp )

ADD_EXECUTABLE(test1 ${SRC_LIST_1})
ADD_EXECUTABLE(test2 ${SRC_LIST_2})
ADD_EXECUTABLE(test3 ${SRC_LIST_3})

TARGET_LINK_LIBRARIES(test1 muduo_net)
TARGET_LINK_LIBRARIES(test1 muduo_base)
TARGET_LINK_LIBRARIES(test1 pthread)

TARGET_LINK_LIBRARIES(test2 muduo_net)
TARGET_LINK_LIBRARIES(test2 muduo_base)
TARGET_LINK_LIBRARIES(test2 pthread)

TARGET_LINK_LIBRARIES(test3 muduo_net)
TARGET_LINK_LIBRARIES(test3 muduo_base)
TARGET_LINK_LIBRARIES(test3 pthread)
