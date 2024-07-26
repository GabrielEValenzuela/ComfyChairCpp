/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "SelectionStrategyBest.hpp"

std::vector<std::shared_ptr<Article>> SelectionStrategyBest::select(
    std::unordered_map<std::shared_ptr<Article>, std::shared_ptr<Rating>> articuleRatingMap, int number)
{
    if (number < -3 || number > 3)
    {
        throw std::runtime_error("Number is not within the valid range of -3 to +3.");
    }

    std::vector<std::shared_ptr<Article>> selectedArticles;
    for (const auto& pair : articuleRatingMap)
    {
        if (convertRatingToNumber(*pair.second) >= number)
        {
            selectedArticles.push_back(pair.first);
        }
    }

    return selectedArticles;
}

int SelectionStrategyBest::convertRatingToNumber(Rating number)
{
    switch (number)
    {
    case Rating::NotRecommended:
        return -3;
        break;
    case Rating::VeryBad:
        return -2;
        break;
    case Rating::Bad:
        return -1;
        break;
    case Rating::Neutral:
        return 0;
        break;
    case Rating::Good:
        return 1;
        break;
    case Rating::VeryGood:
        return 2;
        break;
    case Rating::Excellent:
        return 3;
        break;
    default:
        throw std::runtime_error("Number is not within the valid range of -3 to +3.");
    }
}
