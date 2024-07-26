/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 21, 2024.
 *
 * MIT License
 */

#ifndef TRACK_STATE_BIDDING_HPP
#define TRACK_STATE_BIDDING_HPP

#include "track.hpp"
#include "trackStateInterface.hpp"

/**
 * @brief Bidding state class that represents the state of a track in the conference.
 */
class BiddingStateTrack : public ITrackState
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
    virtual void handleBidding(std::unordered_map<std::shared_ptr<Article>, BiddingInterest>& interestMap,
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
    std::string m_stateName{"Bidding"}; // The state's name.

    /**
     * @brief Updates an bidding in the track.
     * @param interestMap The map of articles and their bidding interests.
     * @param article The article.
     * @param interest The interest to set.
     */
    void updateBidding(std::unordered_map<std::shared_ptr<Article>, BiddingInterest>& interestMap,
                       const std::shared_ptr<Article>& article, BiddingInterest interest);

    /**
     * @brief Removes an bidding from the map.
     * @param interestMap The map of articles and their bidding interests.
     * @param article The article.
     * @param interest The interest to remove.
     */
    void removeBidding(std::unordered_map<std::shared_ptr<Article>, BiddingInterest>& interestMap,
                       const std::shared_ptr<Article>& article, BiddingInterest interest);
};

#endif // TRACK_STATE_INTERFACE_HPP
