/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 13, 2024.
 *
 * MIT License
 */

#ifndef CONFERENCE_MANAGER_TEST_HPP
#define CONFERENCE_MANAGER_TEST_HPP

#include "gtest/gtest.h"

#include "conferenceManager.hpp"

/**
 * @brief Runs unit tests for ConferenceManager.
 *
 */
class ConferenceManagerTest : public ::testing::Test
{
  protected:
    // LCOV_EXCL_START
    ConferenceManagerTest() = default;
    ~ConferenceManagerTest() = default;

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

#endif // CONFERENCE_MANAGER_HPP
