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
#include <unordered_map>
#include <vector>

/**
 * @class Conference
 * @brief Represents a conference with tracks, users, and important event dates.
 *
 * The Conference class encapsulates the details of a conference, including
 * its tracks, users, and key dates such as bidding start, revision start, and
 * selection start times. It provides functionalities to manage these details and
 * to summarize bidding and review activities.
 */
class Conference
{
  public:
    /**
     * @brief Default constructor.
     *
     * Initializes a Conference object with default values.
     */
    Conference() = default;

    /**
     * @brief Parameterized constructor to initialize a conference with JSON data.
     * @param ConferenceJson A JSON object containing the conference's metadata.
     *
     * Constructs a Conference object by parsing the provided JSON data, extracting
     * relevant fields such as tracks, users, and event dates.
     */
    explicit Conference(const nlohmann::json& ConferenceJson);

    /**
     * @brief Default destructor.
     *
     * Cleans up any resources used by the Conference object.
     */
    virtual ~Conference() = default;

    /**
     * @brief Get the tracks associated with the conference.
     * @return A vector of shared pointers to Track objects representing the conference tracks.
     *
     * Retrieves the list of tracks that are part of the conference.
     */
    std::vector<std::shared_ptr<Track>> tracks();

    /**
     * @brief Get the creation date and time of the conference.
     * @return The time point representing when the conference was created.
     *
     * Retrieves the timestamp indicating the creation time of the conference.
     */
    std::chrono::system_clock::time_point createdAt();

    /**
     * @brief Get the start date and time for the bidding phase.
     * @return The time point representing the start of the bidding phase.
     *
     * Retrieves the timestamp for when the bidding phase of the conference begins.
     */
    std::chrono::system_clock::time_point biddingStart();

    /**
     * @brief Set the start date and time for the bidding phase.
     * @param timePoint The time point representing the start of the bidding phase.
     *
     * Updates the timestamp for the beginning of the bidding phase.
     */
    void biddingStart(const std::chrono::system_clock::time_point& timePoint);

    /**
     * @brief Get the start date and time for the revision phase.
     * @return The time point representing the start of the revision phase.
     *
     * Retrieves the timestamp for when the revision phase of the conference begins.
     */
    std::chrono::system_clock::time_point revisionStart();

    /**
     * @brief Set the start date and time for the revision phase.
     * @param timePoint The time point representing the start of the revision phase.
     *
     * Updates the timestamp for the beginning of the revision phase.
     */
    void revisionStart(const std::chrono::system_clock::time_point& timePoint);

    /**
     * @brief Get the start date and time for the selection phase.
     * @return The time point representing the start of the selection phase.
     *
     * Retrieves the timestamp for when the selection phase of the conference begins.
     */
    std::chrono::system_clock::time_point selectionStart();

    /**
     * @brief Set the start date and time for the selection phase.
     * @param timePoint The time point representing the start of the selection phase.
     *
     * Updates the timestamp for the beginning of the selection phase.
     */
    void selectionStart(const std::chrono::system_clock::time_point& timePoint);

    /**
     * @brief Get the number of participants including reviewers, chairs, and authors.
     * @return The total number of participants in the conference.
     *
     * Retrieves the total count of participants involved in the conference.
     */
    size_t sizeParticipants();

    /**
     * @brief Print a summary of the bidding process.
     *
     * Outputs a summary of the bidding activities, providing an overview of
     * the bids placed by reviewers on the conference tracks.
     */
    void printBiddingSummary();

    /**
     * @brief Print a summary of the review process.
     *
     * Outputs a summary of the review activities, providing an overview of
     * the reviews conducted by reviewers on the conference tracks.
     */
    void printReviewSummary();

  private:
    /**
     * @brief Parse a date string into a time point.
     * @param dateStr The date string to parse.
     * @return The time point representing the parsed date and time.
     *
     * Converts a date string into a time point for internal use.
     */
    std::chrono::system_clock::time_point parseDate(const std::string& dateStr);

    std::vector<std::shared_ptr<User>> m_users; /**< List of users involved in the conference. */
    std::unordered_map<std::string, std::shared_ptr<User>> m_reviewers; /**< Map of reviewer names to user objects. */
    std::vector<std::shared_ptr<Track>> m_tracks;                       /**< List of tracks in the conference. */
    std::chrono::system_clock::time_point m_createdAt;     /**< Timestamp indicating when the conference was created. */
    std::chrono::system_clock::time_point m_biddingStart;  /**< Timestamp for the start of the bidding phase. */
    std::chrono::system_clock::time_point m_revisionStart; /**< Timestamp for the start of the revision phase. */
    std::chrono::system_clock::time_point m_selectionStart; /**< Timestamp for the start of the selection phase. */

    /**
     * @brief Validate and add reviewers for a track based on conference JSON data.
     * @param track The track for which reviewers are being validated and added.
     * @param ConferenceJson The JSON object containing the conference's information.
     *
     * Validates the reviewers for a track and adds them to the conference. Throws
     * an exception if a reviewer is not listed in the users.
     */
    void validateAndAddReviewers(std::shared_ptr<Track> track, const nlohmann::json& ConferenceJson);
};

#endif // CONFERENCE_HPP
