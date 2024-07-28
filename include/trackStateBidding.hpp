/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 21, 2024.
 *
 * MIT License
 */

#ifndef TRACK_STATE_BIDDING_HPP
#define TRACK_STATE_BIDDING_HPP

#include "itrackState.hpp"
#include "track.hpp"

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
     * @param articles The articles to bid.
     * @param biddingMap The map of articles and their bidding interests.
     * @param reviewers The reviewers that are bidding.
     */
    void handleBidding(const std::vector<std::shared_ptr<Article>>& articles,
                       std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                       const std::vector<std::shared_ptr<User>> reviewers) override;

    /**
     * @brief Operate in a CUD way to review an article.
     * @param articles The articles to bid.
     * @param reviewMap The map of articles and their bidding interests.
     * @param biddingMap The map of articles and their bidding interests.
     * @param reviewers The reviewers that are making the review.
     */
    void handleReview(const std::vector<std::shared_ptr<Article>>& articles,
                      const std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                      std::unordered_map<std::shared_ptr<Article>, Review>& reviewMap,
                      const std::vector<std::shared_ptr<User>> reviewers) override;

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
    void updateBidding(std::unordered_map<std::shared_ptr<Article>, Bid>& interestMap,
                       const std::shared_ptr<Article>& article, BiddingInterest interest);

    /**
     * @brief Removes an bidding from the map.
     * @param interestMap The map of articles and their bidding interests.
     * @param article The article.
     * @param interest The interest to remove.
     */
    void removeBidding(std::unordered_map<std::shared_ptr<Article>, Bid>& interestMap,
                       const std::shared_ptr<Article>& article, BiddingInterest interest);
};

#endif // TRACK_STATE_INTERFACE_HPP
