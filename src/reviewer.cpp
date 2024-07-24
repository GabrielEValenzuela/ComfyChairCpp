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
    else if (operation == OperationType::Delete)
    {
        // Remove the review from the list
        m_reviews.erase(std::remove(m_reviews.begin(), m_reviews.end(), review), m_reviews.end());
    }
}

const std::vector<std::shared_ptr<Bid>>& Reviewer::bids()
{
    return m_bids;
}

const std::vector<std::shared_ptr<Review>>& Reviewer::reviews()
{
    return m_reviews;
}
