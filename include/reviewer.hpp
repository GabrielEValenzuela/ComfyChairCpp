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
 * @brief Reviewer class that represents a reviewer in the conference.
 */
class Reviewer : public User
{
  public:
    /**
     * @brief Default constructor.
     * @note Avoid its use.
     */
    Reviewer() = default;

    /**
     * @brief Constructor.
     * @param userJson Represents the reviewer's information, in a JSON format.
     */
    Reviewer(const nlohmann::json& userJson) : User(userJson){};

    /**
     * @brief Destructor.
     */
    virtual ~Reviewer() = default;

    /**
     * @brief Getter for the bids vector.
     * @return A const reference to the bids vector.
     */
    const std::vector<Bid>& bids();

    /**
     * @brief Getter for the reviews vector.
     * @return A const reference to the reviews vector.
     */
    const std::vector<std::shared_ptr<Review>>& reviews();

    /**
     * @brief Places a bid
     */
    Bid determineInterest(const std::string& title) override;

    /**
     * @brief Performs a review operation on the given review.
     *
     * This method is responsible for performing a review operation on the provided review object.
     * The review operation can be specified using the `operation` parameter.
     *
     * @param review A shared pointer to the review object to be reviewed.
     * @param operation The type of review operation to be performed.
     */
    void review(const std::shared_ptr<Review>& review, OperationType operation);

    /**
     * @brief Bool is reviewer
     * @return True if the user is a reviewer.
     */
    bool isReviewer()
    {
        return true;
    }

  private:
    std::vector<Bid> m_bids;
    std::vector<std::shared_ptr<Review>> m_reviews;
};

#endif // USER_REVIEWER_HPP
