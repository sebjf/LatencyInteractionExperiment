/*
 * Simulators.h
 *
 *  Created on: 21 Mar 2014
 *      Author: sfriston
 */

#ifndef SIMULATORS_H_
#define SIMULATORS_H_

#include "Logging.h"

class Simulator
{
private:
	bool m_do_simulation;

public:
	Simulator(Logger& logger)
		:m_do_simulation(false),
		logger(logger)
	{}

	virtual void MainLoop() = 0;

	const bool& do_simulation() const { return m_do_simulation; }
	void do_simuation(const bool& val) { m_do_simulation = val; }

	Logger& logger;

	//volatile bool DoSimulation;
	virtual ~Simulator()
	{}
};

class SimulatorFitts : public Simulator
{
public:
	SimulatorFitts(Logger& logger)
	 :Simulator(logger)
	{}

	virtual void MainLoop();
};

#endif /* SIMULATORS_H_ */
