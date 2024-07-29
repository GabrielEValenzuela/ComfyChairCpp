/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef REVIEW_HPP
#define REVIEW_HPP

#include <string>

/**
 * @enum Rating
 * @brief Enum class that represents the rating of a review.
 */
enum class Rating
{
    Excellent = 3,
    VeryGood = 2,
    Good = 1,
    Neutral = 0,
    Bad = -1,
    VeryBad = -2,
    NotRecommended = -3,
};

/**
 * @class Review
 * @brief Review class that represents a review in the conference.
 */
class Review
{
  public:
    /**
     * @brief Default constructor.
     * @note Avoid its use.
     */
    Review() = default;

    /**
     * @brief Parameterized constructor.
     * @param text The text of the review.
     * @param rating The rating of the review.
     */
    Review(const std::string& text, Rating rating) : m_text(text), m_rating(rating)
    {
    }

    /**
     * @brief Destructor.
     */
    ~Review() = default;

    /**
     * @brief Getter for the text of the review.
     * @return The text of the review.
     */
    std::string reviewText();

    /**
     * @brief Getter for the rating of the review.
     * @return The rating of the review.
     */
    Rating rating();

    /**
     * @brief Setter for the rating of the review.
     * @param rating The new rating for the review.
     */
    void rating(Rating rating);

    /**
     * @brief Display the review.
     */
    void printReview() const;

  private:
    std::string m_text;
    Rating m_rating;
};

#endif // REVIEW_HPP
