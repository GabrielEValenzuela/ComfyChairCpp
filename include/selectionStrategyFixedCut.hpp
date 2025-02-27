/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#ifndef SELECTION_STRATEGY_FIXED_CUT_HPP
#define SELECTION_STRATEGY_FIXED_CUT_HPP

#include "articleInterface.hpp"
#include "review.hpp"
#include "selectionStrategy.hpp"
#include <unordered_map>
#include <vector>

/**
 * @class SelectionStrategyFixedCut
 * @brief Implements a fixed cut selection strategy for selecting the top-rated articles.
 *
 * The SelectionStrategyFixedCut class extends the SelectionStrategy class to provide an implementation
 * that selects a fixed number of top-rated articles based on their ratings. It uses the ratings to determine
 * which articles to select, up to a specified threshold.
 */
class SelectionStrategyFixedCut : public SelectionStrategy
{
  public:
    /**
     * @brief Select the top-rated articles based on their ratings.
     * @param selectedArticles The vector to store the selected articles.
     * @param ratingMap A map containing articles and their corresponding ratings.
     * @param selectionThreshold The number of articles to select.
     *
     * This method populates the selectedArticles vector with the top-rated articles
     * from the ratingMap, up to the number specified by selectionThreshold. It overrides
     * the pure virtual method defined in the SelectionStrategy base class.
     */
    void select(std::vector<std::shared_ptr<Article>>& selectedArticles,
                const std::unordered_map<std::shared_ptr<Article>, Rating>& ratingMap, int selectionThreshold) override;
};

#endif // SELECTION_STRATEGY_FIXED_CUT_HPP
