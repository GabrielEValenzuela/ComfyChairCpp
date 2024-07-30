/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "conferenceManager.hpp"
#include "trackStateBidding.hpp"
#include "trackStateReception.hpp"
#include "trackStateReview.hpp"
#include "trackStateSelection.hpp"

void ConferenceManager::startBidding(std::chrono::system_clock::time_point time)
{
    for (auto& track : m_conference->tracks())
    {
        track->establishState(std::make_unique<BiddingStateTrack>());
        m_conference->biddingStart(time);
    }
}

void ConferenceManager::startRevision(std::chrono::system_clock::time_point time)
{

    for (auto& track : m_conference->tracks())
    {
        track->establishState(std::make_unique<ReviewStateTrack>());
        m_conference->revisionStart(time);
    }
}

void ConferenceManager::startSelection(std::chrono::system_clock::time_point time)
{
    for (auto& track : m_conference->tracks())
    {
        track->establishState(std::make_unique<TrackStateSelection>());
        m_conference->selectionStart(time);
    }
}

std::shared_ptr<Conference> ConferenceManager::conference()
{
    return m_conference;
}
