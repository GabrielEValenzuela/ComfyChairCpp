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
#include "trackStateBidding.hpp"
#include "trackStateInterface.hpp"
#include "trackStateReception.hpp"

void TrackTest::SetUp()
{
}

void TrackTest::TearDown()
{
}

TEST_F(TrackTest, ConstructorInitializesProperties)
{
    auto state = std::make_shared<MockTrackState>();
    std::vector<std::shared_ptr<User>> users; // Assuming User class with mocks or real instances

    const std::string expectedState{"Initial State"};

    auto track = std::make_unique<Track>("AI Conference", state, users);

    // Trigger behavior that uses the mock object's methods if not used in constructor
    // Assuming `currentState()` method that uses `stateName()`
    EXPECT_EQ(track->trackName(), "AI Conference");
    testing::internal::CaptureStdout();
    // Setting expectations before the object that uses it is created
    EXPECT_CALL(*state, stateName()).WillOnce(testing::ReturnRef(expectedState));
    track->currentState();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Track currently is in 'Initial State' state\n");
}

TEST_F(TrackTest, AddArticle)
{
    // Setup
    auto mockState = std::make_shared<MockTrackState>();
    Track track;
    track.establishState(mockState); // Assuming this method sets the current state

    auto article = std::make_shared<Article>(); // Assuming default constructor exists

    // Expectation: handleArticle should be called with the correct parameters
    EXPECT_CALL(*mockState, handleArticle(testing::_, testing::Eq(article), testing::Eq(OperationType::Create)))
        .Times(1) // handleArticle should be called exactly once
        .WillOnce(testing::Return());

    // Action
    track.addArticle(article);
}

TEST_F(TrackTest, UpdateArticle)
{
    // Setup
    auto mockState = std::make_shared<MockTrackState>();
    Track track;
    track.establishState(mockState); // Assuming this method sets the current state

    auto article = std::make_shared<Article>(); // Assuming default constructor exists

    // Expectation: handleArticle should be called with the correct parameters
    EXPECT_CALL(*mockState, handleArticle(testing::_, testing::Eq(article), testing::Eq(OperationType::Update)))
        .Times(1) // handleArticle should be called exactly once
        .WillOnce(testing::Return());

    // Action
    track.updateArticle(article);
}

TEST_F(TrackTest, UpdateArticlePoster)
{
    // Setup
    auto mockState = std::make_shared<ReceptionStateTrack>();
    Track track;
    track.establishState(mockState); // Assuming this method sets the current state

    auto article = std::make_shared<ArticlePoster>(); // Assuming default constructor exists
    track.addArticle(article);

    // Action
    track.updateArticle(article);

    EXPECT_EQ(track.amountArticles(), 1);
}

TEST_F(TrackTest, UpdateArticleRegular)
{
    // Setup
    auto mockState = std::make_shared<ReceptionStateTrack>();
    Track track;
    track.establishState(mockState); // Assuming this method sets the current state

    auto article = std::make_shared<ArticleRegular>(); // Assuming default constructor exists
    track.addArticle(article);

    // Action
    track.updateArticle(article);

    EXPECT_EQ(track.amountArticles(), 1);
}

TEST_F(TrackTest, UpdateArticleNotFound)
{
    // ToDo Implement when Article class has been fully implemented
}

TEST_F(TrackTest, RemoveArticle)
{
    // Setup
    auto mockState = std::make_shared<MockTrackState>();
    Track track;
    track.establishState(mockState); // Assuming this method sets the current state

    auto article = std::make_shared<Article>(); // Assuming default constructor exists

    // Expectation: handleArticle should be called with the correct parameters
    EXPECT_CALL(*mockState, handleArticle(testing::_, testing::Eq(article), testing::Eq(OperationType::Delete)))
        .Times(1) // handleArticle should be called exactly once
        .WillOnce(testing::Return());

    // Action
    track.removeArticle(article);
}

