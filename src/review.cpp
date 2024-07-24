/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 13, 2024.
 *
 * MIT License
 */

#include "review.hpp"

std::string Review::titleArticle()
{
    return m_titleArticle;
}

/**
 * @brief Getter for the text of the review.
 * @return The text of the review.
 */
std::string Review::text()
{
    return m_text;
}

/**
 * @brief Getter for the rating of the review.
 * @return The rating of the review.
 */
Rating Review::rating()
{
    return m_rating;
}

/**
 * @brief Setter for the rating of the review.
 * @param rating The new rating for the review.
 */
void Review::rating(Rating rating)
{
    m_rating = rating;
}