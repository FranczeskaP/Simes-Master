#ifndef MQTT_DEFINITIONS_H
#define MQTT_DEFINITIONS_H

typedef enum
{
	StateSupport = 0,
	StateTotalForwardActiveEnergy,
	StateTotalReverseActiveEnergy,
	StateTotalForwardActiveEnergyBalanced,
	StateTotalReverseActiveEnergyBalanced,
	Phases1TotalForwardActiveEnergy,
	Phases1TotalReverseActiveEnergy,
	Phases1TotalForwardActiveEnergyBalanced,
	Phases1TotalReverseActiveEnergyBalanced,
	Phases1Frequency,
	Phases1Voltage,
	Phases1Current,
	Phases1PowerActive,
	Phases1PowerReactive,
	Phases1POwerApparent,
	Phases1PowerFactor,
	Phases1PhaseAngle,
	Phases2TotalForwardActiveEnergy,
	Phases2TotalReverseActiveEnergy,
	Phases2TotalForwardActiveEnergyBalanced,
	Phases2TotalReverseActiveEnergyBalanced,
	Phases2Frequency,
	Phases2Voltage,
	Phases2Current,
	Phases2PowerActive,
	Phases2PowerReactive,
	Phases2POwerApparent,
	Phases2PowerFactor,
	Phases2PhaseAngle,
	Phases3TotalForwardActiveEnergy,
	Phases3TotalReverseActiveEnergy,
	Phases3TotalForwardActiveEnergyBalanced,
	Phases3TotalReverseActiveEnergyBalanced,
	Phases3Frequency,
	Phases3Voltage,
	Phases3Current,
	Phases3PowerActive,
	Phases3PowerReactive,
	Phases3POwerApparent,
	Phases3PowerFactor,
	Phases3PhaseAngle,
	TotalNumOfZamelTopics
}ZamelTopicsNums;

typedef enum
{
	Ch1 = 0,
	Ch2,
	Ch3,
	Ch4,
	Eff,
	P1,
	P2,
	EnergyCh1,
	EnergyCh2,
	QCh1,
	QCh2,
	Temp,
	TotalNumOfDcSensorTopics
}DcSensorsTopicsNums;

extern const char * const DcSensor1Topics[TotalNumOfDcSensorTopics];
extern const char * const DcSensor2Topics[TotalNumOfDcSensorTopics];
extern const char * const DcSensor3Topics[TotalNumOfDcSensorTopics];
extern const char * const DcSensor4Topics[TotalNumOfDcSensorTopics];
extern const char * const DcSensor5Topics[TotalNumOfDcSensorTopics];
extern const char * const ZamelTopics[TotalNumOfZamelTopics];

#endif
