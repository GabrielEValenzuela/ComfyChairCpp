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
#include "itrackState.hpp"
#include "selectionStrategy.hpp"
#include "user.hpp"
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
     * @brief Adds a bid to each article in the track.
     */
    virtual void handleTrackBidding() = 0;

    /**
     * @brief Adds a review to an article.
     */
    virtual void handleTrackReview() = 0;

    /**
     * @brief Handles the selection of a track.
     * @param articleRatingMap The unordered map of articles and their ratings.
     * @param number The track number to be selected.
     */
    virtual void handleTrackSelection(
        std::unordered_map<std::shared_ptr<Article>, std::shared_ptr<Rating>> articleRatingMap, int number) = 0;

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

    /**
     * @brief Sets the selection strategy for the track.
     * @param strategy A shared pointer to the selection strategy to be set.
     */
    virtual void selectionStrategy(const std::shared_ptr<SelectionStrategy>& strategy) = 0;

    /**
     * @brief Get the selected articles in the track.
     * @return A vector of shared pointers to the selected articles.
     */
    virtual std::vector<std::shared_ptr<Article>> selectedArticles() = 0;

    /**
     * @brief Get the amount of bids on the track
     * @return Number of bids
     */
    virtual size_t amountBids() const = 0;

    /**
     * @brief Prints the current bids of the track.
     */
    virtual void currentBids() const = 0;

    /**
     * @brief Get the amount of reviews on the track
     * @return Number of reviews
     */
    virtual size_t amountReviews() const = 0;

    /**
     * @brief Prints the current reviews of the track.
     */
    virtual void currentReviews() const = 0;

    /**
     * @brief Add a reviewer to the track.
     */
    virtual void addReviewer(const std::shared_ptr<User> reviewer) = 0;
};

#endif // TRACK_HPP
