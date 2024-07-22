/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef TRACK_HPP
#define TRACK_HPP

#include "articleInterface.hpp"
#include "trackStateInterface.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

/**
 * @brief Track class that represents a track in the conference.
 * This a interface class that defines the methods that a track must implement.
 */
class Track
{
  public:
    /**
     * @brief Track constructor.
     */
    Track() = default;

    /**
     * @brief Destructor.
     */
    virtual ~Track() = default;

    /**
     * @brief Adds an article to the track.
     * @param article The article to add.
     * @param operation Operation to perform.
     */
    virtual void handleTrackArticle(const std::shared_ptr<Article>& article, OperationType operation) = 0;

    /**
     * @brief Adds a bid to an article.
     * @param article The article to bid.
     * @param interest The interest to set.
     * @param operation Operation to perform.
     */
    virtual void handleTrackBidding(const std::shared_ptr<Article>& article, BiddingInterest interest,
                                    OperationType operation) = 0;

    /**
     * @brief Adds a review to an article.
     * @param article The article to review.
     * @param review The review to set. //Todo Define the parameter once review class is implemented.
     * @param operation Operation to perform.
     */
    virtual void handleTrackReview(const std::shared_ptr<Article>& article, const std::string& review,
                                   OperationType operation) = 0;

    /**
     * @brief Get the track's name.
     * @return The track's name.
     */
    virtual const std::string& trackName() const = 0;

    /**
     * @brief Set the track's state.
     * @param state The track's state.
     */
    virtual void establishState(const std::shared_ptr<ITrackState>& state) = 0;

    /**
     * @brief Prints the current state of the track.
     */
    virtual void currentState() const = 0;

    /**
     * @brief Get the amount of articles on the track
     * @return Number of articles
     */
    virtual int amountArticles() const = 0;
};

#endif // TRACK_HPP
