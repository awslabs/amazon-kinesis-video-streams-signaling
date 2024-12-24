/* Standard includes. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* API includes. */
#include "signaling_api.h"

/* CoreJSON includes. */
#include "core_json.h"

/**
 * Helper macro to check if the AWS region is China region.
 */
#define SIGNALING_IS_CHINA_REGION( pAwsRegion )     \
        ( ( ( pAwsRegion )->awsRegionLength >= 3 ) &&   \
          ( strncmp( "cn-", ( pAwsRegion )->pAwsRegion, 3 ) == 0 ) )

/* Longest protocol string is is "WSS","HTTPS","WEBRTC". */
#define SIGNALING_GET_ENDPOINT_PROTOCOL_MAX_STRING_LENGTH    ( 23 ) /* Includes NULL terminator. */

/*-----------------------------------------------------------*/

static SignalingResult_t InterpretSnprintfReturnValue( int snprintfRetVal,
                                                       size_t bufferLength );

static char * GetStringFromMessageType( SignalingTypeMessage_t messageType );

static void ParseUris( const char * pUris,
                       size_t urisLength,
                       SignalingIceServer_t * pIceServer );

static SignalingResult_t ParseIceServerList( const char * pIceServerListBuffer,
                                             size_t iceServerListBufferLength,
                                             SignalingIceServer_t * pIceServers,
                                             size_t * pNumIceServers );

/*-----------------------------------------------------------*/

static SignalingResult_t InterpretSnprintfReturnValue( int snprintfRetVal,
                                                       size_t bufferLength )
{
    SignalingResult_t result;

    /* LCOV_EXCL_START */
    if( snprintfRetVal < 0 )
    {
        result = SIGNALING_RESULT_SNPRINTF_ERROR;
    }
    /* LCOV_EXCL_STOP  */
    else if( ( size_t ) snprintfRetVal >= bufferLength )
    {
        result = SIGNALING_RESULT_OUT_OF_MEMORY;
    }
    else
    {
        result = SIGNALING_RESULT_OK;
    }

    return result;
}

/*-----------------------------------------------------------*/

static char * GetStringFromMessageType( SignalingTypeMessage_t messageType )
{
    char * ret = NULL;

    switch( messageType )
    {
        case SIGNALING_TYPE_MESSAGE_SDP_OFFER:
            ret = "SDP_OFFER";
            break;

        case SIGNALING_TYPE_MESSAGE_SDP_ANSWER:
            ret = "SDP_ANSWER";
            break;

        case SIGNALING_TYPE_MESSAGE_ICE_CANDIDATE:
            ret = "ICE_CANDIDATE";
            break;

        default:
            ret = "UNKNOWN";
            break;
    }

    return ret;
}

/*-----------------------------------------------------------*/

static void ParseUris( const char * pUris,
                       size_t urisLength,
                       SignalingIceServer_t * pIceServer )
{
    JSONStatus_t jsonResult = JSONSuccess;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };

    jsonResult = JSON_Iterate( pUris, urisLength, &( start ), &( next ), &( pair ) );

    while( jsonResult == JSONSuccess )
    {
        pIceServer->pUris[ pIceServer->urisNum ] = pair.value;
        pIceServer->urisLength[ pIceServer->urisNum ] = pair.valueLength;
        pIceServer->urisNum++;

        jsonResult = JSON_Iterate( pUris, urisLength, &( start ), &( next ), &( pair ) );
    }
}

/*-----------------------------------------------------------*/

