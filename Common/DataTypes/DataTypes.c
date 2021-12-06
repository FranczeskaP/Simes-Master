#include "DataTypes.h"

MqttStruct_t DcSensor1[TotalNumOfDcSensorTopics] = {
    [Ch1] = {"DeviceNo1/Ch1", false},
    [Ch2] = {"DeviceNo1/Ch2", false},
    [Ch3] = {"DeviceNo1/Ch3", false},
    [Ch4] = {"DeviceNo1/Ch4", false},
    [Eff] = {"DeviceNo1/Eff", false},
    [P1] = {"DeviceNo1/P1", false},
    [P2] = {"DeviceNo1/P2", false},
    [EnergyCh1] = {"DeviceNo1/EnergyCH1", false},
    [EnergyCh2] = {"DeviceNo1/EnergyCH2", false},
    [QCh1] = {"DeviceNo1/Q_CH1", false},
    [QCh2] = {"DeviceNo1/Q_CH2", false},
    [Temp] = {"DeviceNo1/Temp", false}
};

MqttStruct_t DcSensor2[TotalNumOfDcSensorTopics] = {
    [Ch1] = {"DeviceNo2/Ch1", false},
    [Ch2] = {"DeviceNo2/Ch2", false},
    [Ch3] = {"DeviceNo2/Ch3", false},
    [Ch4] = {"DeviceNo2/Ch4", false},
    [Eff] = {"DeviceNo2/Eff", false},
    [P1] = {"DeviceNo2/P1", false},
    [P2] = {"DeviceNo2/P2", false},
    [EnergyCh1] = {"DeviceNo2/EnergyCH1", false},
    [EnergyCh2] = {"DeviceNo2/EnergyCH2", false},
    [QCh1] = {"DeviceNo2/Q_CH1", false},
    [QCh2] = {"DeviceNo2/Q_CH2", false},
    [Temp] = {"DeviceNo2/Temp", false}
};

MqttStruct_t DcSensor3[TotalNumOfDcSensorTopics] = {
    [Ch1] = {"DeviceNo3/Ch1", false},
    [Ch2] = {"DeviceNo3/Ch2", false},
    [Ch3] = {"DeviceNo3/Ch3", false},
    [Ch4] = {"DeviceNo3/Ch4", false},
    [Eff] = {"DeviceNo3/Eff", false},
    [P1] = {"DeviceNo3/P1", false},
    [P2] = {"DeviceNo3/P2", false},
    [EnergyCh1] = {"DeviceNo3/EnergyCH1", false},
    [EnergyCh2] = {"DeviceNo3/EnergyCH2", false},
    [QCh1] = {"DeviceNo3/Q_CH1", false},
    [QCh2] = {"DeviceNo3/Q_CH2", false},
    [Temp] = {"DeviceNo3/Temp", false}
};

MqttStruct_t DcSensor4[TotalNumOfDcSensorTopics] = {
    [Ch1] = {"DeviceNo4/Ch1", false},
    [Ch2] = {"DeviceNo4/Ch2", false},
    [Ch3] = {"DeviceNo4/Ch3", false},
    [Ch4] = {"DeviceNo4/Ch4", false},
    [Eff] = {"DeviceNo4/Eff", false},
    [P1] = {"DeviceNo4/P1", false},
    [P2] = {"DeviceNo4/P2", false},
    [EnergyCh1] = {"DeviceNo4/EnergyCH1", false},
    [EnergyCh2] = {"DeviceNo4/EnergyCH2", false},
    [QCh1] = {"DeviceNo4/Q_CH1", false},
    [QCh2] = {"DeviceNo4/Q_CH2", false},
    [Temp] = {"DeviceNo4/Temp", false}
};

MqttStruct_t DcSensor5[TotalNumOfDcSensorTopics] = {
    [Ch1] = {"DeviceNo5/Ch1", false},
    [Ch2] = {"DeviceNo5/Ch2", false},
    [Ch3] = {"DeviceNo5/Ch3", false},
    [Ch4] = {"DeviceNo5/Ch4", false},
    [Eff] = {"DeviceNo5/Eff", false},
    [P1] = {"DeviceNo5/P1", false},
    [P2] = {"DeviceNo5/P2", false},
    [EnergyCh1] = {"DeviceNo5/EnergyCH1", false},
    [EnergyCh2] = {"DeviceNo5/EnergyCH2", false},
    [QCh1] = {"DeviceNo5/Q_CH1", false},
    [QCh2] = {"DeviceNo5/Q_CH2", false},
    [Temp] = {"DeviceNo5/Temp", false}
};

