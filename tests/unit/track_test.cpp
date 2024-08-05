/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "track_test.hpp"
#include "articlePoster.hpp"
#include "articleRegular.hpp"
#include "bid.hpp"
#include "itrackState.hpp"
#include "selectionStrategyFixedCut.hpp"
#include "track.hpp"
#include "trackFactory.hpp"
#include "trackStateBidding.hpp"
#include "trackStateReception.hpp"
#include "trackStateReview.hpp"
#include "trackStateSelection.hpp"

void TrackTest::SetUp()
{
}

void TrackTest::TearDown()
{
}

TEST_F(TrackTest, FactoryTest)
{
    const auto& jsonTrackGenericR = R"( { "trackType": "regular", "trackTopic": "Track SW Engineering" } )"_json;
    const auto& jsonTrackGenericP = R"( { "trackType": "poster", "trackTopic": "Track SW Engineering" } )"_json;
    const auto& jsonTrackGenericW = R"( { "trackType": "workshop", "trackTopic": "Track SW Engineering" } )"_json;
    const auto& jsonTrackGeneric = R"( { "trackTopic": "Track SW Engineering" } )"_json;

    auto trackRegular = TrackFactory::createTrack(jsonTrackGenericR);
    auto trackWorkshop = TrackFactory::createTrack(jsonTrackGenericP);
    auto trackPoster = TrackFactory::createTrack(jsonTrackGenericW);

    EXPECT_TRUE(trackRegular != nullptr);
    EXPECT_TRUE(trackWorkshop != nullptr);
    EXPECT_TRUE(trackPoster != nullptr);
    EXPECT_THROW(TrackFactory::createTrack(jsonTrackGeneric), std::invalid_argument);
}

