/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef TRACK_WORKSHOP_HPP
#define TRACK_WORKSHOP_HPP

#include "bid.hpp"
#include "track.hpp"
#include "user.hpp"

/**
 * @brief Track class that represents a track in the conference.
 */
class TrackWorkshop : public Track
{
  public:
    /**
     * @brief Track constructor.
     */
    TrackWorkshop() = default;

    /**
     * @brief Track constructor.
     * @param trackData The track data.
     */
    explicit TrackWorkshop(const nlohmann::json& trackData);

    /**
     * @brief Track constructor.
     * @param trackName The track's name.
     * @param state The track's state.
     * @param users The users in the track.
     */
    explicit TrackWorkshop(const std::string& trackName, const std::shared_ptr<ITrackState>& state,
                           const std::vector<std::shared_ptr<User>>& users);

    /**
     * @brief Destructor.
     */
    ~TrackWorkshop() = default;

    /**
     * @brief Adds an article to the track.
     * @param article The article to add.
     * @param operation Operation to perform.
     */
    void handleTrackArticle(const std::shared_ptr<Article>& article, OperationType operation) override;

    /**
     * @brief Adds a bid to an article.
     */
    void handleTrackBidding() override;

    /**
     * @brief Adds a review to an article.
     */
    void handleTrackReview() override;

    /**
     * @brief Handles the selection of a track.
     * @param threshold The track number to be selected.
     */
    void handleTrackSelection(int threshold) override;

    /**
     * @brief Get the track's name.
     * @return The track's name.
     */
    const std::string& trackName() const override;

    /**
     * @brief Set the track's state.
     * @param state The track's state.
     */
    void establishState(const std::shared_ptr<ITrackState>& state) override;

    /**
     * @brief Prints the current state of the track.
     */
    void currentState() const override;

    /**
     * @brief Get the amount of articles on the track
     * @return Number of articles
     */
    int amountArticles() const override;

    /**
     * @brief Get the selected articles in the track.
     * @return A vector of shared pointers to the selected articles.
     */
    std::vector<std::shared_ptr<Article>> selectedArticles() override;

    /**
     * @brief Sets the selection strategy for the track poster.
     * @param strategy A shared pointer to the selection strategy to be set.
     */
    void selectionStrategy(const std::shared_ptr<SelectionStrategy>& strategy) override;

    /**
     * @brief Get the amount of bids on the track
     * @return Number of bids
     */
    size_t amountBids() const override;

    /**
     * @brief Prints the current bids of the track.
     */
    void currentBids() const override;

    /**
     * @brief Get the amount of reviews on the track
     * @return Number of reviews
     */
    size_t amountReviews() const override;

    /**
     * @brief Prints the current reviews of the track.
     */
    void currentReviews() const override;

    /**
     * @brief Add a reviewer to the track.
     */
    void addReviewer(const std::shared_ptr<User> reviewer) override;

  private:
    std::string m_trackName;                                  ///< The track's name.
    std::vector<std::shared_ptr<Article>> m_articles;         ///< The articles in the track.
    std::vector<std::shared_ptr<User>> m_reviewers;           ///< The users in the track.
    std::vector<std::shared_ptr<Article>> m_selectedArticles; ///< The selected articles in the track.
    std::shared_ptr<ITrackState> m_currentState;              ///< The track's state.
    std::shared_ptr<SelectionStrategy> m_selectionStrategy;   ///< The selection strategy.
    std::unordered_map<std::shared_ptr<Article>, Bid>
        m_articleBidding; ///< Relation between article and bidding interest.
    std::unordered_map<std::shared_ptr<Article>, std::vector<Review>>
        m_articleReviews;                                                 ///< Relation between article and review.
    std::unordered_map<std::shared_ptr<Article>, Rating> m_articleRating; ///< Relation between article and rating.
};

#endif // TRACK_WORKSHOP_HPP
