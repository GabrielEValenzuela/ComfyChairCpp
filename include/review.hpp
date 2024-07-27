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
    Excellent,
    VeryGood,
    Good,
    Neutral,
    Bad,
    VeryBad,
    NotRecommended,
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
     * @param titleArticle The title of the article.
     * @param text The text of the review.
     * @param rating The rating of the review.
     */
    Review(const std::string& titleArticle, const std::string& text, Rating rating)
        : m_titleArticle(titleArticle), m_text(text), m_rating(rating)
    {
    }

    /**
     * @brief Destructor.
     */
    virtual ~Review() = default;

    /**
     * @brief Getter for the title of the article.
     * @return The title of the article.
     */
    std::string titleArticle() const;

    /**
     * @brief Getter for the text of the review.
     * @return The text of the review.
     */
    std::string text();

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

  private:
    std::string m_titleArticle;
    std::string m_text;
    Rating m_rating;
};

#endif // REVIEW_HPP
