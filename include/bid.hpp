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
     * @param title The title of the article.
     * @param bidType The bid type.
     */
    Bid(const std::string& title, std::string& reviewerName, BiddingInterest bidType);

    /**
     * @brief Destructor.
     */
    ~Bid() = default;

    /**
     * @brief Getter for the title of the article.
     * @return The title of the article.
     */
    std::string titleArticle() const;

    /**
     * @brief Getter for the bid type.
     * @return The bid type.
     */
    BiddingInterest bidInterest();

    /**
     * @brief Setter for the bidding interest.
     * @param interest The new bidding interest.
     */
    void biddingInterest(BiddingInterest interest);

    /**
     * @brief Display the bid summary.
     */
    void bidSummary() const;

  private:
    std::string m_titleArticle; /**< The title of the article. */
    std::string m_reviewerName; /**< The name of the reviewer. */
    BiddingInterest m_bidType;  /**< The bid type. */
};
;

#endif // BID_HPP
