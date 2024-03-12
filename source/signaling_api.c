/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "signaling_api.h"
#include "core_json.h"

/* AWS_GETENDPOINT_PROTOCOL_MAX_STRING is ["WSS", "HTTPS", "WEBRTC"] */
#define AWS_GETENDPOINT_PROTOCOL_MAX_STRING_LENGTH ( 25 ) /* with NULL terminator */
#define AWS_STRING_QUOTE_WSS "\"WSS\""
#define AWS_STRING_LENGTH_QUOTE_WSS ( 5 )
#define AWS_STRING_QUOTE_HTTPS "\"HTTPS\""
#define AWS_STRING_LENGTH_QUOTE_HTTPS ( 7 )
#define AWS_STRING_QUOTE_WEBRTC "\"WEBRTC\""
#define AWS_STRING_LENGTH_QUOTE_WEBRTC ( 8 )

#define AWS_STRING_SDP_OFFER "SDP_OFFER"
#define AWS_STRING_SDP_ANSWER "SDP_ANSWER"
#define AWS_STRING_SDP_ICE_CANDIDATE "ICE_CANDIDATE"

static char * getStringFromMessageType( SignalingTypeMessage_t messageType )
{
    char * ret;

    switch(messageType) {
        case SIGNALING_TYPE_MESSAGE_SDP_OFFER:
            ret = AWS_STRING_SDP_OFFER;
            break;
        case SIGNALING_TYPE_MESSAGE_SDP_ANSWER:
            ret = AWS_STRING_SDP_ANSWER;
            break;
        case SIGNALING_TYPE_MESSAGE_ICE_CANDIDATE:
            ret = AWS_STRING_SDP_ICE_CANDIDATE;
            break;
        default:
            ret = SIGNALING_STRING_UNKNOWN;
            break;
    }

    return ret;
}

static SignalingResult_t appendIceServerList( char *pBuffer, int *pBufferLength, SignalingIceServerList_t * pIceServerList )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int length = 0, i, j;
    char * pCurrentWrite = pBuffer;
    size_t remainingLength = *pBufferLength;

    /* pBuffer, pBufferLength, and pIceServerList are guaranteed before calling. */
    if (pIceServerList->iceServerNum > SIGNALING_AWS_ICE_SERVER_MAX_NUM) {
        result = SIGNALING_RESULT_INVALID_ICE_SERVER_COUNT;
    }

    if (result == SIGNALING_RESULT_OK) {
        /* Append ice server configs. */
        for (i = 0; i < pIceServerList->iceServerNum; i++) {
            if (pIceServerList->iceServer[i].urisNum > SIGNALING_AWS_ICE_SERVER_MAX_URIS) {
                result = SIGNALING_RESULT_INVALID_ICE_SERVER_URIS_COUNT;
                break;
            }

            /* Start appending ICE server config prefix, including password, ttl */
            if (i == 0) {
                length = snprintf(pCurrentWrite, remainingLength, AWS_SIGNALING_ICE_SERVER_TEMPLATE_PREFIX,
                                  (int) pIceServerList->iceServer[i].passwordLength, pIceServerList->iceServer[i].pPassword,
                                  pIceServerList->iceServer[i].messageTtlSeconds);
            } else {
                length = snprintf(pCurrentWrite, remainingLength, "," AWS_SIGNALING_ICE_SERVER_TEMPLATE_PREFIX,
                                  (int) pIceServerList->iceServer[i].passwordLength, pIceServerList->iceServer[i].pPassword,
                                  pIceServerList->iceServer[i].messageTtlSeconds);
            }

            if (length < 0) { //LCOV_EXCL_BR_LINE
                result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
                break;
            }
            else if (length >= remainingLength) {
                result = SIGNALING_RESULT_OUT_OF_MEMORY;
                break;
            }
            else {
                remainingLength -= length;
                pCurrentWrite += length;
            }

            /* Append URIs. */
            for (j = 0; j < pIceServerList->iceServer[i].urisNum; j++) {
                if (j == 0) {
                    length = snprintf(pCurrentWrite, remainingLength, "\n\t\t\t\t\"%.*s\"",
                                      (int) pIceServerList->iceServer[i].urisLength[j], pIceServerList->iceServer[i].pUris[j]);
                } else {
                    length = snprintf(pCurrentWrite, remainingLength, ",\n\t\t\t\t\"%.*s\"",
                                      (int) pIceServerList->iceServer[i].urisLength[j], pIceServerList->iceServer[i].pUris[j]);
                }

                if (length < 0) { //LCOV_EXCL_BR_LINE
                    result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
                    break;
                }
                else if (length >= remainingLength) {
                    result = SIGNALING_RESULT_OUT_OF_MEMORY;
                    break;
                }
                else {
                    remainingLength -= length;
                    pCurrentWrite += length;
                }
            }

            if (result != SIGNALING_RESULT_OK) {
                break;
            }
            
            /* Append user name. */
            length = snprintf(pCurrentWrite, remainingLength, AWS_SIGNALING_ICE_SERVER_TEMPLATE_POSTFIX,
                              (int) pIceServerList->iceServer[i].userNameLength, pIceServerList->iceServer[i].pUserName);

            if (length < 0) { //LCOV_EXCL_BR_LINE
                result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
                break;
            }
            else if (length >= remainingLength) {
                result = SIGNALING_RESULT_OUT_OF_MEMORY;
                break;
            }
            else {
                remainingLength -= length;
                pCurrentWrite += length;
            }
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        length = snprintf(pCurrentWrite, remainingLength, AWS_SIGNALING_SEND_MESSAGE_TEMPLATE_POSTFIX);

        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= remainingLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            remainingLength -= length;
            pCurrentWrite += length;
        }
    }

    if (result == SIGNALING_RESULT_OK ) {
        *pBufferLength = *pBufferLength - remainingLength;
    }

    return result;
}

static SignalingChannelEndpointProtocol_t getProtocolFromString( const char *pProtocolString, size_t protocolStringLength )
{
    SignalingChannelEndpointProtocol_t ret = SIGNALING_ENDPOINT_PROTOCOL_NONE;

    if ( strncmp(pProtocolString, "WSS", 3) == 0 ||
         strncmp(pProtocolString, "wss", 3) == 0 ) {
        ret = SIGNALING_ENDPOINT_PROTOCOL_WEBSOCKET_SECURE;
    } else if ( strncmp(pProtocolString, "HTTPS", 5) == 0 ||
         strncmp(pProtocolString, "https", 5) == 0 ) {
        ret = SIGNALING_ENDPOINT_PROTOCOL_HTTPS;
    } else if ( strncmp(pProtocolString, "WEBRTC", 6) == 0 ||
         strncmp(pProtocolString, "webrtc", 6) == 0 ) {
        ret = SIGNALING_ENDPOINT_PROTOCOL_WEBRTC;
    } else {
        /* Do nothing, coverity happy. */
    }

    return ret;
}

static void updateUris(SignalingIceServer_t *pIceServer, const char * pUris, size_t urisLength)
{
    JSONStatus_t jsonResult = JSONSuccess;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };

    jsonResult = JSON_Iterate( pUris, urisLength, &start, &next, &pair );
    
    while (jsonResult == JSONSuccess) {
        pIceServer->pUris[pIceServer->urisNum] = pair.value;
        pIceServer->urisLength[pIceServer->urisNum] = pair.valueLength;
        pIceServer->urisNum++;
        
        jsonResult = JSON_Iterate( pUris, urisLength, &start, &next, &pair );
    }
}

