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
#include <vector>

/**
 * @brief The SelectionStrategy class represents a strategy for selecting reviewers for articles.
 *
 * This is an abstract base class that defines the interface for different selection strategies.
 * Subclasses of SelectionStrategy can implement different algorithms for selecting reviewers.
 */
class SelectionStrategy
{
  public:
    /**
     * @brief Destructor for the SelectionStrategy class.
     */
    virtual ~SelectionStrategy() = default;

    /**
     * @brief Selects a number of articles based on a given article-rating map.
     * @param selectedArticles The vector of selected articles.
     * @param ratingMap The map containing articles and their corresponding ratings.
     * @param selectionThreshold The number of articles to select.
     */
    virtual void select(std::vector<std::shared_ptr<Article>>& selectedArticles,
                        std::unordered_map<std::shared_ptr<Article>, Rating> ratingMap, int selectionThreshold) = 0;
};

#endif // SELECTION_STRATEGY_HPP
