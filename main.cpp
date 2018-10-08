/*main.cpp*/

//
// <<YOUR NAME>>
// U. of Illinois, Chicago
// CS 341, Fall 2018
// Project #03: Counter container
//
// Test cases for Counter container, which acts like a set but keeps a count
// of how many times each element was inserted.
//
// References:
//   Unit testing based on Catch framework: https://github.com/catchorg/Catch2
//   Catch tutorial: https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top
//   install:     sudo apt-get install catch
//   compilation: g++ -std=c++11 -Wall -o main.exe main.cpp
//   execution:   ./main.exe
//

// let Catch provide main():
#define CATCH_CONFIG_MAIN

// gain access to Catch framework:
#include <catch.hpp>

// our Counter class:
#include "counter.h"

// *****************************************************************
//
// Test cases:
//
// *****************************************************************

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


TEST_CASE( "empty Counter<int>", "[Counter]" )
{
    Counter<int> C;

    REQUIRE(C.empty() == true);
    REQUIRE(C.size() == 0);
}//test


TEST_CASE( "Counter<int> with 1 element", "[Counter]" )
{
    Counter<int> C;

    REQUIRE(C.size() == 0);
    REQUIRE(C.empty() == true);

    SECTION("inserting element")
    {
        C.insert(123);

        REQUIRE(C.size() == 1);
        REQUIRE(!C.empty());

        SECTION("element contains")
        {
            REQUIRE(C[123] == true);
        }

        SECTION("element count")
        {
            REQUIRE(C(123) == 1);
        }

        SECTION("unknown elements not contained")
        {
            REQUIRE(!C[0]);
            REQUIRE(!C[122]);
            REQUIRE(!C[124]);
        }

        SECTION("unknown element counts")
        {
            REQUIRE(C(0) == 0);
            REQUIRE(C(122) == 0);
            REQUIRE(C(124) == 0);
        }
    }
}//test


TEST_CASE( "Counter<string> with 4 elements", "[Counter]" )
{
    Counter<string> C;

    REQUIRE(C.size() == 0);
    REQUIRE(C.empty() == true);

    SECTION("inserting 1st element")
    {
        C.insert("apple");

        REQUIRE(C.size() == 1);
        REQUIRE(!C.empty());

        REQUIRE(C["apple"] == true);
        REQUIRE(C("apple") == 1);

        SECTION("inserting 3 more elements")
        {
            C += "banana";
            C.insert("pear");
            C += "pizza";

            REQUIRE(C.size() == 4);
            REQUIRE(!C.empty());

            REQUIRE(C["apple"] == true);
            REQUIRE(C["banana"] == true);
            REQUIRE(C["pear"] == true);
            REQUIRE(C["pizza"] == true);

            SECTION("checking element counts")
            {
                REQUIRE(C("apple") == 1);
                REQUIRE(C("banana") == 1);
                REQUIRE(C("pear") == 1);
                REQUIRE(C("pizza") == 1);
            }

            SECTION("checking non-elements")
            {
                REQUIRE(!C["appl"]);
                REQUIRE(!C["applee"]);
                REQUIRE(!C["Pear"]);
                REQUIRE(!C["piazza"]);
                REQUIRE(!C["zizza"]);
            }

            SECTION("checking non-element counts")
            {
                REQUIRE(C("appl") == 0);
                REQUIRE(C("applee") == 0);
                REQUIRE(C("Pear") == 0);
                REQUIRE(C("piazza") == 0);
                REQUIRE(C("zizza") == 0);
            }
        }
    }
}//test


