#include "trackStateReview.hpp"

void ReviewStateTrack::handleArticle(std::vector<std::shared_ptr<Article>>& articles,
                                     const std::shared_ptr<Article>& article, OperationType operation)
{
    throw TrackStateException("Cannot handle articles in review state");
}

void ReviewStateTrack::handleBidding(const std::vector<std::shared_ptr<Article>>& articles,
                                     std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                                     const std::vector<std::shared_ptr<User>> reviewers)
{
    throw TrackStateException("Bidding is not allowed in review state");
}

void ReviewStateTrack::handleSelection(
    std::vector<std::shared_ptr<Article>> selectedArticles, std::shared_ptr<SelectionStrategy> selectionStrategy,
    std::unordered_map<std::shared_ptr<Article>, std::shared_ptr<Rating>> articuleRatingMap, int number)
{
    throw TrackStateException("Cannot handle selection in review state");
}

void ReviewStateTrack::handleReview(const std::vector<std::shared_ptr<Article>>& articles,
                                    const std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                                    std::unordered_map<std::shared_ptr<Article>, Review>& reviewMap,
                                    const std::vector<std::shared_ptr<User>> reviewers)
{
    size_t numArticlesPerReviewer = articles.size() / reviewers.size();
    size_t extraArticles = articles.size() % reviewers.size();

    // Step 1: Distribute articles based on bids and reviewer capacity
    std::unordered_map<std::shared_ptr<User>, std::vector<std::shared_ptr<Article>>> assignments;
    for (const auto& reviewer : reviewers)
    {
        assignments[reviewer] = {}; // Initialize assignments for each reviewer
    }

    // Sort articles by the number of high bids they received (as an example)
    std::vector<std::shared_ptr<Article>> sortedArticles(articles.begin(), articles.end());
    std::sort(sortedArticles.begin(), sortedArticles.end(),
              [&](const std::shared_ptr<Article>& leftSide, const std::shared_ptr<Article>& rightSide) {
                  return biddingMap.at(leftSide) > biddingMap.at(rightSide);
              });

    // Assign articles to reviewers
    size_t currentReviewerIndex = 0;
    for (const auto& article : sortedArticles)
    {
        if (assignments[reviewers[currentReviewerIndex]].size() < numArticlesPerReviewer + (extraArticles > 0 ? 1 : 0))
        {
            assignments[reviewers[currentReviewerIndex]].push_back(article);
            if (extraArticles > 0)
            {
                --extraArticles;
            }
        }
        else
        {
            currentReviewerIndex = (currentReviewerIndex + 1) % reviewers.size();
            assignments[reviewers[currentReviewerIndex]].push_back(article);
        }
    }

    // Step 2: Each reviewer reviews their assigned articles
    for (const auto& [reviewer, assignedArticles] : assignments)
    {
        for (const auto& article : assignedArticles)
        {
            reviewMap[article] = reviewer->reviewArticle();
        }
    }
}

const std::string& ReviewStateTrack::stateName()
{
    return m_stateName;
}
