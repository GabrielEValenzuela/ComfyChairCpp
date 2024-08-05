/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 13, 2024.
 *
 * MIT License
 */

#ifndef ARTICLE_TEST_HPP
#define ARTICLE_TEST_HPP

#include "articleInterface.hpp"
#include "gtest/gtest.h"

/**
 * @brief Runs unit tests for ExampleClass.
 *
 */
class ArticleTest : public ::testing::Test
{
  protected:
    // LCOV_EXCL_START
    ArticleTest() = default;
    ~ArticleTest() = default;

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

#endif // ARTICLE_TEST_HPP
