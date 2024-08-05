/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "trackStateSelection.hpp"
#include "review.hpp"

void SelectionStateTrack::handleBidding(const std::vector<std::shared_ptr<Article>>& articles,
                                        std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                                        const std::vector<std::shared_ptr<User>>& reviewers)
{
    throw TrackStateException("Bidding is not allowed in selection state");
}

void SelectionStateTrack::handleArticle(std::vector<std::shared_ptr<Article>>& articles,
                                        const std::shared_ptr<Article>& article, OperationType operation)
{
    throw TrackStateException("Cannot handle articles in selection state");
}

void SelectionStateTrack::handleReview(const std::vector<std::shared_ptr<Article>>& articles,
                                       const std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                                       std::unordered_map<std::shared_ptr<Article>, std::vector<Review>>& reviewMap,
                                       std::unordered_map<std::shared_ptr<Article>, Rating>& averageRatings,
                                       const std::vector<std::shared_ptr<User>>& reviewers)
{
    throw TrackStateException("Review is not allowed in selection state");
}

const std::string& SelectionStateTrack::stateName()
{
    return m_stateName;
}

void SelectionStateTrack::handleSelection(std::vector<std::shared_ptr<Article>>& selectedArticles,
                                          std::shared_ptr<SelectionStrategy> selectionStrategy,
                                          std::unordered_map<std::shared_ptr<Article>, Rating> ratingMap,
                                          int selectionThreshold)
{
    selectionStrategy->select(selectedArticles, ratingMap, selectionThreshold);
}
