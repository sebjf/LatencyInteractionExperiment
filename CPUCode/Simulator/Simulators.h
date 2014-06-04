/*
 * Simulators.h
 *
 *  Created on: 21 Mar 2014
 *      Author: sfriston
 */

#ifndef SIMULATORS_H_
#define SIMULATORS_H_


#include "Resources.h"

class Simulator
{
private:
	bool m_do_simulation;

public:
	Simulator(Resources& resources, Logger& logger)
		:m_do_simulation(false),
		m_resources(resources),
		m_logger(logger)
	{}

	virtual void MainLoop() = 0;

	const bool& do_simulation() const { return m_do_simulation; }
	void do_simuation(const bool& val) { m_do_simulation = val; }

	Resources& m_resources;
	Logger& m_logger;

	//volatile bool DoSimulation;
	virtual ~Simulator()
	{}
};

class SimulatorFitts : public Simulator
{
public:
	SimulatorFitts(Resources& resources, Logger& logger)
	 :Simulator(resources, logger)
	{}

	virtual void MainLoop();
};

class SteeringConditionBuilder;

class SimulatorSteering : public Simulator
{
public:
	SimulatorSteering(Resources& resources, Logger& logger, SteeringConditionBuilder& conditions)
	 :Simulator(resources, logger),
	  m_conditions(conditions)
	{}

	virtual void MainLoop();

private:
	SteeringConditionBuilder& m_conditions;
};

#endif /* SIMULATORS_H_ */
