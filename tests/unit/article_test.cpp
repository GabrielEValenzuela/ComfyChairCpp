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
    const auto& jsonArticle = R"(
    {
            "articleType": "Article",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "additionalFileUrl": "https://bit.ly/example2",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    auto article = Article(jsonArticle);
    EXPECT_STREQ("Visualizing Big Data", article.articleName().c_str());

    testing::internal::CaptureStdout();
    article.display();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(),
                 "Title: Visualizing Big Data\nAuthors: Jane Smith, Bruce Wayne\nURL: https://bit.ly/example\n");
}

TEST_F(ArticleTest, PosterCreation)
{
    const auto& jsonArticle = R"(
    {
            "articleType": "Poster",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "additionalFileUrl": "https://bit.ly/example2",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    auto article = ArticlePoster(jsonArticle);
    EXPECT_STREQ("Visualizing Big Data", article.articleName().c_str());

    testing::internal::CaptureStdout();
    article.display();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Title: Visualizing Big Data\nAuthors: Jane Smith, Bruce Wayne\nURL: "
                                             "https://bit.ly/example\nSecond Attachment: https://bit.ly/example2\n");
}

TEST_F(ArticleTest, RegularArticleCreation)
{
    const auto& jsonArticle = R"(
    {
            "articleType": "Regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper!",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    auto article = ArticleRegular(jsonArticle);
    EXPECT_STREQ("Visualizing Big Data", article.articleName().c_str());

    testing::internal::CaptureStdout();
    article.display();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Title: Visualizing Big Data\nAuthors: Jane Smith, Bruce Wayne\nURL: "
                                             "https://bit.ly/example\nSecond Attachment: https://bit.ly/example2\n");
}
