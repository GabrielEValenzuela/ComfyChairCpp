/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 13, 2024.
 *
 * MIT License
 */

#include "reviewer_test.hpp"
#include "bid.hpp"
#include "reviewer.hpp"

void ReviewerTest::SetUp()
{
    const auto& jsonUser = R"(
    {
            "fullNames": "Martin Venturino",
            "affiliation": "Tecnicas y herramientas",
            "email": "marven@tyh.com",
            "password": "https://bit.ly/example2"
    }
    )"_json;

    reviewer = std::make_shared<Reviewer>(jsonUser);
}

void ReviewerTest::TearDown()
{
}

TEST_F(ReviewerTest, ReviewerCreation)
{
    EXPECT_TRUE(reviewer != nullptr);
    EXPECT_EQ(reviewer->fullNames(), "Martin Venturino");
}

TEST_F(ReviewerTest, ReviewerAddBid)
{

    auto bid = std::make_shared<Bid>("Visualizing Big Data", BiddingInterest::Interested);
    reviewer->bid(bid, OperationType::Create);

    EXPECT_EQ(reviewer->bids().size(), 1);
    EXPECT_EQ(reviewer->bids()[0]->titleArticle(), "Visualizing Big Data");
}

TEST_F(ReviewerTest, ReviewerRemoveBid)
{

    auto bid = std::make_shared<Bid>("Visualizing Big Data", BiddingInterest::Interested);
    reviewer->bid(bid, OperationType::Create);

    auto bid2 = std::make_shared<Bid>("Bing Band", BiddingInterest::Maybe);
    reviewer->bid(bid2, OperationType::Create);

    EXPECT_EQ(reviewer->bids().size(), 2);

    reviewer->bid(bid, OperationType::Delete);

    EXPECT_EQ(reviewer->bids().size(), 1);
}

TEST_F(ReviewerTest, ReviewerUpdateBid)
{

    auto bid = std::make_shared<Bid>("Visualizing Big Data", BiddingInterest::Interested);
    reviewer->bid(bid, OperationType::Create);

    EXPECT_EQ(reviewer->bids()[0]->bidInterest(), BiddingInterest::Interested);

    bid->biddingInterest(BiddingInterest::NotInterested);
    reviewer->bid(bid, OperationType::Update);

    EXPECT_EQ(reviewer->bids()[0]->bidInterest(), BiddingInterest::NotInterested);
}

TEST_F(ReviewerTest, ReviewerAddReview)
{

    auto review = std::make_shared<Review>(
        "Visualizing Big Data",
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore "
        "magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
        "commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat "
        "nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit "
        "anim id est laborum.",
        Rating::Good);
    reviewer->review(review, OperationType::Create);

    EXPECT_EQ(reviewer->reviews().size(), 1);
    EXPECT_EQ(reviewer->reviews()[0]->rating(), Rating::Good);
}

TEST_F(ReviewerTest, ReviewerDeleteReview)
{

    auto review = std::make_shared<Review>(
        "Visualizing Big Data",
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore "
        "magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
        "commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat "
        "nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit "
        "anim id est laborum.",
        Rating::Good);
    reviewer->review(review, OperationType::Create);

    EXPECT_EQ(reviewer->reviews().size(), 1);

    reviewer->review(review, OperationType::Delete);

    EXPECT_EQ(reviewer->reviews().size(), 0);
}

TEST_F(ReviewerTest, ReviewerUpdateReview)
{

    auto review = std::make_shared<Review>(
        "Visualizing Big Data",
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore "
        "magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
        "commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat "
        "nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit "
        "anim id est laborum.",
        Rating::Good);
    reviewer->review(review, OperationType::Create);

    EXPECT_EQ(reviewer->reviews()[0]->rating(), Rating::Good);

    review->rating(Rating::Bad);

    EXPECT_EQ(reviewer->reviews()[0]->rating(), Rating::Bad);
}

TEST_F(ReviewerTest, ReviewerTitleTextReview)
{

    auto review = std::make_shared<Review>(
        "Visualizing Big Data",
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore "
        "magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
        "commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat "
        "nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit "
        "anim id est laborum.",
        Rating::Good);
    reviewer->review(review, OperationType::Create);

    EXPECT_EQ(reviewer->reviews()[0]->titleArticle(), "Visualizing Big Data");
    EXPECT_EQ(
        reviewer->reviews()[0]->text(),
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore "
        "magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
        "commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat "
        "nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit "
        "anim id est laborum.");
}
