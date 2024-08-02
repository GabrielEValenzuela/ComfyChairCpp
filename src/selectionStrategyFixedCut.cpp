/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "selectionStrategyFixedCut.hpp"
#include <algorithm>

void SelectionStrategyFixedCut::select(std::vector<std::shared_ptr<Article>>& selectedArticles,
                                       std::unordered_map<std::shared_ptr<Article>, Rating> ratingMap,
                                       int selectionThreshold)
{
    if (selectionThreshold <= 0 || selectionThreshold > 100)
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
    std::cerr << "Sorted articles" << articles.size() << std::endl;

    selectedArticles.clear(); // Clear any existing articles
    selectedArticles.insert(selectedArticles.end(), articles.begin(), articles.begin() + numberArticlesToTake);
}
