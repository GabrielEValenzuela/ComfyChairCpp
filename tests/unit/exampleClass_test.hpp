/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 13, 2024.
 *
 * MIT License
 */

#ifndef _EXAMPLE_CLASS_TEST_HPP
#define _EXAMPLE_CLASS_TEST_HPP

#include "exampleClass.hpp"
#include "gtest/gtest.h"

/**
 * @brief Runs unit tests for ExampleClass.
 *
 */
class ExampleClassTest : public ::testing::Test
{
  protected:
    // LCOV_EXCL_START
    ExampleClassTest() = default;
    ~ExampleClassTest() = default;

    /**
     * @brief Set the environment for testing.
     *
     */
    void SetUp() override;

    /**
     * @brief Clean the environment after testing.
     *
     */
    void TearDown() override;
    // LCOV_EXCL_STOP
};

#endif // _EXAMPLE_CLASS_TEST_HPP
