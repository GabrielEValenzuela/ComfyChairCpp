/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "track_test.hpp"
#include "MockArticle.hpp"
#include "MockTrackState.hpp"
#include "articlePoster.hpp"
#include "articleRegular.hpp"
#include "track.hpp"
#include "trackFactory.hpp"
#include "trackStateBidding.hpp"
#include "trackStateInterface.hpp"
#include "trackStateReception.hpp"
#include "bid.hpp"

void TrackTest::SetUp()
{
}

void TrackTest::TearDown()
{
}

TEST_F(TrackTest, FactoryTest)
{
    const auto& jsonTrackGeneric = R"( { "trackTopic": "Track SW Engineering" } )"_json;

    auto trackRegular = TrackFactory::createTrack(jsonTrackGeneric, TrackType::Regular);
    auto trackWorkshop = TrackFactory::createTrack(jsonTrackGeneric, TrackType::Workshop);
    auto trackPoster = TrackFactory::createTrack(jsonTrackGeneric, TrackType::Poster);

    EXPECT_TRUE(trackRegular != nullptr);
    EXPECT_TRUE(trackWorkshop != nullptr);
    EXPECT_TRUE(trackPoster != nullptr);
}

TEST_F(TrackTest, RegularTrack)
{
    // Crate the JSON input
    const auto& jsonTrackRegular = R"(
    {
            "trackTopic": "Track SW Engineering"
    }
    )"_json;

    // Create the track
    auto trackRegular = TrackFactory::createTrack(jsonTrackRegular, TrackType::Regular);

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
            "articleType": "Regular",
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
            "articleType": "Regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper of: C++",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the regular article and check it's valid
    auto articleRegularNonValid = std::make_shared<ArticleRegular>(jsonArticleRegular);

    EXPECT_FALSE(articleRegularNonValid->isValid());

    // Handle the article
    trackRegular->handleTrackArticle(articleRegularNonValid, OperationType::Create);

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

    // Handle the article
    trackRegular->handleTrackArticle(articlePoster, OperationType::Create);

    // Check amount of articles
    EXPECT_EQ(trackRegular->amountArticles(), 1);

    // No bidding ni review allowed
    testing::internal::CaptureStdout();
    trackRegular->handleTrackBidding(articleRegular, BiddingInterest::Interested, OperationType::Create);
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Bidding is not allowed in reception state\n");

    testing::internal::CaptureStdout();
    trackRegular->handleTrackReview(articleRegular, "Great article", OperationType::Create);
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Not implemented yet\n");
}

TEST_F(TrackTest, WorkshopTrack)
{
    // Crate the JSON input
    const auto& jsonTrackWorkshop = R"(
    {
            "trackTopic": "Track SW Engineering"
    }
    )"_json;

    // Create the track
    auto trackWorkshop = TrackFactory::createTrack(jsonTrackWorkshop, TrackType::Workshop);

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
            "articleType": "Regular",
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
            "articleType": "Regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper of: C++",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the regular article and check it's valid
    auto articleRegularNonValid = std::make_shared<ArticleRegular>(jsonArticleRegular);

    EXPECT_FALSE(articleRegularNonValid->isValid());

    // Handle the article
    trackWorkshop->handleTrackArticle(articleRegularNonValid, OperationType::Create);

    // Define the JSON to build the regular article
    const auto& jsonArticlePosterValid = R"(
    {
            "articleType": "Poster",
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
    EXPECT_EQ(trackWorkshop->amountArticles(), 2);

    // No bidding ni review allowed
    testing::internal::CaptureStdout();
    trackWorkshop->handleTrackBidding(articleRegular, BiddingInterest::Interested, OperationType::Create);
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Bidding is not allowed in reception state\n");

    testing::internal::CaptureStdout();
    trackWorkshop->handleTrackReview(articleRegular, "Great article", OperationType::Create);
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Not implemented yet\n");
}

TEST_F(TrackTest, PosterTrack)
{
    // Crate the JSON input
    const auto& jsonTrackPoster = R"(
    {
            "trackTopic": "Track SW Engineering"
    }
    )"_json;

    // Create the track
    auto trackPoster = TrackFactory::createTrack(jsonTrackPoster, TrackType::Poster);

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
            "articleType": "Regular",
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
            "articleType": "Regular",
            "articleTitle": "Visualizing Big Data",
            "attachedFileUrl": "https://bit.ly/example",
            "abstract": "An amazing paper of: C++",
            "authors": ["Jane Smith", "Bruce Wayne"]
    }
    )"_json;

    // Create smartpointer to the regular article and check it's valid
    auto articleRegularNonValid = std::make_shared<ArticleRegular>(jsonArticleRegular);

    EXPECT_FALSE(articleRegularNonValid->isValid());

    // Handle the article
    trackPoster->handleTrackArticle(articleRegularNonValid, OperationType::Create);

    // Define the JSON to build the regular article
    const auto& jsonArticlePosterValid = R"(
    {
            "articleType": "Poster",
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
    trackPoster->handleTrackBidding(articleRegular, BiddingInterest::Interested, OperationType::Create);
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Bidding is not allowed in reception state\n");

    testing::internal::CaptureStdout();
    trackPoster->handleTrackReview(articleRegular, "Great article", OperationType::Create);
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Not implemented yet\n");
}

TEST_F(TrackTest, TrackOperations)
{
    // Crate the JSON input
    const auto& jsonTrackRegular = R"(
    {
            "trackTopic": "Track SW Engineering"
    }
    )"_json;

    // Create the track
    auto trackRegular = TrackFactory::createTrack(jsonTrackRegular, TrackType::Regular);

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
            "articleType": "Regular",
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
            "articleType": "Regular",
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
            "trackTopic": "Track SW Engineering"
    }
    )"_json;

    // Create the track
    auto trackRegular = TrackFactory::createTrack(jsonTrackRegular, TrackType::Regular);

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
            "articleType": "Regular",
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

    auto biddingState = std::make_shared<BiddingStateTrack>();

    EXPECT_TRUE(biddingState != nullptr);

    // Change state
    trackRegular->establishState(biddingState);

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

    // Create a bidding
    trackRegular->handleTrackBidding(articleRegular, BiddingInterest::Interested, OperationType::Create);

    // Update the bidding
    trackRegular->handleTrackBidding(articleRegular, BiddingInterest::NotInterested, OperationType::Update);

    // Delete the bidding
    trackRegular->handleTrackBidding(articleRegular, BiddingInterest::NotInterested, OperationType::Delete);
}
