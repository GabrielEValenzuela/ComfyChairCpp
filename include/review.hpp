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
    Review(const std::string& titleArticle, const std::string& text, int rating)
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
    std::string getTitleArticle() const
    {
        return m_titleArticle;
    }

    /**
     * @brief Getter for the text of the review.
     * @return The text of the review.
     */
    std::string getText() const
    {
        return m_text;
    }

    /**
     * @brief Getter for the rating of the review.
     * @return The rating of the review.
     */
    int getRating() const
    {
        return m_rating;
    }

  private:
    std::string m_titleArticle;
    std::string m_text;
    int m_rating;
};

#endif // REVIEW_HPP