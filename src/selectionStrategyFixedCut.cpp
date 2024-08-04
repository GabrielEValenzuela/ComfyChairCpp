/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "selectionStrategyFixedCut.hpp"
#include <algorithm>
#include <iostream>

constexpr auto MIN_THRESHOLD_PERCENTAGE = 0;
constexpr auto MAX_THRESHOLD_PERCENTAGE = 100;

void SelectionStrategyFixedCut::select(std::vector<std::shared_ptr<Article>>& selectedArticles,
                                       const std::unordered_map<std::shared_ptr<Article>, Rating>& ratingMap,
                                       int selectionThreshold)
{
    if (selectionThreshold <= MIN_THRESHOLD_PERCENTAGE || selectionThreshold > MAX_THRESHOLD_PERCENTAGE)
    {
        throw std::out_of_range("Selection threshold must be between 1 and 100");
    }

    int numberArticlesToTake = ratingMap.size() * selectionThreshold / MAX_THRESHOLD_PERCENTAGE;

    // Create a vector of articles from the map
    std::vector<std::shared_ptr<Article>> articles;
    articles.reserve(ratingMap.size());
    for (const auto& pair : ratingMap)
    {
        articles.push_back(pair.first);
    }

    // Custom comparator function to order the map based on rating
    auto ratingComparator = [&](const std::shared_ptr<Article>& article1, const std::shared_ptr<Article>& article2) {
        const Rating rating1 = ratingMap.at(article1);
        const Rating rating2 = ratingMap.at(article2);

        return static_cast<int>(rating1) > static_cast<int>(rating2); // Higher ratings come first
    };

    // Sort the articles based on rating using the custom comparator
    std::sort(articles.begin(), articles.end(), ratingComparator);

    selectedArticles.clear(); // Clear any existing articles
    selectedArticles.insert(selectedArticles.end(), articles.begin(), articles.begin() + numberArticlesToTake);
}
