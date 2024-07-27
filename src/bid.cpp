/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "bid.hpp"
#include <iostream>

Bid::Bid(const std::string& title, std::string& reviewerName, BiddingInterest bidType)
    : m_titleArticle(title), m_bidType(bidType), m_reviewerName(reviewerName)
{
}

std::string Bid::titleArticle() const
{
    return m_titleArticle;
}

// LCOV_EXCL_START
BiddingInterest Bid::bidInterest()
{
    return m_bidType;
}
// LCOV_EXCL_STOP

// LCOV_EXCL_START
void Bid::biddingInterest(BiddingInterest interest)
{
    m_bidType = interest;
}
// LCOV_EXCL_STOP

void Bid::bidSummary() const
{
    std::cout << "Reviewer: " << m_reviewerName << std::endl;
    std::cout << "Interest: " << static_cast<int>(m_bidType) << std::endl;
}
