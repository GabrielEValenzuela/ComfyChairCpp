/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "trackStateSelection.hpp"
#include "review.hpp"

void TrackStateSelection::handleBidding(std::unordered_map<std::shared_ptr<Article>, BiddingInterest>& interestMap,
                                        const std::shared_ptr<Article>& article, BiddingInterest interest,
                                        OperationType operation)
{
    throw TrackStateException("Bidding is not allowed in selection state");
}

void TrackStateSelection::handleArticle(std::vector<std::shared_ptr<Article>>& articles,
                                        const std::shared_ptr<Article>& article, OperationType operation)
{
    throw TrackStateException("Cannot handle articles in selection state");
}

const std::string& TrackStateSelection::stateName()
{
    return m_stateName;
}

void TrackStateSelection::handleSelection(
    std::vector<std::shared_ptr<Article>> selectedArticles, std::shared_ptr<SelectionStrategy> selectionStrategy,
    std::unordered_map<std::shared_ptr<Article>, std::shared_ptr<Rating>> articuleRatingMap, int number)
{
    selectedArticles = selectionStrategy->select(articuleRatingMap, number);
}