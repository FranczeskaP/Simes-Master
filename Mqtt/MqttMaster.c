#include <mosquitto.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "MqttMaster.h"
#include "DataTypes.h"

#define IP	"192.168.1.103"
#define CA_FILE_DIR	("/etc/mosquitto/ca_certificates/ca1.crt")

struct mosquitto *master;
static uint8_t NotAllTopicsUpdated = 0u;

static void OnConnect(struct mosquitto *mosq, void *obj, int rc);
static void OnMessage(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg);

void MqttMainFunction(void)
{
	if(NotAllTopicsUpdated >= 5u)
	{
		printf("!!! ERROR !!! Not all sensors send data. !!! ERROR !!!\n");
		//todo Post with error data ?? 
    }
	 
}

void MqttInit(void)
{
	int id = 1;
	mosquitto_lib_init();
	master = mosquitto_new("master", true, &id);
	mosquitto_connect_callback_set(master, OnConnect);
	mosquitto_message_callback_set(master, OnMessage);
	if(mosquitto_tls_opts_set(master, 1, "tlsv1.1", NULL))
	{
		printf("Error2");
	}
	if(mosquitto_tls_set(master, CA_FILE_DIR, NULL, NULL, NULL, NULL))
	{
		printf("Error.");
	}
	if(mosquitto_connect(master, IP, 8883, 10))
	{
		printf("Could not connect");
	}
}

void ReadMqtt(void)
{
	mosquitto_loop_start(master);
    sleep(1);
	mosquitto_loop_stop(master, true);
}

bool CheckIfAllUpdated(void)
{
    for(uint8_t i = 0u; i < numOfDcSlaves; i++)
    {
        DcSensorData[i].allTopicsUpdated = true;
    }
	for(int i = 0; i < TotalNumOfDcSensorTopics; i++)
	{
		if(true != DcSensorData[slave0].DcSensorMqttData->topicUpdated[i])
		{
            DcSensorData[slave0].allTopicsUpdated = false;
		}
		else if(true != DcSensorData[slave1].DcSensorMqttData->topicUpdated[i])
		{
            DcSensorData[slave1].allTopicsUpdated = false;
		}
		else if(true != DcSensorData[slave2].DcSensorMqttData->topicUpdated[i])
		{
            DcSensorData[slave2].allTopicsUpdated = false;
		}
		else if(true != DcSensorData[slave3].DcSensorMqttData->topicUpdated[i])
		{
            DcSensorData[slave3].allTopicsUpdated = false;
		}
		else if(true != DcSensorData[slave4].DcSensorMqttData->topicUpdated[i])
		{
            DcSensorData[slave4].allTopicsUpdated = false;
		}
	}
	if((true == DcSensorData[slave0].allTopicsUpdated) && (true == DcSensorData[slave1].allTopicsUpdated) && 
	   (true == DcSensorData[slave2].allTopicsUpdated) && (true == DcSensorData[slave3].allTopicsUpdated) && 
       (true == DcSensorData[slave4].allTopicsUpdated))
	{
		for(int i = 0; i < TotalNumOfDcSensorTopics; i++)
		{
			DcSensorData[slave0].DcSensorMqttData->topicUpdated[i] = false;
			DcSensorData[slave1].DcSensorMqttData->topicUpdated[i] = false;
			DcSensorData[slave2].DcSensorMqttData->topicUpdated[i] = false;
			DcSensorData[slave3].DcSensorMqttData->topicUpdated[i] = false;
			DcSensorData[slave4].DcSensorMqttData->topicUpdated[i] = false;
		}
		return true;
	}
	else
	{
		NotAllTopicsUpdated++;
		return false;
	}
}


static void OnConnect(struct mosquitto *mosq, void *obj, int rc)
{
	for(int i = 0; i < TotalNumOfDcSensorTopics; i++)
	{
		for(uint8_t j = 0u; j < MAX_NUM_OF_SENSORS; j++)
		{
			if(DcSensorData[j].communicationProtocol == Mqtt)
			{
				mosquitto_subscribe(mosq, NULL, DcSensorData[j].DcSensorMqttData->topic[i], 0);
			}
		}
	}
}

static void OnMessage(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
	for(int i = 0; i < TotalNumOfDcSensorTopics; i++)
	{
		if(0 == strcmp(DcSensorData[slave0].DcSensorMqttData->topic[i], msg->topic))
		{
			DcSensorData[slave0].DcSensorMqttData->topicUpdated[i] = true;
            strcpy(DcSensorData[slave0].mqttReceivedData[i], msg->payload);
			break;
		}
		else if(0 == strcmp(DcSensorData[slave1].DcSensorMqttData->topic[i], msg->topic))
		{
			DcSensorData[slave1].DcSensorMqttData->topicUpdated[i] = true;
            strcpy(DcSensorData[slave1].mqttReceivedData[i], msg->payload);
			break;
		}
		else if(0 == strcmp(DcSensorData[slave2].DcSensorMqttData->topic[i], msg->topic))
		{
			DcSensorData[slave2].DcSensorMqttData->topicUpdated[i] = true;
            strcpy(DcSensorData[slave2].mqttReceivedData[i], msg->payload);
			break;
		}
		else if(0 == strcmp(DcSensorData[slave3].DcSensorMqttData->topic[i], msg->topic))
		{
			DcSensorData[slave3].DcSensorMqttData->topicUpdated[i] = true;
            strcpy(DcSensorData[slave3].mqttReceivedData[i], msg->payload);
			break;
		}
		else if(0 == strcmp(DcSensorData[slave4].DcSensorMqttData->topic[i], msg->topic))
		{
			DcSensorData[slave4].DcSensorMqttData->topicUpdated[i] = true;
            strcpy(DcSensorData[slave4].mqttReceivedData[i], msg->payload);
			break;
		}
	}
	printf("New message with topic %s: %s\n", msg->topic, (char*) msg->payload);
}