TEST_F(TrackTest, ChangeStateTrack)
{
    auto state = std::make_shared<MockTrackState>();
    auto newState = std::make_shared<MockTrackState>();
    std::vector<std::shared_ptr<User>> users; // Assuming User class with mocks or real instances

    const std::string expectedState{"Initial State"};
    const std::string expectedNewState{"Final State"};

    auto track = std::make_unique<Track>("AI Conference", state, users);

    // Trigger behavior that uses the mock object's methods if not used in constructor
    // Assuming `currentState()` method that uses `stateName()`
    EXPECT_EQ(track->trackName(), "AI Conference");
    testing::internal::CaptureStdout();
    // Setting expectations before the object that uses it is created
    EXPECT_CALL(*state, stateName()).WillOnce(testing::ReturnRef(expectedState));
    track->currentState();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Track currently is in 'Initial State' state\n");
    outputCurrentState.clear();

    track->establishState(newState);
    testing::internal::CaptureStdout();
    // Setting expectations before the object that uses it is created
    EXPECT_CALL(*newState, stateName()).WillOnce(testing::ReturnRef(expectedNewState));
    track->currentState();
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Track currently is in 'Final State' state\n");
}

TEST_F(TrackTest, ReceptionStateTest)
{
    // Setup
    auto mockState = std::make_shared<ReceptionStateTrack>();
    Track track;
    track.establishState(mockState); // Assuming this method sets the current state

    testing::internal::CaptureStdout();
    track.currentState();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Track currently is in 'Reception' state\n");

    auto article = std::make_shared<Article>(); // Assuming default constructor exists

    // Action
    track.addArticle(article);
    EXPECT_EQ(track.amountArticles(), 1);

    track.updateArticle(article);
    EXPECT_EQ(track.amountArticles(), 1);

    track.removeArticle(article);
    EXPECT_EQ(track.amountArticles(), 0);
}

TEST_F(TrackTest, BiddingStateTest)
{
    // Setup
    auto mockState = std::make_shared<ReceptionStateTrack>();
    Track track;
    track.establishState(mockState); // Assuming this method sets the current state

    testing::internal::CaptureStdout();
    track.currentState();
    auto outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Track currently is in 'Reception' state\n");
    outputCurrentState.clear();

    auto article = std::make_shared<Article>(); // Assuming default constructor exists

    // Action
    track.addArticle(article);
    EXPECT_EQ(track.amountArticles(), 1);

    testing::internal::CaptureStderr();
    track.addBid(article, BiddingInterest::NotInterested);

    outputCurrentState = testing::internal::GetCapturedStderr();

    EXPECT_STREQ(outputCurrentState.c_str(), "Bidding is not allowed in reception state\n");

    testing::internal::CaptureStderr();
    track.updateBid(article, BiddingInterest::Maybe);

    outputCurrentState = testing::internal::GetCapturedStderr();

    EXPECT_STREQ(outputCurrentState.c_str(), "Bidding is not allowed in reception state\n");

    testing::internal::CaptureStderr();
    track.removeBid(article);
    outputCurrentState = testing::internal::GetCapturedStderr();

    EXPECT_STREQ(outputCurrentState.c_str(), "Bidding is not allowed in reception state\n");

    // Move to bidding
    auto bidingMock = std::make_shared<BiddingStateTrack>();
    track.establishState(bidingMock); // Assuming this method sets the current state

    testing::internal::CaptureStdout();
    track.currentState();
    outputCurrentState = testing::internal::GetCapturedStdout();
    EXPECT_STREQ(outputCurrentState.c_str(), "Track currently is in 'Bidding' state\n");

    testing::internal::CaptureStderr();
    track.addArticle(article);
    outputCurrentState = testing::internal::GetCapturedStderr();

    EXPECT_STREQ(outputCurrentState.c_str(), "Cannot handle articles in Bidding state\n");

    testing::internal::CaptureStderr();
    track.updateArticle(article);
    outputCurrentState = testing::internal::GetCapturedStderr();

    EXPECT_STREQ(outputCurrentState.c_str(), "Cannot handle articles in Bidding state\n");

    testing::internal::CaptureStderr();
    track.removeArticle(article);
    outputCurrentState = testing::internal::GetCapturedStderr();

    EXPECT_STREQ(outputCurrentState.c_str(), "Cannot handle articles in Bidding state\n");

    track.addBid(article, BiddingInterest::NotInterested);
    track.updateBid(article, BiddingInterest::Maybe);
    track.removeBid(article);
}
