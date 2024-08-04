/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef USER_REVIEWER_HPP
#define USER_REVIEWER_HPP

#include "bid.hpp"
#include "itrackState.hpp"
#include "review.hpp"
#include "user.hpp"
#include <memory>
#include <random>
#include <vector>

/**
 * @class Reviewer
 * @brief Represents a reviewer in the conference.
 *
 * The Reviewer class extends the User class to provide specific functionalities
 * related to reviewers, such as managing bids and reviews. It encapsulates the
 * details and behaviors associated with a reviewer in the conference system.
 */
class Reviewer : public User
{
  public:
    /**
     * @brief Default constructor.
     *
     * Initializes a Reviewer object with default values. Its use is generally
     * discouraged unless specific default initialization is required.
     */
    Reviewer() = default;

    /**
     * @brief Parameterized constructor to initialize a reviewer with JSON data.
     * @param userJson A JSON object containing the reviewer's information.
     *
     * Constructs a Reviewer object by parsing the provided JSON data, extracting
     * relevant fields such as user details.
     */
    explicit Reviewer(const nlohmann::json& userJson) : User(userJson)
    {
    }

    /**
     * @brief Default destructor.
     *
     * Cleans up any resources used by the Reviewer object.
     */
    ~Reviewer() = default;

    /**
     * @brief Getter for the bids vector.
     * @return A constant reference to the vector of bids.
     *
     * Retrieves the list of bids placed by the reviewer.
     */
    const std::vector<Bid>& bids() const;

    /**
     * @brief Getter for the reviews vector.
     * @return A constant reference to the vector of reviews.
     *
     * Retrieves the list of reviews submitted by the reviewer.
     */
    const std::vector<std::shared_ptr<Review>>& reviews() const;

    /**
     * @brief Checks if the user is a reviewer.
     * @return True if the user is a reviewer, false otherwise.
     *
     * Indicates that this user is a reviewer.
     */
    bool isReviewer() const
    {
        return true;
    }

    /**
     * @brief Performs a review operation on the given review.
     * @param review A shared pointer to the review object to be operated on.
     * @param operation The type of review operation to be performed (Create, Update, Delete).
     *
     * This method handles review operations such as creating, updating, or deleting a review.
     */
    void review(const std::shared_ptr<Review>& review, OperationType operation);

    /**
     * @brief Determines and places a bid on an article.
     * @return A Bid object representing the reviewer's interest in an article.
     *
     * This method determines the reviewer's interest in an article and places a bid accordingly.
     */
    Bid determineInterest() override;

    /**
     * @brief Reviews an article.
     * @return A Review object containing the reviewer's evaluation of an article.
     *
     * This method allows the reviewer to evaluate and review an article.
     */
    Review reviewArticle() override;

  private:
    std::vector<Bid> m_bids;                        /**< Vector of bids placed by the reviewer. */
    std::vector<std::shared_ptr<Review>> m_reviews; /**< Vector of reviews submitted by the reviewer. */
};

#endif // USER_REVIEWER_HPP
