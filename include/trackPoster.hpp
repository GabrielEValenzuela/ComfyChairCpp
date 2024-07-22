/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef TRACK_POSTER_HPP
#define TRACK_POSTER_HPP

#include "track.hpp"

/**
 * @brief Track class that represents a track in the conference.
 */
class TrackPoster : public Track
{
  public:
    /**
     * @brief Track constructor.
     */
    TrackPoster() = default;

    /**
     * @brief Track constructor.
     * @param trackData The track data.
     */
    explicit TrackPoster(const nlohmann::json& trackData);

    /**
     * @brief Destructor.
     */
    ~TrackPoster() = default;

    /**
     * @brief Adds an article to the track.
     * @param article The article to add.
     */
    void handleTrackArticle(const std::shared_ptr<Article>& article, OperationType operation) override;

    /**
     * @brief Adds a bid to an article.
     * @param article The article to bid.
     * @param interest The interest to set.
     */
    void handleTrackBidding(const std::shared_ptr<Article>& article, BiddingInterest interest,
                            OperationType operation) override;

    /**
     * @brief Adds a review to an article.
     * @param article The article to review.
     * @param review The review to set. //Todo Define the parameter once review class is implemented.
     */
    void handleTrackReview(const std::shared_ptr<Article>& article, const std::string& review,
                           OperationType operation) override;

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

  private:
    std::string m_trackName;                                  ///< The track's name.
    std::vector<std::shared_ptr<Article>> m_articles;         ///< The articles in the track.
    std::vector<std::shared_ptr<User>> m_users;               ///< The users in the track.
    std::vector<std::shared_ptr<Article>> m_selectedArticles; ///< The selected articles in the track.
    std::shared_ptr<ITrackState> m_currentState;              ///< The track's state.
    std::unordered_map<std::shared_ptr<Article>, BiddingInterest>
        m_articleBidding; ///< Relation between article and bidding interest.
};

#endif // TRACK_POSTER_HPP
