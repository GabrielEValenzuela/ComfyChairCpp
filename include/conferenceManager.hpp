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
 * @brief Manages the conference tracks and their states.
 */
class ConferenceManager
{
  public:
    /**
     * @brief Default constructor.
     * @note Avoid its use.
     */
    ConferenceManager() = default;

    /**
     * @brief Constructor that takes a shared pointer to a Conference object.
     *
     * @param conference A shared pointer to a Conference object.
     */
    ConferenceManager(std::shared_ptr<Conference> conference) : m_conference(conference)
    {
    }

    /**
     * @brief Destructor.
     */
    virtual ~ConferenceManager() = default;

    /**
     * @brief Starts the bidding process for all tracks in the conference.
     *
     * This method changes the state of all tracks in the conference to the bidding state.
     *
     * @note This method does not return any value.
     */
    void startBidding();

    /**
     * @brief Starts the assingment and revision process for all tracks in the conference.
     *
     * This method changes the state of all tracks in the conference to the revision state.
     *
     * @note This method does not return any value.
     */
    void startRevision();

    /**
     * @brief Starts the selection process for all tracks in the conference.
     *
     * This method changes the state of all tracks in the conference to the selection state.
     *
     * @note This method does not return any value.
     */
    void startSelection();

    /**
     * @brief Gets the shared pointer to the Conference object.
     *
     * @return A shared pointer to the Conference object.
     */
    std::shared_ptr<Conference> getConference() const
    {
        return m_conference;
    }

  private:
    std::shared_ptr<Conference> m_conference;
};

#endif // CONFERENCE_MANAGER_HPP
