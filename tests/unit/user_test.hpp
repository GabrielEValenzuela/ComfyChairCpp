/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 13, 2024.
 *
 * MIT License
 */

#ifndef USER_TEST_HPP
#define USER_TEST_HPP

#include "gtest/gtest.h"

/**
 * @brief Runs unit tests for User.
 *
 */
class UserTest : public ::testing::Test
{
  protected:
    // LCOV_EXCL_START
    UserTest() = default;
    ~UserTest() = default;

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

#endif // USER_TEST_HPP
