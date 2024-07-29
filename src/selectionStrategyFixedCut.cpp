/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "SelectionStrategyFixedCut.hpp"

std::vector<std::shared_ptr<Article>> SelectionStrategyFixedCut::select(
    std::unordered_map<std::shared_ptr<Article>, Rating> ratingMap, int selectionThreshold)
{
    if (selectionThreshold <= 0 || selectionThreshold >= 100)
    {
        throw std::out_of_range("Number must be between 1 and 100");
    }

    int numberArticlesToTake = ratingMap.size() * selectionThreshold / 100;

    // Create a vector of articles from the map
    std::vector<std::shared_ptr<Article>> articles;
    for (const auto& pair : ratingMap)
    {
        articles.push_back(pair.first);
    }

    // Custom comparator function to order the map based on rating
    auto ratingComparator = [&](const std::shared_ptr<Article>& article1, const std::shared_ptr<Article>& article2) {
        const Rating rating1 = ratingMap[article1];
        const Rating rating2 = ratingMap[article2];

        return static_cast<int>(rating1) < static_cast<int>(rating2);
    };

    // Sort the articles based on rating using the custom comparator
    std::sort(articles.begin(), articles.end(), ratingComparator);

    // Take the required number of articles
    std::vector<std::shared_ptr<Article>> selectedArticles(articles.begin(), articles.begin() + numberArticlesToTake);

    return selectedArticles;
}
