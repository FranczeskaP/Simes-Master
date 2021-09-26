#include <mosquitto.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include "Mqtt.h"

#define IP	"192.168.1.103"

struct mosquitto *master;
void on_connect(struct mosquitto *mosq, void *obj, int rc)
{
	for(int i = 0; i < TotalNumOfDcSensorTopics; i++)
	{
		mosquitto_subscribe(mosq, NULL, DcSensor1Topics[i], 0);
		mosquitto_subscribe(mosq, NULL, DcSensor2Topics[i], 0);
		mosquitto_subscribe(mosq, NULL, DcSensor3Topics[i], 0);
		mosquitto_subscribe(mosq, NULL, DcSensor4Topics[i], 0);
		mosquitto_subscribe(mosq, NULL, DcSensor5Topics[i], 0);
	}
	for(int i = 0; i < TotalNumOfZamelTopics; i++)
	{
		mosquitto_subscribe(mosq, NULL, ZamelTopics[i], 0);
	}
}

void on_message(struct mosquitto *mosq, void *obj, const struct mosquitto_message *msg)
{
	printf("New message with topis %s: %s\n", msg->topic, (char*) msg->payload);
}


static void SchedulerCalled(int signum)
{
    printf("We're in sceduler\n");

	mosquitto_loop_start(master);
    sleep(1);
	mosquitto_loop_stop(master, true);
    alarm(5);
}

void SwitchToMqtt(void)
{
    signal(SIGALRM, SchedulerCalled);
    alarm(5);
	int id = 1, id1 = 2;
	mosquitto_lib_init();
	master = mosquitto_new("master", true, &id);
	mosquitto_connect_callback_set(master, on_connect);
	mosquitto_message_callback_set(master, on_message);
	if(mosquitto_tls_opts_set(master, 1, "tlsv1.2", NULL))
	{
		printf("Error2");
	}
	int *p = NULL;
	if(mosquitto_tls_set(master, "/etc/mosquitto/ca_certificates/ca1.crt", NULL, NULL, NULL, NULL))
	{
		printf("Error.");
	}

	if(mosquitto_connect(master, IP, 8883, 10))
	{
		printf("Could not connect");
	}
	while(1)
    {
        sleep(1);
        printf(".\n");
    }
	 
}
