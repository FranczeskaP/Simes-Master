#include "MqttDefinitions.h"

const char * const DcSensor1Topics[TotalNumOfDcSensorTopics] = {
	[Ch1] = "DeviceNo1/Ch1",
	[Ch2] = "DeviceNo1/Ch2",
	[Ch3] = "DeviceNo1/Ch3",
	[Ch4] = "DeviceNo1/Ch4",
	[Eff] = "DeviceNo1/Eff",
	[P1] = "DeviceNo1/P1",
	[P2] = "DeviceNo1/P2",
	[EnergyCh1] = "DeviceNo1/EnergyCH1",
	[EnergyCh2] = "DeviceNo1/EnergyCH2",
	[QCh1] = "DeviceNo1/Q_CH1",
	[QCh2] = "DeviceNo1/Q_CH2",
	[Temp] = "DeviceNo1/Temp"
};

const char * const DcSensor2Topics[TotalNumOfDcSensorTopics] = {
	[Ch1] = "DeviceNo2/Ch1",
	[Ch2] = "DeviceNo2/Ch2",
	[Ch3] = "DeviceNo2/Ch3",
	[Ch4] = "DeviceNo2/Ch4",
	[Eff] = "DeviceNo2/Eff",
	[P1] = "DeviceNo2/P1",
	[P2] = "DeviceNo2/P2",
	[EnergyCh1] = "DeviceNo2/EnergyCH1",
	[EnergyCh2] = "DeviceNo2/EnergyCH2",
	[QCh1] = "DeviceNo2/Q_CH1",
	[QCh2] = "DeviceNo2/Q_CH2",
	[Temp] = "DeviceNo2/Temp"
};

const char * const DcSensor3Topics[TotalNumOfDcSensorTopics] = {
	[Ch1] = "DeviceNo3/Ch1",
	[Ch2] = "DeviceNo3/Ch2",
	[Ch3] = "DeviceNo3/Ch3",
	[Ch4] = "DeviceNo3/Ch4",
	[Eff] = "DeviceNo3/Eff",
	[P1] = "DeviceNo3/P1",
	[P2] = "DeviceNo3/P2",
	[EnergyCh1] = "DeviceNo3/EnergyCH1",
	[EnergyCh2] = "DeviceNo3/EnergyCH2",
	[QCh1] = "DeviceNo3/Q_CH1",
	[QCh2] = "DeviceNo3/Q_CH2",
	[Temp] = "DeviceNo3/Temp"
};

const char * const DcSensor4Topics[TotalNumOfDcSensorTopics] = {
	[Ch1] = "DeviceNo4/Ch1",
	[Ch2] = "DeviceNo4/Ch2",
	[Ch3] = "DeviceNo4/Ch3",
	[Ch4] = "DeviceNo4/Ch4",
	[Eff] = "DeviceNo4/Eff",
	[P1] = "DeviceNo4/P1",
	[P2] = "DeviceNo4/P2",
	[EnergyCh1] = "DeviceNo4/EnergyCH1",
	[EnergyCh2] = "DeviceNo4/EnergyCH2",
	[QCh1] = "DeviceNo4/Q_CH1",
	[QCh2] = "DeviceNo4/Q_CH2",
	[Temp] = "DeviceNo4/Temp"
};

const char * const DcSensor5Topics[TotalNumOfDcSensorTopics] = {
	[Ch1] = "DeviceNo5/Ch1",
	[Ch2] = "DeviceNo5/Ch2",
	[Ch3] = "DeviceNo5/Ch3",
	[Ch4] = "DeviceNo5/Ch4",
	[Eff] = "DeviceNo5/Eff",
	[P1] = "DeviceNo5/P1",
	[P2] = "DeviceNo5/P2",
	[EnergyCh1] = "DeviceNo5/EnergyCH1",
	[EnergyCh2] = "DeviceNo5/EnergyCH2",
	[QCh1] = "DeviceNo5/Q_CH1",
	[QCh2] = "DeviceNo5/Q_CH2",
	[Temp] = "DeviceNo5/Temp"
};

const char * const ZamelTopics[TotalNumOfZamelTopics] = {
	[StateSupport] = "supla/devices/zamel.mew-01-104e6/channels/0/state/support",
	[StateTotalForwardActiveEnergy] = "supla/devices/zamel.mew-01-104e6/channels/0/state/total_forward_active_energy",
	[StateTotalReverseActiveEnergy] = "supla/devices/zamel.mew-01-104e6/channels/0/state/total_reverse_active_energy",
	[StateTotalForwardActiveEnergyBalanced] = "supla/devices/zamel.mew-01-104e6/channels/0/state/total_forward_active_energy_balanced",
	[StateTotalReverseActiveEnergyBalanced] = "supla/devices/zamel.mew-01-104e6/channels/0/state/total_reverse_active_energy_balanced",
	[Phases1TotalForwardActiveEnergy] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/total_forward_active_energy",
	[Phases1TotalReverseActiveEnergy] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/total_reverse_active_energy",
	[Phases1TotalForwardActiveEnergyBalanced] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/total_forward_active_energy_balaced",
	[Phases1TotalReverseActiveEnergyBalanced] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/total_reverse_active_energy_balanced",
	[Phases1Frequency] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/frequency",
	[Phases1Voltage] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/voltage",
	[Phases1Current] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/current",
	[Phases1PowerActive] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/power_active",
	[Phases1PowerReactive] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/power_reactive",
	[Phases1POwerApparent] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/power_apparent",
	[Phases1PowerFactor] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/power_factor",
	[Phases1PhaseAngle] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/phase_angle",
	[Phases2TotalForwardActiveEnergy] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/total_forward_active_energy",
	[Phases2TotalReverseActiveEnergy] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/total_reverse_active_energy",
	[Phases2TotalForwardActiveEnergyBalanced] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/total_forward_active_energy_balaced",
	[Phases2TotalReverseActiveEnergyBalanced] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/total_reverse_active_energy_balanced",
	[Phases2Frequency] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/frequency",
	[Phases2Voltage] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/voltage",
	[Phases2Current] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/current",
	[Phases2PowerActive] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/power_active",
	[Phases2PowerReactive] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/power_reactive",
	[Phases2POwerApparent] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/power_apparent",
	[Phases2PowerFactor] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/power_factor",
	[Phases2PhaseAngle] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/phase_angle",
	[Phases3TotalForwardActiveEnergy] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/total_forward_active_energy",
	[Phases3TotalReverseActiveEnergy] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/total_reverse_active_energy",
	[Phases3TotalForwardActiveEnergyBalanced] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/total_forward_active_energy_balaced",
	[Phases3TotalReverseActiveEnergyBalanced] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/total_reverse_active_energy_balanced",
	[Phases3Frequency] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/frequency",
	[Phases3Voltage] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/voltage",
	[Phases3Current] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/current",
	[Phases3PowerActive] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/power_active",
	[Phases3PowerReactive] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/power_reactive",
	[Phases3POwerApparent] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/power_apparent",
	[Phases3PowerFactor] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/power_factor",
	[Phases3PhaseAngle] = "supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/phase_angle"
};