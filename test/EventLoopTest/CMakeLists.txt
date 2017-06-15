cmake_minimum_required(VERSION 3.5)
PROJECT(EventLoopTest)
set(CMAKE_C_COMPILER g++)
add_compile_options(-std=c++11)

set(NET ../../net)
set(BASE ../../base)

set(SRC_LIST_1 ${NET}/EventLoop.o ${NET}/Poller.o ${NET}/Channel.o test1.cpp)
set(SRC_LIST_2 ${NET}/EventLoop.o ${NET}/Poller.o ${NET}/Channel.o test2.cpp)
set(SRC_LIST_3 ${NET}/EventLoop.o ${NET}/Poller.o ${NET}/Channel.o test3.cpp)
set(SRC_LIST_4 ${NET}/EventLoop.o ${NET}/Channel.o ${NET}/Poller.o test4.cpp)

ADD_EXECUTABLE(test1 ${SRC_LIST_1})
ADD_EXECUTABLE(test2 ${SRC_LIST_2})
ADD_EXECUTABLE(test3 ${SRC_LIST_3})
ADD_EXECUTABLE(test4 ${SRC_LIST_4})

TARGET_LINK_LIBRARIES(test1 muduo_net)
TARGET_LINK_LIBRARIES(test1 muduo_base)
TARGET_LINK_LIBRARIES(test1 pthread)

TARGET_LINK_LIBRARIES(test2 muduo_net)
TARGET_LINK_LIBRARIES(test2 muduo_base)
TARGET_LINK_LIBRARIES(test2 pthread)

TARGET_LINK_LIBRARIES(test3 muduo_net)
TARGET_LINK_LIBRARIES(test3 muduo_base)
TARGET_LINK_LIBRARIES(test3 pthread)

TARGET_LINK_LIBRARIES(test4 muduo_net)
TARGET_LINK_LIBRARIES(test4 muduo_base)
TARGET_LINK_LIBRARIES(test4 pthread)

TARGET_LINK_LIBRARIES(test5 muduo_net)
TARGET_LINK_LIBRARIES(test5 muduo_base)
TARGET_LINK_LIBRARIES(test5 pthread)
