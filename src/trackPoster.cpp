/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "trackPoster.hpp"
#include "articlePoster.hpp"
#include "bid.hpp"
#include "trackStateReception.hpp"
#include <iostream>

TrackPoster::TrackPoster(const nlohmann::json& trackData)
{
    m_trackName = trackData.value("trackTopic", "");
    m_currentState = std::make_shared<ReceptionStateTrack>();
}

void TrackPoster::handleTrackArticle(const std::shared_ptr<Article>& article, OperationType operation)
{
    if (!article->isValid() || dynamic_cast<ArticlePoster*>(article.get()) == nullptr)
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

void TrackPoster::handleTrackBidding()
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

void TrackPoster::handleTrackReview()
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

void TrackPoster::handleTrackSelection(int threshold)
{
    if (m_selectionStrategy == nullptr)
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

const std::string& TrackPoster::trackName() const
{
    return m_trackName;
}

void TrackPoster::establishState(const std::shared_ptr<ITrackState>& state)
{
    m_currentState = state;
}

void TrackPoster::currentState() const
{
    std::cout << "Poster '" << m_trackName << "' currently is in '" << m_currentState->stateName() << "' state"
              << std::endl;
}

int TrackPoster::amountArticles() const
{
    return m_articles.size();
}

void TrackPoster::selectionStrategy(const std::shared_ptr<SelectionStrategy>& strategy)
{
    m_selectionStrategy = strategy;
}

std::vector<std::shared_ptr<Article>> TrackPoster::selectedArticles()
{
    return m_selectedArticles;
}

size_t TrackPoster::amountBids() const
{
    return m_articleBidding.size();
}

void TrackPoster::addReviewer(const std::shared_ptr<User>& reviewer)
{
    m_reviewers.push_back(reviewer);
}

void TrackPoster::currentBids() const
{
    for (const auto& article : m_articleBidding)
    {
        std::cout << "The article '" << article.first->articleName() << "' has the following biddings:" << std::endl;
        article.second.bidSummary();
    }
}

size_t TrackPoster::amountReviews() const
{
    return m_articleReviews.size();
}

void TrackPoster::currentReviews() const
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
