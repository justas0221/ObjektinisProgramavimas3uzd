#include <iostream>

#define CATCH_CONFIG_MAIN
#include "Testai/catch.hpp"
#include "funkcijos.h"
#include "vector.h"

TEST_CASE("Default Vector Constructor", "[Default Vector Constructor]")
{
    std::Vector<int> v;

    REQUIRE(v.empty());
}

TEST_CASE("Vector Copy Constructor", "[Vector Copy Constructor]")
{
    std::Vector<int> v1{1, 2, 3};
    std::Vector<int> v2(v1);

    REQUIRE(v1 == v2);
}

TEST_CASE("Vector Move Constructor", "[Vector Move Constructor]")
{
    std::Vector<int> v1{1, 2, 3};
    std::Vector<int> v2(std::move(v1));

    REQUIRE(v2.size() == 3);
    REQUIRE(v2[0] == 1);
    REQUIRE(v2[1] == 2);
    REQUIRE(v2[2] == 3);

    REQUIRE(v1.size() == 0);
    REQUIRE(v1.empty());
    REQUIRE_FALSE(v1 == v2);
}

TEST_CASE("Vector Copy Assignment Operator", "[Vector Copy Assignment Operator]")
{
    std::Vector<int> v1{1, 2, 3};
    std::Vector<int> v2;
    v2 = v1;

    REQUIRE(v1 == v2);
}

TEST_CASE("Vector Move Assignment Operator", "[Vector Move Assignment Operator]")
{
    std::Vector<int> v1{1, 2, 3};
    std::Vector<int> v2;
    v2 = std::move(v1);

    REQUIRE(v2.size() == 3);
    REQUIRE(v2[0] == 1);
    REQUIRE(v2[1] == 2);
    REQUIRE(v2[2] == 3);

    REQUIRE(v1.size() == 0);
    REQUIRE(v1.empty());
    REQUIRE_FALSE(v1 == v2);
}

TEST_CASE("Vector Resize Function", "[Vector Resize Function]")
{
    std::Vector<int> v1{1, 2, 3};
    v1.resize(2);

    REQUIRE(v1.size() == 2);
}

TEST_CASE("Vector Reserve Function", "[Vector Reserve Function]")
{
    std::Vector<int> v1{1, 2, 3};
    v1.reserve(20);

    REQUIRE(v1.capacity() == 20);
}

TEST_CASE("Vector Shrink to Fit Function", "[Vector Shrink to Fit Function]")
{
    std::Vector<int> v1{1, 2, 3};
    v1.reserve(20);
    v1.shrink_to_fit();

    REQUIRE(v1.capacity() == v1.size());
}

TEST_CASE("Vector Emplace Back Function", "[Vector Emplace Back Function]")
{
    std::Vector<int> v1{1, 2, 3};
    v1.emplace_back(4);
    v1.emplace_back(5);

    REQUIRE(v1[3] == 4);
    REQUIRE(v1[4] == 5);
}

TEST_CASE("Vector Push Back Function", "[Vector Push Back Function]")
{
    std::Vector<int> v1{1, 2, 3};
    v1.push_back(4);
    v1.push_back(5);

    REQUIRE(v1[3] == 4);
    REQUIRE(v1[4] == 5);
}

TEST_CASE("Vector Pop Back Function", "[Vector Pop Back Function]")
{
    std::Vector<int> v1{1, 2, 3};
    v1.pop_back();
    v1.pop_back();

    REQUIRE(v1.size() == 1);
}

TEST_CASE("Vector Insert Function", "[Vector Insert Function]")
{
    std::Vector<int> v1{1, 2, 3};
    std::Vector<int>::iterator it = v1.begin() + 1;
    v1.insert(it, 3, 5);

    REQUIRE(v1.size() == 6);
    REQUIRE(v1[1] == 5);
    REQUIRE(v1[2] == 5);
    REQUIRE(v1[3] == 5);
}

TEST_CASE("Vector Erase Function", "[Vector Erase Function]")
{
    std::Vector<int> v1{1, 2, 3};
    std::Vector<int>::iterator it = v1.begin() + 1;
    v1.erase(it);

    REQUIRE(v1.size() == 2);
    REQUIRE(v1[0] == 1);
    REQUIRE(v1[1] == 3);
}

TEST_CASE("Vector Swap Function", "[Vector Swap Function]")
{
    std::Vector<int> v1{1, 2, 3};
    std::Vector<int> v2{10, 20, 30};
    v1.swap(v2);

    REQUIRE(v1.size() == v2.size());
    REQUIRE(v1[0] == 10);
    REQUIRE(v1[1] == 20);
    REQUIRE(v1[2] == 30);
    REQUIRE(v2[0] == 1);
    REQUIRE(v2[1] == 2);
    REQUIRE(v2[2] == 3);
}

TEST_CASE("Vector Clear Function", "[Vector Clear Function]")
{
    std::Vector<int> v1{1, 2, 3};
    v1.clear();

    REQUIRE(v1.size() == 0);
}

TEST_CASE("Default Student Constructor", "[Default Student Constructor]")
{
    studentas studentas1;

    REQUIRE(studentas1 == studentas("", "", {}, 0));
}

TEST_CASE("Student Copy Constructor", "[Student Copy Constructor]")
{
    studentas studentas1;
    studentas studentas2(studentas1);

    REQUIRE(studentas2 == studentas1);
}

TEST_CASE("Student Move Constructor", "[Student Move Constructor]")
{
    studentas studentas1("Vardenis", "Pavardenis", {}, 0);
    studentas studentas2(std::move(studentas1));

    REQUIRE(studentas2 == studentas("Vardenis", "Pavardenis", {}, 0));
    REQUIRE_FALSE(studentas1 == studentas2);
}

TEST_CASE("Student Copy Assignment Operator", "[Student Copy Assignment Operator]")
{
    studentas studentas1("Vardenis", "Pavardenis", {1, 2, 3}, 7);
    studentas studentas2;
    studentas2 = studentas1;

    REQUIRE(studentas2 == studentas1);
}

TEST_CASE("Student Move Assignment Operator", "[Student Move Assignment Operator]")
{
    studentas studentas1("Vardenis", "Pavardenis", {1, 2, 3}, 7);
    studentas studentas2;
    studentas2 = std::move(studentas1);

    REQUIRE(studentas2 == studentas("Vardenis", "Pavardenis", {1, 2, 3}, 7));
    REQUIRE_FALSE(studentas2 == studentas1);
}

TEST_CASE("Student Getters", "[Student Getters]")
{
    studentas studentas1("Vardenis", "Pavardenis2", {1, 2, 3}, 7);

    REQUIRE(studentas1.getVardas() == "Vardenis");
    REQUIRE_FALSE(studentas1.getPavarde() == "Pavardenis");
    REQUIRE(studentas1.getEgz() == 7);
}