TEST_F(TrackTest, RegularTrack)
{
    // Crate the JSON input
    const auto& jsonTrackRegular = R"(
    {
        "trackType": "regular",
        "trackTopic": "Track SW Engineering"
    }
    )"_json;

    // Create the track
    auto trackRegular = TrackFactory::createTrack(jsonTrackRegular);

    // Validate topic name
    EXPECT_STREQ(trackRegular->trackName().c_str(), "Track SW Engineering");

    // Verify the track information
    testing::internal::CaptureStdout();
    trackRegular->currentState();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Track 'Track SW Engineering' currently is in 'Reception' state\n");

    // Define the JSON to build the regular article
    const auto& jsonArticleRegularValid = R"(
    {
            "articleType": "regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper of: C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the regular article and check it's valid
    auto articleRegular = std::make_shared<ArticleRegular>(jsonArticleRegularValid);

    EXPECT_TRUE(articleRegular->isValid());

    // Handle the article
    trackRegular->handleTrackArticle(articleRegular, OperationType::Create);

    // Define the JSON to build the regular article
    const auto& jsonArticleRegular = R"(
    {
            "articleType": "regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper of: C++",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the regular article and check it's valid
    auto articleRegularNonValid = std::make_shared<ArticleRegular>(jsonArticleRegular);

    // EXPECT_FALSE(articleRegularNonValid->isValid()); //Todo Uncomment this line when the minimum abstract size is 300
    EXPECT_TRUE(articleRegularNonValid->isValid());

    // Handle the article
    trackRegular->handleTrackArticle(articleRegularNonValid, OperationType::Create);

    // Define the JSON to build the regular article
    const auto& jsonArticlePoster = R"(
    {
            "articleType": "poster",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "",
            "additionalFileUrl": "https://bit.ly/example2",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the poster article
    auto articlePoster = std::make_shared<ArticlePoster>(jsonArticlePoster);

    // Handle the article
    trackRegular->handleTrackArticle(articlePoster, OperationType::Create);

    // Check amount of articles
    // EXPECT_EQ(trackRegular->amountArticles(), 1); //Todo Uncomment this line when the minimum abstract size is 300
    EXPECT_EQ(trackRegular->amountArticles(), 2);

    // No bidding, review  or selection allowed
    testing::internal::CaptureStdout();
    trackRegular->handleTrackBidding();
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Bidding is not allowed in reception state\n");

    testing::internal::CaptureStdout();
    trackRegular->handleTrackReview();
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Review is not allowed in reception state\n");
}

TEST_F(TrackTest, WorkshopTrack)
{
    // Crate the JSON input
    const auto& jsonTrackWorkshop = R"(
    {
        "trackType": "workshop",
        "trackTopic": "Track SW Engineering"
    }
    )"_json;

    // Create the track
    auto trackWorkshop = TrackFactory::createTrack(jsonTrackWorkshop);

    // Validate topic name
    EXPECT_STREQ(trackWorkshop->trackName().c_str(), "Track SW Engineering");

    // Verify the track information
    testing::internal::CaptureStdout();
    trackWorkshop->currentState();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Workshop 'Track SW Engineering' currently is in 'Reception' state\n");

    // Define the JSON to build the regular article
    const auto& jsonArticleRegularValid = R"(
    {
            "articleType": "regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper of: C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the regular article and check it's valid
    auto articleRegular = std::make_shared<ArticleRegular>(jsonArticleRegularValid);

    EXPECT_TRUE(articleRegular->isValid());

    // Handle the article
    trackWorkshop->handleTrackArticle(articleRegular, OperationType::Create);

    // Define the JSON to build the regular article
    const auto& jsonArticleRegular = R"(
    {
            "articleType": "regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper of: C++",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the regular article and check it's valid
    auto articleRegularNonValid = std::make_shared<ArticleRegular>(jsonArticleRegular);

    // EXPECT_FALSE(articleRegularNonValid->isValid()); //Todo Uncomment this line when the minimum abstract size is 300
    EXPECT_TRUE(articleRegularNonValid->isValid());

    // Handle the article
    trackWorkshop->handleTrackArticle(articleRegularNonValid, OperationType::Create);

    // Define the JSON to build the regular article
    const auto& jsonArticlePosterValid = R"(
    {
            "articleType": "poster",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "additionalFileUrl": "https://bit.ly/example2",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the poster article
    auto articlePoster = std::make_shared<ArticlePoster>(jsonArticlePosterValid);

    // Handle the article
    trackWorkshop->handleTrackArticle(articlePoster, OperationType::Create);

    // Check amount of articles
    // EXPECT_EQ(trackWorkshop->amountArticles(), 2); //Todo Uncomment this line when the minimum abstract size is 300
    EXPECT_EQ(trackWorkshop->amountArticles(), 3);

    // No bidding ni review allowed
    testing::internal::CaptureStdout();
    trackWorkshop->handleTrackBidding();
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Bidding is not allowed in reception state\n");

    testing::internal::CaptureStdout();
    trackWorkshop->handleTrackReview();
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Review is not allowed in reception state\n");
}

TEST_F(TrackTest, PosterTrack)
{
    // Crate the JSON input
    const auto& jsonTrackPoster = R"(
    {
        "trackType": "poster",
        "trackTopic": "Track SW Engineering"
    }
    )"_json;

    // Create the track
    auto trackPoster = TrackFactory::createTrack(jsonTrackPoster);

    // Validate topic name
    EXPECT_STREQ(trackPoster->trackName().c_str(), "Track SW Engineering");

    // Verify the track information
    testing::internal::CaptureStdout();
    trackPoster->currentState();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Poster 'Track SW Engineering' currently is in 'Reception' state\n");

    // Define the JSON to build the regular article
    const auto& jsonArticleRegularValid = R"(
    {
            "articleType": "regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper of: C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the regular article and check it's valid
    auto articleRegular = std::make_shared<ArticleRegular>(jsonArticleRegularValid);

    EXPECT_TRUE(articleRegular->isValid());

    // Handle the article
    trackPoster->handleTrackArticle(articleRegular, OperationType::Create);

    // Define the JSON to build the regular article
    const auto& jsonArticleRegular = R"(
    {
            "articleType": "regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper of: C++",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the regular article and check it's valid
    auto articleRegularNonValid = std::make_shared<ArticleRegular>(jsonArticleRegular);

    // EXPECT_FALSE(articleRegularNonValid->isValid()); //Todo Uncomment this line when the minimum abstract size is 300
    EXPECT_TRUE(articleRegularNonValid->isValid());

    // Handle the article
    trackPoster->handleTrackArticle(articleRegularNonValid, OperationType::Create);

    // Define the JSON to build the regular article
    const auto& jsonArticlePosterValid = R"(
    {
            "articleType": "poster",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "additionalFileUrl": "https://bit.ly/example2",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the poster article
    auto articlePoster = std::make_shared<ArticlePoster>(jsonArticlePosterValid);

    // Handle the article
    trackPoster->handleTrackArticle(articlePoster, OperationType::Create);

    // Check amount of articles
    EXPECT_EQ(trackPoster->amountArticles(), 1);

    // No bidding ni review allowed
    testing::internal::CaptureStdout();
    trackPoster->handleTrackBidding();
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Bidding is not allowed in reception state\n");

    testing::internal::CaptureStdout();
    trackPoster->handleTrackReview();
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Review is not allowed in reception state\n");
}

TEST_F(TrackTest, TrackOperations)
{
    // Crate the JSON input
    const auto& jsonTrackRegular = R"(
    {
        "trackType": "regular",
        "trackTopic": "Track SW Engineering"
    }
    )"_json;

    // Create the track
    auto trackRegular = TrackFactory::createTrack(jsonTrackRegular);

    // Validate topic name
    EXPECT_STREQ(trackRegular->trackName().c_str(), "Track SW Engineering");

    // Verify the track information
    testing::internal::CaptureStdout();
    trackRegular->currentState();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Track 'Track SW Engineering' currently is in 'Reception' state\n");

    // Define the JSON to build the regular article
    const auto& jsonArticleRegularValid = R"(
    {
            "articleType": "regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper of: C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the regular article and check it's valid
    auto articleRegular = std::make_shared<ArticleRegular>(jsonArticleRegularValid);

    EXPECT_TRUE(articleRegular->isValid());

    // Handle the article
    trackRegular->handleTrackArticle(articleRegular, OperationType::Create);

    // Define the JSON to build the regular article v2
    const auto& jsonArticleRegularValidV2 = R"(
    {
            "articleType": "regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper of: C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Check amount of articles
    EXPECT_EQ(trackRegular->amountArticles(), 1);

    auto articleRegularV2 = std::make_shared<ArticleRegular>(jsonArticleRegularValid);

    // Handle the article
    trackRegular->handleTrackArticle(articleRegularV2, OperationType::Update);

    // Check amount of articles
    EXPECT_EQ(trackRegular->amountArticles(), 1);

    // Handle the article
    trackRegular->handleTrackArticle(articleRegularV2, OperationType::Delete);

    // Check amount of articles
    EXPECT_EQ(trackRegular->amountArticles(), 0);
}

TEST_F(TrackTest, TrackBidding)
{
    // Crate the JSON input
    const auto& jsonTrackRegular = R"(
    {
        "trackType": "regular",
        "trackTopic": "Track SW Engineering"
    }
    )"_json;

    // Create the track
    auto trackRegular = TrackFactory::createTrack(jsonTrackRegular);

    // Validate topic name
    EXPECT_STREQ(trackRegular->trackName().c_str(), "Track SW Engineering");

    // Verify the track information
    testing::internal::CaptureStdout();
    trackRegular->currentState();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Track 'Track SW Engineering' currently is in 'Reception' state\n");

    // Define the JSON to build the regular article
    const auto& jsonArticleRegularValid = R"(
    {
            "articleType": "regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper of: C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the regular article and check it's valid
    auto articleRegular = std::make_shared<ArticleRegular>(jsonArticleRegularValid);

    EXPECT_TRUE(articleRegular->isValid());

    // Handle the article
    trackRegular->handleTrackArticle(articleRegular, OperationType::Create);

    auto selectionState = std::make_shared<BiddingStateTrack>();

    EXPECT_TRUE(selectionState != nullptr);

    // Change state
    trackRegular->establishState(selectionState);

    // Verify the track information
    testing::internal::CaptureStdout();
    trackRegular->currentState();
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Track 'Track SW Engineering' currently is in 'Bidding' state\n");

    // No more handle articles
    testing::internal::CaptureStdout();
    trackRegular->handleTrackArticle(articleRegular, OperationType::Create);
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Cannot handle articles in Bidding state\n");

    testing::internal::CaptureStdout();
    auto strategyCut = std::make_shared<SelectionStrategyFixedCut>();
    trackRegular->selectionStrategy(strategyCut);
    trackRegular->handleTrackSelection(100); // Take all
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Cannot handle selection in Bidding state\n");

    testing::internal::CaptureStdout();
    trackRegular->handleTrackReview();
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Review is not allowed in bidding state\n");
}

TEST_F(TrackTest, TrackSelection)
{
    // Crate the JSON input
    const auto& jsonTrackRegular = R"(
    {
        "trackType": "regular",
        "trackTopic": "Track SW Engineering"
    }
    )"_json;

    // Create the track
    auto trackRegular = TrackFactory::createTrack(jsonTrackRegular);

    // Validate topic name
    EXPECT_STREQ(trackRegular->trackName().c_str(), "Track SW Engineering");

    // Verify the track information
    testing::internal::CaptureStdout();
    trackRegular->currentState();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Track 'Track SW Engineering' currently is in 'Reception' state\n");

    // Define the JSON to build the regular article
    const auto& jsonArticleRegularValid = R"(
    {
            "articleType": "regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper of: C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the regular article and check it's valid
    auto articleRegular = std::make_shared<ArticleRegular>(jsonArticleRegularValid);

    EXPECT_TRUE(articleRegular->isValid());

    // Handle the article
    trackRegular->handleTrackArticle(articleRegular, OperationType::Create);

    auto selectionState = std::make_shared<SelectionStateTrack>();

    EXPECT_TRUE(selectionState != nullptr);

    // Change state
    trackRegular->establishState(selectionState);

    // Verify the track information
    testing::internal::CaptureStdout();
    trackRegular->currentState();
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Track 'Track SW Engineering' currently is in 'Selection' state\n");

    // No more handle articles
    testing::internal::CaptureStdout();
    trackRegular->handleTrackArticle(articleRegular, OperationType::Create);
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Cannot handle articles in selection state\n");

    testing::internal::CaptureStdout();
    trackRegular->handleTrackBidding();
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Bidding is not allowed in selection state\n");

    testing::internal::CaptureStdout();
    trackRegular->handleTrackReview();
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Review is not allowed in selection state\n");
}

TEST_F(TrackTest, TrackReview)
{
    // Crate the JSON input
    const auto& jsonTrackRegular = R"(
    {
        "trackType": "regular",
        "trackTopic": "Track SW Engineering"
    }
    )"_json;

    // Create the track
    auto trackRegular = TrackFactory::createTrack(jsonTrackRegular);

    // Validate topic name
    EXPECT_STREQ(trackRegular->trackName().c_str(), "Track SW Engineering");

    // Verify the track information
    testing::internal::CaptureStdout();
    trackRegular->currentState();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Track 'Track SW Engineering' currently is in 'Reception' state\n");

    // Define the JSON to build the regular article
    const auto& jsonArticleRegularValid = R"(
    {
            "articleType": "regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper of: C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++C++",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the regular article and check it's valid
    auto articleRegular = std::make_shared<ArticleRegular>(jsonArticleRegularValid);

    EXPECT_TRUE(articleRegular->isValid());

    // Handle the article
    trackRegular->handleTrackArticle(articleRegular, OperationType::Create);

    auto reviewState = std::make_shared<ReviewStateTrack>();

    EXPECT_TRUE(reviewState != nullptr);

    // Change state
    trackRegular->establishState(reviewState);

    // Verify the track information
    testing::internal::CaptureStdout();
    trackRegular->currentState();
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Track 'Track SW Engineering' currently is in 'Review' state\n");

    // No more handle articles
    testing::internal::CaptureStdout();
    trackRegular->handleTrackArticle(articleRegular, OperationType::Create);
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Cannot handle articles in review state\n");

    testing::internal::CaptureStdout();
    trackRegular->handleTrackBidding();
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Bidding is not allowed in review state\n");

    testing::internal::CaptureStdout();
    auto strategyCut = std::make_shared<SelectionStrategyFixedCut>();
    trackRegular->selectionStrategy(strategyCut);
    trackRegular->handleTrackSelection(100); // Take all
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Cannot handle selection in review state\n");
}
