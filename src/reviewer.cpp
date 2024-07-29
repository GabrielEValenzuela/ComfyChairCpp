/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "reviewer.hpp"

Bid Reviewer::determineInterest()
{
    static std::mt19937 gen(time(nullptr));           // Random number generator
    static std::uniform_int_distribution<> dis(0, 3); // Distribution

    int decision = dis(gen);
    Bid bid;
    if (decision == 0)
    {
        bid = Bid(m_fullNames, BiddingInterest::None); // No bid
    }
    else
    {
        bid = Bid(m_fullNames, static_cast<BiddingInterest>(decision - 1)); // Adjusted for enum indexing
    }
    m_bids.push_back(bid);
    return bid;
}

Review Reviewer::reviewArticle()
{
    static std::mt19937 gen(time(nullptr));           // Random number generator
    static std::uniform_int_distribution<> dis(0, 5); // Distribution
    auto message = "I, " + m_fullNames + ", have reviewed this article and considered that is:";

    int decision = dis(gen);
    auto review = std::make_shared<Review>(message, static_cast<Rating>(decision));
    m_reviews.push_back(review);
    return *review;
}

void Reviewer::review(const std::shared_ptr<Review>& review, OperationType operation)
{
    if (operation == OperationType::Create)
    {
        m_reviews.push_back(review);
    }
    else if (operation == OperationType::Delete)
    {
        // Remove the review from the list
        m_reviews.erase(std::remove(m_reviews.begin(), m_reviews.end(), review), m_reviews.end());
    }
}

const std::vector<Bid>& Reviewer::bids()
{
    return m_bids;
}

const std::vector<std::shared_ptr<Review>>& Reviewer::reviews()
{
    return m_reviews;
}
