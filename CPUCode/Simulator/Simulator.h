/*
 * Simulator.h
 *
 *  Created on: 26 Jun 2014
 *      Author: sfriston
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include "Resources.h"

class Simulator
{
private:
	bool m_do_simulation;

public:
	Simulator(Resources& resources, Logger& logger)
		:m_do_simulation(false),
		m_resources(resources),
		m_logger(logger),
		flag(0)
	{}

	bool do_simulation() { return m_do_simulation; }
	void do_simuation(bool val) { m_do_simulation = val; }

	Resources& m_resources;
	Logger& m_logger;

	int current_test;
	int flag;

	virtual void Start() = 0;
	virtual void Stop() = 0;

	virtual ~Simulator()
	{}
};

#endif /* SIMULATOR_H_ */
