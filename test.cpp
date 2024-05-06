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

TEST_CASE("Copy Assignment Operator", "[Copy Assignment Operator]")
{
    studentas studentas1("Vardenis", "Pavardenis", {1, 2, 3}, 7);
    studentas studentas2;
    studentas2 = studentas1;

    REQUIRE(studentas2 == studentas1);
}

TEST_CASE("Move Assignment Operator", "[Move Assignment Operator]")
{
    studentas studentas1("Vardenis", "Pavardenis", {1, 2, 3}, 7);
    studentas studentas2;
    studentas2 = move(studentas1);

    REQUIRE(studentas2 == studentas("Vardenis", "Pavardenis", {1, 2, 3}, 7));
    REQUIRE_FALSE(studentas2 == studentas1);
}

TEST_CASE("Getters", "[Getters]")
{
    studentas studentas1("Vardenis", "Pavardenis2", {1, 2, 3}, 7);

    REQUIRE(studentas1.getVardas() == "Vardenis");
    REQUIRE_FALSE(studentas1.getPavarde() == "Pavardenis");
    REQUIRE(studentas1.getEgz() == 7);
}