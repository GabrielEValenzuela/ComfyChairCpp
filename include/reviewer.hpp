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
#include "review.hpp"
#include "trackStateInterface.hpp"
#include "user.hpp"
#include <memory>
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
     * @param fullNames The full name of the reviewer.
     * @param affiliation The affiliation of the reviewer.
     * @param email The email of the reviewer.
     * @param password The password of the reviewer.
     */
    Reviewer(const std::string& fullNames, const std::string& affiliation, const std::string& email,
             const std::string& password)
        : User(fullNames, affiliation, email, password){};

    /**
     * @brief Destructor.
     */
    virtual ~Reviewer() = default;

    /**
     * @brief Getter for the bids vector.
     * @return A const reference to the bids vector.
     */
    const std::vector<std::shared_ptr<Bid>>& getBids() const
    {
        return m_bids;
    }

    /**
     * @brief Getter for the reviews vector.
     * @return A const reference to the reviews vector.
     */
    const std::vector<std::shared_ptr<Review>>& getReviews() const
    {
        return m_reviews;
    }

    /**
     * @brief Places a bid on an item.
     *
     * This method is used to place a bid on an item. The bid is represented by a shared pointer to a `Bid` object.
     * The `operation` parameter specifies the type of operation to be performed on the bid.
     *
     * @param bid A shared pointer to a `Bid` object representing the bid to be placed.
     * @param operation The type of operation to be performed on the bid.
     */
    void bid(const std::shared_ptr<Bid>& bid, OperationType operation);

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

  private:
    std::vector<std::shared_ptr<Bid>> m_bids;
    std::vector<std::shared_ptr<Review>> m_reviews;
};

#endif // USER_REVIEWER_HPP
