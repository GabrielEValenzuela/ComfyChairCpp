/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef TRACK_STATE_INTERFACE_HPP
#define TRACK_STATE_INTERFACE_HPP

#include "articleInterface.hpp"
#include "bid.hpp"
#include "review.hpp"
#include "selectionStrategy.hpp"
#include "trackStateException.hpp"
#include "user.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

enum class OperationType
{
    Create,
    Update,
    Delete
};

/**
 * @class ITrackState
 * @brief Interface for managing track states in a conference system.
 *
 * The ITrackState interface defines the methods that a track state must implement
 * to handle articles, bidding, reviews, and selection operations within a track.
 * It enforces the implementation of state-specific behavior for different phases
 * of track management.
 */
class ITrackState
{
  public:
    /**
     * @brief Virtual destructor.
     *
     * Ensures proper cleanup of derived classes.
     */
    virtual ~ITrackState() = default;

    /**
     * @brief Default constructor.
     *
     * Initializes an ITrackState object.
     */
    ITrackState() = default;

    /**
     * @brief Handle an article in a Create, Update, Delete (CUD) manner.
     * @param articles The list of articles to modify.
     * @param article The article to handle.
     * @param operation The type of operation to perform (Create, Update, Delete).
     *
     * This pure virtual method must be implemented by derived classes to manage
     * articles according to the specified operation type. Only the reception state
     * is expected to implement this method.
     */
    virtual void handleArticle(std::vector<std::shared_ptr<Article>>& articles, const std::shared_ptr<Article>& article,
                               OperationType operation) = 0;

    /**
     * @brief Handle the bidding process for articles.
     * @param articles The articles to bid on.
     * @param biddingMap A map of articles and their corresponding bids.
     * @param reviewers The reviewers participating in the bidding process.
     *
     * This pure virtual method must be implemented by derived classes to manage
     * the bidding process, associating articles with bids made by reviewers.
     */
    virtual void handleBidding(const std::vector<std::shared_ptr<Article>>& articles,
                               std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                               const std::vector<std::shared_ptr<User>>& reviewers) = 0;

    /**
     * @brief Handle the review process for articles.
     * @param articles The articles to review.
     * @param biddingMap A map of articles and their corresponding bids.
     * @param reviewMap A map of articles and their associated reviews.
     * @param averageRatings A map of articles and their average ratings.
     * @param reviewers The reviewers conducting the reviews.
     *
     * This pure virtual method must be implemented by derived classes to manage
     * the review process, ensuring that articles are reviewed and rated by the reviewers.
     */
    virtual void handleReview(const std::vector<std::shared_ptr<Article>>& articles,
                              const std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                              std::unordered_map<std::shared_ptr<Article>, std::vector<Review>>& reviewMap,
                              std::unordered_map<std::shared_ptr<Article>, Rating>& averageRatings,
                              const std::vector<std::shared_ptr<User>>& reviewers) = 0;

    /**
     * @brief Handle the selection of articles based on provided parameters.
     * @param selectedArticles A vector of shared pointers to the selected articles.
     * @param selectionStrategy A shared pointer to the selection strategy to be used.
     * @param ratingMap An unordered map of articles and their corresponding ratings.
     * @param selectionThreshold The number of articles to be selected.
     *
     * This pure virtual method must be implemented by derived classes to manage
     * the selection process, determining which articles are selected based on
     * the provided strategy and ratings.
     */
    virtual void handleSelection(std::vector<std::shared_ptr<Article>>& selectedArticles,
                                 std::shared_ptr<SelectionStrategy> selectionStrategy,
                                 std::unordered_map<std::shared_ptr<Article>, Rating> ratingMap,
                                 int selectionThreshold) = 0;

    /**
     * @brief Get the name of the current state.
     * @return A constant reference to a string representing the state's name.
     *
     * This pure virtual method must be implemented by derived classes to provide
     * the name of the current state.
     */
    virtual const std::string& stateName() = 0;
};

#endif // TRACK_STATE_INTERFACE_HPP
