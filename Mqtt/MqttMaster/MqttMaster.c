#include <mosquitto.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "Decoder.h"
#include "MqttMaster.h"

#define IP	"192.168.1.103"
#define CA_FILE_DIR	("/etc/mosquitto/ca_certificates/ca1.crt")

struct mosquitto *master;
static bool MeassagesReceived = FALSE;
static uint8_t NotAllTopicsUpdated = 0u;

static void OnConnect(struct mosquitto *mosq, void *obj, int rc);
static void OnMessage(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg);
static void MqttSchedulerCalled(int signum);
static bool CheckIfAllUpdated(void);
static void MqttInit(void);

void MqttMainFunction(void)
{
	bool allSensorsUpdated = FALSE;
    signal(SIGALRM, MqttSchedulerCalled);
    alarm(5);
	MqttInit();
	while(1)
    {
		if(MeassagesReceived)
		{
			MeassagesReceived = FALSE;
			if(CheckIfAllUpdated())
			{
				//todo PostMqtt
			}
		}
        sleep(1);
        printf(".\n");
		if(NotAllTopicsUpdated >= 5u)
		{
			printf("!!! ERROR !!! Not all sensors send data. !!! ERROR !!!\n");
			//todo Post with error data ?? 
		}
    }
	 
}

static void OnConnect(struct mosquitto *mosq, void *obj, int rc)
{
	for(int i = 0; i < TotalNumOfDcSensorTopics; i++)
	{
		mosquitto_subscribe(mosq, NULL, DcSensor1[i].topic, 0);
		mosquitto_subscribe(mosq, NULL, DcSensor2[i].topic, 0);
		mosquitto_subscribe(mosq, NULL, DcSensor3[i].topic, 0);
		mosquitto_subscribe(mosq, NULL, DcSensor4[i].topic, 0);
		mosquitto_subscribe(mosq, NULL, DcSensor5[i].topic, 0);
	}
}

static void OnMessage(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
	for(int i = 0; i < TotalNumOfDcSensorTopics; i++)
	{
		if(msg->topic == DcSensor1[i].topic)
		{
			DcSensor1[i].topicUpdated = TRUE;
			DcSensor1[i].data = (char*)msg->payload;
			break;
		}
		else if(msg->topic == DcSensor2[i].topic)
		{
			DcSensor2[i].topicUpdated = TRUE;
			DcSensor2[i].data = (char*)msg->payload;
			break;
		}
		else if(msg->topic == DcSensor3[i].topic)
		{
			DcSensor3[i].topicUpdated = TRUE;
			DcSensor3[i].data = (char*)msg->payload;
			break;
		}
		else if(msg->topic == DcSensor4[i].topic)
		{
			DcSensor4[i].topicUpdated = TRUE;
			DcSensor4[i].data = (char*)msg->payload;
			break;
		}
		else if(msg->topic == DcSensor5[i].topic)
		{
			DcSensor5[i].topicUpdated = TRUE;
			DcSensor5[i].data = (char*)msg->payload;
			break;
		}
	}
	printf("New message with topic %s: %s\n", msg->topic, (char*) msg->payload);
}


static void MqttSchedulerCalled(int signum)
{
    printf("We're in sceduler\n");
	MeassagesReceived = TRUE;
	mosquitto_loop_start(master);
    sleep(1);
	mosquitto_loop_stop(master, TRUE);
    alarm(5);
}

static bool CheckIfAllUpdated(void)
{
	bool DcSensor1Updated = TRUE;
	bool DcSensor2Updated = TRUE;
	bool DcSensor3Updated = TRUE;
	bool DcSensor4Updated = TRUE;
	bool DcSensor5Updated = TRUE;
	for(int i = 0; i < TotalNumOfDcSensorTopics; i++)
	{
		if(TRUE != DcSensor1[i].topicUpdated)
		{
			DcSensor1Updated = FALSE;
		}
		else if(TRUE != DcSensor2[i].topicUpdated)
		{
			DcSensor2Updated = FALSE;
		}
		else if(TRUE != DcSensor3[i].topicUpdated)
		{
			DcSensor3Updated = FALSE;
		}
		else if(TRUE != DcSensor4[i].topicUpdated)
		{
			DcSensor4Updated = FALSE;
		}
		else if(TRUE != DcSensor5[i].topicUpdated)
		{
			DcSensor5Updated = FALSE;
		}
	}
	if((TRUE == DcSensor1Updated) && (TRUE == DcSensor2Updated) && 
	   (TRUE == DcSensor3Updated) && (TRUE == DcSensor4Updated) && (TRUE == DcSensor5Updated))
	{
		for(int i = 0; i < TotalNumOfDcSensorTopics; i++)
		{
			DcSensor1[i].topicUpdated = FALSE;
			DcSensor2[i].topicUpdated = FALSE;
			DcSensor3[i].topicUpdated = FALSE;
			DcSensor4[i].topicUpdated = FALSE;
			DcSensor5[i].topicUpdated = FALSE;
		}
		return TRUE;
	}
	else
	{
		NotAllTopicsUpdated++;
		return FALSE;
	}
}

static void MqttInit(void)
{
	int id = 1;
	mosquitto_lib_init();
	master = mosquitto_new("master", TRUE, &id);
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
