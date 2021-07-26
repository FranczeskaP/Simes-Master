#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <curl/curl.h>
#include "cJSON.h"
 
CURL *curl;

static char * createStringToBePosted(DecodedData_t * decodedData);

uint16_t InitCurl(void)
{
    uint16_t returnValue = 1u;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    if(curl) 
    {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
        curl_easy_setopt(curl, CURLOPT_USERPWD, "rpi:R12345678"); 
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 4L);
        curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:8000/api/v1/data/");
        returnValue = 0u;
    }    
    CURLcode response;
    response = curl_easy_perform(curl);
    if(response != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(response));
    }
    return returnValue;
}

void PerformPost(DecodedData_t * decodedData)
{
    char * dataToPost = createStringToBePosted(decodedData);
    CURLcode response;
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(dataToPost)); 
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, dataToPost);
    response = curl_easy_perform(curl);
    if(response != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(response));
    }
}

void DeInitCurl(void)
{
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

static char * createStringToBePosted(DecodedData_t * decodedData)
{
    cJSON *data = cJSON_CreateObject();
    cJSON *sensor1 = cJSON_AddObjectToObject(data, "sensor1") ;

    if (sensor1 == NULL)
    {
        goto end;
    }

    if (cJSON_AddNumberToObject(sensor1, "voltage", decodedData[0].voltage1) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "current", decodedData[0].current1) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "power", decodedData[0].power1) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "energy", decodedData[0].power2) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "charge_cycles", decodedData[0].voltage2) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "temperature", decodedData[0].temperature) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "status", 1) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "error", 0) == NULL)
    {
        goto end;
    }
    cJSON *sensor2 = cJSON_AddObjectToObject(data, "sensor2") ;
    if (sensor2 == NULL)
    {
        goto end;
    }

    if (cJSON_AddNumberToObject(sensor2, "voltage", decodedData[0].voltage1) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "current", decodedData[0].current1) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "power", decodedData[0].power1) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "energy", decodedData[0].power2) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "charge_cycles", decodedData[0].voltage2) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "temperature", decodedData[0].temperature) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "status", 0) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "error", 1) == NULL)
    {
        goto end;
    }


    char *string = cJSON_Print(data);
    if (string == NULL)
    {
        fprintf(stderr, "Failed to print data.\n");
    }

end:
    cJSON_Delete(data);
    return string;
}
