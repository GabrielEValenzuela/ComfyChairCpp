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
 * @enum BiddingInterest
 * @brief Represents the type of bid.
 *
 * This enumeration defines the levels of interest a reviewer can express
 * when bidding on an article. The levels range from no interest to high interest.
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
 * @brief Represents a bid made by a reviewer on an article.
 *
 * The Bid class encapsulates the details of a bid made by a reviewer,
 * including the reviewer's name and the level of interest in the article.
 */
class Bid
{
  public:
    /**
     * @brief Default constructor.
     *
     * Initializes a Bid object with default values. Its use is generally
     * discouraged unless specific default initialization is required.
     */
    Bid() = default;

    /**
     * @brief Parameterized constructor to initialize a bid with reviewer name and bid type.
     * @param reviewerName The name of the reviewer making the bid.
     * @param bidType The type of bid indicating the reviewer's interest level.
     *
     * Constructs a Bid object with the specified reviewer name and bidding interest.
     */
    Bid(const std::string& reviewerName, BiddingInterest bidType);

    /**
     * @brief Default destructor.
     *
     * Cleans up any resources used by the Bid object.
     */
    ~Bid() = default;

    /**
     * @brief Getter for the bid type.
     * @return The bid type indicating the reviewer's level of interest.
     *
     * Retrieves the current bidding interest level of the reviewer.
     */
    BiddingInterest biddingInterest() const;

    /**
     * @brief Setter for the bidding interest.
     * @param interest The new bidding interest level.
     *
     * Updates the bidding interest level for the reviewer.
     */
    void biddingInterest(BiddingInterest interest);

    /**
     * @brief Display a summary of the bid.
     *
     * Outputs a summary of the bid to the standard output, including the
     * reviewer's name and their level of interest in the article.
     */
    void bidSummary() const;

    /**
     * @brief Overload the greater than operator.
     * @param other Another Bid object to compare with.
     * @return True if the current bid's interest level is greater than the other bid's interest level.
     *
     * Provides a comparison operator to facilitate sorting or comparing
     * Bid objects based on the bidding interest level.
     */
    bool operator>(const Bid& other) const
    {
        return this->m_bidType > other.m_bidType;
    }

  private:
    std::string m_titleArticle; /**< The title of the article being bid on. */
    std::string m_reviewerName; /**< The name of the reviewer making the bid. */
    BiddingInterest m_bidType;  /**< The type of bid indicating the reviewer's level of interest. */
};

#endif // BID_HPP
