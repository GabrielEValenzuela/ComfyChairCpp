/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef SELECTION_STRATEGY_BEST_HPP
#define SELECTION_STRATEGY_BEST_HPP

#include "articleInterface.hpp"
#include "review.hpp"
#include "selectionStrategy.hpp"
#include <vector>

/**
 * @brief The SelectionStrategyBest class represents a selection strategy that selects the best reviewers for articles.
 */
class SelectionStrategyBest : public SelectionStrategy
{
  public:
    /**
     * @brief Selects a number of articles based on a given article-rating map.
     * @param articuleRatingMap The map containing articles and their corresponding ratings.
     * @param number The number of articles to select.
     * @return A vector of shared pointers to the selected articles.
     */
    std::vector<std::shared_ptr<Article>> select(
        std::unordered_map<std::shared_ptr<Article>, std::shared_ptr<Rating>> articuleRatingMap, int number) override;

  private:
    /**
     * @brief Converts a Rating enum value to its corresponding numerical representation.
     * @param rating The Rating enum value to be converted.
     * @return The numerical representation of the Rating enum value.
     */
    int convertRatingToNumber(Rating rating);
};

#endif // SELECTION_STRATEGY_BEST_HPP
