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

static void OnConnect(struct mosquitto *mosq, void *obj, int rc)
{
	for(int i = 0; i < TotalNumOfDcSensorTopics; i++)
	{
		for(uint8_t j = 0u; j < MAX_NUM_OF_SENSORS; j++)
		{
			if(DcSensorData[j].communicationProtocol == Mqtt)
			{
				mosquitto_subscribe(mosq, NULL, DcSensorData[j].DcSensorMqttData[i].topic, 0);
			}
		}
	}
}

static void OnMessage(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
	for(int i = 0; i < TotalNumOfDcSensorTopics; i++)
	{
		if(0 == strcmp(DcSensorData[slave0].DcSensorMqttData[i].topic, msg->topic))
		{
			DcSensorData[slave0].DcSensorMqttData[i].topicUpdated = true;
            strcpy(DcSensorData[slave0].mqttReceivedData[i], msg->payload);
			break;
		}
		else if(0 == strcmp(DcSensorData[slave1].DcSensorMqttData[i].topic, msg->topic))
		{
			DcSensorData[slave1].DcSensorMqttData[i].topicUpdated = true;
            strcpy(DcSensorData[slave1].mqttReceivedData[i], msg->payload);
			break;
		}
		else if(0 == strcmp(DcSensorData[slave2].DcSensorMqttData[i].topic, msg->topic))
		{
			DcSensorData[slave2].DcSensorMqttData[i].topicUpdated = true;
            strcpy(DcSensorData[slave2].mqttReceivedData[i], msg->payload);
			break;
		}
		else if(0 == strcmp(DcSensorData[slave3].DcSensorMqttData[i].topic, msg->topic))
		{
			DcSensorData[slave3].DcSensorMqttData[i].topicUpdated = true;
            strcpy(DcSensorData[slave3].mqttReceivedData[i], msg->payload);
			break;
		}
		else if(0 == strcmp(DcSensorData[slave4].DcSensorMqttData[i].topic, msg->topic))
		{
			DcSensorData[slave4].DcSensorMqttData[i].topicUpdated = true;
            strcpy(DcSensorData[slave4].mqttReceivedData[i], msg->payload);
			break;
		}
	}
	printf("New message with topic %s: %s\n", msg->topic, (char*) msg->payload);
}

