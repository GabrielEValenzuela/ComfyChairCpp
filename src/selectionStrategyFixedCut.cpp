/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "SelectionStrategyFixedCut.hpp"

std::vector<std::shared_ptr<Article>> SelectionStrategyFixedCut::select(
    std::unordered_map<std::shared_ptr<Article>, std::shared_ptr<Rating>> articuleRatingMap, int number)
{
    if (number < 1 || number > 100)
    {
        throw std::out_of_range("Number must be between 1 and 100");
    }

    int numberArticlesToTake = articuleRatingMap.size() * number / 100;

    // Custom comparator function to order the map based on rating
    auto ratingComparator = [&](const std::shared_ptr<Article>& article1, const std::shared_ptr<Article>& article2) {
        std::unordered_map<Rating, int> ratingOrder = {
            {Rating::Excellent, 0}, {Rating::VeryGood, 1}, {Rating::Good, 2},          {Rating::Neutral, 3},
            {Rating::Bad, 4},       {Rating::VeryBad, 5},  {Rating::NotRecommended, 6}};

        const std::shared_ptr<Rating>& rating1 = articuleRatingMap[article1];
        const std::shared_ptr<Rating>& rating2 = articuleRatingMap[article2];

        return ratingOrder[*rating1] < ratingOrder[*rating2];
    };

    // Create a vector of articles from the map
    std::vector<std::shared_ptr<Article>> articles;
    for (const auto& pair : articuleRatingMap)
    {
        articles.push_back(pair.first);
    }

    // Sort the articles based on rating using the custom comparator
    std::sort(articles.begin(), articles.end(), ratingComparator);

    // Take the required number of articles
    std::vector<std::shared_ptr<Article>> selectedArticles(articles.begin(), articles.begin() + numberArticlesToTake);

    return selectedArticles;
}