static SignalingResult_t parseIceServerList(const char *pIceServerListBuffer, size_t iceServerListBufferLength, SignalingIceServerList_t *pIceServerList)
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    JSONStatus_t jsonResult = JSONSuccess;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };
    const char *pIceSingleServerBuffer;
    size_t iceSingleServerBufferLength;
    size_t iceSingleServerStart = 0, iceSingleServerNext = 0;
    char ttlSecondsBuffer[AWS_MESSAGE_ICE_SERVER_TTL_SECONDS_BUFFER_MAX] = { 0 };

    /* Input check. */
    if (pIceServerListBuffer == NULL || pIceServerList == NULL) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    while (result == SIGNALING_RESULT_OK && pIceServerList->iceServerNum < SIGNALING_AWS_ICE_SERVER_MAX_NUM) {
        jsonResult = JSON_Iterate( pIceServerListBuffer, iceServerListBufferLength, &start, &next, &pair );

        if (jsonResult == JSONSuccess) {
            pIceSingleServerBuffer = pair.value;
            iceSingleServerBufferLength = pair.valueLength;
            iceSingleServerStart = 0;
            iceSingleServerNext = 0;

            jsonResult = JSON_Iterate( pIceSingleServerBuffer, iceSingleServerBufferLength, &iceSingleServerStart, &iceSingleServerNext, &pair );
            while (jsonResult == JSONSuccess) {
                if (strncmp(pair.key, "Password", pair.keyLength) == 0) {
                    if (pIceServerList->iceServer[pIceServerList->iceServerNum].pPassword != NULL) {
                        pIceServerList->iceServerNum++;

                        if (pIceServerList->iceServerNum >= SIGNALING_AWS_ICE_SERVER_MAX_NUM) {
                            /* Ignore following servers. */
                            break;
                        }
                    }
                    
                    pIceServerList->iceServer[pIceServerList->iceServerNum].pPassword = pair.value;
                    pIceServerList->iceServer[pIceServerList->iceServerNum].passwordLength = pair.valueLength;
                } else if (strncmp(pair.key, "Ttl", pair.keyLength) == 0) {
                    if( pair.valueLength >= AWS_MESSAGE_ICE_SERVER_TTL_SECONDS_BUFFER_MAX ) {
                        /* Unexpect TTL value from cloud. */
                        result = SIGNALING_RESULT_INVALID_TTL;
                        break;
                    }

                    if (pIceServerList->iceServer[pIceServerList->iceServerNum].messageTtlSeconds != 0) {
                        pIceServerList->iceServerNum++;

                        if (pIceServerList->iceServerNum >= SIGNALING_AWS_ICE_SERVER_MAX_NUM) {
                            /* Ignore following servers. */
                            break;
                        }
                    }

                    strncpy(ttlSecondsBuffer, pair.value, pair.valueLength);
                    pIceServerList->iceServer[pIceServerList->iceServerNum].messageTtlSeconds = (uint32_t) strtoul(ttlSecondsBuffer, NULL, 10);

                    if (pIceServerList->iceServer[pIceServerList->iceServerNum].messageTtlSeconds < AWS_MESSAGE_ICE_SERVER_TTL_SECONDS_MIN ||
                        pIceServerList->iceServer[pIceServerList->iceServerNum].messageTtlSeconds > AWS_MESSAGE_ICE_SERVER_TTL_SECONDS_MAX) {
                        /* Unexpect TTL value from cloud. */
                        result = SIGNALING_RESULT_INVALID_TTL;
                    }
                } else if (strncmp(pair.key, "Uris", pair.keyLength) == 0) {
                    if (pIceServerList->iceServer[pIceServerList->iceServerNum].pUris[0] != NULL) {
                        pIceServerList->iceServerNum++;

                        if (pIceServerList->iceServerNum >= SIGNALING_AWS_ICE_SERVER_MAX_NUM) {
                            /* Ignore following servers. */
                            break;
                        }
                    }
                    
                    updateUris(&pIceServerList->iceServer[pIceServerList->iceServerNum], pair.value, pair.valueLength);
                } else if (strncmp(pair.key, "Username", pair.keyLength) == 0) {
                    if (pIceServerList->iceServer[pIceServerList->iceServerNum].pUserName != NULL) {
                        pIceServerList->iceServerNum++;

                        if (pIceServerList->iceServerNum >= SIGNALING_AWS_ICE_SERVER_MAX_NUM) {
                            /* Ignore following servers. */
                            break;
                        }
                    }
                    
                    pIceServerList->iceServer[pIceServerList->iceServerNum].pUserName = pair.value;
                    pIceServerList->iceServer[pIceServerList->iceServerNum].userNameLength = pair.valueLength;
                } else {
                    /* Skip unknown messages. */
                }

                jsonResult = JSON_Iterate( pIceSingleServerBuffer, iceSingleServerBufferLength, &iceSingleServerStart, &iceSingleServerNext, &pair );
            }

        } else {
            /* All parsed. */
            pIceServerList->iceServerNum++;
            break;
        }
    }

    return result;
}

SignalingResult_t Signaling_Init( SignalingContext_t *pCtx, SignalingAwsControlPlaneInfo_t *pAwsControlPlaneInfo )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int length = 0;

    /* input check */
    if (pCtx == NULL || pAwsControlPlaneInfo == NULL) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    /* Set region. */
    if (result == SIGNALING_RESULT_OK) {
        memset(pCtx, 0, sizeof(SignalingContext_t));

        if (pAwsControlPlaneInfo->pRegion == NULL) {
            length = snprintf(pCtx->region, SIGNALING_AWS_REGION_MAX_LENGTH, "%.*s",
                              (int) strlen(SIGNALING_AWS_DEFAULT_REGION), SIGNALING_AWS_DEFAULT_REGION);
        } else {
            length = snprintf(pCtx->region, SIGNALING_AWS_REGION_MAX_LENGTH, "%.*s",
                              (int) pAwsControlPlaneInfo->regionLength, pAwsControlPlaneInfo->pRegion);
        }

        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= SIGNALING_AWS_CONTROL_PLANE_URL_MAX_LENGTH) {
            result = SIGNALING_RESULT_REGION_LENGTH_TOO_LARGE;
        }
        else {
            pCtx->regionLength = length;
        }
    }

    /* Set control plane. */
    if (result == SIGNALING_RESULT_OK) {
        if (pAwsControlPlaneInfo->pControlPlaneUrl == NULL) {
            length = snprintf(pCtx->controlPlaneUrl, SIGNALING_AWS_CONTROL_PLANE_URL_MAX_LENGTH, "%s%s.%s%s",
                              AWS_CONTROL_PLANE_URI_PREFIX, AWS_KINESIS_VIDEO_SERVICE_NAME, 
                              pCtx->region, AWS_CONTROL_PLANE_URI_POSTFIX);
        } else {
            length = snprintf(pCtx->controlPlaneUrl, SIGNALING_AWS_CONTROL_PLANE_URL_MAX_LENGTH, "%.*s",
                              (int) pAwsControlPlaneInfo->controlPlaneUrlLength, pAwsControlPlaneInfo->pControlPlaneUrl);
        }

        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= SIGNALING_AWS_CONTROL_PLANE_URL_MAX_LENGTH) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pCtx->controlPlaneUrlLength = length;
        }
    }

    return result;
}

