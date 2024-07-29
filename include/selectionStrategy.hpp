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
     * @param articuleRatingMap The map containing articles and their corresponding ratings.
     * @param number The number of articles to select.
     * @return A vector of shared pointers to the selected articles.
     */
    virtual std::vector<std::shared_ptr<Article>> select(
        std::unordered_map<std::shared_ptr<Article>, std::shared_ptr<Rating>> articuleRatingMap, int number) = 0;
};

#endif // SELECTION_STRATEGY_HPP