static SignalingResult_t ParseIceServerList( const char * pIceServerListBuffer,
                                             size_t iceServerListBufferLength,
                                             SignalingIceServer_t * pIceServers,
                                             size_t * pNumIceServers )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    JSONStatus_t jsonResult = JSONSuccess;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };
    const char * pIceServerBuffer;
    size_t iceServerBufferLength;
    size_t iceServerStart = 0, iceServerNext = 0;
    char ttlSecondsBuffer[ SIGNALING_ICE_SERVER_TTL_SECONDS_BUFFER_MAX ] = { 0 };
    size_t iceServerCount = 0;

    while( ( result == SIGNALING_RESULT_OK ) &&
           ( iceServerCount < *pNumIceServers ) )
    {
        jsonResult = JSON_Iterate( pIceServerListBuffer, iceServerListBufferLength, &( start ), &( next ), &( pair ) );

        if( jsonResult == JSONSuccess )
        {
            pIceServerBuffer = pair.value;
            iceServerBufferLength = pair.valueLength;
            iceServerStart = 0;
            iceServerNext = 0;

            jsonResult = JSON_Iterate( pIceServerBuffer, iceServerBufferLength, &( iceServerStart ), &( iceServerNext ), &( pair ) );

            while( jsonResult == JSONSuccess )
            {
                if( strncmp( pair.key, "Password", pair.keyLength ) == 0 )
                {
                    pIceServers[ iceServerCount ].pPassword = pair.value;
                    pIceServers[ iceServerCount ].passwordLength = pair.valueLength;
                }
                else if( strncmp( pair.key, "Ttl", pair.keyLength ) == 0 )
                {
                    if( pair.valueLength >= SIGNALING_ICE_SERVER_TTL_SECONDS_BUFFER_MAX )
                    {
                        /* Unexpected TTL value from cloud. */
                        result = SIGNALING_RESULT_INVALID_TTL;
                        break;
                    }

                    strncpy( ttlSecondsBuffer, pair.value, pair.valueLength );
                    pIceServers[ iceServerCount ].messageTtlSeconds = ( uint32_t ) strtoul( ttlSecondsBuffer, NULL, 10 );

                    if( ( pIceServers[ iceServerCount ].messageTtlSeconds < SIGNALING_ICE_SERVER_TTL_SECONDS_MIN ) ||
                        ( pIceServers[ iceServerCount ].messageTtlSeconds > SIGNALING_ICE_SERVER_TTL_SECONDS_MAX ) )
                    {
                        /* Unexpected TTL value from cloud. */
                        result = SIGNALING_RESULT_INVALID_TTL;
                        break;
                    }
                }
                else if( strncmp( pair.key, "Uris", pair.keyLength ) == 0 )
                {
                    ParseUris( pair.value, pair.valueLength, &( pIceServers[ iceServerCount ] ) );
                }
                else if( strncmp( pair.key, "Username", pair.keyLength ) == 0 )
                {
                    pIceServers[ iceServerCount ].pUserName = pair.value;
                    pIceServers[ iceServerCount ].userNameLength = pair.valueLength;
                }
                else
                {
                    /* Skip unknown messages. */
                }

                jsonResult = JSON_Iterate( pIceServerBuffer, iceServerBufferLength, &( iceServerStart ), &( iceServerNext ), &( pair ) );
            }

            iceServerCount++;
        }
        else
        {
            /* All parsed. */
            break;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        *pNumIceServers = iceServerCount;
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ConstructDescribeSignalingChannelRequest( SignalingAwsRegion_t * pAwsRegion,
                                                                      SignalingChannelName_t * pChannelName,
                                                                      SignalingRequest_t * pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int snprintfRetVal = 0;

    if( ( pAwsRegion == NULL ) ||
        ( pAwsRegion->pAwsRegion == NULL ) ||
        ( pChannelName == NULL ) ||
        ( pRequestBuffer == NULL ) ||
        ( pRequestBuffer->pUrl == NULL ) ||
        ( pRequestBuffer->pBody == NULL ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        if( SIGNALING_IS_CHINA_REGION( pAwsRegion ) )
        {
            snprintfRetVal = snprintf( pRequestBuffer->pUrl,
                                       pRequestBuffer->urlLength,
                                       "https://kinesisvideo.%.*s.amazonaws.com.cn/describeSignalingChannel",
                                       ( int ) pAwsRegion->awsRegionLength,
                                       pAwsRegion->pAwsRegion );
        }
        else
        {
            snprintfRetVal = snprintf( pRequestBuffer->pUrl,
                                       pRequestBuffer->urlLength,
                                       "https://kinesisvideo.%.*s.amazonaws.com/describeSignalingChannel",
                                       ( int ) pAwsRegion->awsRegionLength,
                                       pAwsRegion->pAwsRegion );
        }

        result = InterpretSnprintfReturnValue( snprintfRetVal, pRequestBuffer->urlLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->urlLength = snprintfRetVal;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        snprintfRetVal = snprintf( pRequestBuffer->pBody,
                                   pRequestBuffer->bodyLength,
                                   "{"
                                        "\"ChannelName\":\"%.*s\""
                                   "}",
                                   ( int ) pChannelName->channelNameLength,
                                   pChannelName->pChannelName );

        result = InterpretSnprintfReturnValue( snprintfRetVal, pRequestBuffer->bodyLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->bodyLength = snprintfRetVal;
        }
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ParseDescribeSignalingChannelResponse( const char * pMessage,
                                                                   size_t messageLength,
                                                                   SignalingChannelInfo_t * pChannelInfo )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    JSONStatus_t jsonResult;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };
    const char * pChannelInfoBuffer = NULL;
    size_t channelInfoBufferLength;
    size_t channelInfoStart = 0, channelInfoNext = 0;
    char ttlSecondsBuffer[ SIGNALING_CHANNEL_TTL_SECONDS_BUFFER_MAX ] = { 0 };

    if( ( pMessage == NULL ) ||
        ( pChannelInfo == NULL ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        jsonResult = JSON_Validate( pMessage, messageLength );

        if( jsonResult != JSONSuccess )
        {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        memset( pChannelInfo, 0, sizeof( SignalingChannelInfo_t ) );

        jsonResult = JSON_Iterate( pMessage, messageLength, &( start ), &( next ), &( pair ) );

        if( jsonResult == JSONSuccess )
        {
            if( ( pair.jsonType != JSONObject ) ||
                ( pair.keyLength != strlen( "ChannelInfo" ) ) ||
                ( strncmp( pair.key, "ChannelInfo", pair.keyLength ) != 0 ) )
            {
                result = SIGNALING_RESULT_UNEXPECTED_RESPONSE;
            }
            else
            {
                pChannelInfoBuffer = pair.value;
                channelInfoBufferLength = pair.valueLength;
            }
        }
        else
        {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        jsonResult = JSON_Iterate( pChannelInfoBuffer, channelInfoBufferLength, &( channelInfoStart ), &( channelInfoNext ), &( pair ) );

        while( jsonResult == JSONSuccess )
        {
            if( strncmp( pair.key, "ChannelARN", pair.keyLength ) == 0 )
            {
                pChannelInfo->channelArn.pChannelArn = pair.value;
                pChannelInfo->channelArn.channelArnLength = pair.valueLength;
            }
            else if( strncmp( pair.key, "ChannelName", pair.keyLength ) == 0 )
            {
                if( pair.valueLength < SIGNALING_CHANNEL_NAME_MAX_LEN )
                {
                    pChannelInfo->channelName.pChannelName = pair.value;
                    pChannelInfo->channelName.channelNameLength = pair.valueLength;
                }
                else
                {
                    result = SIGNALING_RESULT_INVALID_CHANNEL_NAME;
                }
            }
            else if( strncmp( pair.key, "ChannelStatus", pair.keyLength ) == 0 )
            {
                pChannelInfo->pChannelStatus = pair.value;
                pChannelInfo->channelStatusLength = pair.valueLength;
            }
            else if( strncmp( pair.key, "ChannelType", pair.keyLength ) == 0 )
            {
                if( strncmp( pair.value, "SINGLE_MASTER", pair.valueLength ) == 0 )
                {
                    pChannelInfo->channelType = SIGNALING_TYPE_CHANNEL_SINGLE_MASTER;
                }
                else
                {
                    result = SIGNALING_RESULT_INVALID_CHANNEL_TYPE;
                }
            }
            else if( strncmp( pair.key, "CreationTime", pair.keyLength ) == 0 )
            {
                /* We do not need CreationTime as of now. */
            }
            else if( strncmp( pair.key, "SingleMasterConfiguration", pair.keyLength ) == 0 )
            {
                const char * pConfigBuffer = pair.value;
                size_t configBufferLength = pair.valueLength;
                size_t configStart = 0, configNext = 0;

                jsonResult = JSON_Iterate( pConfigBuffer, configBufferLength, &( configStart ), &( configNext ), &( pair ) );

                if( jsonResult == JSONSuccess )
                {
                    if( strncmp( pair.key, "MessageTtlSeconds", pair.keyLength ) == 0 )
                    {
                        if( pair.valueLength >= SIGNALING_CHANNEL_TTL_SECONDS_BUFFER_MAX )
                        {
                            /* Unexpected TTL value from cloud. */
                            result = SIGNALING_RESULT_INVALID_TTL;
                            break;
                        }

                        strncpy( ttlSecondsBuffer, pair.value, pair.valueLength );
                        pChannelInfo->messageTtlSeconds = ( uint32_t ) strtoul( ttlSecondsBuffer, NULL, 10 );

                        if( ( pChannelInfo->messageTtlSeconds < SIGNALING_CHANNEL_TTL_SECONDS_MIN ) ||
                            ( pChannelInfo->messageTtlSeconds > SIGNALING_CHANNEL_TTL_SECONDS_MAX ) )
                        {
                            /* Unexpected TTL value from cloud. */
                            result = SIGNALING_RESULT_INVALID_TTL;
                        }
                    }
                    else
                    {
                        /* Unknown attribute. */
                        result = SIGNALING_RESULT_INVALID_JSON;
                    }
                }
                else
                {
                    /* Invalid single master configuration. */
                    result = SIGNALING_RESULT_INVALID_JSON;
                }
            }
            else if( strncmp( pair.key, "Version", pair.keyLength ) == 0 )
            {
                pChannelInfo->pVersion = pair.value;
                pChannelInfo->versionLength = pair.valueLength;
            }
            else
            {
                /* Skip unknown attributes. */
            }

            if( result != SIGNALING_RESULT_OK )
            {
                break;
            }

            jsonResult = JSON_Iterate( pChannelInfoBuffer, channelInfoBufferLength, &( channelInfoStart ), &( channelInfoNext ), &( pair ) );
        }
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ConstructFetchTemporaryCredentialRequest( const char * pEndpoint,
                                                                      size_t endpointLength,
                                                                      const char * pRoleAlias,
                                                                      size_t roleAliasLength,
                                                                      SignalingRequest_t * pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int snprintfRetVal = 0;

    if( ( pEndpoint == NULL ) ||
        ( pRoleAlias == NULL ) ||
        ( pRequestBuffer == NULL ) ||
        ( pRequestBuffer->pUrl == NULL ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        snprintfRetVal = snprintf( pRequestBuffer->pUrl,
                                   pRequestBuffer->urlLength,
                                   "https://%.*s/role-aliases/%.*s/credentials",
                                   ( int ) endpointLength,
                                   pEndpoint,
                                   ( int ) roleAliasLength,
                                   pRoleAlias );

        result = InterpretSnprintfReturnValue( snprintfRetVal,
                                               pRequestBuffer->urlLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->urlLength = snprintfRetVal;
        }
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ParseFetchTemporaryCredentialsResponse( const char * pMessage,
                                                                    size_t messageLength,
                                                                    SignalingCredential_t * pCredentials )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    JSONStatus_t jsonResult;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };
    const char * pCredentialsBuffer = NULL;
    size_t credentialsBufferLength;
    size_t credentialsStart = 0, credentialsNext = 0;
    bool hasAccessKeyId = false;
    bool hasSecretKey = false;
    bool hasSessionToken = false;
    bool hasExpiration = false;

    if( ( pMessage == NULL ) ||
        ( pCredentials == NULL ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        jsonResult = JSON_Validate( pMessage,
                                    messageLength );

        if( jsonResult != JSONSuccess )
        {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        memset( pCredentials, 0, sizeof( SignalingCredential_t ) );

        jsonResult = JSON_Iterate( pMessage, messageLength, &( start ), &( next ), &( pair ) );

        if( jsonResult == JSONSuccess )
        {
            if( ( pair.jsonType != JSONObject ) ||
                ( pair.keyLength != strlen( "credentials" ) ) ||
                ( strncmp( pair.key, "credentials", pair.keyLength ) != 0 ) )
            {
                result = SIGNALING_RESULT_UNEXPECTED_RESPONSE;
            }
            else
            {
                pCredentialsBuffer = pair.value;
                credentialsBufferLength = pair.valueLength;
            }
        }
        else
        {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        jsonResult = JSON_Iterate( pCredentialsBuffer, credentialsBufferLength, &( credentialsStart ), &( credentialsNext ), &( pair ) );

        while( jsonResult == JSONSuccess )
        {
            if( strncmp( pair.key,
                         "accessKeyId",
                         pair.keyLength ) == 0 )
            {
                if( pair.valueLength < MAX_ACCESS_KEY_LEN )
                {
                    pCredentials->pAccessKeyId = pair.value;
                    pCredentials->accessKeyIdLength = pair.valueLength;
                    hasAccessKeyId = true;
                }
                else
                {
                    result = SIGNALING_RESULT_ACCESS_KEY_LENGTH_TOO_LARGE;
                }

            }
            else if( strncmp( pair.key,
                              "secretAccessKey",
                              pair.keyLength ) == 0 )
            {
                if( pair.valueLength < MAX_SECRET_KEY_LEN )
                {
                    pCredentials->pSecretAccessKey = pair.value;
                    pCredentials->secretAccessKeyLength = pair.valueLength;
                    hasSecretKey = true;
                }
                else
                {
                    result = SIGNALING_RESULT_SECRET_ACCESS_KEY_LENGTH_TOO_LARGE;
                }
            }
            else if( strncmp( pair.key,
                              "sessionToken",
                              pair.keyLength ) == 0 )
            {
                if( pair.valueLength < MAX_SESSION_TOKEN_LEN )
                {
                    pCredentials->sessionToken = pair.value;
                    pCredentials->sessionTokenLength = pair.valueLength;
                    hasSessionToken = true;
                }
                else
                {
                    result = SIGNALING_RESULT_SESSION_TOKEN_LENGTH_TOO_LARGE;
                }
            }
            else if( strncmp( pair.key,
                              "expiration",
                              pair.keyLength ) == 0 )
            {
                if( pair.valueLength < MAX_EXPIRATION_LEN )
                {
                    pCredentials->expiration = pair.value;
                    pCredentials->expirationLength = pair.valueLength;
                    hasExpiration = true;

                }
                else
                {
                    result = SIGNALING_RESULT_EXPIRATION_LENGTH_TOO_LARGE;
                }
            }
            else
            {
                /* Skip unknown attributes. */
            }

            if( result != SIGNALING_RESULT_OK )
            {
                break;
            }

            jsonResult = JSON_Iterate( pCredentialsBuffer, credentialsBufferLength, &( credentialsStart ), &( credentialsNext ), &( pair ) );
        }
    }

    if( ( result == SIGNALING_RESULT_OK ) && ( !hasAccessKeyId || !hasSecretKey || !hasSessionToken || !hasExpiration ) )
    {
        result = SIGNALING_RESULT_UNEXPECTED_RESPONSE;
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ConstructDescribeMediaStorageConfigRequest( SignalingAwsRegion_t * pAwsRegion,
                                                                        SignalingChannelArn_t * pChannelArn,
                                                                        SignalingRequest_t * pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int snprintfRetVal = 0;

    if( ( pAwsRegion == NULL ) ||
        ( pAwsRegion->pAwsRegion == NULL ) ||
        ( pChannelArn == NULL ) ||
        ( pRequestBuffer == NULL ) ||
        ( pRequestBuffer->pUrl == NULL ) ||
        ( pRequestBuffer->pBody == NULL ) ||
        ( pChannelArn->pChannelArn == NULL ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        if( SIGNALING_IS_CHINA_REGION( pAwsRegion ) )
        {
            snprintfRetVal = snprintf( pRequestBuffer->pUrl,
                                       pRequestBuffer->urlLength,
                                       "https://kinesisvideo.%.*s.amazonaws.com.cn/describeMediaStorageConfiguration",
                                       ( int ) pAwsRegion->awsRegionLength,
                                       pAwsRegion->pAwsRegion );
        }
        else
        {
            snprintfRetVal = snprintf( pRequestBuffer->pUrl,
                                       pRequestBuffer->urlLength,
                                       "https://kinesisvideo.%.*s.amazonaws.com/describeMediaStorageConfiguration",
                                       ( int ) pAwsRegion->awsRegionLength,
                                       pAwsRegion->pAwsRegion );
        }

        result = InterpretSnprintfReturnValue( snprintfRetVal, pRequestBuffer->urlLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->urlLength = snprintfRetVal;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        snprintfRetVal = snprintf( pRequestBuffer->pBody,
                                   pRequestBuffer->bodyLength,
                                   "{"
                                        "\"ChannelARN\":\"%.*s\""
                                   "}",
                                   ( int ) pChannelArn->channelArnLength,
                                   pChannelArn->pChannelArn );

        result = InterpretSnprintfReturnValue( snprintfRetVal, pRequestBuffer->bodyLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->bodyLength = snprintfRetVal;
        }
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ParseDescribeMediaStorageConfigResponse( const char * pMessage,
                                                                     size_t messageLength,
                                                                     SignalingMediaStorageConfig_t * pMediaStorageConfig )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    JSONStatus_t jsonResult;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };
    const char * pMediaStorageConfigBuffer = NULL;
    size_t mediaStorageConfigBufferLength;
    size_t mediaStorageConfigStart = 0, mediaStorageConfigNext = 0;

    if( ( pMessage == NULL ) ||
        ( pMediaStorageConfig == NULL ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        jsonResult = JSON_Validate( pMessage, messageLength );

        if( jsonResult != JSONSuccess )
        {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        memset( pMediaStorageConfig, 0, sizeof( SignalingMediaStorageConfig_t ) );

        jsonResult = JSON_Iterate( pMessage, messageLength, &( start ), &( next ), &( pair ) );

        if( jsonResult == JSONSuccess )
        {
            if( ( pair.jsonType != JSONObject ) ||
                ( pair.keyLength != strlen( "MediaStorageConfiguration" ) ) ||
                ( strncmp( pair.key, "MediaStorageConfiguration", pair.keyLength ) != 0 ) )
            {
                result = SIGNALING_RESULT_UNEXPECTED_RESPONSE;
            }
            else
            {
                pMediaStorageConfigBuffer = pair.value;
                mediaStorageConfigBufferLength = pair.valueLength;
            }
        }
        else
        {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        jsonResult = JSON_Iterate( pMediaStorageConfigBuffer, mediaStorageConfigBufferLength, &( mediaStorageConfigStart ), &( mediaStorageConfigNext ), &( pair ) );

        while( jsonResult == JSONSuccess )
        {
            if( strncmp( pair.key, "Status", pair.keyLength ) == 0 )
            {
                pMediaStorageConfig->pStatus = pair.value;
                pMediaStorageConfig->statusLength = pair.valueLength;
            }
            else if( strncmp( pair.key, "StreamARN", pair.keyLength ) == 0 )
            {
                pMediaStorageConfig->pStreamArn = pair.value;
                pMediaStorageConfig->streamArnLength = pair.valueLength;
            }
            else
            {
                /* Skip unknown attributes. */
            }

            jsonResult = JSON_Iterate( pMediaStorageConfigBuffer, mediaStorageConfigBufferLength, &( mediaStorageConfigStart ), &( mediaStorageConfigNext ), &( pair ) );
        }
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ConstructCreateSignalingChannelRequest( SignalingAwsRegion_t * pAwsRegion,
                                                                    CreateSignalingChannelRequestInfo_t * pCreateSignalingChannelRequestInfo,
                                                                    SignalingRequest_t * pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int snprintfRetVal = 0;
    size_t remainingLength = 0, currentIndex = 0, i;

    if( ( pAwsRegion == NULL ) ||
        ( pAwsRegion->pAwsRegion == NULL ) ||
        ( pRequestBuffer == NULL ) ||
        ( pCreateSignalingChannelRequestInfo == NULL ) ||
        ( pRequestBuffer->pUrl == NULL ) ||
        ( pRequestBuffer->pBody == NULL ) ||
        ( ( pCreateSignalingChannelRequestInfo->numTags > 0 ) && ( pCreateSignalingChannelRequestInfo->pTags == NULL ) ) ||
        ( pCreateSignalingChannelRequestInfo->channelName.channelNameLength >= SIGNALING_CHANNEL_NAME_MAX_LEN ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        if( SIGNALING_IS_CHINA_REGION( pAwsRegion ) )
        {
            snprintfRetVal = snprintf( pRequestBuffer->pUrl,
                                       pRequestBuffer->urlLength,
                                       "https://kinesisvideo.%.*s.amazonaws.com.cn/createSignalingChannel",
                                       ( int ) pAwsRegion->awsRegionLength,
                                       pAwsRegion->pAwsRegion );
        }
        else
        {
            snprintfRetVal = snprintf( pRequestBuffer->pUrl,
                                       pRequestBuffer->urlLength,
                                       "https://kinesisvideo.%.*s.amazonaws.com/createSignalingChannel",
                                       ( int ) pAwsRegion->awsRegionLength,
                                       pAwsRegion->pAwsRegion );
        }

        result = InterpretSnprintfReturnValue( snprintfRetVal, pRequestBuffer->urlLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->urlLength = snprintfRetVal;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        remainingLength = pRequestBuffer->bodyLength;

        snprintfRetVal = snprintf( &( pRequestBuffer->pBody[ currentIndex ] ),
                                   remainingLength,
                                   "{"
                                        "\"ChannelName\":\"%.*s\","
                                        "\"ChannelType\":\"%s\","
                                        "\"SingleMasterConfiguration\":"
                                        "{"
                                            "\"MessageTtlSeconds\":%u"
                                        "}",
                                   ( int ) pCreateSignalingChannelRequestInfo->channelName.channelNameLength,
                                   pCreateSignalingChannelRequestInfo->channelName.pChannelName,
                                   ( pCreateSignalingChannelRequestInfo->channelType == SIGNALING_TYPE_CHANNEL_SINGLE_MASTER ) ? "SINGLE_MASTER" : "UNKOWN",
                                   pCreateSignalingChannelRequestInfo->messageTtlSeconds );

        result = InterpretSnprintfReturnValue( snprintfRetVal, remainingLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->bodyLength = snprintfRetVal;
            remainingLength -= snprintfRetVal;
            currentIndex += snprintfRetVal;
        }
    }

    if( ( result == SIGNALING_RESULT_OK ) && ( pCreateSignalingChannelRequestInfo->numTags > 0 ) )
    {
        snprintfRetVal = snprintf( &( pRequestBuffer->pBody[ currentIndex ] ),
                                   remainingLength,
                                   ","
                                   "\"Tags\":"
                                   "[" );

        result = InterpretSnprintfReturnValue( snprintfRetVal, remainingLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->bodyLength += snprintfRetVal;
            remainingLength -= snprintfRetVal;
            currentIndex += snprintfRetVal;
        }

        for( i = 0; ( i < pCreateSignalingChannelRequestInfo->numTags ) && ( result == SIGNALING_RESULT_OK ); i++ )
        {
            if( i == 0 )
            {
                snprintfRetVal = snprintf( &( pRequestBuffer->pBody[ currentIndex ] ),
                                           remainingLength,
                                           "{"
                                                "\"Key\":\"%.*s\","
                                                "\"Value\":\"%.*s\""
                                           "}",
                                           ( int ) pCreateSignalingChannelRequestInfo->pTags[ i ].nameLength,
                                           pCreateSignalingChannelRequestInfo->pTags[ i ].pName,
                                           ( int ) pCreateSignalingChannelRequestInfo->pTags[ i ].valueLength,
                                           pCreateSignalingChannelRequestInfo->pTags[ i ].pValue );
            }
            else
            {
                snprintfRetVal = snprintf( &( pRequestBuffer->pBody[ currentIndex ] ),
                                           remainingLength,
                                           ",{"
                                                "\"Key\":\"%.*s\","
                                                "\"Value\":\"%.*s\""
                                           "}",
                                           ( int ) pCreateSignalingChannelRequestInfo->pTags[ i ].nameLength,
                                           pCreateSignalingChannelRequestInfo->pTags[ i ].pName,
                                           ( int ) pCreateSignalingChannelRequestInfo->pTags[ i ].valueLength,
                                           pCreateSignalingChannelRequestInfo->pTags[ i ].pValue );
            }

            result = InterpretSnprintfReturnValue( snprintfRetVal, remainingLength );

            if( result == SIGNALING_RESULT_OK )
            {
                pRequestBuffer->bodyLength += snprintfRetVal;
                remainingLength -= snprintfRetVal;
                currentIndex += snprintfRetVal;
            }
        }

        if( result == SIGNALING_RESULT_OK )
        {
            snprintfRetVal = snprintf( &( pRequestBuffer->pBody[ currentIndex ] ),
                                       remainingLength,
                                       "]" );

            result = InterpretSnprintfReturnValue( snprintfRetVal, remainingLength );

            if( result == SIGNALING_RESULT_OK )
            {
                pRequestBuffer->bodyLength += snprintfRetVal;
                remainingLength -= snprintfRetVal;
                currentIndex += snprintfRetVal;
            }
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        snprintfRetVal = snprintf( &( pRequestBuffer->pBody[ currentIndex ] ),
                                   remainingLength,
                                   "}" );

        result = InterpretSnprintfReturnValue( snprintfRetVal, remainingLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->bodyLength += snprintfRetVal;
            remainingLength -= snprintfRetVal;
            currentIndex += snprintfRetVal;
        }
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ParseCreateSignalingChannelResponse( const char * pMessage,
                                                                 size_t messageLength,
                                                                 SignalingChannelArn_t * pChannelArn )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    JSONStatus_t jsonResult;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };

    if( ( pMessage == NULL ) ||
        ( pChannelArn == NULL ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        jsonResult = JSON_Validate( pMessage, messageLength );

        if( jsonResult != JSONSuccess )
        {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        memset( pChannelArn, 0, sizeof( SignalingChannelArn_t ) );

        jsonResult = JSON_Iterate( pMessage, messageLength, &( start ), &( next ), &( pair ) );

        if( jsonResult == JSONSuccess )
        {
            if( strncmp( pair.key, "ChannelARN", pair.keyLength ) == 0 )
            {
                pChannelArn->pChannelArn = pair.value;
                pChannelArn->channelArnLength = pair.valueLength;
            }
            else
            {
                result = SIGNALING_RESULT_UNEXPECTED_RESPONSE;
            }
        }
        else
        {
            result = SIGNALING_RESULT_UNEXPECTED_RESPONSE;
        }
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ConstructGetSignalingChannelEndpointRequest( SignalingAwsRegion_t * pAwsRegion,
                                                                         GetSignalingChannelEndpointRequestInfo_t * pGetSignalingChannelEndpointRequestInfo,
                                                                         SignalingRequest_t * pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int snprintfRetVal = 0;
    char protocolsString[ SIGNALING_GET_ENDPOINT_PROTOCOL_MAX_STRING_LENGTH ] = { 0 };
    size_t protocolIndex = 0;
    uint8_t isFirstProtocol = 1;

    if( ( pAwsRegion == NULL ) ||
        ( pAwsRegion->pAwsRegion == NULL ) ||
        ( pRequestBuffer == NULL ) ||
        ( pGetSignalingChannelEndpointRequestInfo == NULL ) ||
        ( pRequestBuffer->pUrl == NULL ) ||
        ( pRequestBuffer->pBody == NULL ) ||
        ( pGetSignalingChannelEndpointRequestInfo->channelArn.pChannelArn == NULL ) ||
        ( ( pGetSignalingChannelEndpointRequestInfo->role != SIGNALING_ROLE_MASTER ) && ( pGetSignalingChannelEndpointRequestInfo->role != SIGNALING_ROLE_VIEWER ) ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        if( SIGNALING_IS_CHINA_REGION( pAwsRegion ) )
        {
            snprintfRetVal = snprintf( pRequestBuffer->pUrl,
                                       pRequestBuffer->urlLength,
                                       "https://kinesisvideo.%.*s.amazonaws.com.cn/getSignalingChannelEndpoint",
                                       ( int ) pAwsRegion->awsRegionLength,
                                       pAwsRegion->pAwsRegion );
        }
        else
        {
            snprintfRetVal = snprintf( pRequestBuffer->pUrl,
                                       pRequestBuffer->urlLength,
                                       "https://kinesisvideo.%.*s.amazonaws.com/getSignalingChannelEndpoint",
                                       ( int ) pAwsRegion->awsRegionLength,
                                       pAwsRegion->pAwsRegion );
        }

        result = InterpretSnprintfReturnValue( snprintfRetVal, pRequestBuffer->urlLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->urlLength = snprintfRetVal;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        if( ( pGetSignalingChannelEndpointRequestInfo->protocols & SIGNALING_PROTOCOL_WEBSOCKET_SECURE ) != 0 )
        {
            memcpy( ( void * ) &( protocolsString[ protocolIndex ] ),
                    ( const void * ) "\"WSS\"",
                    5 );
            protocolIndex += 5;

            isFirstProtocol = 0;
        }

        if( ( pGetSignalingChannelEndpointRequestInfo->protocols & SIGNALING_PROTOCOL_HTTPS ) != 0 )
        {
            if( isFirstProtocol == 0 )
            {
                memcpy( ( void * ) &( protocolsString[ protocolIndex ] ),
                        ( const void * ) ",",
                        1 );
                protocolIndex += 1;
            }

            memcpy( ( void * ) &( protocolsString[ protocolIndex ] ),
                    ( const void * ) "\"HTTPS\"",
                    8 );
            protocolIndex += 7;

            isFirstProtocol = 0;
        }

        if( ( pGetSignalingChannelEndpointRequestInfo->protocols & SIGNALING_PROTOCOL_WEBRTC ) != 0 )
        {
            if( isFirstProtocol == 0 )
            {
                memcpy( ( void * ) &( protocolsString[ protocolIndex ] ),
                        ( const void * ) ",",
                        2 );
                protocolIndex += 1;
            }

            memcpy( ( void * ) &( protocolsString[ protocolIndex ] ),
                    ( const void * ) "\"WEBRTC\"",
                    9 );
            protocolIndex += 8;

            isFirstProtocol = 0;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        snprintfRetVal = snprintf( pRequestBuffer->pBody,
                                   pRequestBuffer->bodyLength,
                                   "{"
                                        "\"ChannelARN\":\"%.*s\","
                                        "\"SingleMasterChannelEndpointConfiguration\":"
                                        "{"
                                            "\"Protocols\":[%.*s],"
                                            "\"Role\":\"%s\""
                                        "}"
                                   "}",
                                   ( int ) pGetSignalingChannelEndpointRequestInfo->channelArn.channelArnLength,
                                   pGetSignalingChannelEndpointRequestInfo->channelArn.pChannelArn,
                                   ( int ) protocolIndex,
                                   protocolsString,
                                   ( pGetSignalingChannelEndpointRequestInfo->role == SIGNALING_ROLE_MASTER ) ? "MASTER" : "VIEWER" );

        result = InterpretSnprintfReturnValue( snprintfRetVal, pRequestBuffer->bodyLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->bodyLength = snprintfRetVal;
        }
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ParseGetSignalingChannelEndpointResponse( const char * pMessage,
                                                                      size_t messageLength,
                                                                      SignalingChannelEndpoints_t * pSignalingChannelEndpoints )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    JSONStatus_t jsonResult;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };
    const char * pResourceEndpointListBuffer = NULL;
    size_t resourceEndpointListBufferLength;
    size_t resourceEndpointStart = 0, resourceEndpointNext = 0;
    const char * pEndpointListBuffer = NULL;
    size_t endpointListBufferLength;
    size_t endpointListStart = 0, endpointListNext = 0;
    const char * pEndpoint = NULL;
    size_t endpointLength;
    const char * pProtocol = NULL;
    size_t protocolLength = 0;

    if( ( pMessage == NULL ) ||
        ( pSignalingChannelEndpoints == NULL ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        jsonResult = JSON_Validate( pMessage, messageLength );

        if( jsonResult != JSONSuccess )
        {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        memset( pSignalingChannelEndpoints, 0, sizeof( SignalingChannelEndpoints_t ) );

        jsonResult = JSON_Iterate( pMessage, messageLength, &( start ), &( next ), &( pair ) );

        if( jsonResult == JSONSuccess )
        {
            if( ( pair.jsonType != JSONArray ) ||
                ( pair.keyLength != strlen( "ResourceEndpointList" ) ) ||
                ( strncmp( pair.key, "ResourceEndpointList", pair.keyLength ) != 0 ) )
            {
                result = SIGNALING_RESULT_UNEXPECTED_RESPONSE;
            }
            else
            {
                pResourceEndpointListBuffer = pair.value;
                resourceEndpointListBufferLength = pair.valueLength;
            }
        }
        else
        {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    while( result == SIGNALING_RESULT_OK )
    {
        jsonResult = JSON_Iterate( pResourceEndpointListBuffer, resourceEndpointListBufferLength, &( resourceEndpointStart ), &( resourceEndpointNext ), &( pair ) );

        if( jsonResult == JSONSuccess )
        {
            pEndpointListBuffer = pair.value;
            endpointListBufferLength = pair.valueLength;
            endpointListStart = 0;
            endpointListNext = 0;
            pEndpoint = NULL;
            endpointLength = 0;
            pProtocol = NULL;
            protocolLength = 0;

            jsonResult = JSON_Iterate( pEndpointListBuffer, endpointListBufferLength, &( endpointListStart ), &( endpointListNext ), &( pair ) );

            while( jsonResult == JSONSuccess )
            {
                if( strncmp( pair.key, "Protocol", pair.keyLength ) == 0 )
                {
                    pProtocol = pair.value;
                    protocolLength = pair.valueLength;
                }
                else if( strncmp( pair.key, "ResourceEndpoint", pair.keyLength ) == 0 )
                {
                    pEndpoint = pair.value;
                    endpointLength = pair.valueLength;
                }

                jsonResult = JSON_Iterate( pEndpointListBuffer, endpointListBufferLength, &( endpointListStart ), &( endpointListNext ), &( pair ) );
            }

            if( ( pEndpoint != NULL ) && ( pProtocol != NULL ) )
            {
                if( ( protocolLength == 3 ) && ( ( strncmp( pProtocol, "WSS", 3 ) == 0 ) ||
                                                 ( strncmp( pProtocol, "wss", 3 ) == 0 ) ) )
                {
                    pSignalingChannelEndpoints->wssEndpoint.pEndpoint = pEndpoint;
                    pSignalingChannelEndpoints->wssEndpoint.endpointLength = endpointLength;
                }
                else if( ( protocolLength == 5 ) && ( ( strncmp( pProtocol, "HTTPS", 5 ) == 0 ) ||
                                                      ( strncmp( pProtocol, "https", 5 ) == 0 ) ) )
                {
                    pSignalingChannelEndpoints->httpsEndpoint.pEndpoint = pEndpoint;
                    pSignalingChannelEndpoints->httpsEndpoint.endpointLength = endpointLength;
                }
                else if( ( protocolLength == 6 ) && ( ( strncmp( pProtocol, "WEBRTC", 6 ) == 0 ) ||
                                                      ( strncmp( pProtocol, "webrtc", 6 ) == 0 ) ) )
                {
                    pSignalingChannelEndpoints->webrtcEndpoint.pEndpoint = pEndpoint;
                    pSignalingChannelEndpoints->webrtcEndpoint.endpointLength = endpointLength;
                }
                else
                {
                    result = SIGNALING_RESULT_INVALID_PROTOCOL;
                }
            }
        }
        else
        {
            /* All parsed. */
            break;
        }
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ConstructGetIceServerConfigRequest( SignalingChannelEndpoint_t * pHttpsEndpoint,
                                                                GetIceServerConfigRequestInfo_t * pGetIceServerConfigRequestInfo,
                                                                SignalingRequest_t * pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int snprintfRetVal = 0;

    if( ( pHttpsEndpoint == NULL ) ||
        ( pHttpsEndpoint->pEndpoint == NULL ) ||
        ( pRequestBuffer == NULL ) ||
        ( pGetIceServerConfigRequestInfo == NULL ) ||
        ( pRequestBuffer->pUrl == NULL ) ||
        ( pRequestBuffer->pBody == NULL ) ||
        ( pGetIceServerConfigRequestInfo->pClientId == NULL ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        snprintfRetVal = snprintf( pRequestBuffer->pUrl,
                                   pRequestBuffer->urlLength,
                                   "%.*s/v1/get-ice-server-config",
                                   ( int ) pHttpsEndpoint->endpointLength,
                                   pHttpsEndpoint->pEndpoint );

        result = InterpretSnprintfReturnValue( snprintfRetVal, pRequestBuffer->urlLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->urlLength = snprintfRetVal;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        snprintfRetVal = snprintf( pRequestBuffer->pBody,
                                   pRequestBuffer->bodyLength,
                                   "{"
                                        "\"ChannelARN\":\"%.*s\","
                                        "\"ClientId\":\"%.*s\","
                                        "\"Service\":\"TURN\""
                                   "}",
                                   ( int ) pGetIceServerConfigRequestInfo->channelArn.channelArnLength,
                                   pGetIceServerConfigRequestInfo->channelArn.pChannelArn,
                                   ( int ) pGetIceServerConfigRequestInfo->clientIdLength,
                                   pGetIceServerConfigRequestInfo->pClientId );

        result = InterpretSnprintfReturnValue( snprintfRetVal, pRequestBuffer->bodyLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->bodyLength = snprintfRetVal;
        }
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ParseGetIceServerConfigResponse( const char * pMessage,
                                                             size_t messageLength,
                                                             SignalingIceServer_t * pIceServers,
                                                             size_t * pNumIceServers )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    JSONStatus_t jsonResult;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };
    const char * pIceServerListBuffer = NULL;
    size_t iceServerListBufferLength;

    if( ( pMessage == NULL ) ||
        ( pIceServers == NULL ) ||
        ( pNumIceServers == NULL ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        jsonResult = JSON_Validate( pMessage, messageLength );

        if( jsonResult != JSONSuccess )
        {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        memset( pIceServers, 0, sizeof( SignalingIceServer_t ) * ( *pNumIceServers ) );

        jsonResult = JSON_Iterate( pMessage, messageLength, &( start ), &( next ), &( pair ) );

        if( jsonResult == JSONSuccess )
        {
            if( ( pair.jsonType != JSONArray ) ||
                ( pair.keyLength != strlen( "IceServerList" ) ) ||
                ( strncmp( pair.key, "IceServerList", pair.keyLength ) != 0 ) )
            {
                result = SIGNALING_RESULT_UNEXPECTED_RESPONSE;
            }
            else
            {
                pIceServerListBuffer = pair.value;
                iceServerListBufferLength = pair.valueLength;
            }
        }
        else
        {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        result = ParseIceServerList( pIceServerListBuffer, iceServerListBufferLength, pIceServers, pNumIceServers );
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ConstructJoinStorageSessionRequest( SignalingChannelEndpoint_t * pWebrtcEndpoint,
                                                                JoinStorageSessionRequestInfo_t * pJoinStorageSessionRequestInfo,
                                                                SignalingRequest_t * pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int snprintfRetVal = 0;

    if( ( pWebrtcEndpoint == NULL ) ||
        ( pWebrtcEndpoint->pEndpoint == NULL ) ||
        ( pRequestBuffer == NULL ) ||
        ( pJoinStorageSessionRequestInfo == NULL ) ||
        ( pRequestBuffer->pUrl == NULL ) ||
        ( pRequestBuffer->pBody == NULL ) ||
        ( pJoinStorageSessionRequestInfo->channelArn.pChannelArn == NULL ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        snprintfRetVal = snprintf( pRequestBuffer->pUrl,
                                   pRequestBuffer->urlLength,
                                   "%.*s/joinStorageSession",
                                   ( int ) pWebrtcEndpoint->endpointLength,
                                   pWebrtcEndpoint->pEndpoint );

        result = InterpretSnprintfReturnValue( snprintfRetVal, pRequestBuffer->urlLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->urlLength = snprintfRetVal;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        if( pJoinStorageSessionRequestInfo->role == SIGNALING_ROLE_MASTER )
        {
            snprintfRetVal = snprintf( pRequestBuffer->pBody,
                                       pRequestBuffer->bodyLength,
                                       "{"
                                            "\"channelArn\":\"%.*s\""
                                       "}",
                                       ( int ) pJoinStorageSessionRequestInfo->channelArn.channelArnLength,
                                       pJoinStorageSessionRequestInfo->channelArn.pChannelArn );
        }
        else
        {
            snprintfRetVal = snprintf( pRequestBuffer->pBody,
                                       pRequestBuffer->bodyLength,
                                       "{"
                                            "\"channelArn\":\"%.*s\","
                                            "\"clientId\":\"%.*s\""
                                       "}",
                                       ( int ) pJoinStorageSessionRequestInfo->channelArn.channelArnLength,
                                       pJoinStorageSessionRequestInfo->channelArn.pChannelArn,
                                       ( int ) pJoinStorageSessionRequestInfo->clientIdLength,
                                       pJoinStorageSessionRequestInfo->pClientId );
        }

        result = InterpretSnprintfReturnValue( snprintfRetVal, pRequestBuffer->bodyLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->bodyLength = snprintfRetVal;
        }
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ConstructDeleteSignalingChannelRequest( SignalingAwsRegion_t * pAwsRegion,
                                                                    DeleteSignalingChannelRequestInfo_t * pDeleteSignalingChannelRequestInfo,
                                                                    SignalingRequest_t * pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int snprintfRetVal = 0;

    if( ( pAwsRegion == NULL ) ||
        ( pAwsRegion->pAwsRegion == NULL ) ||
        ( pRequestBuffer == NULL ) ||
        ( pDeleteSignalingChannelRequestInfo == NULL ) ||
        ( pRequestBuffer->pUrl == NULL ) ||
        ( pRequestBuffer->pBody == NULL ) ||
        ( pDeleteSignalingChannelRequestInfo->channelArn.pChannelArn == NULL ) ||
        ( pDeleteSignalingChannelRequestInfo->pVersion == NULL ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        if( SIGNALING_IS_CHINA_REGION( pAwsRegion ) )
        {
            snprintfRetVal = snprintf( pRequestBuffer->pUrl,
                                       pRequestBuffer->urlLength,
                                       "https://kinesisvideo.%.*s.amazonaws.com.cn/deleteSignalingChannel",
                                       ( int ) pAwsRegion->awsRegionLength,
                                       pAwsRegion->pAwsRegion );
        }
        else
        {
            snprintfRetVal = snprintf( pRequestBuffer->pUrl,
                                       pRequestBuffer->urlLength,
                                       "https://kinesisvideo.%.*s.amazonaws.com/deleteSignalingChannel",
                                       ( int ) pAwsRegion->awsRegionLength,
                                       pAwsRegion->pAwsRegion );
        }

        result = InterpretSnprintfReturnValue( snprintfRetVal, pRequestBuffer->urlLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->urlLength = snprintfRetVal;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        snprintfRetVal = snprintf( pRequestBuffer->pBody,
                                   pRequestBuffer->bodyLength,
                                   "{"
                                   "\"ChannelARN\":\"%.*s\","
                                   "\"CurrentVersion\":\"%.*s\""
                                   "}",
                                   ( int ) pDeleteSignalingChannelRequestInfo->channelArn.channelArnLength,
                                   pDeleteSignalingChannelRequestInfo->channelArn.pChannelArn,
                                   ( int ) pDeleteSignalingChannelRequestInfo->versionLength,
                                   pDeleteSignalingChannelRequestInfo->pVersion );

        result = InterpretSnprintfReturnValue( snprintfRetVal, pRequestBuffer->bodyLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->bodyLength = snprintfRetVal;
        }
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ConstructConnectWssEndpointRequest( SignalingChannelEndpoint_t * pWssEndpoint,
                                                                ConnectWssEndpointRequestInfo_t * pConnectWssEndpointRequestInfo,
                                                                SignalingRequest_t * pRequestBuffer )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int snprintfRetVal = 0;

    if( ( pWssEndpoint == NULL ) ||
        ( pWssEndpoint->pEndpoint == NULL ) ||
        ( pRequestBuffer == NULL ) ||
        ( pConnectWssEndpointRequestInfo == NULL ) ||
        ( pRequestBuffer->pUrl == NULL ) ||
        ( pConnectWssEndpointRequestInfo->channelArn.pChannelArn == NULL ) ||
        ( ( pConnectWssEndpointRequestInfo->role != SIGNALING_ROLE_MASTER ) &&
          ( pConnectWssEndpointRequestInfo->role != SIGNALING_ROLE_VIEWER ) ) ||
        ( ( pConnectWssEndpointRequestInfo->role == SIGNALING_ROLE_VIEWER ) &&
          ( pConnectWssEndpointRequestInfo->pClientId == NULL ) ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        if( pConnectWssEndpointRequestInfo->role == SIGNALING_ROLE_MASTER )
        {
            snprintfRetVal = snprintf( pRequestBuffer->pUrl,
                                       pRequestBuffer->urlLength,
                                       "%.*s?X-Amz-ChannelARN=%.*s",
                                       ( int ) pWssEndpoint->endpointLength,
                                       pWssEndpoint->pEndpoint,
                                       ( int ) pConnectWssEndpointRequestInfo->channelArn.channelArnLength,
                                       pConnectWssEndpointRequestInfo->channelArn.pChannelArn );
        }
        else
        {
            snprintfRetVal = snprintf( pRequestBuffer->pUrl,
                                       pRequestBuffer->urlLength,
                                       "%.*s?X-Amz-ChannelARN=%.*s&X-Amz-ClientId=%.*s",
                                       ( int ) pWssEndpoint->endpointLength,
                                       pWssEndpoint->pEndpoint,
                                       ( int ) pConnectWssEndpointRequestInfo->channelArn.channelArnLength,
                                       pConnectWssEndpointRequestInfo->channelArn.pChannelArn,
                                       ( int ) pConnectWssEndpointRequestInfo->clientIdLength,
                                       pConnectWssEndpointRequestInfo->pClientId );
        }

        result = InterpretSnprintfReturnValue( snprintfRetVal, pRequestBuffer->urlLength );

        if( result == SIGNALING_RESULT_OK )
        {
            pRequestBuffer->urlLength = snprintfRetVal;
        }
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ConstructWssMessage( WssSendMessage_t * pWssSendMessage,
                                                 char * pBuffer,
                                                 size_t * pBufferLength )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    int snprintfRetVal = 0;
    size_t remainingLength = *pBufferLength;
    size_t currentIndex = 0;

    if( ( pWssSendMessage == NULL ) ||
        ( pBuffer == NULL ) ||
        ( pWssSendMessage->pBase64EncodedMessage == NULL ) ||
        ( pWssSendMessage->pRecipientClientId == NULL ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        snprintfRetVal = snprintf( &( pBuffer[ currentIndex ] ),
                                   remainingLength,
                                   "{"
                                        "\"action\":\"%s\","
                                        "\"RecipientClientId\":\"%.*s\","
                                        "\"MessagePayload\":\"%.*s\"",
                                   GetStringFromMessageType( pWssSendMessage->messageType ),
                                   ( int ) pWssSendMessage->recipientClientIdLength,
                                   pWssSendMessage->pRecipientClientId,
                                   ( int ) pWssSendMessage->base64EncodedMessageLength,
                                   pWssSendMessage->pBase64EncodedMessage );

        result = InterpretSnprintfReturnValue( snprintfRetVal, remainingLength );

        if( result == SIGNALING_RESULT_OK )
        {
            remainingLength -= snprintfRetVal;
            currentIndex += snprintfRetVal;
        }
    }

    /* Append correlation ID. */
    if( ( result == SIGNALING_RESULT_OK ) &&
        ( pWssSendMessage->correlationIdLength > 0 ) )
    {
        snprintfRetVal = snprintf( &( pBuffer[ currentIndex ] ),
                                   remainingLength,
                                   ","
                                   "\"CorrelationId\":\"%.*s\"",
                                   ( int ) pWssSendMessage->correlationIdLength,
                                   pWssSendMessage->pCorrelationId );

        result = InterpretSnprintfReturnValue( snprintfRetVal, remainingLength );

        if( result == SIGNALING_RESULT_OK )
        {
            remainingLength -= snprintfRetVal;
            currentIndex += snprintfRetVal;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        snprintfRetVal = snprintf( &( pBuffer[ currentIndex ] ),
                                   remainingLength,
                                   "}" );

        result = InterpretSnprintfReturnValue( snprintfRetVal, remainingLength );

        if( result == SIGNALING_RESULT_OK )
        {
            remainingLength -= snprintfRetVal;
            currentIndex += snprintfRetVal;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        *pBufferLength = currentIndex;
    }

    return result;
}

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_ParseWssRecvMessage( const char * pMessage,
                                                 size_t messageLength,
                                                 WssRecvMessage_t * pWssRecvMessage )
{
    SignalingResult_t result = SIGNALING_RESULT_OK;
    JSONStatus_t jsonResult;
    size_t start = 0, next = 0;
    JSONPair_t pair = { 0 };
    const char * pStatusResponseBuffer = NULL;
    size_t statusResponseBufferLength = 0;
    size_t statusResponseStart = 0, statusResponseNext = 0;

    if( ( pMessage == NULL ) ||
        ( pWssRecvMessage == NULL ) )
    {
        result = SIGNALING_RESULT_BAD_PARAM;
    }

    if( result == SIGNALING_RESULT_OK )
    {
        /* Exclude null terminator in messageLength. */
        if(messageLength > 0 )
        {
            if( pMessage[ messageLength - 1 ] == '\0' )
                {
                    messageLength--;
                }      
        }

        jsonResult = JSON_Validate( pMessage, messageLength );

        if( jsonResult != JSONSuccess )
        {
            result = SIGNALING_RESULT_INVALID_JSON;
        }
    }

    if( result == SIGNALING_RESULT_OK )
    {
        pWssRecvMessage->pSenderClientId = NULL;
        pWssRecvMessage->senderClientIdLength = 0;
        pWssRecvMessage->messageType = SIGNALING_TYPE_MESSAGE_UNKNOWN;
        pWssRecvMessage->pBase64EncodedPayload = NULL;
        pWssRecvMessage->base64EncodedPayloadLength = 0;
        memset( &( pWssRecvMessage->statusResponse ), 0, sizeof( WssStatusResponse_t ) );

        jsonResult = JSON_Iterate( pMessage, messageLength, &( start ), &( next ), &( pair ) );

        while( jsonResult == JSONSuccess )
        {
            if( strncmp( pair.key, "senderClientId", pair.keyLength ) == 0 )
            {
                pWssRecvMessage->pSenderClientId = pair.value;
                pWssRecvMessage->senderClientIdLength = pair.valueLength;
            }
            else if( strncmp( pair.key, "messageType", pair.keyLength ) == 0 )
            {
                if( strncmp( pair.value, "SDP_OFFER", pair.valueLength ) == 0 )
                {
                    pWssRecvMessage->messageType = SIGNALING_TYPE_MESSAGE_SDP_OFFER;
                }
                else if( strncmp( pair.value, "SDP_ANSWER", pair.valueLength ) == 0 )
                {
                    pWssRecvMessage->messageType = SIGNALING_TYPE_MESSAGE_SDP_ANSWER;
                }
                else if( strncmp( pair.value, "ICE_CANDIDATE", pair.valueLength ) == 0 )
                {
                    pWssRecvMessage->messageType = SIGNALING_TYPE_MESSAGE_ICE_CANDIDATE;
                }
                else if( strncmp( pair.value, "GO_AWAY", pair.valueLength ) == 0 )
                {
                    pWssRecvMessage->messageType = SIGNALING_TYPE_MESSAGE_GO_AWAY;
                }
                else if( strncmp( pair.value, "RECONNECT_ICE_SERVER", pair.valueLength ) == 0 )
                {
                    pWssRecvMessage->messageType = SIGNALING_TYPE_MESSAGE_RECONNECT_ICE_SERVER;
                }
                else if( strncmp( pair.value, "STATUS_RESPONSE", pair.valueLength ) == 0 )
                {
                    pWssRecvMessage->messageType = SIGNALING_TYPE_MESSAGE_STATUS_RESPONSE;
                }
                else
                {
                    pWssRecvMessage->messageType = SIGNALING_TYPE_MESSAGE_UNKNOWN;
                }
            }
            else if( strncmp( pair.key, "messagePayload", pair.keyLength ) == 0 )
            {
                pWssRecvMessage->pBase64EncodedPayload = pair.value;
                pWssRecvMessage->base64EncodedPayloadLength = pair.valueLength;
            }
            else if( strncmp( pair.key, "statusResponse", pair.keyLength ) == 0 )
            {
                if( pair.jsonType == JSONObject )
                {
                    pStatusResponseBuffer = pair.value;
                    statusResponseBufferLength = pair.valueLength;
                }
                else
                {
                    result = SIGNALING_RESULT_UNEXPECTED_RESPONSE;
                    break;
                }
            }
            else
            {
                /* Do nothing, ignore unknown tags. */
            }

            jsonResult = JSON_Iterate( pMessage, messageLength, &( start ), &( next ), &( pair ) );
        }
    }

    if( ( result == SIGNALING_RESULT_OK ) && ( pStatusResponseBuffer != NULL ) )
    {
        jsonResult = JSON_Iterate( pStatusResponseBuffer, statusResponseBufferLength, &( statusResponseStart ), &( statusResponseNext ), &( pair ) );

        if( jsonResult != JSONSuccess )
        {
            result = SIGNALING_RESULT_INVALID_STATUS_RESPONSE;
        }

        while( jsonResult == JSONSuccess )
        {
            if( strncmp( pair.key, "correlationId", pair.keyLength ) == 0 )
            {
                pWssRecvMessage->statusResponse.pCorrelationId = pair.value;
                pWssRecvMessage->statusResponse.correlationIdLength = pair.valueLength;
            }
            else if( strncmp( pair.key, "errorType", pair.keyLength ) == 0 )
            {
                pWssRecvMessage->statusResponse.pErrorType = pair.value;
                pWssRecvMessage->statusResponse.errorTypeLength = pair.valueLength;
            }
            else if( strncmp( pair.key, "statusCode", pair.keyLength ) == 0 )
            {
                pWssRecvMessage->statusResponse.pStatusCode = pair.value;
                pWssRecvMessage->statusResponse.statusCodeLength = pair.valueLength;
            }
            else if( strncmp( pair.key, "description", pair.keyLength ) == 0 )
            {
                pWssRecvMessage->statusResponse.pDescription = pair.value;
                pWssRecvMessage->statusResponse.descriptionLength = pair.valueLength;
            }
            else
            {
                /* Do nothing, ignore unknown tags. */
            }

            jsonResult = JSON_Iterate( pStatusResponseBuffer, statusResponseBufferLength, &( statusResponseStart ), &( statusResponseNext ), &( pair ) );
        }
    }

    return result;
}

/*-----------------------------------------------------------*/
