/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "trackWorkshop.hpp"
#include "bid.hpp"
#include "trackStateReception.hpp"
#include <iostream>

TrackWorkshop::TrackWorkshop(const nlohmann::json& trackData)
{
    m_trackName = trackData.value("trackTopic", "");
    m_currentState = std::make_shared<ReceptionStateTrack>();
}

TrackWorkshop::TrackWorkshop(const std::string& trackName, const std::shared_ptr<ITrackState>& state,
                             const std::vector<std::shared_ptr<User>>& users)
    : m_trackName(trackName), m_currentState(state), m_reviewers(users)
{
}

void TrackWorkshop::handleTrackArticle(const std::shared_ptr<Article>& article, OperationType operation)
{
    if (!article->isValid())
    {
        std::cout << "Article is not valid for this track" << std::endl;
        return;
    }
    try
    {
        m_currentState->handleArticle(m_articles, article, operation);
    }
    catch (const TrackStateException& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void TrackWorkshop::handleTrackBidding()
{
    try
    {
        m_currentState->handleBidding(m_articles, m_articleBidding, m_reviewers);
    }
    catch (const TrackStateException& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void TrackWorkshop::handleTrackReview()
{
    try
    {
        m_currentState->handleReview(m_articles, m_articleBidding, m_articleReviews, m_articleRating, m_reviewers);
    }
    catch (const TrackStateException& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void TrackWorkshop::handleTrackSelection(int threshold)
{
    if (!m_selectionStrategy)
    {
        throw std::runtime_error("Selection strategy is null");
    }

    try
    {
        m_currentState->handleSelection(m_selectedArticles, m_selectionStrategy, m_articleRating, threshold);
    }
    catch (const TrackStateException& e)
    {
        std::cout << e.what() << std::endl;
    }
}

const std::string& TrackWorkshop::trackName() const
{
    return m_trackName;
}

void TrackWorkshop::establishState(const std::shared_ptr<ITrackState>& state)
{
    m_currentState = state;
}

void TrackWorkshop::currentState() const
{
    std::cout << "Workshop '" << m_trackName << "' currently is in '" << m_currentState->stateName() << "' state"
              << std::endl;
}

int TrackWorkshop::amountArticles() const
{
    return m_articles.size();
}

void TrackWorkshop::selectionStrategy(const std::shared_ptr<SelectionStrategy>& strategy)
{
    m_selectionStrategy = strategy;
}

std::vector<std::shared_ptr<Article>> TrackWorkshop::selectedArticles()
{
    return m_selectedArticles;
}

size_t TrackWorkshop::amountBids() const
{
    return m_articleBidding.size();
}

void TrackWorkshop::addReviewer(const std::shared_ptr<User>& reviewer)
{
    m_reviewers.push_back(reviewer);
}

void TrackWorkshop::currentBids() const
{
    for (const auto& article : m_articleBidding)
    {
        std::cout << "The article '" << article.first->articleName() << "' has the following biddings:" << std::endl;
        article.second.bidSummary();
    }
}

size_t TrackWorkshop::amountReviews() const
{
    return m_articleReviews.size();
}

void TrackWorkshop::currentReviews() const
{
    for (const auto& article : m_articleReviews)
    {
        std::cout << "The article '" << article.first->articleName() << "' has the following reviews:" << std::endl;
        for (const auto& review : article.second)
        {
            review.printReview();
        }
    }
}
