/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef CONFERENCE_MANAGER_HPP
#define CONFERENCE_MANAGER_HPP

#include "conference.hpp"
#include <memory>

/**
 * @class ConferenceManager
 * @brief Manages the lifecycle and state transitions of a conference's tracks.
 *
 * The ConferenceManager class provides functionalities to manage and control the
 * state transitions of tracks within a conference. It handles the initiation of
 * various phases such as bidding, revision, and selection for all tracks.
 */
class ConferenceManager
{
  public:
    /**
     * @brief Default constructor.
     *
     * Initializes a ConferenceManager object with default values. Its use is generally
     * discouraged unless specific default initialization is required.
     */
    ConferenceManager() = default;

    /**
     * @brief Parameterized constructor to initialize a ConferenceManager with a Conference object.
     * @param conference A shared pointer to a Conference object.
     *
     * Constructs a ConferenceManager object that manages the given Conference object.
     */
    explicit ConferenceManager(std::shared_ptr<Conference> conference) : m_conference(conference)
    {
    }

    /**
     * @brief Default destructor.
     *
     * Cleans up any resources used by the ConferenceManager object.
     */
    virtual ~ConferenceManager() = default;

    /**
     * @brief Starts the bidding process for all tracks in the conference.
     * @param time The time point at which the bidding process starts.
     *
     * This method sets the state of all tracks in the conference to the bidding state
     * and updates the bidding start time.
     */
    void startBidding(std::chrono::system_clock::time_point time);

    /**
     * @brief Starts the assignment and revision process for all tracks in the conference.
     * @param time The time point at which the revision process starts.
     *
     * This method sets the state of all tracks in the conference to the revision state
     * and updates the revision start time.
     */
    void startRevision(std::chrono::system_clock::time_point time);

    /**
     * @brief Starts the selection process for all tracks in the conference.
     * @param time The time point at which the selection process starts.
     *
     * This method sets the state of all tracks in the conference to the selection state
     * and updates the selection start time.
     */
    void startSelection(std::chrono::system_clock::time_point time);

    /**
     * @brief Retrieves the shared pointer to the Conference object.
     * @return A shared pointer to the Conference object managed by this ConferenceManager.
     *
     * Provides access to the Conference object that this ConferenceManager is responsible for.
     */
    std::shared_ptr<Conference> conference();

  private:
    std::shared_ptr<Conference> m_conference; /**< Shared pointer to the Conference object being managed. */
};

#endif // CONFERENCE_MANAGER_HPP
