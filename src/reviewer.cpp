/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "reviewer.hpp"

void Reviewer::bid(const std::shared_ptr<Bid>& bid, OperationType operation)
{
    if (operation == OperationType::Create)
    {
        m_bids.push_back(bid);
    }
    else if (operation == OperationType::Update)
    {
        // Update the bid in the list
        // Find the index of the bid in the list
        auto it = std::find(m_bids.begin(), m_bids.end(), bid);
        if (it != m_bids.end())
        {
            // Replace the bid with the new bid
            *it = bid;
        }
    }
    else if (operation == OperationType::Delete)
    {
        // Remove the bid from the list
        m_bids.erase(std::remove(m_bids.begin(), m_bids.end(), bid), m_bids.end());
    }
}

void Reviewer::review(const std::shared_ptr<Review>& review, OperationType operation)
{
    if (operation == OperationType::Create)
    {
        m_reviews.push_back(review);
    }
    else if (operation == OperationType::Update)
    {
        // Update the review in the list
        // Find the index of the review in the list
        auto it = std::find(m_reviews.begin(), m_reviews.end(), review);
        if (it != m_reviews.end())
        {
            // Replace the review with the new review
            *it = review;
        }
    }
    else if (operation == OperationType::Delete)
    {
        // Remove the review from the list
        m_reviews.erase(std::remove(m_reviews.begin(), m_reviews.end(), review), m_reviews.end());
    }
}
