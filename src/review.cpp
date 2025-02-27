/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 13, 2024.
 *
 * MIT License
 */

#include "review.hpp"
#include <iostream>

Review::Review(const std::string& text, Rating rating) : m_text(text), m_rating(rating)
{
}

std::string Review::reviewText() const
{
    return m_text;
}

Rating Review::rating() const
{
    return m_rating;
}

void Review::rating(Rating rating)
{
    m_rating = rating;
}

void Review::printReview() const
{
    std::cout << m_text << "\tRating: " << static_cast<int>(m_rating) << std::endl;
}
