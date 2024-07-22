/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */
#ifndef _MOCK_ARTICLE_HPP
#define _MOCK_ARTICLE_HPP

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "articleInterface.hpp"
#include "nlohmann/json.hpp"
#include "trackStateInterface.hpp"
#include "user.hpp"

#include <memory>

/**
 * @class MockArticle
 *
 * @brief Mock class for simulating a track state object.
 *
 * The `MockArticle` class is designed to simulate the behavior of a track state
 * for testing purposes. It provides mock implementations of methods and
 * allows you to set expectations on method calls and their return values for testing.
 *
 * This class is used in unit tests only to verify interactions with a content
 * register without actually performing real operations on it.
 */
class MockArticle : public Article
{
  public:
    /**
     * @brief MockArticle constructor
     */
    MockArticle(const nlohmann::json& articleJson){};

    MockArticle() = default;
    ~MockArticle() = default;

    /**
     * @brief Mock method for updateFields.
     *
     * @note This method is intended for testing purposes and does not perform any real action.
     */
    MOCK_METHOD(void, updateFields, (const std::shared_ptr<Article>&), (override));

    /**
     * @brief Mock method for addAuthor.
     *
     * @note This method is intended for testing purposes and does not perform any real action.
     */
    MOCK_METHOD(void, addAuthor, (const User&), ());

    /**
     * @brief Mock method for articleName.
     *
     * @note This method is intended for testing purposes and does not perform any real action.
     */
    MOCK_METHOD(const std::string&, articleName, (), (const));

    /**
     * @brief Mock method for display.
     *
     * @note This method is intended for testing purposes and does not perform any real action.
     */
    // MOCK_METHOD(void, display, (), (override));
};

#endif // _MOCK_ARTICLE_HPP
