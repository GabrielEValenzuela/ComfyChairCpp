/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "bid.hpp"

std::string Bid::titleArticle()
{
    return m_titleArticle;
}

/**
 * @brief Getter for the bid type.
 * @return The bid type.
 */
BiddingInterest Bid::bidInterest()
{
    return m_bidType;
}

/**
 * @brief Setter for the bidding interest.
 * @param interest The new bidding interest.
 */
void Bid::biddingInterest(BiddingInterest interest)
{
    m_bidType = interest;
}