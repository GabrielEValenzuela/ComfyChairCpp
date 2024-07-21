/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 13, 2024.
 *
 * MIT License
 */

#ifndef TRACK_TEST_HPP
#define TRACK_TEST_HPP

#include "gtest/gtest.h"

/**
 * @brief Runs unit tests for ExampleClass.
 *
 */
class TrackTest : public ::testing::Test
{
  protected:
    // LCOV_EXCL_START
    TrackTest() = default;
    ~TrackTest() = default;

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

#endif // TRACK_TEST_HPP
