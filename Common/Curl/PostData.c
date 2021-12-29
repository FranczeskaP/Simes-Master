#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <curl/curl.h>
#include "PostData.h"
#include "cJSON.h"
#include "DataTypes.h"
 
CURL *curl;
static char* SensorNames[6] = {"acdc_sensor_data", "dc_sensor1_data", "dc_sensor2pv_data",
                               "dc_sensor3liion_data", "dc_sensor4scap_data", "dc_sensor5charger_data"};

void InitCurl(void)
{
    curl_global_init(CURL_GLOBAL_ALL);
}

void PerformPost(char * dataToPost)
{   
    CURL *curl = curl_easy_init();
    if(curl) 
    {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
        curl_easy_setopt(curl, CURLOPT_USERPWD, "rpi:R12345678"); 
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8000/api/v1/data/");
    }
    CURLcode response;
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(dataToPost)); 
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dataToPost);
    response = curl_easy_perform(curl);
    if(response != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(response));
    }
    curl_easy_cleanup(curl);
}

void DeInitCurl(void)
{
    curl_global_cleanup();
}

char * CreateStringToBePosted(void)
{
    cJSON *data = cJSON_CreateObject();
    /*Sensor Ac */
    cJSON *sensorAc = cJSON_AddObjectToObject(data, SensorNames[0u]);
    if (sensorAc == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorAc, "voltage1Rms", AcSensorData.acDecodedData.voltage1Rms) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorAc, "voltage2Rms", AcSensorData.acDecodedData.voltage2Rms) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorAc, "voltage3Rms", AcSensorData.acDecodedData.voltage3Rms) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorAc, "current1Rms", AcSensorData.acDecodedData.current1Rms) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorAc, "current2Rms", AcSensorData.acDecodedData.current2Rms) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorAc, "current3Rms", AcSensorData.acDecodedData.current3Rms) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorAc, "pPower", AcSensorData.acDecodedData.pPower) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorAc, "qPower", AcSensorData.acDecodedData.qPower) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorAc, "sPower", AcSensorData.acDecodedData.sPower) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorAc, "pEnergy", AcSensorData.acDecodedData.pEnergy) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorAc, "qEnergy", AcSensorData.acDecodedData.qEnergy) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorAc, "currentThd", AcSensorData.acDecodedData.currentThd) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorAc, "voltageThd", AcSensorData.acDecodedData.voltageThd) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorAc, "powerCos", AcSensorData.acDecodedData.powerCos) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorAc, "frequence", AcSensorData.acDecodedData.frequence) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorAc, "status", AcSensorData.acDecodedData.status) == NULL) goto end;

    /*Sensor Dc1 */
    cJSON *sensorDc1 = cJSON_AddObjectToObject(data, SensorNames[1u]);
    if (sensorDc1 == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc1, "voltageCh1", DcSensorData[1u].dcDecodedData.voltageCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc1, "currentCh1", DcSensorData[1u].dcDecodedData.currentCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc1, "powerDcCh1", DcSensorData[1u].dcDecodedData.pPowerCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc1, "energyDcCh1", DcSensorData[1u].dcDecodedData.energyCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc1, "statusCh1", DcSensorData[1u].dcDecodedData.statusCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc1, "temperatureCh1", DcSensorData[1u].dcDecodedData.temperatureCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc1, "voltageCh2", DcSensorData[1u].dcDecodedData.voltageCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc1, "currentCh2", DcSensorData[1u].dcDecodedData.currentCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc1, "powerDcCh2", DcSensorData[1u].dcDecodedData.pPowerCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc1, "energyDcCh2", DcSensorData[1u].dcDecodedData.energyCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc1, "statusCh2", DcSensorData[1u].dcDecodedData.statusCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc1, "temperatureCh2", DcSensorData[1u].dcDecodedData.temperatureCh2) == NULL) goto end;

    /*Sensor Dc2 */
    cJSON *sensorDc2 = cJSON_AddObjectToObject(data, SensorNames[2u]);
    if (sensorDc2 == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc2, "voltageCh1", DcSensorData[1u].dcDecodedData.voltageCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc2, "currentCh1", DcSensorData[2u].dcDecodedData.currentCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc2, "powerDcCh1", DcSensorData[2u].dcDecodedData.pPowerCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc2, "energyDcCh1", DcSensorData[2u].dcDecodedData.energyCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc2, "statusCh1", DcSensorData[2u].dcDecodedData.statusCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc2, "temperatureCh1", DcSensorData[2u].dcDecodedData.temperatureCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc2, "voltageCh2", DcSensorData[2u].dcDecodedData.voltageCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc2, "currentCh2", DcSensorData[2u].dcDecodedData.currentCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc2, "powerDcCh2", DcSensorData[2u].dcDecodedData.pPowerCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc2, "energyDcCh2", DcSensorData[2u].dcDecodedData.energyCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc2, "statusCh2", DcSensorData[2u].dcDecodedData.statusCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc2, "temperatureCh2", DcSensorData[2u].dcDecodedData.temperatureCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc2, "lighting", DcSensorData[2u].dcDecodedData.insolation) == NULL) goto end;

    /*Sensor Dc3 */
    cJSON *sensorDc3 = cJSON_AddObjectToObject(data, SensorNames[3u]);
    if (sensorDc3 == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc3, "voltageCh1", DcSensorData[1u].dcDecodedData.voltageCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc3, "currentCh1", DcSensorData[3u].dcDecodedData.currentCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc3, "powerDcCh1", DcSensorData[3u].dcDecodedData.pPowerCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc3, "energyDcCh1", DcSensorData[3u].dcDecodedData.energyCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc3, "statusCh1", DcSensorData[3u].dcDecodedData.statusCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc3, "temperatureCh1", DcSensorData[3u].dcDecodedData.temperatureCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc3, "charge", 0) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc3, "cycles", 0) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc3, "voltageCh2", DcSensorData[3u].dcDecodedData.voltageCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc3, "currentCh2", DcSensorData[3u].dcDecodedData.currentCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc3, "powerDcCh2", DcSensorData[3u].dcDecodedData.pPowerCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc3, "energyDcCh2", DcSensorData[3u].dcDecodedData.energyCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc3, "statusSoh", DcSensorData[3u].dcDecodedData.statusCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc3, "temperatureCh2", DcSensorData[3u].dcDecodedData.temperatureCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc3, "soc", 0) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc3, "capacity", 0) == NULL) goto end;

    /*Sensor Dc4 */
    cJSON *sensorDc4 = cJSON_AddObjectToObject(data, SensorNames[4u]);
    if (sensorDc4 == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc4, "voltageCh1", DcSensorData[1u].dcDecodedData.voltageCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc4, "currentCh1", DcSensorData[4u].dcDecodedData.currentCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc4, "powerDcCh1", DcSensorData[4u].dcDecodedData.pPowerCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc4, "energyDcCh1", DcSensorData[4u].dcDecodedData.energyCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc4, "statusCh1", DcSensorData[4u].dcDecodedData.statusCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc4, "temperatureCh1", DcSensorData[4u].dcDecodedData.temperatureCh1) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc4, "charge", 0) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc4, "cycles", 0) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc4, "voltageCh2", DcSensorData[4u].dcDecodedData.voltageCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc4, "currentCh2", DcSensorData[4u].dcDecodedData.currentCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc4, "powerDcCh2", DcSensorData[4u].dcDecodedData.pPowerCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc4, "energyDcCh2", DcSensorData[4u].dcDecodedData.energyCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc4, "statusSoh", DcSensorData[4u].dcDecodedData.statusCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc4, "temperatureCh2", DcSensorData[4u].dcDecodedData.temperatureCh2) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc4, "soc", 0) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc4, "capacity", 0) == NULL) goto end;

    /*Sensor Dc5 */
    cJSON *sensorDc5 = cJSON_AddObjectToObject(data, SensorNames[5u]);
    if (sensorDc5 == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc5, "voltageCh1", DcSensorData[1u].dcDecodedDataCh1.voltage) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc5, "currentCh1", DcSensorData[5u].dcDecodedDataCh1.current) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc5, "powerDcCh1", DcSensorData[5u].dcDecodedDataCh1.power) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc5, "energyDcCh1", DcSensorData[5u].dcDecodedDataCh1.energy) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc5, "statusCh1", 0) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc5, "temperatureCh1", DcSensorData[5u].dcDecodedDataCh1.temperature) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc5, "charge", 0) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc5, "voltageCh2", DcSensorData[5u].dcDecodedDataCh2.voltage) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc5, "currentCh2", DcSensorData[5u].dcDecodedDataCh2.current) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc5, "powerDcCh2", DcSensorData[5u].dcDecodedDataCh2.power) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc5, "energyDcCh2", DcSensorData[5u].dcDecodedDataCh2.energy) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc5, "status", 0) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc5, "temperatureCh2", DcSensorData[5u].dcDecodedDataCh2.temperature) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc5, "soc", 0) == NULL) goto end;
    if (cJSON_AddNumberToObject(sensorDc5, "capacity", 0) == NULL) goto end;

    char *string = cJSON_Print(data);
    printf("%s", string);
    if (string == NULL)
    {
        fprintf(stderr, "Failed to print data.\n");
    }

end:
    cJSON_Delete(data);
    return string;
}



