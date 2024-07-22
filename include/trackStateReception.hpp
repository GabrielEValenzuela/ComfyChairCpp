/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef TRACK_STATE_RECEPTION_HPP
#define TRACK_STATE_RECEPTION_HPP

#include "track.hpp"
#include "trackStateInterface.hpp"

/**
 * @brief ITrackState is an interface class that defines the methods that a track must implement.
 */
class ReceptionStateTrack : public ITrackState
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
     * @brief Get the state's name.
     * @return The state's name.
     */
    const std::string& stateName() override;

  private:
    std::string m_stateName{"Reception"}; // The state's name.

    /**
     * @brief Updates an article in the track.
     * @param articles The list of articles to modify.
     * @param article The article to update.
     */
    void updateArticle(std::vector<std::shared_ptr<Article>>& articles, const std::shared_ptr<Article>& article);

    /**
     * @brief Removes an article from the track.
     * @param articles The list of articles to modify.
     * @param article The article to remove.
     */
    void removeArticle(std::vector<std::shared_ptr<Article>>& articles, const std::shared_ptr<Article>& article);
};

#endif // TRACK_STATE_INTERFACE_HPP
