/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef TRACK_STATE_SELECTION_HPP
#define TRACK_STATE_SELECTION_HPP

#include "review.hpp"
#include "selectionStrategy.hpp"
#include "trackStateInterface.hpp"

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
    void handleBidding(std::unordered_map<std::shared_ptr<Article>, BiddingInterest>& interestMap,
                       const std::shared_ptr<Article>& article, BiddingInterest interest,
                       OperationType operation) override;

    /**
     * @brief Handles the selection of articles based on the provided parameters.
     * @param selectedArticles A vector of shared pointers to the selected articles.
     * @param selectionStrategy A shared pointer to the selection strategy to be used.
     * @param articuleRatingMap An unordered map that maps articles to their corresponding ratings.
     * @param number An integer representing the number of articles to be selected.
     */
    virtual void handleSelection(
        std::vector<std::shared_ptr<Article>> selectedArticles, std::shared_ptr<SelectionStrategy> selectionStrategy,
        std::unordered_map<std::shared_ptr<Article>, std::shared_ptr<Rating>> articuleRatingMap, int number) override;

    /**
     * @brief Get the state's name.
     * @return The state's name.
     */
    const std::string& stateName() override;

  private:
    std::string m_stateName{"Selection"}; // The state's name.
};

#endif // TRACK_STATE_SELECTION_HPP