DcSensorData_t DcSensorData[numOfDcSlaves] = {
    [slave0] = {
        .dcSensorMqttData = {
        [Ch1] = {"DeviceNo1/Ch1", false},
        [Ch2] = {"DeviceNo1/Ch2", false},
        [Ch3] = {"DeviceNo1/Ch3", false},
        [Ch4] = {"DeviceNo1/Ch4", false},
        [Eff] = {"DeviceNo1/Eff", false},
        [P1] = {"DeviceNo1/P1", false},
        [P2] = {"DeviceNo1/P2", false},
        [EnergyCh1] = {"DeviceNo1/EnergyCH1", false},
        [EnergyCh2] = {"DeviceNo1/EnergyCH2", false},
        [QCh1] = {"DeviceNo1/Q_CH1", false},
        [QCh2] = {"DeviceNo1/Q_CH2", false},
        [Temp] = {"DeviceNo1/Temp", false}
        }, 
        .allTopicsUpdated = false,
        .updated = false
    },
    [slave1] = {
        .dcSensorMqttData = {
        [Ch1] = {"DeviceNo2/Ch1", false},
        [Ch2] = {"DeviceNo2/Ch2", false},
        [Ch3] = {"DeviceNo2/Ch3", false},
        [Ch4] = {"DeviceNo2/Ch4", false},
        [Eff] = {"DeviceNo2/Eff", false},
        [P1] = {"DeviceNo2/P1", false},
        [P2] = {"DeviceNo2/P2", false},
        [EnergyCh1] = {"DeviceNo2/EnergyCH1", false},
        [EnergyCh2] = {"DeviceNo2/EnergyCH2", false},
        [QCh1] = {"DeviceNo2/Q_CH1", false},
        [QCh2] = {"DeviceNo2/Q_CH2", false},
        [Temp] = {"DeviceNo2/Temp", false}
        }, 
        .allTopicsUpdated = false,
        .updated = false
    },
    [slave2] = {
        .dcSensorMqttData = {
        [Ch1] = {"DeviceNo3/Ch1", false},
        [Ch2] = {"DeviceNo3/Ch2", false},
        [Ch3] = {"DeviceNo3/Ch3", false},
        [Ch4] = {"DeviceNo3/Ch4", false},
        [Eff] = {"DeviceNo3/Eff", false},
        [P1] = {"DeviceNo3/P1", false},
        [P2] = {"DeviceNo3/P2", false},
        [EnergyCh1] = {"DeviceNo3/EnergyCH1", false},
        [EnergyCh2] = {"DeviceNo3/EnergyCH2", false},
        [QCh1] = {"DeviceNo3/Q_CH1", false},
        [QCh2] = {"DeviceNo3/Q_CH2", false},
        [Temp] = {"DeviceNo3/Temp", false}
        }, 
        .allTopicsUpdated = false,
        .updated = false
    },
    [slave3] = {
        .dcSensorMqttData = {
        [Ch1] = {"DeviceNo4/Ch1", false},
        [Ch2] = {"DeviceNo4/Ch2", false},
        [Ch3] = {"DeviceNo4/Ch3", false},
        [Ch4] = {"DeviceNo4/Ch4", false},
        [Eff] = {"DeviceNo4/Eff", false},
        [P1] = {"DeviceNo4/P1", false},
        [P2] = {"DeviceNo4/P2", false},
        [EnergyCh1] = {"DeviceNo4/EnergyCH1", false},
        [EnergyCh2] = {"DeviceNo4/EnergyCH2", false},
        [QCh1] = {"DeviceNo4/Q_CH1", false},
        [QCh2] = {"DeviceNo4/Q_CH2", false},
        [Temp] = {"DeviceNo4/Temp", false}
        }, 
        .allTopicsUpdated = false,
        .updated = false
    },
    [slave4] = {
        .dcSensorMqttData = {
        [Ch1] = {"DeviceNo5/Ch1", false},
        [Ch2] = {"DeviceNo5/Ch2", false},
        [Ch3] = {"DeviceNo5/Ch3", false},
        [Ch4] = {"DeviceNo5/Ch4", false},
        [Eff] = {"DeviceNo5/Eff", false},
        [P1] = {"DeviceNo5/P1", false},
        [P2] = {"DeviceNo5/P2", false},
        [EnergyCh1] = {"DeviceNo5/EnergyCH1", false},
        [EnergyCh2] = {"DeviceNo5/EnergyCH2", false},
        [QCh1] = {"DeviceNo5/Q_CH1", false},
        [QCh2] = {"DeviceNo5/Q_CH2", false},
        [Temp] = {"DeviceNo5/Temp", false}
        }, 
        .allTopicsUpdated = false,
        .updated = false
    }
};

