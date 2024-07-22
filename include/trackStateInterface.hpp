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
#include "trackStateException.hpp"
#include <memory>
#include <string>

enum class OperationType
{
    Create,
    Update,
    Delete
};

enum class BiddingInterest
{
    NotInterested,
    Maybe,
    Interested
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
     * @brief Operate in a CUD way to handle an article.
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
     * @brief Operate in a CUD way to bidding an article.
     * @param interestMap The map of articles and their bidding interests.
     * @param article The article.
     * @param interest The interest to set.
     * @param operation The operation to perform.
     */
    virtual void handleBidding(std::unordered_map<std::shared_ptr<Article>, BiddingInterest>& interestMap,
                               const std::shared_ptr<Article>& article, BiddingInterest interest,
                               OperationType operation) = 0;

    /**
     * @brief Get the state's name.
     * @return The state's name.
     */
    virtual const std::string& stateName() = 0;
};

#endif // TRACK_STATE_INTERFACE_HPP
