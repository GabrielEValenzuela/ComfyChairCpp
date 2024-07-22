/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef CONFERENCE_HPP
#define CONFERENCE_HPP

#include "track.hpp"
#include "user.hpp"
#include <chrono>

/**
 * @class Conference
 * @brief Represents a conference.
 */
class Conference
{

  public:
    /**
     * @brief Conference constructor.
     */
    Conference() = default;

    /**
     * @brief Constructor.
     * @param ConferenceJson Represents the conference's information, in a JSON format.
     */
    explicit Conference(const nlohmann::json& ConferenceJson);

    /**
     * @brief Destructor.
     */
    virtual ~Conference() = default;

    /**
     * @brief Get the tracks.
     * @return A vector of shared pointers to Track objects representing the tracks.
     */
    std::vector<std::shared_ptr<Track>> getTracks() const
    {
        return m_tracks;
    }

    /**
     * @brief Add a track to the conference.
     * @param track The track to add.
     */
    void addTrack(const std::shared_ptr<Track>& track)
    {
        m_tracks.push_back(track);
    }

    /**
     * @brief Get the createdAt time point.
     * @return The createdAt time point.
     */
    std::chrono::system_clock::time_point getCreatedAt() const
    {
        return m_createdAt;
    }

    /**
     * @brief Get the biddingStart time point.
     * @return The biddingStart time point.
     */
    std::chrono::system_clock::time_point getBiddingStart() const
    {
        return m_biddingStart;
    }

    /**
     * @brief Set the biddingStart time point.
     * @param timePoint The biddingStart time point to set.
     */
    void setBiddingStart(const std::chrono::system_clock::time_point& timePoint)
    {
        m_biddingStart = timePoint;
    }

    /**
     * @brief Get the revisionStart time point.
     * @return The revisionStart time point.
     */
    std::chrono::system_clock::time_point getRevisionStart() const
    {
        return m_revisionStart;
    }

    /**
     * @brief Set the revisionStart time point.
     * @param timePoint The revisionStart time point to set.
     */
    void setRevisionStart(const std::chrono::system_clock::time_point& timePoint)
    {
        m_revisionStart = timePoint;
    }

    /**
     * @brief Get the selectionStart time point.
     * @return The selectionStart time point.
     */
    std::chrono::system_clock::time_point getSelectionStart() const
    {
        return m_selectionStart;
    }

    /**
     * @brief Set the selectionStart time point.
     * @param timePoint The selectionStart time point to set.
     */
    void setSelectionStart(const std::chrono::system_clock::time_point& timePoint)
    {
        m_selectionStart = timePoint;
    }

  private:
    std::chrono::system_clock::time_point parseDate(const std::string& dateStr);
    std::vector<std::shared_ptr<User>> m_chairs;
    std::vector<std::shared_ptr<User>> m_authors;
    std::vector<std::shared_ptr<Track>> m_tracks;
    std::chrono::system_clock::time_point m_createdAt;
    std::chrono::system_clock::time_point m_biddingStart;
    std::chrono::system_clock::time_point m_revisionStart;
    std::chrono::system_clock::time_point m_selectionStart;
};

#endif // CONFERENCE_HPP
