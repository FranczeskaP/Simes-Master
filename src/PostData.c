#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <curl/curl.h>
 
CURL *curl;


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

