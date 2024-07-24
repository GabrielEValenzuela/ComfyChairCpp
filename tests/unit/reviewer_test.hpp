/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 13, 2024.
 *
 * MIT License
 */

#ifndef REVIEWER_TEST_HPP
#define REVIEWER_TEST_HPP

#include "bid.hpp"
#include "reviewer.hpp"
#include "gtest/gtest.h"
#include <memory>

/**
 * @brief Runs unit tests for Reviewer.
 *
 */
class ReviewerTest : public ::testing::Test
{
  protected:
    // LCOV_EXCL_START
    ReviewerTest() = default;
    ~ReviewerTest() = default;

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

    std::shared_ptr<Reviewer> reviewer;
};

#endif // REVIEWER_TEST_HPP