SignalingResult_t Signaling_constructDescribeSignalingChannelRequest( SignalingContext_t *pCtx, SignalingDescribeSignalingChannelRequest_t * pDescribeSignalingChannelRequest, SignalingRequest_t *pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int length=0;

    /* input check */
    if (pCtx == NULL || pRequestBuffer == NULL || pDescribeSignalingChannelRequest == NULL ||
        pRequestBuffer->pUrl == NULL || pRequestBuffer->pBody == NULL || pDescribeSignalingChannelRequest->pChannelName == NULL) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if (result == SIGNALING_RESULT_OK) {
        // calculate the length of url
        length = snprintf(pRequestBuffer->pUrl, pRequestBuffer->urlLength, "%.*s%s",
                          (int) pCtx->controlPlaneUrlLength, pCtx->controlPlaneUrl,
                          AWS_DESCRIBE_SIGNALING_CHANNEL_API_POSTFIX);

        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= pRequestBuffer->urlLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->urlLength = length;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        // Prepare the body for the call
        length = snprintf(pRequestBuffer->pBody, pRequestBuffer->bodyLength, AWS_DESCRIBE_CHANNEL_PARAM_JSON_TEMPLATE,
                          (int) pDescribeSignalingChannelRequest->channelNameLength, pDescribeSignalingChannelRequest->pChannelName);
        
        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= pRequestBuffer->bodyLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->bodyLength = length;
        }
    }

    return result;
}

SignalingResult_t Signaling_parseDescribeSignalingChannelResponse( SignalingContext_t *pCtx, char * pMessage, size_t messageLength, SignalingDescribeSignalingChannelResponse_t *pDescribeSignalingChannelResponse )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    JSONStatus_t jsonResult;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };
    const char *pChannelInfoBuffer;
    size_t channelInfoBufferLength;
    size_t channelInfoStart = 0, channelInfoNext = 0;
    char ttlSecondsBuffer[AWS_MESSAGE_CHANNEL_TTL_SECONDS_BUFFER_MAX] = { 0 };

    /* input check */
    if (pCtx == NULL || pMessage == NULL || pDescribeSignalingChannelResponse == NULL) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if (result == SIGNALING_RESULT_OK) {
        jsonResult = JSON_Validate(pMessage, messageLength);

        if (jsonResult != JSONSuccess) {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        memset(pDescribeSignalingChannelResponse, 0, sizeof(SignalingDescribeSignalingChannelResponse_t));

        /* Check if it's ChannelInfo. */
        jsonResult = JSON_Iterate( pMessage, messageLength, &start, &next, &pair );

        if (jsonResult == JSONSuccess) {
            if (pair.jsonType != JSONObject || 
                pair.keyLength != strlen("ChannelInfo") || 
                strncmp(pair.key, "ChannelInfo", pair.keyLength) != 0) {
                /* Not an ice server list meesage. */
                result = SIGNALING_RESULT_NOT_EXPECT_RESPONSE;
            } else {
                pChannelInfoBuffer = pair.value;
                channelInfoBufferLength = pair.valueLength;
            }
        } else {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        jsonResult = JSON_Iterate(pChannelInfoBuffer, channelInfoBufferLength, &channelInfoStart, &channelInfoNext, &pair);

        while (jsonResult == JSONSuccess) {
            if (strncmp(pair.key, "ChannelARN", pair.keyLength) == 0) {
                pDescribeSignalingChannelResponse->pChannelArn = pair.value;
                pDescribeSignalingChannelResponse->channelArnLength = pair.valueLength;
            } else if (strncmp(pair.key, "ChannelName", pair.keyLength) == 0) {
                if (pair.valueLength < SIGNALING_AWS_MAX_CHANNEL_NAME_LEN) {
                    pDescribeSignalingChannelResponse->pChannelName = pair.value;
                    pDescribeSignalingChannelResponse->channelNameLength = pair.valueLength;

                    /* Store channel name in context. */
                    pCtx->channelNameLength = pDescribeSignalingChannelResponse->channelNameLength;
                    memcpy(pCtx->channelName, pDescribeSignalingChannelResponse->pChannelName, pCtx->channelNameLength);
                    pCtx->channelName[pCtx->channelNameLength] = '\0';
                } else {
                    result = SIGNALING_RESULT_INVALID_CHANNEL_NAME;
                }
            } else if (strncmp(pair.key, "ChannelStatus", pair.keyLength) == 0) {
                pDescribeSignalingChannelResponse->pChannelStatus = pair.value;
                pDescribeSignalingChannelResponse->channelStatusLength = pair.valueLength;
            } else if (strncmp(pair.key, "ChannelType", pair.keyLength) == 0) {
                pDescribeSignalingChannelResponse->pChannelType = pair.value;
                pDescribeSignalingChannelResponse->channelTypeLength = pair.valueLength;

                /* Store channel type in context. */
                if (strncmp(pDescribeSignalingChannelResponse->pChannelType, "SINGLE_MASTER", pDescribeSignalingChannelResponse->channelTypeLength) != 0) {
                    result = SIGNALING_RESULT_INVALID_CHANNEL_TYPE;
                }
            } else if (strncmp(pair.key, "CreationTime", pair.keyLength) == 0) {
                // TODO: In the future parse out the creation time but currently we don't need it
            } else if (strncmp(pair.key, "SingleMasterConfiguration", pair.keyLength) == 0) {
                const char *pBuffer = pair.value;
                size_t bufferLength = pair.valueLength;
                size_t bufferStart = 0, bufferNext = 0;

                jsonResult = JSON_Iterate( pBuffer, bufferLength, &bufferStart, &bufferNext, &pair );

                if (jsonResult == JSONSuccess) {
                    if (strncmp(pair.key, "MessageTtlSeconds", pair.keyLength) == 0) {
                        if( pair.valueLength >= AWS_MESSAGE_CHANNEL_TTL_SECONDS_BUFFER_MAX ) {
                            /* Unexpect TTL value from cloud. */
                            result = SIGNALING_RESULT_INVALID_TTL;
                            break;
                        }

                        strncpy(ttlSecondsBuffer, pair.value, pair.valueLength);
                        pDescribeSignalingChannelResponse->messageTtlSeconds = (uint32_t) strtoul(ttlSecondsBuffer, NULL, 10);

                        if (pDescribeSignalingChannelResponse->messageTtlSeconds < AWS_MESSAGE_CHANNEL_TTL_SECONDS_MIN || pDescribeSignalingChannelResponse->messageTtlSeconds > AWS_MESSAGE_CHANNEL_TTL_SECONDS_MAX) {
                            /* Unexpect TTL value from cloud. */
                            result = SIGNALING_RESULT_INVALID_TTL;
                        }
                    } else {
                        // unknown attribute
                        result = SIGNALING_RESULT_INVALID_JSON;
                    }
                } else {
                    // invalid single master configuration
                    result = SIGNALING_RESULT_INVALID_JSON;
                }
            } else if (strncmp(pair.key, "Version", pair.keyLength) == 0) {
                pDescribeSignalingChannelResponse->pVersion = pair.value;
                pDescribeSignalingChannelResponse->versionLength = pair.valueLength;
            } else {
                /* Skip unknown attributes. */
            }
            
            if (result != SIGNALING_RESULT_OK) {
                break;
            }

            jsonResult = JSON_Iterate(pChannelInfoBuffer, channelInfoBufferLength, &channelInfoStart, &channelInfoNext, &pair);
        }
    }

    return result;
}

SignalingResult_t Signaling_constructDescribeMediaStorageConfigRequest( SignalingContext_t *pCtx, SignalingDescribeMediaStorageConfigRequest_t * pDescribeMediaStorageConfigRequest, SignalingRequest_t *pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int length=0;

    /* input check */
    if (pCtx == NULL || pRequestBuffer == NULL || pDescribeMediaStorageConfigRequest == NULL ||
        pRequestBuffer->pUrl == NULL || pRequestBuffer->pBody == NULL || 
        pDescribeMediaStorageConfigRequest->pChannelArn == NULL ) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if (result == SIGNALING_RESULT_OK) {
        // calculate the length of url
        length = snprintf(pRequestBuffer->pUrl, pRequestBuffer->urlLength, "%.*s%s",
                          (int) pCtx->controlPlaneUrlLength, pCtx->controlPlaneUrl,
                          AWS_DESCRIBE_MEDIA_STORAGE_CONF_API_POSTFIX);

        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= pRequestBuffer->urlLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->urlLength = length;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        // Prepare the body for the call
        length = snprintf(pRequestBuffer->pBody, pRequestBuffer->bodyLength, AWS_DESCRIBE_MEDIA_STORAGE_CONF_PARAM_JSON_TEMPLATE,
                          (int) pDescribeMediaStorageConfigRequest->channelArnLength, pDescribeMediaStorageConfigRequest->pChannelArn);
        
        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= pRequestBuffer->bodyLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->bodyLength = length;
        }
    }

    return result;
}

