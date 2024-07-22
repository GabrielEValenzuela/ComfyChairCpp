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
}

void ReviewerTest::TearDown()
{
}

TEST_F(ReviewerTest, ReviewerCreation)
{

    auto reviewer = std::make_shared<Reviewer>("fullNames", "affiliation", "email", "password");

    EXPECT_TRUE(reviewer != nullptr);
    EXPECT_EQ(reviewer->getFullNames(), "fullNames");
}

TEST_F(ReviewerTest, ReviewerAddBid)
{
    auto reviewer = std::make_shared<Reviewer>("fullNames", "affiliation", "email", "password");

    auto bid = std::make_shared<Bid>("Visualizing Big Data", BiddingInterest::Interested);
    reviewer->bid(bid, OperationType::Create);

    EXPECT_EQ(reviewer->getBids().size(), 1);
    EXPECT_EQ(reviewer->getBids()[0]->getTitleArticle(), "Visualizing Big Data");
}

TEST_F(ReviewerTest, ReviewerRemoveBid)
{
    auto reviewer = std::make_shared<Reviewer>("fullNames", "affiliation", "email", "password");

    auto bid = std::make_shared<Bid>("Visualizing Big Data", BiddingInterest::Interested);
    reviewer->bid(bid, OperationType::Create);

    auto bid2 = std::make_shared<Bid>("Bing Band", BiddingInterest::Maybe);
    reviewer->bid(bid2, OperationType::Create);

    EXPECT_EQ(reviewer->getBids().size(), 2);

    reviewer->bid(bid, OperationType::Delete);

    EXPECT_EQ(reviewer->getBids().size(), 1);
}

TEST_F(ReviewerTest, ReviewerUpdateBid)
{
    auto reviewer = std::make_shared<Reviewer>("fullNames", "affiliation", "email", "password");

    auto bid = std::make_shared<Bid>("Visualizing Big Data", BiddingInterest::Interested);
    reviewer->bid(bid, OperationType::Create);

    EXPECT_EQ(reviewer->getBids()[0]->getBidType(), BiddingInterest::Interested);

    bid->setBiddingInterest(BiddingInterest::NotInterested);
    // reviewer->bid(bid, OperationType::Update);

    EXPECT_EQ(reviewer->getBids()[0]->getBidType(), BiddingInterest::NotInterested);
}

TEST_F(ReviewerTest, ReviewerAddReview)
{
    auto reviewer = std::make_shared<Reviewer>("fullNames", "affiliation", "email", "password");

    auto review = std::make_shared<Review>(
        "Visualizing Big Data",
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore "
        "magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
        "commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat "
        "nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit "
        "anim id est laborum.",
        Rating::Good);
    reviewer->review(review, OperationType::Create);

    EXPECT_EQ(reviewer->getReviews().size(), 1);
    EXPECT_EQ(reviewer->getReviews()[0]->getRating(), Rating::Good);
}

TEST_F(ReviewerTest, ReviewerDeleteReview)
{
    auto reviewer = std::make_shared<Reviewer>("fullNames", "affiliation", "email", "password");

    auto review = std::make_shared<Review>(
        "Visualizing Big Data",
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore "
        "magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
        "commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat "
        "nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit "
        "anim id est laborum.",
        Rating::Good);
    reviewer->review(review, OperationType::Create);

    EXPECT_EQ(reviewer->getReviews().size(), 1);

    reviewer->review(review, OperationType::Delete);

    EXPECT_EQ(reviewer->getReviews().size(), 0);
}

TEST_F(ReviewerTest, ReviewerUpdateReview)
{
    auto reviewer = std::make_shared<Reviewer>("fullNames", "affiliation", "email", "password");

    auto review = std::make_shared<Review>(
        "Visualizing Big Data",
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore "
        "magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea "
        "commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat "
        "nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit "
        "anim id est laborum.",
        Rating::Good);
    reviewer->review(review, OperationType::Create);

    EXPECT_EQ(reviewer->getReviews()[0]->getRating(), Rating::Good);

    review->setRating(Rating::Bad);

    EXPECT_EQ(reviewer->getReviews()[0]->getRating(), Rating::Bad);
}