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
 * @brief Enum class representing the rating of a review.
 *
 * This enumeration defines the possible ratings that can be assigned to a review,
 * ranging from "Excellent" to "Not Recommended".
 */
enum class Rating
{
    Excellent = 3,
    VeryGood = 2,
    Good = 1,
    Neutral = 0,
    Bad = -1,
    VeryBad = -2,
    NotRecommended = -3
};

/**
 * @class Review
 * @brief Represents a review in the conference.
 *
 * The Review class encapsulates the details of a review, including the review text
 * and the associated rating. It provides methods to access and modify these attributes.
 */
class Review
{
  public:
    /**
     * @brief Default constructor.
     *
     * Initializes a Review object with default values. Its use is generally discouraged
     * unless specific default initialization is required.
     */
    Review() = default;

    /**
     * @brief Parameterized constructor to initialize a review with text and rating.
     * @param text The text of the review.
     * @param rating The rating assigned to the review.
     *
     * Constructs a Review object with the specified review text and rating.
     */
    Review(const std::string& text, Rating rating);

    /**
     * @brief Default destructor.
     *
     * Cleans up any resources used by the Review object.
     */
    ~Review() = default;

    /**
     * @brief Getter for the text of the review.
     * @return A string representing the text of the review.
     *
     * Retrieves the textual content of the review.
     */
    std::string reviewText() const;

    /**
     * @brief Getter for the rating of the review.
     * @return The rating assigned to the review.
     *
     * Retrieves the rating associated with the review.
     */
    Rating rating() const;

    /**
     * @brief Setter for the rating of the review.
     * @param rating The new rating to be assigned to the review.
     *
     * Updates the rating associated with the review.
     */
    void rating(Rating rating);

    /**
     * @brief Display the review.
     *
     * Outputs the review text and rating to the standard output, providing a
     * comprehensive overview of the review's content.
     */
    void printReview() const;

  private:
    std::string m_text; /**< The textual content of the review. */
    Rating m_rating;    /**< The rating assigned to the review. */
};

#endif // REVIEW_HPP
