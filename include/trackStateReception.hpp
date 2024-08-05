/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef TRACK_STATE_RECEPTION_HPP
#define TRACK_STATE_RECEPTION_HPP

#include "bid.hpp"
#include "itrackState.hpp"
#include "track.hpp"

/**
 * @class ReceptionStateTrack
 * @brief Represents the reception state of a track in the conference.
 *
 * The ReceptionStateTrack class implements the ITrackState interface to provide
 * functionalities specific to the reception state of a track. It handles operations
 * such as adding articles, managing bids, and processing reviews and selections.
 */
class ReceptionStateTrack : public ITrackState
{
  public:
    /**
     * @brief Handle an article within the track in the reception state.
     * @param articles The list of articles to modify.
     * @param article The article to handle.
     * @param operation The operation to perform (Create, Update, Delete).
     *
     * Manages the specified article within the track based on the operation type during the reception state.
     */
    void handleArticle(std::vector<std::shared_ptr<Article>>& articles, const std::shared_ptr<Article>& article,
                       OperationType operation) override;

    /**
     * @brief Handle the bidding process for articles within the track.
     * @param articles The articles to bid on.
     * @param biddingMap A map of articles and their corresponding bids.
     * @param reviewers The reviewers participating in the bidding process.
     *
     * Manages the bidding process for articles in the track, associating articles with bids made by reviewers.
     */
    void handleBidding(const std::vector<std::shared_ptr<Article>>& articles,
                       std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                       const std::vector<std::shared_ptr<User>>& reviewers) override;

    /**
     * @brief Handle the review process for articles within the track.
     * @param articles The articles to review.
     * @param biddingMap A map of articles and their corresponding bids.
     * @param reviewMap A map of articles and their associated reviews.
     * @param averageRatings A map of articles and their average ratings.
     * @param reviewers The reviewers conducting the reviews.
     *
     * Manages the review process for articles in the track, ensuring that articles are reviewed and rated by the
     * reviewers.
     */
    void handleReview(const std::vector<std::shared_ptr<Article>>& articles,
                      const std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                      std::unordered_map<std::shared_ptr<Article>, std::vector<Review>>& reviewMap,
                      std::unordered_map<std::shared_ptr<Article>, Rating>& averageRatings,
                      const std::vector<std::shared_ptr<User>>& reviewers) override;

    /**
     * @brief Handle the selection of articles based on the provided parameters.
     * @param selectedArticles A vector of shared pointers to the selected articles.
     * @param selectionStrategy A shared pointer to the selection strategy to be used.
     * @param ratingMap An unordered map that maps articles to their corresponding ratings.
     * @param selectionThreshold An integer representing the number of articles to be selected.
     *
     * Manages the selection process for articles in the track, determining which articles are selected based on the
     * provided strategy and ratings.
     */
    void handleSelection(std::vector<std::shared_ptr<Article>>& selectedArticles,
                         std::shared_ptr<SelectionStrategy> selectionStrategy,
                         std::unordered_map<std::shared_ptr<Article>, Rating> ratingMap,
                         int selectionThreshold) override;

    /**
     * @brief Get the state's name.
     * @return A constant reference to a string representing the state's name.
     *
     * Returns the name of the current state.
     */
    const std::string& stateName() override;

  private:
    std::string m_stateName{"Reception"}; /**< The name of the current state. */

    /**
     * @brief Update an article in the track.
     * @param articles The list of articles to modify.
     * @param article The article to update.
     *
     * Updates the specified article within the track.
     */
    void updateArticle(std::vector<std::shared_ptr<Article>>& articles, const std::shared_ptr<Article>& article);

    /**
     * @brief Remove an article from the track.
     * @param articles The list of articles to modify.
     * @param article The article to remove.
     *
     * Removes the specified article from the track.
     */
    void removeArticle(std::vector<std::shared_ptr<Article>>& articles, const std::shared_ptr<Article>& article);
};

#endif // TRACK_STATE_RECEPTION_HPP