SignalingResult_t Signaling_parseDescribeMediaStorageConfigResponse( SignalingContext_t *pCtx, char * pMessage, size_t messageLength, SignalingDescribeMediaStorageConfigResponse_t *pDescribeMediaStorageConfigResponse )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    JSONStatus_t jsonResult;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };
    const char *pMediaStorageConfigBuffer;
    size_t mediaStorageConfigBufferLength;
    size_t mediaStorageConfigStart = 0, mediaStorageConfigNext = 0;

    /* input check */
    if (pCtx == NULL || pMessage == NULL || pDescribeMediaStorageConfigResponse == NULL) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if (result == SIGNALING_RESULT_OK) {
        jsonResult = JSON_Validate(pMessage, messageLength);

        if (jsonResult != JSONSuccess) {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        memset(pDescribeMediaStorageConfigResponse, 0, sizeof(SignalingDescribeMediaStorageConfigResponse_t));

        /* Check if it's MediaStorageConfiguration. */
        jsonResult = JSON_Iterate( pMessage, messageLength, &start, &next, &pair );

        if (jsonResult == JSONSuccess) {
            if (pair.jsonType != JSONArray || 
                pair.keyLength != strlen("MediaStorageConfiguration") || 
                strncmp(pair.key, "MediaStorageConfiguration", pair.keyLength) != 0) {
                /* Not an ice server list meesage. */
                result = SIGNALING_RESULT_NOT_EXPECT_RESPONSE;
            } else {
                pMediaStorageConfigBuffer = pair.value;
                mediaStorageConfigBufferLength = pair.valueLength;
            }
        } else {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        jsonResult = JSON_Iterate(pMediaStorageConfigBuffer, mediaStorageConfigBufferLength, &mediaStorageConfigStart, &mediaStorageConfigNext, &pair);

        while (jsonResult == JSONSuccess) {
            if (strncmp(pair.key, "Status", pair.keyLength) == 0) {
                pDescribeMediaStorageConfigResponse->pStatus = pair.value;
                pDescribeMediaStorageConfigResponse->statusLength = pair.valueLength;
            } else if (strncmp(pair.key, "StreamARN", pair.keyLength) == 0) {
                pDescribeMediaStorageConfigResponse->pStreamArn = pair.value;
                pDescribeMediaStorageConfigResponse->streamArnLength = pair.valueLength;
            } else {
                /* Skip unknown attributes. */
            }
            
            jsonResult = JSON_Iterate(pMediaStorageConfigBuffer, mediaStorageConfigBufferLength, &mediaStorageConfigStart, &mediaStorageConfigNext, &pair);
        }
    }

    return result;
}

SignalingResult_t Signaling_constructCreateSignalingChannelRequest( SignalingContext_t *pCtx, SignalingCreateSignalingChannelRequest_t * pCreateSignalingChannelRequest, SignalingRequest_t *pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int length=0;
    char *pCurBody = pRequestBuffer->pBody;
    size_t remainingLength = 0;
    int i;
    SignalingTag_t *pCurTags = NULL;

    /* input check */
    if (pCtx == NULL || pRequestBuffer == NULL || pCreateSignalingChannelRequest == NULL ||
        pRequestBuffer->pUrl == NULL || pRequestBuffer->pBody == NULL || 
        (pCreateSignalingChannelRequest->tagsCount > 0 && pCreateSignalingChannelRequest->pTags == NULL) ||
        pCreateSignalingChannelRequest->channelInfo.channelNameLength >= SIGNALING_AWS_MAX_CHANNEL_NAME_LEN) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if (result == SIGNALING_RESULT_OK) {
        // calculate the length of url
        length = snprintf(pRequestBuffer->pUrl, pRequestBuffer->urlLength, "%.*s%s",
                          (int) pCtx->controlPlaneUrlLength, pCtx->controlPlaneUrl,
                          AWS_CREATE_SIGNALING_CHANNEL_API_POSTFIX);

        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= pRequestBuffer->urlLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->urlLength = length;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        // Prepare the body for the call
        remainingLength = pRequestBuffer->bodyLength;

        length = snprintf(pCurBody, remainingLength, AWS_CREATE_CHANNEL_PARAM_JSON_TEMPLATE_PREFIX,
                          (int) pCreateSignalingChannelRequest->channelInfo.channelNameLength, pCreateSignalingChannelRequest->channelInfo.pChannelName,
                          pCreateSignalingChannelRequest->channelInfo.type == SIGNALING_TYPE_CHANNEL_SINGLE_MASTER? SIGNALING_STRING_SINGLE_MASTER:SIGNALING_STRING_UNKNOWN,
                          pCreateSignalingChannelRequest->channelInfo.messageTtlSeconds);
        
        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= remainingLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->bodyLength = length;
            remainingLength -= length;
            pCurBody += length;
        }
    }

    /* Append tags prefix. */
    if (result == SIGNALING_RESULT_OK && pCreateSignalingChannelRequest->tagsCount > 0) {
        length = snprintf(pCurBody, remainingLength, AWS_CREATE_CHANNEL_PARAM_JSON_TAGS_PREFIX);
        
        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= remainingLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->bodyLength += length;
            remainingLength -= length;
            pCurBody += length;
        }
    }

    /* Append tags content. */
    if (result == SIGNALING_RESULT_OK && pCreateSignalingChannelRequest->tagsCount > 0) {
        pCurTags = pCreateSignalingChannelRequest->pTags;

        for (i = 0; i < pCreateSignalingChannelRequest->tagsCount; i++) {
            if (i == 0) {
                length = snprintf(pCurBody, remainingLength, AWS_CREATE_CHANNEL_PARAM_JSON_TAGS_TEMPLATE,
                                  (int) (pCurTags + i)->nameLength, (pCurTags + i)->pName,
                                  (int) (pCurTags + i)->valueLength, (pCurTags + i)->pValue);
            } else {
                length = snprintf(pCurBody, remainingLength, "," AWS_CREATE_CHANNEL_PARAM_JSON_TAGS_TEMPLATE,
                                  (int) (pCurTags + i)->nameLength, (pCurTags + i)->pName,
                                  (int) (pCurTags + i)->valueLength, (pCurTags + i)->pValue);
            }

            if (length < 0) { //LCOV_EXCL_BR_LINE
                result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
            }
            else if (length >= remainingLength) {
                result = SIGNALING_RESULT_OUT_OF_MEMORY;
            }
            else {
                pRequestBuffer->bodyLength += length;
                remainingLength -= length;
                pCurBody += length;
            }
        }
    }

    /* Append tags postfix. */
    if (result == SIGNALING_RESULT_OK && pCreateSignalingChannelRequest->tagsCount > 0) {
        length = snprintf(pCurBody, remainingLength, AWS_CREATE_CHANNEL_PARAM_JSON_TAGS_POSTFIX);
        
        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= remainingLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->bodyLength += length;
            remainingLength -= length;
            pCurBody += length;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        // Prepare the body for the call
        length = snprintf(pCurBody, remainingLength, AWS_CREATE_CHANNEL_PARAM_JSON_TEMPLATE_POSTFIX);
        
        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= remainingLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->bodyLength += length;
            remainingLength -= length;
            pCurBody += length;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        /* Store channel information in context. */
        pCtx->channelNameLength = pCreateSignalingChannelRequest->channelInfo.channelNameLength;
        memcpy(pCtx->channelName, pCreateSignalingChannelRequest->channelInfo.pChannelName, pCtx->channelNameLength);
        pCtx->channelName[pCtx->channelNameLength] = '\0';
    }

    return result;
}

