/**
 * test_testable.c
 * 
 * Unit tests for testable.h
 */

#include "testable.h"

#include "unity.h"

/**
 * Tests that the return value of passesFunc is correct.
 */
TEST_CASE("passesFunc", "[testable]")
{
    TEST_ASSERT_EQUAL(17, passesFunc());
}

/**
 * Tests that the return value of failsFunc is correct.
 */
TEST_CASE("failsFunc", "[testable]")
{
    TEST_ASSERT_EQUAL(31, failsFunc());
}