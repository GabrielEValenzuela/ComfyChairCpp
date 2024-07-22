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

void ConferenceManager::startBidding()
{
    std::vector<std::shared_ptr<Track>> tracks = m_conference->getTracks();
    for (auto& track : tracks)
    {
        track->establishState(std::make_unique<BiddingStateTrack>());
    }
}

void ConferenceManager::startRevision()
{
    std::vector<std::shared_ptr<Track>> tracks = m_conference->getTracks();
    for (auto& track : tracks)
    {
        track->establishState(std::make_unique<ReceptionStateTrack>());
    }
}

void ConferenceManager::startSelection()
{
    std::vector<std::shared_ptr<Track>> tracks = m_conference->getTracks();
    for (auto& track : tracks)
    {
        // track->establishState(std::make_unique<BiddingStateTrack>());
    }
}
