/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef TRACK_REGULAR_HPP
#define TRACK_REGULAR_HPP

#include "track.hpp"
#include "user.hpp"

/**
 * @class TrackRegular
 * @brief Represents a regular track in the conference.
 *
 * The TrackRegular class extends the Track class to provide specific functionalities
 * for managing a regular track within the conference. It handles operations such as
 * adding articles, managing bids and reviews, and selecting articles based on a strategy.
 */
class TrackRegular : public Track
{
  public:
    /**
     * @brief Default constructor.
     *
     * Initializes a TrackRegular object with default values.
     */
    TrackRegular() = default;

    /**
     * @brief Parameterized constructor to initialize a regular track with JSON data.
     * @param trackData A JSON object containing the track data.
     *
     * Constructs a TrackRegular object by parsing the provided JSON data, extracting
     * relevant fields such as track name and articles.
     */
    explicit TrackRegular(const nlohmann::json& trackData);

    /**
     * @brief Default destructor.
     *
     * Cleans up any resources used by the TrackRegular object.
     */
    ~TrackRegular() = default;

    /**
     * @brief Handle an article within the track.
     * @param article The article to handle.
     * @param operation The operation to perform (Create, Update, Delete).
     *
     * Manages the specified article within the track based on the operation type.
     */
    void handleTrackArticle(const std::shared_ptr<Article>& article, OperationType operation) override;

    /**
     * @brief Handle the bidding process for articles within the track.
     *
     * Manages the bidding process for articles in the track, associating articles with bids made by reviewers.
     */
    void handleTrackBidding() override;

    /**
     * @brief Handle the review process for articles within the track.
     *
     * Manages the review process for articles in the track, ensuring that articles are reviewed and rated by reviewers.
     */
    void handleTrackReview() override;

    /**
     * @brief Handle the selection of articles within the track.
     * @param threshold The number of articles to select.
     *
     * Manages the selection of articles based on the provided threshold and selection strategy.
     */
    void handleTrackSelection(int threshold) override;

    /**
     * @brief Get the name of the track.
     * @return A constant reference to a string representing the track's name.
     *
     * Returns the name of the track.
     */
    const std::string& trackName() const override;

    /**
     * @brief Set the state of the track.
     * @param state A shared pointer to the new state of the track.
     *
     * Establishes the current state of the track.
     */
    void establishState(const std::shared_ptr<ITrackState>& state) override;

    /**
     * @brief Print the current state of the track.
     *
     * Outputs the current state of the track to the standard output.
     */
    void currentState() const override;

    /**
     * @brief Get the number of articles in the track.
     * @return The number of articles in the track.
     *
     * Returns the number of articles in the track.
     */
    int amountArticles() const override;

    /**
     * @brief Set the selection strategy for the track.
     * @param strategy A shared pointer to the selection strategy to be set.
     *
     * Establishes the selection strategy to be used for selecting articles in the track.
     */
    void selectionStrategy(const std::shared_ptr<SelectionStrategy>& strategy) override;

    /**
     * @brief Get the selected articles in the track.
     * @return A vector of shared pointers to the selected articles.
     *
     * Returns the selected articles in the track.
     */
    std::vector<std::shared_ptr<Article>> selectedArticles() override;

    /**
     * @brief Get the number of bids in the track.
     * @return The number of bids in the track.
     *
     * Returns the number of bids in the track.
     */
    size_t amountBids() const override;

    /**
     * @brief Print the current bids in the track.
     *
     * Outputs the current bids in the track to the standard output.
     */
    void currentBids() const override;

    /**
     * @brief Get the number of reviews in the track.
     * @return The number of reviews in the track.
     *
     * Returns the number of reviews in the track.
     */
    size_t amountReviews() const override;

    /**
     * @brief Print the current reviews in the track.
     *
     * Outputs the current reviews in the track to the standard output.
     */
    void currentReviews() const override;

    /**
     * @brief Add a reviewer to the track.
     * @param reviewer A shared pointer to the reviewer to be added.
     *
     * Adds the specified reviewer to the track.
     */
    void addReviewer(const std::shared_ptr<User>& reviewer) override;

  private:
    std::string m_trackName;                                  /**< The name of the track. */
    std::vector<std::shared_ptr<Article>> m_articles;         /**< The articles in the track. */
    std::vector<std::shared_ptr<User>> m_reviewers;           /**< The reviewers in the track. */
    std::vector<std::shared_ptr<Article>> m_selectedArticles; /**< The selected articles in the track. */
    std::shared_ptr<ITrackState> m_currentState;              /**< The current state of the track. */
    std::shared_ptr<SelectionStrategy> m_selectionStrategy;   /**< The selection strategy used in the track. */
    std::unordered_map<std::shared_ptr<Article>, Bid>
        m_articleBidding; /**< A map associating articles with their bidding interest. */
    std::unordered_map<std::shared_ptr<Article>, std::vector<Review>>
        m_articleReviews; /**< A map associating articles with their reviews. */
    std::unordered_map<std::shared_ptr<Article>, Rating>
        m_articleRating; /**< A map associating articles with their ratings. */
};

#endif // TRACK_REGULAR_HPP
