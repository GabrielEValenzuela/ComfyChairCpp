/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef TRACK_STATE_SELECTION_HPP
#define TRACK_STATE_SELECTION_HPP

#include "itrackState.hpp"
#include "review.hpp"
#include "selectionStrategy.hpp"

/**
 * @brief ITrackState is an interface class that defines the methods that a track must implement.
 */
class TrackStateSelection : public ITrackState
{
  public:
    /**
     * @brief Adds an article to the track.
     * @param articles The list of articles to modify.
     * @param article The article to add.
     * @param operation The operation to perform.
     *
     */
    void handleArticle(std::vector<std::shared_ptr<Article>>& articles, const std::shared_ptr<Article>& article,
                       OperationType operation) override;

    /**
     * @brief Operate in a CUD way to bidding an article.
     * @param interestMap The map of articles and their bidding interests.
     * @param article The article.
     * @param interest The interest to set.
     * @param operation The operation to perform.
     */
    void handleBidding(const std::vector<std::shared_ptr<Article>>& articles,
                       std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                       const std::vector<std::shared_ptr<User>> reviewers) override;

    /**
     * @brief Operate in a CUD way to review an article.
     * @param articles The articles to bid.
     * @param reviewMap The map of articles and their bidding interests.
     * @param biddingMap The map of articles and their bidding interests.
     * @param averageRatings The average ratings of the articles.
     * @param reviewers The reviewers that are making the review.
     */
    void handleReview(const std::vector<std::shared_ptr<Article>>& articles,
                      const std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                      std::unordered_map<std::shared_ptr<Article>, std::vector<Review>>& reviewMap,
                      std::unordered_map<std::shared_ptr<Article>, Rating>& averageRatings,
                      const std::vector<std::shared_ptr<User>> reviewers) override;

    /**
     * @brief Handles the selection of articles based on the provided parameters.
     * @param selectedArticles A vector of shared pointers to the selected articles.
     * @param selectionStrategy A shared pointer to the selection strategy to be used.
     * @param ratingMap An unordered map that maps articles to their corresponding ratings.
     * @param selectionThreshold An integer representing the number of articles to be selected.
     */
    virtual void handleSelection(std::vector<std::shared_ptr<Article>>& selectedArticles,
                                 std::shared_ptr<SelectionStrategy> selectionStrategy,
                                 std::unordered_map<std::shared_ptr<Article>, Rating> ratingMap,
                                 int selectionThreshold) override;

    /**
     * @brief Get the state's name.
     * @return The state's name.
     */
    const std::string& stateName() override;

  private:
    std::string m_stateName{"Selection"}; // The state's name.
};

#endif // TRACK_STATE_SELECTION_HPP
