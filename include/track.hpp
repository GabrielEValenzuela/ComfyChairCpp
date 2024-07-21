/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef TRACK_HPP
#define TRACK_HPP

#include "articleInterface.hpp"
#include "trackStateInterface.hpp"
#include <memory>
#include <string>
#include <vector>

class Track
{
  public:
    /**
     * @brief Track constructor.
     */
    Track() = default;

    /**
     * @brief Track constructor.
     * @param trackName The track's name.
     * @param state The track's state.
     * @param users The users in the track.
     */
    explicit Track(const std::string& trackName, const std::shared_ptr<ITrackState>& state,
                   const std::vector<std::shared_ptr<User>>& users);

    /**
     * @brief Destructor.
     */
    virtual ~Track() = default;

    /**
     * @brief Adds an article to the track.
     * @param article The article to add.
     */
    void addArticle(const std::shared_ptr<Article>& article);

    /**
     * @brief Updates an article in the track.
     * @param article The article to update.
     */
    void updateArticle(const std::shared_ptr<Article>& article);

    /**
     * @brief Removes an article from the track.
     * @param article The article to remove.
     */
    void removeArticle(const std::shared_ptr<Article>& article);

    /**
     * @brief Get the track's name.
     * @return The track's name.
     */
    const std::string& trackName() const;

    /**
     * @brief Set the track's state.
     * @param state The track's state.
     */
    void establishState(const std::shared_ptr<ITrackState>& state);

    /**
     * @brief Prints the current state of the track.
     */
    void currentState() const;

    /**
     * @brief Get the amount of articles on the track
     * @return Number of articles
     */
    int amountArticles() const;

  private:
    std::string m_trackName;                                  //< The track's name.
    std::vector<std::shared_ptr<Article>> m_articles;         //< The articles in the track.
    std::vector<std::shared_ptr<User>> m_users;               //< The users in the track.
    std::vector<std::shared_ptr<Article>> m_selectedArticles; //< The selected articles in the track.
    std::shared_ptr<ITrackState> m_currentState;              //< The track's state.
};

#endif // TRACK_HPP