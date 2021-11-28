#include <mosquitto.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "MqttMaster.h"
#include "Configuration.h"

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
	bool DcSensor1Updated = true;
	bool DcSensor2Updated = true;
	bool DcSensor3Updated = true;
	bool DcSensor4Updated = true;
	bool DcSensor5Updated = true;
	for(int i = 0; i < TotalNumOfDcSensorTopics; i++)
	{
		if(true != DcSensor1[i].topicUpdated)
		{
			DcSensor1Updated = false;
		}
		else if(true != DcSensor2[i].topicUpdated)
		{
			DcSensor2Updated = false;
		}
		else if(true != DcSensor3[i].topicUpdated)
		{
			DcSensor3Updated = false;
		}
		else if(true != DcSensor4[i].topicUpdated)
		{
			DcSensor4Updated = false;
		}
		else if(true != DcSensor5[i].topicUpdated)
		{
			DcSensor5Updated = false;
		}
	}
	if((true == DcSensor1Updated) && (true == DcSensor2Updated) && 
	   (true == DcSensor3Updated) && (true == DcSensor4Updated) && (true == DcSensor5Updated))
	{
		for(int i = 0; i < TotalNumOfDcSensorTopics; i++)
		{
			DcSensor1[i].topicUpdated = false;
			DcSensor2[i].topicUpdated = false;
			DcSensor3[i].topicUpdated = false;
			DcSensor4[i].topicUpdated = false;
			DcSensor5[i].topicUpdated = false;
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
			if((configurationData[j].communicationProtocol == Mqtt) && (!configurationData[j].acSensor))
			{
				mosquitto_subscribe(mosq, NULL, DcSensor1[i].topic, 0);
			}
		}
	}
}

static void OnMessage(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
	for(int i = 0; i < TotalNumOfDcSensorTopics; i++)
	{
		if(msg->topic == DcSensor1[i].topic)
		{
			DcSensor1[i].topicUpdated = true;
			DcReceivedData[0].mqttReceivedData[i] = (char*)msg->payload;
			break;
		}
		else if(msg->topic == DcSensor2[i].topic)
		{
			DcSensor2[i].topicUpdated = true;
			DcReceivedData[1].mqttReceivedData[i] = (char*)msg->payload;
			break;
		}
		else if(msg->topic == DcSensor3[i].topic)
		{
			DcSensor3[i].topicUpdated = true;
			DcReceivedData[2].mqttReceivedData[i] = (char*)msg->payload;
			break;
		}
		else if(msg->topic == DcSensor4[i].topic)
		{
			DcSensor4[i].topicUpdated = true;
			DcReceivedData[3].mqttReceivedData[i] = (char*)msg->payload;
			break;
		}
		else if(msg->topic == DcSensor5[i].topic)
		{
			DcSensor5[i].topicUpdated = true;
			DcReceivedData[4].mqttReceivedData[i] = (char*)msg->payload;
			break;
		}
	}
	printf("New message with topic %s: %s\n", msg->topic, (char*) msg->payload);
}

