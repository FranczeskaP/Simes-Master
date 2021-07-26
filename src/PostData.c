#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <curl/curl.h>
 
//CURL *curl;

uint16_t InitCurl(char *dataToPost)
{
    uint16_t returnValue = 1u;
    //curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();
    if(curl) 
    {
        struct curl_slist *headers = NULL;
        curl_slist_append(headers, "Accept: application/json");
        curl_slist_append(headers, "Content-Type: application/json");

    //curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(dataToPost)); 
    //curl_easy_setopt(curl, CURLOPT_POSTFIELDS, &dataToPost);
    printf("%s\n", dataToPost);
        //curl_slist_append(headers, "charset: utf-8");
        curl_easy_setopt(curl, CURLOPT_USERPWD, "rpi:R12345678"); 
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

void PerformPost(char *dataToPost)
{

}

void DeInitCurl(void)
{
    //curl_easy_cleanup(curl);
    curl_global_cleanup();
}
