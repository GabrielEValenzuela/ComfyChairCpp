/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 25, 2024.
 *
 * MIT License
 */

#ifndef TIR_ONE_HPP_
#define TIR_ONE_HPP_

#include "articleInterface.hpp"
#include "articlePoster.hpp"
#include "articleRegular.hpp"
#include "conference.hpp"
#include "conferenceManager.hpp"
#include "nlohmann/json.hpp"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

/**
 * @brief Runs unit tests for ExampleClass.
 *
 */
class TIROne : public ::testing::Test
{
  protected:
    // LCOV_EXCL_START
    TIROne() = default;
    ~TIROne() = default;

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

    nlohmann::json jsonInput;
};

#endif // TIR_ONE_HPP_
