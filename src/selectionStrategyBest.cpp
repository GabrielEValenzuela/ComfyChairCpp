/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "selectionStrategyBest.hpp"

constexpr auto MINIMUN_THRESHOLD = -3;
constexpr auto MAXIMUM_THRESHOLD = 3;

void SelectionStrategyBest::select(std::vector<std::shared_ptr<Article>>& selectedArticles,
                                   const std::unordered_map<std::shared_ptr<Article>, Rating>& ratingMap,
                                   int selectionThreshold)
{
    if (selectionThreshold < MINIMUN_THRESHOLD || selectionThreshold > MAXIMUM_THRESHOLD)
    {
        throw std::runtime_error("Selection threshold is not within the valid range of -3 to +3.");
    }

    selectedArticles.clear(); // Clear any existing articles

    for (const auto& pair : ratingMap)
    {
        if (static_cast<int>(pair.second) >= selectionThreshold)
        {
            selectedArticles.push_back(pair.first);
        }
    }
}