AcSensorData_t AcSensorData = {
    .acSensorMqttData = {
    [StateSupport] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/support", false},
    [StateTotalForwardActiveEnergy] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/total_forward_active_energy", false},
    [StateTotalReverseActiveEnergy] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/total_reverse_active_energy", false},
    [StateTotalForwardActiveEnergyBalanced] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/total_forward_active_energy_balanced", false},
    [StateTotalReverseActiveEnergyBalanced] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/total_reverse_active_energy_balanced", false},
    [Phases1TotalForwardActiveEnergy] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/total_forward_active_energy", false},
    [Phases1TotalReverseActiveEnergy] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/total_reverse_active_energy", false},
    [Phases1TotalForwardActiveEnergyBalanced] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/total_forward_active_energy_balaced", false},
    [Phases1TotalReverseActiveEnergyBalanced] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/total_reverse_active_energy_balanced", false},
    [Phases1Frequency] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/frequency", false},
    [Phases1Voltage] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/voltage", false},
    [Phases1Current] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/current", false},
    [Phases1PowerActive] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/power_active", false},
    [Phases1PowerReactive] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/power_reactive", false},
    [Phases1POwerApparent] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/power_apparent", false},
    [Phases1PowerFactor] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/power_factor", false},
    [Phases1PhaseAngle] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/1/phase_angle", false},
    [Phases2TotalForwardActiveEnergy] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/total_forward_active_energy", false},
    [Phases2TotalReverseActiveEnergy] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/total_reverse_active_energy", false},
    [Phases2TotalForwardActiveEnergyBalanced] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/total_forward_active_energy_balaced", false},
    [Phases2TotalReverseActiveEnergyBalanced] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/total_reverse_active_energy_balanced", false},
    [Phases2Frequency] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/frequency", false},
    [Phases2Voltage] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/voltage", false},
    [Phases2Current] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/current", false},
    [Phases2PowerActive] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/power_active", false},
    [Phases2PowerReactive] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/power_reactive", false},
    [Phases2POwerApparent] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/power_apparent", false},
    [Phases2PowerFactor] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/power_factor", false},
    [Phases2PhaseAngle] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/2/phase_angle", false},
    [Phases3TotalForwardActiveEnergy] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/total_forward_active_energy", false},
    [Phases3TotalReverseActiveEnergy] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/total_reverse_active_energy", false},
    [Phases3TotalForwardActiveEnergyBalanced] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/total_forward_active_energy_balaced", false},
    [Phases3TotalReverseActiveEnergyBalanced] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/total_reverse_active_energy_balanced", false},
    [Phases3Frequency] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/frequency", false},
    [Phases3Voltage] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/voltage", false},
    [Phases3Current] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/current", false},
    [Phases3PowerActive] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/power_active", false},
    [Phases3PowerReactive] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/power_reactive", false},
    [Phases3POwerApparent] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/power_apparent", false},
    [Phases3PowerFactor] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/power_factor", false},
    [Phases3PhaseAngle] = {"supla/devices/zamel.mew-01-104e6/channels/0/state/phases/3/phase_angle", false}
    },
    .updated = false,
    .allTopicsUpdated = false
};
