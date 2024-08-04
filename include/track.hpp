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
 * @class Track
 * @brief Represents a track in the conference.
 *
 * The Track class defines the interface for managing articles, bids, and reviews within a conference track.
 * It enforces the implementation of methods for handling various track-related operations.
 */
class Track
{
  public:
    /**
     * @brief Default constructor.
     *
     * Initializes a Track object with default values.
     */
    Track() = default;

    /**
     * @brief Virtual destructor.
     *
     * Ensures proper cleanup of derived classes.
     */
    virtual ~Track() = default;

    /**
     * @brief Handle an article within the track.
     * @param article The article to handle.
     * @param operation The operation to perform (Create, Update, Delete).
     *
     * This pure virtual method must be implemented by derived classes to manage articles within the track.
     */
    virtual void handleTrackArticle(const std::shared_ptr<Article>& article, OperationType operation) = 0;

    /**
     * @brief Handle the bidding process for articles within the track.
     *
     * This pure virtual method must be implemented by derived classes to manage the bidding process for articles.
     */
    virtual void handleTrackBidding() = 0;

    /**
     * @brief Handle the review process for articles within the track.
     *
     * This pure virtual method must be implemented by derived classes to manage the review process for articles.
     */
    virtual void handleTrackReview() = 0;

    /**
     * @brief Handle the selection of articles within the track.
     * @param threshold The number of articles to select.
     *
     * This pure virtual method must be implemented by derived classes to manage the selection of articles based on a
     * threshold.
     */
    virtual void handleTrackSelection(int threshold) = 0;

    /**
     * @brief Get the name of the track.
     * @return A constant reference to a string representing the track's name.
     *
     * This pure virtual method must be implemented by derived classes to provide the name of the track.
     */
    virtual const std::string& trackName() const = 0;

    /**
     * @brief Set the state of the track.
     * @param state A shared pointer to the new state of the track.
     *
     * This pure virtual method must be implemented by derived classes to establish the track's current state.
     */
    virtual void establishState(const std::shared_ptr<ITrackState>& state) = 0;

    /**
     * @brief Print the current state of the track.
     *
     * This pure virtual method must be implemented by derived classes to print the track's current state.
     */
    virtual void currentState() const = 0;

    /**
     * @brief Get the number of articles in the track.
     * @return The number of articles in the track.
     *
     * This pure virtual method must be implemented by derived classes to return the number of articles in the track.
     */
    virtual int amountArticles() const = 0;

    /**
     * @brief Set the selection strategy for the track.
     * @param strategy A shared pointer to the selection strategy to be set.
     *
     * This pure virtual method must be implemented by derived classes to set the selection strategy for the track.
     */
    virtual void selectionStrategy(const std::shared_ptr<SelectionStrategy>& strategy) = 0;

    /**
     * @brief Get the selected articles in the track.
     * @return A vector of shared pointers to the selected articles.
     *
     * This pure virtual method must be implemented by derived classes to return the selected articles in the track.
     */
    virtual std::vector<std::shared_ptr<Article>> selectedArticles() = 0;

    /**
     * @brief Get the number of bids in the track.
     * @return The number of bids in the track.
     *
     * This pure virtual method must be implemented by derived classes to return the number of bids in the track.
     */
    virtual size_t amountBids() const = 0;

    /**
     * @brief Print the current bids in the track.
     *
     * This pure virtual method must be implemented by derived classes to print the current bids in the track.
     */
    virtual void currentBids() const = 0;

    /**
     * @brief Get the number of reviews in the track.
     * @return The number of reviews in the track.
     *
     * This pure virtual method must be implemented by derived classes to return the number of reviews in the track.
     */
    virtual size_t amountReviews() const = 0;

    /**
     * @brief Print the current reviews in the track.
     *
     * This pure virtual method must be implemented by derived classes to print the current reviews in the track.
     */
    virtual void currentReviews() const = 0;

    /**
     * @brief Add a reviewer to the track.
     * @param reviewer A shared pointer to the reviewer to be added.
     *
     * This pure virtual method must be implemented by derived classes to add a reviewer to the track.
     */
    virtual void addReviewer(const std::shared_ptr<User>& reviewer) = 0;
};

#endif // TRACK_HPP