SignalingResult_t Signaling_parseCreateSignalingChannelResponse( SignalingContext_t *pCtx, char * pMessage, size_t messageLength, SignalingCreateSignalingChannelResponse_t *pCreateSignalingChannelResponse )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    JSONStatus_t jsonResult;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };

    /* input check */
    if (pCtx == NULL || pMessage == NULL || pCreateSignalingChannelResponse == NULL) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if (result == SIGNALING_RESULT_OK) {
        jsonResult = JSON_Validate(pMessage, messageLength);

        if (jsonResult != JSONSuccess) {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        memset(pCreateSignalingChannelResponse, 0, sizeof(SignalingCreateSignalingChannelResponse_t));

        /* Check if it's IceServerList. */
        jsonResult = JSON_Iterate( pMessage, messageLength, &start, &next, &pair );

        if (jsonResult == JSONSuccess) {
            if (strncmp(pair.key, "ChannelARN", pair.keyLength) == 0) {
                pCreateSignalingChannelResponse->pChannelArn = pair.value;
                pCreateSignalingChannelResponse->channelArnLength = pair.valueLength;
            }
        } else {
            result = SIGNALING_RESULT_NOT_EXPECT_RESPONSE;
        }
    }

    return result;
}

SignalingResult_t Signaling_constructGetSignalingChannelEndpointRequest( SignalingContext_t *pCtx, SignalingGetSignalingChannelEndpointRequest_t * pGetSignalingChannelEndpointRequest, SignalingRequest_t *pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int length=0;
    char protocols[AWS_GETENDPOINT_PROTOCOL_MAX_STRING_LENGTH] = { 0 };
    int protocolIndex = 0;
    uint8_t isFirstProtocol = true;

    /* input check */
    if (pCtx == NULL || pRequestBuffer == NULL || pGetSignalingChannelEndpointRequest == NULL ||
        pRequestBuffer->pUrl == NULL || pRequestBuffer->pBody == NULL || 
        pGetSignalingChannelEndpointRequest->pChannelArn == NULL ||
        (pGetSignalingChannelEndpointRequest->role != SIGNALING_ROLE_MASTER && pGetSignalingChannelEndpointRequest->role != SIGNALING_ROLE_VIEWER)) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if (result == SIGNALING_RESULT_OK) {
        // calculate the length of url
        length = snprintf(pRequestBuffer->pUrl, pRequestBuffer->urlLength, "%.*s%s",
                          (int) pCtx->controlPlaneUrlLength, pCtx->controlPlaneUrl,
                          AWS_GET_SIGNALING_CHANNEL_ENDPOINT_API_POSTFIX);

        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= pRequestBuffer->urlLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->urlLength = length;
        }
    }

    /* Prepare protocol string. */
    if (result == SIGNALING_RESULT_OK) {
        if ((pGetSignalingChannelEndpointRequest->protocolsBitsMap & SIGNALING_ENDPOINT_PROTOCOL_WEBSOCKET_SECURE) != 0) {
            strcpy(protocols, AWS_STRING_QUOTE_WSS);
            protocolIndex += AWS_STRING_LENGTH_QUOTE_WSS;

            isFirstProtocol = false;
        }

        if ((pGetSignalingChannelEndpointRequest->protocolsBitsMap & SIGNALING_ENDPOINT_PROTOCOL_HTTPS) != 0) {
            if (isFirstProtocol == false) {
                strcpy(protocols + protocolIndex, ", ");
                protocolIndex += 2;
            }
            strcpy(protocols + protocolIndex, AWS_STRING_QUOTE_HTTPS);
            protocolIndex += AWS_STRING_LENGTH_QUOTE_HTTPS;

            isFirstProtocol = false;
        }

        if ((pGetSignalingChannelEndpointRequest->protocolsBitsMap & SIGNALING_ENDPOINT_PROTOCOL_WEBRTC) != 0) {
            if (isFirstProtocol == false) {
                strcpy(protocols + protocolIndex, ", ");
                protocolIndex += 2;
            }
            strcpy(protocols + protocolIndex, AWS_STRING_QUOTE_WEBRTC);
            protocolIndex += AWS_STRING_LENGTH_QUOTE_WEBRTC;

            isFirstProtocol = false;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        // Prepare the body for the call
        length = snprintf(pRequestBuffer->pBody, pRequestBuffer->bodyLength, AWS_GET_CHANNEL_ENDPOINT_PARAM_JSON_TEMPLATE,
                          (int) pGetSignalingChannelEndpointRequest->channelArnLength, pGetSignalingChannelEndpointRequest->pChannelArn,
                          protocols,
                          pGetSignalingChannelEndpointRequest->role == SIGNALING_ROLE_MASTER? SIGNALING_STRING_MASTER:SIGNALING_STRING_VIEWER);
        
        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= pRequestBuffer->bodyLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->bodyLength = length;
        }
    }

    return result;
}

