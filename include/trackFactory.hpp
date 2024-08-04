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
#include <nlohmann/json.hpp>

/**
 * @class TrackFactory
 * @brief Factory class for creating tracks.
 *
 * The TrackFactory class provides a static method for creating Track objects
 * based on the provided JSON data. It supports the creation of different types
 * of tracks, such as regular, workshop, and poster tracks.
 */
class TrackFactory
{
  public:
    /**
     * @brief Creates a track based on the provided JSON data.
     * @param trackData A JSON object containing the track data.
     * @return A shared pointer to the created Track object.
     *
     * This method examines the "trackType" field in the JSON data to determine
     * the type of track to create. It returns a shared pointer to the appropriate
     * Track subclass based on the "trackType". If the track type is unknown or
     * missing, it throws an invalid_argument exception.
     */
    static std::shared_ptr<Track> createTrack(const nlohmann::json& trackData)
    {
        try
        {
            const std::string& trackType = trackData.at("trackType");
            if (trackType == "regular")
            {
                return std::make_shared<TrackRegular>(trackData);
            }
            else if (trackType == "workshop")
            {
                return std::make_shared<TrackWorkshop>(trackData);
            }
            else if (trackType == "poster")
            {
                return std::make_shared<TrackPoster>(trackData);
            }
            else
            {
                throw std::invalid_argument("Unknown track type: " + trackType +
                                            ". Did you check if the key 'trackType' is present?");
            }
        }
        catch (const nlohmann::json::exception& e)
        {
            throw std::invalid_argument("Invalid track data: " + std::string(e.what()) +
                                        ". Did you check if the key 'trackType' is present?");
        }
    }
};

#endif // TRACK_FACTORY_HPP
