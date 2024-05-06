#include <iostream>

#define CATCH_CONFIG_MAIN
#include "Testai/catch.hpp"
#include "funkcijos.h"

TEST_CASE("Default Constructor", "[Default Constructor]")
{
    studentas studentas1;

    REQUIRE(studentas1 == studentas("", "", {}, 0));
}

TEST_CASE("Copy Constructor", "[Copy Constructor]")
{
    studentas studentas1;
    studentas studentas2(studentas1);

    REQUIRE(studentas2 == studentas1);
}

TEST_CASE("Move Constructor", "[Move Constructor]")
{
    studentas studentas1("Vardenis", "Pavardenis", {}, 0);
    studentas studentas2(move(studentas1));

    REQUIRE(studentas2 == studentas("Vardenis", "Pavardenis", {}, 0));
    REQUIRE_FALSE(studentas1 == studentas2);
}