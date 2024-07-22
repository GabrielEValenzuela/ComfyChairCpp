/*
 * ComfyChair
 * Copyright (C) 2024, M. Venturino, G. Valenzuela
 * July 20, 2024.
 *
 * MIT License
 */

#include "trackWorkshop.hpp"
#include "trackStateReception.hpp"

TrackWorkshop::TrackWorkshop(const nlohmann::json& trackData)
{
    m_trackName = trackData.value("trackTopic", "");
    m_currentState = std::make_shared<ReceptionStateTrack>();
}

void TrackWorkshop::handleTrackArticle(const std::shared_ptr<Article>& article, OperationType operation)
{
    if (!article->isValid())
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

void TrackWorkshop::handleTrackBidding(const std::shared_ptr<Article>& article, BiddingInterest interest,
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

void TrackWorkshop::handleTrackReview(const std::shared_ptr<Article>& article, const std::string& review,
                                      OperationType operation)
{
    std::cout << "Not implemented yet" << std::endl; // ToDo Implement this method
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