SignalingResult_t Signaling_parseGetSignalingChannelEndpointResponse( SignalingContext_t *pCtx, char * pMessage, size_t messageLength, SignalingGetSignalingChannelEndpointResponse_t * pGetSignalingChannelEndpointResponse )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    JSONStatus_t jsonResult;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };
    const char *pResourceEndpointListBuffer;
    size_t resourceEndpointListBufferLength;
    size_t resourceEndpointStart = 0, resourceEndpointNext = 0;
    const char *pEndpointListBuffer;
    size_t endpointListBufferLength;
    size_t endpointListStart = 0, endpointListNext = 0;
    const char * pTempEndpoint;
    size_t tempEndpointLength;
    SignalingChannelEndpointProtocol_t protocol;

    /* input check */
    if (pCtx == NULL || pMessage == NULL || pGetSignalingChannelEndpointResponse == NULL) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if (result == SIGNALING_RESULT_OK) {
        jsonResult = JSON_Validate(pMessage, messageLength);

        if (jsonResult != JSONSuccess) {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        memset(pGetSignalingChannelEndpointResponse, 0, sizeof(SignalingGetSignalingChannelEndpointResponse_t));

        /* Check if it's resourceEndpoint. */
        jsonResult = JSON_Iterate( pMessage, messageLength, &start, &next, &pair );

        if (jsonResult == JSONSuccess) {
            if (pair.jsonType != JSONArray || 
                pair.keyLength != strlen("ResourceEndpointList") || 
                strncmp(pair.key, "ResourceEndpointList", pair.keyLength) != 0) {
                /* Not an ice server list meesage. */
                result = SIGNALING_RESULT_NOT_EXPECT_RESPONSE;
            } else {
                pResourceEndpointListBuffer = pair.value;
                resourceEndpointListBufferLength = pair.valueLength;
            }
        } else {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    while (result == SIGNALING_RESULT_OK) {
        jsonResult = JSON_Iterate( pResourceEndpointListBuffer, resourceEndpointListBufferLength, &resourceEndpointStart, &resourceEndpointNext, &pair );

        if (jsonResult == JSONSuccess) {
            pEndpointListBuffer = pair.value;
            endpointListBufferLength = pair.valueLength;
            endpointListStart = 0;
            endpointListNext = 0;
            pTempEndpoint = NULL;
            tempEndpointLength = 0;
            protocol = SIGNALING_ENDPOINT_PROTOCOL_NONE;

            jsonResult = JSON_Iterate( pEndpointListBuffer, endpointListBufferLength, &endpointListStart, &endpointListNext, &pair );
            while (jsonResult == JSONSuccess) {
                if (strncmp(pair.key, "Protocol", pair.keyLength) == 0) {
                    protocol = getProtocolFromString(pair.value, pair.valueLength);
                } else if (strncmp(pair.key, "ResourceEndpoint", pair.keyLength) == 0) {
                    pTempEndpoint = pair.value;
                    tempEndpointLength = pair.valueLength;
                }

                jsonResult = JSON_Iterate( pEndpointListBuffer, endpointListBufferLength, &endpointListStart, &endpointListNext, &pair );
            }

            if (pTempEndpoint != NULL && protocol != SIGNALING_ENDPOINT_PROTOCOL_NONE) {
                switch (protocol) {
                    case SIGNALING_ENDPOINT_PROTOCOL_WEBSOCKET_SECURE:
                        pGetSignalingChannelEndpointResponse->pEndpointWebsocketSecure = pTempEndpoint;
                        pGetSignalingChannelEndpointResponse->endpointWebsocketSecureLength = tempEndpointLength;
                        break;
                    case SIGNALING_ENDPOINT_PROTOCOL_HTTPS:
                        pGetSignalingChannelEndpointResponse->pEndpointHttps = pTempEndpoint;
                        pGetSignalingChannelEndpointResponse->endpointHttpsLength = tempEndpointLength;
                        break;
                    case SIGNALING_ENDPOINT_PROTOCOL_WEBRTC:
                    default:
                        pGetSignalingChannelEndpointResponse->pEndpointWebrtc = pTempEndpoint;
                        pGetSignalingChannelEndpointResponse->endpointWebrtcLength = tempEndpointLength;
                        break;
                }
            }
        } else {
            /* All parsed. */
            break;
        }
    }

    return result;
}

SignalingResult_t Signaling_constructGetIceServerConfigRequest( SignalingContext_t *pCtx, SignalingGetIceServerConfigRequest_t * pGetIceServerConfigReqeust, SignalingRequest_t *pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int length=0;

    /* input check */
    if (pCtx == NULL || pRequestBuffer == NULL || pGetIceServerConfigReqeust == NULL ||
        pRequestBuffer->pUrl == NULL || pRequestBuffer->pBody == NULL ||
        pGetIceServerConfigReqeust->pClientId == NULL || pGetIceServerConfigReqeust->pEndpointHttps == NULL) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if (result == SIGNALING_RESULT_OK) {
        // calculate the length of url
        length = snprintf(pRequestBuffer->pUrl, pRequestBuffer->urlLength, "%.*s%s",
                          (int) pGetIceServerConfigReqeust->endpointHttpsLength, pGetIceServerConfigReqeust->pEndpointHttps,
                          AWS_GET_ICE_CONFIG_API_POSTFIX);

        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= pRequestBuffer->urlLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->urlLength = length;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        // Prepare the body for the call
        length = snprintf(pRequestBuffer->pBody, pRequestBuffer->bodyLength, AWS_GET_ICE_CONFIG_PARAM_JSON_TEMPLATE,
                          (int) pGetIceServerConfigReqeust->channelArnLength, pGetIceServerConfigReqeust->pChannelArn,
                          (int) pGetIceServerConfigReqeust->clientIdLength, pGetIceServerConfigReqeust->pClientId);
        
        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= pRequestBuffer->bodyLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->bodyLength = length;
        }
    }

    return result;
}

SignalingResult_t Signaling_parseGetIceServerConfigResponse( SignalingContext_t *pCtx, char * pMessage, size_t messageLength, SignalingGetIceServerConfigResponse_t *pGetIceConfigResponse )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    JSONStatus_t jsonResult;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };
    const char *pIceServerListBuffer;
    size_t iceServerListBufferLength;

    /* input check */
    if (pCtx == NULL || pMessage == NULL || pGetIceConfigResponse == NULL) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if (result == SIGNALING_RESULT_OK) {
        jsonResult = JSON_Validate(pMessage, messageLength);

        if (jsonResult != JSONSuccess) {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        memset(pGetIceConfigResponse, 0, sizeof(SignalingGetIceServerConfigResponse_t));

        /* Check if it's IceServerList. */
        jsonResult = JSON_Iterate( pMessage, messageLength, &start, &next, &pair );

        if (jsonResult == JSONSuccess) {
            if (pair.jsonType != JSONArray || 
                pair.keyLength != strlen("IceServerList") || 
                strncmp(pair.key, "IceServerList", pair.keyLength) != 0) {
                /* Not an ice server list meesage. */
                result = SIGNALING_RESULT_NOT_EXPECT_RESPONSE;
            } else {
                pIceServerListBuffer = pair.value;
                iceServerListBufferLength = pair.valueLength;
            }
        } else {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        result = parseIceServerList(pIceServerListBuffer, iceServerListBufferLength, pGetIceConfigResponse);
    }

    return result;
}

SignalingResult_t Signaling_constuctJoinStorageSessionRequest( SignalingContext_t *pCtx, SignalingJoinStorageSessionRequest_t * pJoinStorageSessionRequest, SignalingRequest_t *pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int length=0;

    /* input check */
    if (pCtx == NULL || pRequestBuffer == NULL || pJoinStorageSessionRequest == NULL ||
        pRequestBuffer->pUrl == NULL || pRequestBuffer->pBody == NULL ||
        pJoinStorageSessionRequest->pChannelArn == NULL || pJoinStorageSessionRequest->pEndpointWebrtc == NULL) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if (result == SIGNALING_RESULT_OK) {
        // calculate the length of url
        length = snprintf(pRequestBuffer->pUrl, pRequestBuffer->urlLength, "%.*s%s",
                          (int) pJoinStorageSessionRequest->endpointWebrtcLength, pJoinStorageSessionRequest->pEndpointWebrtc,
                          AWS_JOIN_STORAGE_SESSION_API_POSTFIX);

        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= pRequestBuffer->urlLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->urlLength = length;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        // Prepare the body for the call
        if (pJoinStorageSessionRequest->role == SIGNALING_ROLE_MASTER) {
            snprintf(pRequestBuffer->pBody, pRequestBuffer->bodyLength, AWS_JOIN_STORAGE_SESSION_MASTER_PARAM_JSON_TEMPLATE,
                     (int) pJoinStorageSessionRequest->channelArnLength, pJoinStorageSessionRequest->pChannelArn);
        } else {
            snprintf(pRequestBuffer->pBody, pRequestBuffer->bodyLength, AWS_JOIN_STORAGE_SESSION_VIEWER_PARAM_JSON_TEMPLATE,
                     (int) pJoinStorageSessionRequest->channelArnLength, pJoinStorageSessionRequest->pChannelArn,
                     (int) pJoinStorageSessionRequest->clientIdLength, pJoinStorageSessionRequest->pClientId);
        }
        
        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= pRequestBuffer->bodyLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->bodyLength = length;
        }
    }

    return result;
}

