/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef TRACK_STATE_INTERFACE_HPP
#define TRACK_STATE_INTERFACE_HPP

#include "articleInterface.hpp"
#include <memory>
#include <string>

enum class OperationType
{
    Create,
    Update,
    Delete
};

/**
 * @brief ITrackState is an interface class that defines the methods that a track must implement.
 */
class ITrackState
{
  public:
    /**
     * @brief Destructor.
     */
    virtual ~ITrackState(){};

    /**
     * @brief Constructor
     */
    ITrackState(){};

    /**
     * @brief Adds an article to the track.
     * @param articles The list of articles modify.
     * @param article The article to add.
     * @param operation The operation to perform.
     *
     * @note This method is pure virtual because and only the
     * reception state implements it.
     */
    virtual void handleArticle(std::vector<std::shared_ptr<Article>>& articles, const std::shared_ptr<Article>& article,
                               OperationType operation) = 0;

    /**
     * @brief Get the state's name.
     * @return The state's name.
     */
    virtual const std::string& stateName() = 0;
};

#endif // TRACK_STATE_INTERFACE_HPP
