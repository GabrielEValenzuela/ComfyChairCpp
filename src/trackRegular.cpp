/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "trackRegular.hpp"
#include "articleRegular.hpp"
#include "trackStateReception.hpp"

TrackRegular::TrackRegular(const nlohmann::json& trackData)
{
    m_trackName = trackData.value("trackTopic", "");
    m_currentState = std::make_shared<ReceptionStateTrack>();
}

void TrackRegular::handleTrackArticle(const std::shared_ptr<Article>& article, OperationType operation)
{
    if (!article->isValid() || (dynamic_cast<ArticleRegular*>(article.get()) == nullptr))
    {
        std::cerr << "Article is not valid for this track" << std::endl;
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

void TrackRegular::handleTrackBidding(const std::shared_ptr<Article>& article, BiddingInterest interest,
                                      OperationType operation)
{
    try
    {
        m_currentState->handleBidding(m_articleBidding, article, interest, operation);
    }
    catch (const TrackStateException& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void TrackRegular::handleTrackReview(const std::shared_ptr<Article>& article, const std::string& review,
                                     OperationType operation)
{
    std::cout << "Not implemented yet" << std::endl; // ToDo Implement this method
}

const std::string& TrackRegular::trackName() const
{
    return m_trackName;
}

void TrackRegular::establishState(const std::shared_ptr<ITrackState>& state)
{
    m_currentState = state;
}

void TrackRegular::currentState() const
{
    std::cout << "Track '" << m_trackName << "' currently is in '" << m_currentState->stateName() << "' state"
              << std::endl;
}

int TrackRegular::amountArticles() const
{
    return m_articles.size();
}
