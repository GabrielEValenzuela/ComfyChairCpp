/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef BID_HPP
#define BID_HPP

#include <string>

/**
 * @brief Represents the type of bid.
 */
enum class BiddingInterest
{
    None,
    NotInterested,
    Maybe,
    Interested
};

/**
 * @class Bid
 * @brief represents a bid's reviewer.
 */
class Bid
{
  public:
    /**
     * @brief Default constructor.
     * @note Avoid its use.
     */
    Bid() = default;

    /**
     * @brief Parameterized constructor.
     * @param reviewerName The reviewer who made the bid.
     * @param bidType The bid type.
     */
    Bid(std::string& reviewerName, BiddingInterest bidType);

    /**
     * @brief Destructor.
     */
    ~Bid() = default;
    /**
     * @brief Getter for the bid type.
     * @return The bid type.
     */
    BiddingInterest biddingInterest();

    /**
     * @brief Setter for the bidding interest.
     * @param interest The new bidding interest.
     */
    void biddingInterest(BiddingInterest interest);

    /**
     * @brief Display the bid summary.
     */
    void bidSummary() const;

    /**
     * @brief Overload the less than operator.
     */
    bool operator>(const Bid& other) const
    {
        return this->m_bidType > other.m_bidType;
    }

  private:
    std::string m_titleArticle; /**< The title of the article. */
    std::string m_reviewerName; /**< The name of the reviewer. */
    BiddingInterest m_bidType;  /**< The bid type. */
};
;

#endif // BID_HPP
