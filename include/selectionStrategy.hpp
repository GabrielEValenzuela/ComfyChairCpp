/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef SELECTION_STRATEGY_HPP
#define SELECTION_STRATEGY_HPP

#include "articleInterface.hpp"
#include "review.hpp"
#include <unordered_map>
#include <vector>

/**
 * @class SelectionStrategy
 * @brief Abstract base class representing a strategy for selecting articles based on their ratings.
 *
 * The SelectionStrategy class defines the interface for various selection strategies
 * that can be used to select articles for a conference. Subclasses should implement
 * specific algorithms for selecting articles based on their ratings.
 */
class SelectionStrategy
{
  public:
    /**
     * @brief Virtual destructor.
     *
     * Ensures proper cleanup of derived classes.
     */
    virtual ~SelectionStrategy() = default;

    /**
     * @brief Select articles based on their ratings.
     * @param selectedArticles The vector to store the selected articles.
     * @param ratingMap A map containing articles and their corresponding ratings.
     * @param selectionThreshold The number of articles to select.
     *
     * This pure virtual method must be implemented by derived classes to define
     * the selection algorithm. The method populates the selectedArticles vector
     * with articles chosen based on their ratings.
     */
    virtual void select(std::vector<std::shared_ptr<Article>>& selectedArticles,
                        const std::unordered_map<std::shared_ptr<Article>, Rating>& ratingMap,
                        int selectionThreshold) = 0;
};

#endif // SELECTION_STRATEGY_HPP
