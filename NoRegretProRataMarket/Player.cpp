#include "Player.h"

#include <ctime>
#include <algorithm>

Player::Player(Adversary* adversary, unsigned seedMultiplier)
	: m_weights(), m_eta(std::min(0.5, std::sqrt(std::log(m_actionMultipliers.size()) / m_timeSteps))),
	m_randomEngine((unsigned int)time(0) * seedMultiplier) {

	m_weights.resize(m_actionMultipliers.size(), 1.0);
}

unsigned int Player::chooseAction() {
	std::discrete_distribution<unsigned int> distribution(m_weights.begin(), m_weights.end());
	int actionChoice = distribution(m_randomEngine);
	return (unsigned int)(m_actionMultipliers[actionChoice] * m_desiredQuantity);
}

void Player::caulculateLosses(const std::vector<double>& allocatedQuantities) {
	std::transform(allocatedQuantities.cbegin(), allocatedQuantities.cend(), m_weights.cbegin(), m_weights.begin(), [this](double allocatedQuantity, double weight) {
		double deltaQuantity = std::abs(allocatedQuantity - m_desiredQuantity);
		double normalisedLoss = deltaQuantity / (m_actionMultipliers.back() * m_desiredQuantity);
		return weight * std::pow(1 - m_eta, normalisedLoss);
	});
}

std::vector<unsigned int> Player::getActions() const {
	std::vector<unsigned int> ret;
	ret.resize(m_actionMultipliers.size());

	std::transform(m_actionMultipliers.cbegin(), m_actionMultipliers.cend(), ret.begin(), [this](double multiplier) {
		return (unsigned int)(multiplier * this->m_desiredQuantity);
	});

	return ret;
}
