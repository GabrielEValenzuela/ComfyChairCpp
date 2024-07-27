/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef TRACK_FACTORY_HPP
#define TRACK_FACTORY_HPP

#include "track.hpp"
#include "trackPoster.hpp"
#include "trackRegular.hpp"
#include "trackWorkshop.hpp"
#include <memory>

/**
 * @brief TrackFactory class that creates tracks.
 */
class TrackFactory
{
  public:
    /**
     * @brief Creates a track.
     * @param trackData The track data.
     * @return The track.
     */
    static std::shared_ptr<Track> createTrack(const nlohmann::json& trackData)
    {
        try
        {
            if (trackData.at("trackType") == "regular")
            {
                return std::make_shared<TrackRegular>(trackData);
            }
            else if (trackData.at("trackType") == "workshop")
            {
                return std::make_shared<TrackWorkshop>(trackData);
            }
            else if (trackData.at("trackType") == "poster")
            {
                return std::make_shared<TrackPoster>(trackData);
            }
            else
            {
                throw std::invalid_argument("Unknown track type. Did you check if the key 'trackType' is present?.");
            }
        }
        catch (const std::exception& e)
        {
            throw std::invalid_argument("Unknown track type. Did you check if the key 'trackType' is present?.");
        }
    }
};

#endif // TRACK_FACTORY_HPP
