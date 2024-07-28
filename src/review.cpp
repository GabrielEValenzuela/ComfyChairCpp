/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 13, 2024.
 *
 * MIT License
 */

#include "review.hpp"
#include <iostream>

std::string Review::reviewText()
{
    return m_text;
}

Rating Review::rating()
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
