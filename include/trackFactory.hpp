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

enum class TrackType
{
    Regular,
    Workshop,
    Poster
};

/**
 * @brief TrackFactory class that creates tracks.
 */
class TrackFactory
{
  public:
    /**
     * @brief Creates a track.
     * @param trackData The track data.
     * @param type The track type.
     * @return The track.
     */
    static std::shared_ptr<Track> createTrack(const nlohmann::json& trackData, TrackType type)
    {
        switch (type)
        {
        case TrackType::Regular:
            return std::make_shared<TrackRegular>(trackData);
        case TrackType::Workshop:
            return std::make_shared<TrackWorkshop>(trackData);
        case TrackType::Poster:
            return std::make_shared<TrackPoster>(trackData);
        default:
            throw std::invalid_argument("Unknown track type.");
        }
    }
};

#endif // TRACK_FACTORY_HPP