SignalingResult_t Signaling_constructDeleteSignalingChannelRequest( SignalingContext_t *pCtx, SignalingDeleteSignalingChannelRequest_t * pDeleteSignalingChannelRequest, SignalingRequest_t *pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int length=0;

    /* input check */
    if (pCtx == NULL || pRequestBuffer == NULL || pDeleteSignalingChannelRequest == NULL ||
        pRequestBuffer->pUrl == NULL || pRequestBuffer->pBody == NULL ||
        pDeleteSignalingChannelRequest->pChannelArn == NULL || pDeleteSignalingChannelRequest->pVersion == NULL) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if (result == SIGNALING_RESULT_OK) {
        // calculate the length of url
        length = snprintf(pRequestBuffer->pUrl, pRequestBuffer->urlLength, "%.*s%s",
                          (int) pCtx->controlPlaneUrlLength, pCtx->controlPlaneUrl,
                          AWS_DELETE_SIGNALING_CHANNEL_API_POSTFIX);

        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= pRequestBuffer->urlLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->urlLength = length;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        // Prepare the body for the call
        snprintf(pRequestBuffer->pBody, pRequestBuffer->bodyLength, AWS_DELETE_CHANNEL_PARAM_JSON_TEMPLATE,
                 (int) pDeleteSignalingChannelRequest->channelArnLength, pDeleteSignalingChannelRequest->pChannelArn,
                 (int) pDeleteSignalingChannelRequest->versionLength, pDeleteSignalingChannelRequest->pVersion);
        
        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= pRequestBuffer->bodyLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->bodyLength = length;
        }
    }

    return result;
}

SignalingResult_t Signaling_constructConnectWssEndpointRequest( SignalingContext_t *pCtx, SignalingConnectWssEndpointRequest_t * pConnectWssEndpointRequest, SignalingRequest_t *pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int length=0;

    /* input check */
    if (pCtx == NULL || pRequestBuffer == NULL || pConnectWssEndpointRequest == NULL ||
        pRequestBuffer->pUrl == NULL ||
        pConnectWssEndpointRequest->pChannelArn == NULL || pConnectWssEndpointRequest->pEndpointWebsocketSecure == NULL ||
        (pConnectWssEndpointRequest->role != SIGNALING_ROLE_MASTER && pConnectWssEndpointRequest->role != SIGNALING_ROLE_VIEWER)) {
        result = SIGNALING_RESULT_BAD_PARAM;
    } else if (pConnectWssEndpointRequest->role == SIGNALING_ROLE_VIEWER && pConnectWssEndpointRequest->pClientId == NULL) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if (result == SIGNALING_RESULT_OK) {
        // calculate the length of url
        if (pConnectWssEndpointRequest->role == SIGNALING_ROLE_MASTER) {
            length = snprintf(pRequestBuffer->pUrl, pRequestBuffer->urlLength, "%.*s?%s=%.*s",
                              (int) pConnectWssEndpointRequest->endpointWebsocketSecureLength, pConnectWssEndpointRequest->pEndpointWebsocketSecure,
                              AWS_SIGNALING_CHANNEL_ARN_PARAM_NAME,
                              (int) pConnectWssEndpointRequest->channelArnLength, pConnectWssEndpointRequest->pChannelArn);
        } else {
            length = snprintf(pRequestBuffer->pUrl, pRequestBuffer->urlLength, "%.*s?%s=%.*s&%s=%.*s",
                              (int) pConnectWssEndpointRequest->endpointWebsocketSecureLength, pConnectWssEndpointRequest->pEndpointWebsocketSecure,
                              AWS_SIGNALING_CHANNEL_ARN_PARAM_NAME,
                              (int) pConnectWssEndpointRequest->channelArnLength, pConnectWssEndpointRequest->pChannelArn,
                              AWS_SIGNALING_CLIENT_ID_PARAM_NAME,
                              (int) pConnectWssEndpointRequest->clientIdLength, pConnectWssEndpointRequest->pClientId);
        }

        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= pRequestBuffer->urlLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            pRequestBuffer->urlLength = length;
        }
    }

    return result;
}

