/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 13, 2024.
 *
 * MIT License
 */

#include "article_test.hpp"
#include "articlePoster.hpp"
#include "articleRegular.hpp"

void ArticleTest::SetUp()
{
}

void ArticleTest::TearDown()
{
}

TEST_F(ArticleTest, ArticleCreation)
{
    const auto& jsonArticleRegular = R"(
    {
            "articleType": "Regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "additionalFileUrl": "https://bit.ly/example2",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    const auto& jsonArticlePoster = R"(
    {
            "articleType": "Poster",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "additionalFileUrl": "https://bit.ly/example2",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    auto articleRegular = std::make_shared<ArticleRegular>(jsonArticleRegular);
    auto articlePoster = std::make_shared<ArticlePoster>(jsonArticlePoster);

    EXPECT_TRUE(articleRegular != nullptr);
    EXPECT_TRUE(articlePoster != nullptr);
}

TEST_F(ArticleTest, RegularArticle)
{
    // Define the JSON to build the regular article
    const auto& jsonArticleRegular = R"(
    {
            "articleType": "Regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper!",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the regular article
    auto articleRegular = std::make_shared<ArticleRegular>(jsonArticleRegular);

    // Check if it was created successfully
    EXPECT_TRUE(articleRegular != nullptr);

    // Check the article's title
    EXPECT_STREQ(articleRegular->articleName().c_str(), "Visualizing Big Data");

    // Verify the article information
    testing::internal::CaptureStdout();
    articleRegular->display();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(),
                 "=== Article ===\nTitle: Visualizing Big Data\nAuthors: Jane Smith, Bruce Wayne\nAttached URL: "
                 "https://bit.ly/example\nAbstract: An amazing paper!\n");

    // The abstract is too short, so is not a valid article
    EXPECT_FALSE(articleRegular->isValid());

    const auto& jsonArticleRegularValid = R"(
    {
            "articleType": "Regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper of: C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Update the fields
    articleRegular->updateFields(std::make_shared<ArticleRegular>(jsonArticleRegularValid));

    // Now is a valid article
    EXPECT_TRUE(articleRegular->isValid());
}

TEST_F(ArticleTest, PosterArticle)
{
    // Define the JSON to build the regular article
    const auto& jsonArticlePoster = R"(
    {
            "articleType": "Poster",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "",
            "additionalFileUrl": "https://bit.ly/example2",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the poster article
    auto articlePoster = std::make_shared<ArticlePoster>(jsonArticlePoster);

    // Check if it was created successfully
    EXPECT_TRUE(articlePoster != nullptr);

    // Check the article's title
    EXPECT_STREQ(articlePoster->articleName().c_str(), "Visualizing Big Data");

    // Verify the article information
    testing::internal::CaptureStdout();
    articlePoster->display();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "=== Poster ===\nTitle: Visualizing Big Data\nAuthors: Jane Smith, Bruce "
                                             "Wayne\nAttached URL: \nSecond Attachment: https://bit.ly/example2\n");

    // The abstract is too short, so is not a valid article
    EXPECT_FALSE(articlePoster->isValid());

    const auto& jsonArticlePosterValid = R"(
    {
            "articleType": "Poster",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "additionalFileUrl": "https://bit.ly/example2",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Update the fields
    articlePoster->updateFields(std::make_shared<ArticlePoster>(jsonArticlePosterValid));

    // Now is a valid article
    EXPECT_TRUE(articlePoster->isValid());
}
