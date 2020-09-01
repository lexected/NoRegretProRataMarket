#pragma once

#include <vector>

#include <cmath>
#include <random>

class Adversary;

class Player {
public:
	Player(Adversary* adversary, unsigned seedMultiplier);
	~Player() = default;

	unsigned int chooseAction();
	void caulculateLosses(const std::vector<double>& allocatedQuantities);

	std::vector<unsigned int> getActions() const;
private:
	std::vector<double> m_weights;

	std::default_random_engine m_randomEngine;

	const unsigned int m_desiredQuantity = 100;
	const std::vector<double> m_actionMultipliers = {
		1.0,
		1.5,
		2.0,
		2.5,
		3.0,
		3.5,
		4.0,
		4.5,
		5.0,
		6.0,
		7.0,
		8.0,
		9.0,
		10.0,
		12.0,
		14.0,
		16.0,
		18.0,
		20.0
	};
	const unsigned int m_timeSteps = 10000;
	double m_eta;
};

