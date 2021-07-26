#include "cJSON.h"
#include "PostData.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <fcntl.h>

//NOTE: Returns a heap allocated string, you are required to free it after use.
char *create_monitor_with_helpers(void)
{
    cJSON *monitor = cJSON_CreateObject();
    cJSON *sensor1 = cJSON_AddObjectToObject(monitor, "sensor1") ;

    if (sensor1 == NULL)
    {
        goto end;
    }

    if (cJSON_AddNumberToObject(sensor1, "voltage", 30) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "current", 30) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "power", 30) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "energy", 30) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "charge_cycles", 30) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor1, "temperature", 30) == NULL)
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
    cJSON *sensor2 = cJSON_AddObjectToObject(monitor, "sensor2") ;
    if (sensor2 == NULL)
    {
        goto end;
    }

    if (cJSON_AddNumberToObject(sensor2, "voltage", 30) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "current", 30) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "power", 30) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "energy", 30) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "charge_cycles", 30) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "temperature", 30) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "status", 1) == NULL)
    {
        goto end;
    }
    if (cJSON_AddNumberToObject(sensor2, "error", 0) == NULL)
    {
        goto end;
    }


    char *string = cJSON_Print(monitor);
    if (string == NULL)
    {
        fprintf(stderr, "Failed to print monitor.\n");
    }

end:
    cJSON_Delete(monitor);
    return string;
}

int main()
{
    char * sting = create_monitor_with_helpers();
    FILE *fp;

    //fp = fopen("../test.txt", "w+");
    //if (fp == NULL)
    {
        // printf("Error opening file!\n");
        //exit(1);
    }
    //fprintf(fp, sting);
    //fclose(fp);
    printf("%s\n", sting);
        uint16_t returnValue = 1u;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    char * str = "\0";
    strcat(sting, str);
    if(curl) 
    {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        //curl_slist_append(headers, "charset: utf-8");

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(sting)); 
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, sting);
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
    //InitCurl(sting);
    //PerformPost();
}
