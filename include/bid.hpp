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
 * @enum BidType
 * @brief Represents the type of bid.
 */
enum class BiddingInterest
{
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
     * @param title The title of the article.
     * @param bidType The bid type.
     */
    Bid(const std::string& title, BiddingInterest bidType) : m_titleArticle(title), m_bidType(bidType)
    {
    }

    /**
     * @brief Destructor.
     */
    virtual ~Bid() = default;

    /**
     * @brief Getter for the title of the article.
     * @return The title of the article.
     */
    std::string getTitleArticle() const
    {
        return m_titleArticle;
    }

    /**
     * @brief Getter for the bid type.
     * @return The bid type.
     */
    BiddingInterest getBidType() const
    {
        return m_bidType;
    }

  private:
    std::string m_titleArticle;
    BiddingInterest m_bidType;
};
;

#endif // BID_HPP
