cmake_minimum_required(VERSION 3.12)
project(proj3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(proj3
        catch.hpp
        catch_reporter_automake.hpp
        catch_reporter_tap.hpp
        catch_reporter_teamcity.hpp
        counter.h
        main.cpp)