SignalingResult_t Signaling_constructWssMessage( SignalingWssSendMessage_t * pWssSendMessage, char * pBuffer, size_t * pBufferLength )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int length=0;
    char * pCurrentWrite = pBuffer;
    size_t remainingLength = *pBufferLength;

    /* input check */
    if (pWssSendMessage == NULL || pBuffer == NULL ||
        pWssSendMessage->pBase64EncodedMessage == NULL ||
        pWssSendMessage->pRecipientClientId == NULL) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if (result == SIGNALING_RESULT_OK) {
        length = snprintf(pCurrentWrite, remainingLength, AWS_SIGNALING_SEND_MESSAGE_TEMPLATE_PREFIX,
                          getStringFromMessageType(pWssSendMessage->messageType),
                          (int) pWssSendMessage->recipientClientIdLength, pWssSendMessage->pRecipientClientId,
                          (int) pWssSendMessage->base64EncodedMessageLength, pWssSendMessage->pBase64EncodedMessage);

        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= remainingLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            remainingLength -= length;
            pCurrentWrite += length;
        }
    }

    /* Append correlation ID. */
    if (result == SIGNALING_RESULT_OK && pWssSendMessage->correlationIdLength > 0) {
        length = snprintf(pCurrentWrite, remainingLength, AWS_SIGNALING_SEND_MESSAGE_TEMPLATE_CORRELATION_ID,
                          (int) pWssSendMessage->correlationIdLength, pWssSendMessage->pCorrelationId);

        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= remainingLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            remainingLength -= length;
            pCurrentWrite += length;
        }
    }

    /* Append ice server list if it's SDP_OFFER. */
    if (result == SIGNALING_RESULT_OK && pWssSendMessage->messageType == SIGNALING_TYPE_MESSAGE_SDP_OFFER &&
        pWssSendMessage->iceServerList.iceServerNum > 0) {
        length = remainingLength;
        result = appendIceServerList(pCurrentWrite, &length, &pWssSendMessage->iceServerList);
    }

    /* Append send message postfix. */
    if (result == SIGNALING_RESULT_OK ) {
        length = snprintf(pCurrentWrite, remainingLength, AWS_SIGNALING_SEND_MESSAGE_TEMPLATE_POSTFIX);

        if (length < 0) { //LCOV_EXCL_BR_LINE
            result = SIGNALING_RESULT_SNPRINTF_ERROR; // LCOV_EXCL_LINE
        }
        else if (length >= remainingLength) {
            result = SIGNALING_RESULT_OUT_OF_MEMORY;
        }
        else {
            remainingLength -= length;
            pCurrentWrite += length;
        }
    }
    
    if (result == SIGNALING_RESULT_OK ) {
        *pBufferLength = *pBufferLength - remainingLength;
    }

    return result;
}

SignalingResult_t Signaling_parseWssRecvMessage( char * pMessage, size_t messageLength, SignalingWssRecvMessage_t * pWssRecvMessage )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    JSONStatus_t jsonResult;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };
    const char *pStatusResponseBuffer = NULL;
    size_t statusResponseBufferLength = 0;
    size_t statusResponseStart = 0, statusResponseNext = 0;

    /* input check */
    if (pMessage == NULL || pWssRecvMessage == NULL) {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    // Exclude '\0' in messageLength.
    if (pMessage[messageLength-1] == '\0') {
        messageLength--;
    }

    if (result == SIGNALING_RESULT_OK) {
        jsonResult = JSON_Validate(pMessage, messageLength);

        if (jsonResult != JSONSuccess) {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if (result == SIGNALING_RESULT_OK) {
        memset(pWssRecvMessage, 0, sizeof(SignalingWssRecvMessage_t));

        jsonResult = JSON_Iterate( pMessage, messageLength, &start, &next, &pair );

        while (jsonResult == JSONSuccess) {
            if (strncmp(pair.key, "senderClientId", pair.keyLength) == 0) {
                pWssRecvMessage->pSenderClientId = pair.value;
                pWssRecvMessage->senderClientIdLength = pair.valueLength;
            } else if (strncmp(pair.key, "messageType", pair.keyLength) == 0) {
                if (strncmp(pair.value, "SDP_OFFER", pair.valueLength) == 0) {
                    pWssRecvMessage->messageType = SIGNALING_TYPE_MESSAGE_SDP_OFFER;
                } else if (strncmp(pair.value, "SDP_ANSWER", pair.valueLength) == 0) {
                    pWssRecvMessage->messageType = SIGNALING_TYPE_MESSAGE_SDP_ANSWER;
                } else if (strncmp(pair.value, "ICE_CANDIDATE", pair.valueLength) == 0) {
                    pWssRecvMessage->messageType = SIGNALING_TYPE_MESSAGE_ICE_CANDIDATE;
                } else if (strncmp(pair.value, "GO_AWAY", pair.valueLength) == 0) {
                    pWssRecvMessage->messageType = SIGNALING_TYPE_MESSAGE_GO_AWAY;
                } else if (strncmp(pair.value, "RECONNECT_ICE_SERVER", pair.valueLength) == 0) {
                    pWssRecvMessage->messageType = SIGNALING_TYPE_MESSAGE_RECONNECT_ICE_SERVER;
                } else if (strncmp(pair.value, "STATUS_RESPONSE", pair.valueLength) == 0) {
                    pWssRecvMessage->messageType = SIGNALING_TYPE_MESSAGE_STATUS_RESPONSE;
                } else {
                    pWssRecvMessage->messageType = SIGNALING_TYPE_MESSAGE_UNKNOWN;
                }
            } else if (strncmp(pair.key, "messagePayload", pair.keyLength) == 0) {
                pWssRecvMessage->pBase64EncodedPayload = pair.value;
                pWssRecvMessage->base64EncodedPayloadLength = pair.valueLength;
            } else if (strncmp(pair.key, "statusResponse", pair.keyLength) == 0) {
                if (pair.jsonType == JSONObject) {
                    pStatusResponseBuffer = pair.value;
                    statusResponseBufferLength = pair.valueLength;
                    statusResponseStart = 0;
                    statusResponseNext = 0;
                } else {
                    result = SIGNALING_RESULT_NOT_EXPECT_RESPONSE;
                    break;
                }
            } else if (pair.jsonType == JSONArray &&
                       pair.keyLength == strlen("IceServerList") &&
                       strncmp(pair.key, "IceServerList", pair.keyLength) == 0) {
                result = parseIceServerList(pair.value, pair.valueLength, &pWssRecvMessage->iceServerList);

                if (result != SIGNALING_RESULT_OK) {
                    break;
                }
            } else {
                /* Do nothing, ignore unknown tags. */
            }
            
            jsonResult = JSON_Iterate( pMessage, messageLength, &start, &next, &pair );
        }
    }

    if (result == SIGNALING_RESULT_OK && pStatusResponseBuffer != NULL) {
        jsonResult = JSON_Iterate( pStatusResponseBuffer, statusResponseBufferLength, &statusResponseStart, &statusResponseNext, &pair );

        if (jsonResult != JSONSuccess) {
            result = SIGNALING_RESULT_INVALID_STATUS_RESPONSE;
        }

        while (jsonResult == JSONSuccess) {
            if (strncmp(pair.key, "correlationId", pair.keyLength) == 0) {
                pWssRecvMessage->statusResponse.pCorrelationId = pair.value;
                pWssRecvMessage->statusResponse.correlationIdLength = pair.valueLength;
            } else if (strncmp(pair.key, "errorType", pair.keyLength) == 0) {
                pWssRecvMessage->statusResponse.pErrorType = pair.value;
                pWssRecvMessage->statusResponse.errorTypeLength = pair.valueLength;
            } else if (strncmp(pair.key, "statusCode", pair.keyLength) == 0) {
                pWssRecvMessage->statusResponse.pStatusCode = pair.value;
                pWssRecvMessage->statusResponse.statusCodeLength = pair.valueLength;
            } else if (strncmp(pair.key, "description", pair.keyLength) == 0) {
                pWssRecvMessage->statusResponse.pDescription = pair.value;
                pWssRecvMessage->statusResponse.descriptionLength = pair.valueLength;
            } else {
                /* Do nothing, ignore unknown tags. */
            }

            jsonResult = JSON_Iterate( pStatusResponseBuffer, statusResponseBufferLength, &statusResponseStart, &statusResponseNext, &pair );
        }
    }

    return result;
}
