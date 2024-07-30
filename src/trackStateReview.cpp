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

void ReviewStateTrack::handleSelection(std::vector<std::shared_ptr<Article>>& selectedArticles,
                                       std::shared_ptr<SelectionStrategy> selectionStrategy,
                                       std::unordered_map<std::shared_ptr<Article>, Rating> ratingMap,
                                       int selectionThreshold)
{
    throw TrackStateException("Cannot handle selection in review state");
}

void ReviewStateTrack::handleReview(const std::vector<std::shared_ptr<Article>>& articles,
                                    const std::unordered_map<std::shared_ptr<Article>, Bid>& biddingMap,
                                    std::unordered_map<std::shared_ptr<Article>, std::vector<Review>>& reviewMap,
                                    std::unordered_map<std::shared_ptr<Article>, Rating>& averageRatings,
                                    const std::vector<std::shared_ptr<User>> reviewers)
{
    size_t numArticlesPerReviewer = std::max(3ul, articles.size() / reviewers.size());
    size_t extraArticles = articles.size() % reviewers.size();

    // Step 1: Distribute articles based on bids and reviewer capacity
    std::unordered_map<std::shared_ptr<User>, std::vector<std::shared_ptr<Article>>> assignments;
    for (const auto& reviewer : reviewers)
    {
        assignments[reviewer] = {}; // Initialize assignments for each reviewer
    }

    // Initialize assignments for each reviewer
    std::vector<std::shared_ptr<Article>> sortedArticles(articles.begin(), articles.end());
    std::sort(sortedArticles.begin(), sortedArticles.end(),
              [&](const std::shared_ptr<Article>& a, const std::shared_ptr<Article>& b) {
                  return biddingMap.at(a) > biddingMap.at(b); // Assuming Bid has an operator> comparing bid importance
              });

    size_t currentReviewerIndex = 0;
    for (const auto& article : sortedArticles)
    {
        assignments[reviewers[currentReviewerIndex]].push_back(article);
        if (++currentReviewerIndex >= reviewers.size())
        {
            currentReviewerIndex = 0;
        }
    }

    // Assign articles and collect reviews
    for (const auto& [reviewer, assignedArticles] : assignments)
    {
        for (const auto& article : assignedArticles)
        {
            Review review = reviewer->reviewArticle();
            reviewMap[article].push_back(review);
        }
    }

    // Calculate average ratings per article
    for (const auto& [article, reviews] : reviewMap)
    {
        double sumRatings = std::accumulate(reviews.begin(), reviews.end(), 0.0, [](double sum, const Review& review) {
            return sum + static_cast<int>(review.rating());
        });
        averageRatings[article] = static_cast<Rating>(std::ceil(sumRatings / reviews.size()));
    }

    // Optional: Display average ratings for debugging
    for (const auto& [article, avgRating] : averageRatings)
    {
        std::cout << "Article '" << article->articleName() << "' has an average rating of "
                  << static_cast<int>(avgRating) << std::endl;
    }
}

const std::string& ReviewStateTrack::stateName()
{
    return m_stateName;
}
