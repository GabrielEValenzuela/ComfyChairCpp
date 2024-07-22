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
     * @param reviewerJson Represents the user's information, in a JSON format.
     */
    explicit Reviewer(const nlohmann::json& reviewerJson);

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
     * @brief Add a bid.
     * @param bid The bid to add.
     */
    void addBid(const std::shared_ptr<Bid>& bid)
    {
        m_bids.push_back(bid);
    }

    /**
     * @brief Add a review.
     * @param review The review to add.
     */
    void addReview(const std::shared_ptr<Review>& review)
    {
        m_reviews.push_back(review);
    }

  private:
    std::vector<std::shared_ptr<Bid>> m_bids;
    std::vector<std::shared_ptr<Review>> m_reviews;
};

#endif // USER_REVIEWER_HPP