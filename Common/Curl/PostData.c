#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <curl/curl.h>
#include "PostData.h"
#include "cJSON.h"
 
CURL *curl;

void InitCurl(void)
{
    curl_global_init(CURL_GLOBAL_ALL);
}

char * CreateStringToBePostedModbus(DcDecodedData_t decodedData[numOfDcSlaves])
{
    /* todo update
    cJSON *data = cJSON_CreateObject();
    for(int i = 0; i<numOfDcSlaves; i++)
    {
        cJSON *sensorDc = cJSON_AddObjectToObject(data, decodedData[i].name);
        if (sensorDc == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensorDc, "voltage", decodedData[i].voltage) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensorDc, "current", decodedData[i].current) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensorDc, "power", decodedData[i].power) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensorDc, "temperature", decodedData[i].temperature) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensorDc, "energy", decodedData[i].energy) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensorDc, "charge", decodedData[i].electricCharge) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensorDc, "status", decodedData[i].efficiency) == NULL)
        {
            goto end;
        }
        if (cJSON_AddNumberToObject(sensorDc, "error", 0) == NULL)
        {
            goto end;
        }
    }
    //todo add Zamel to Posting data

    char *string = cJSON_Print(data);
    if (string == NULL)
    {
        fprintf(stderr, "Failed to print data.\n");
    }

end:
    cJSON_Delete(data);
    return string; */
    return "";
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

