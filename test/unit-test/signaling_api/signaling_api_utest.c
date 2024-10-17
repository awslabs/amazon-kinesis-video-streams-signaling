/* Unity includes. */
#include "unity.h"
#include "catch_assert.h"

/* Standard includes. */
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* API includes. */
#include "signaling_api.h"

/* ===========================  EXTERN VARIABLES    =========================== */



/* ===========================  EXTERN FUNCTIONS   =========================== */



/* ==============================  Test Cases  ============================== */

/**
 * @brief Validate Signaling Construct Describe Channel Request fail functionality for Bad Parameters.
 */
void test_signaling_ConstructDescribeSignalingChannelRequest_BadParams( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    SignalingChannelName_t channelName = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;

    result = Signaling_ConstructDescribeSignalingChannelRequest( NULL,
                                                                 &( channelName ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    awsRegion.pAwsRegion = NULL;
    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );
    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 NULL, &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ), NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pUrl = NULL;
    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pUrl = "https://kinesisvideo.cn-east-1.amazonaws.com.cn/describeSignalingChannel";
    requestBuffer.urlLength = strlen( requestBuffer.pUrl );
    requestBuffer.pBody = NULL;
    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Describe Channel Request functionality.
 */
void test_signaling_ConstructDescribeSignalingChannelRequest( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    SignalingChannelName_t channelName = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 100 ];
    SignalingResult_t result;

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelName.pChannelName = "Test-Channel";
    channelName.channelNameLength = strlen( channelName.pChannelName );

    requestBuffer.pUrl = urlBuffer;
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = bodyBuffer;
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING( "https://kinesisvideo.us-east-1.amazonaws.com/describeSignalingChannel", requestBuffer.pUrl );
    TEST_ASSERT_EQUAL_STRING( "{\"ChannelName\":\"Test-Channel\"}", requestBuffer.pBody );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Describe Channel Request functionality.
 */
void test_signaling_ConstructDescribeSignalingChannelRequest_SmallLengthRegion( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    SignalingChannelName_t channelName = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 100 ];
    SignalingResult_t result;

    awsRegion.pAwsRegion = "ca"; /* The Region Length is < 3 */
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelName.pChannelName = "Test-Channel-China";
    channelName.channelNameLength = strlen( channelName.pChannelName );

    requestBuffer.pUrl = urlBuffer;
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = bodyBuffer;
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING( "https://kinesisvideo.ca.amazonaws.com/describeSignalingChannel", requestBuffer.pUrl );
    TEST_ASSERT_EQUAL_STRING( "{\"ChannelName\":\"Test-Channel-China\"}", requestBuffer.pBody );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Describe Channel Request functionality for China Region.
 */
void test_signaling_ConstructDescribeSignalingChannelRequest_ChinaRegion( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    SignalingChannelName_t channelName = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 100 ];
    SignalingResult_t result;

    awsRegion.pAwsRegion = "cn-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelName.pChannelName = "Test-Channel-China";
    channelName.channelNameLength = strlen( channelName.pChannelName );

    requestBuffer.pUrl = urlBuffer;
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = bodyBuffer;
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING( "https://kinesisvideo.cn-east-1.amazonaws.com.cn/describeSignalingChannel", requestBuffer.pUrl );
    TEST_ASSERT_EQUAL_STRING( "{\"ChannelName\":\"Test-Channel-China\"}", requestBuffer.pBody );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Describe Channel Request functionality.
 */
void test_signaling_ConstructDescribeSignalingChannelRequest_URLOutofMemory( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    SignalingChannelName_t channelName = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 69 ];         /* The url buffer is small */
    char bodyBuffer[ 100 ];
    SignalingResult_t result;

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelName.pChannelName = "Test-Channel";
    channelName.channelNameLength = strlen( channelName.pChannelName );

    requestBuffer.pUrl = urlBuffer;
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = bodyBuffer;
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Describe Channel Request functionality.
 */
void test_signaling_ConstructDescribeSignalingChannelRequest_BodyOutofMemory( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    SignalingChannelName_t channelName = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 30 ];         /* The body buffer is small */
    SignalingResult_t result;

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelName.pChannelName = "Test-Channel";
    channelName.channelNameLength = strlen( channelName.pChannelName );

    requestBuffer.pUrl = urlBuffer;
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = bodyBuffer;
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Response fail functionality for Bad Parameters.
 */
void test_signaling_ParseDescribeSignalingChannelResponse_BadParams( void )
{
    const char message;
    size_t messageLength = sizeof( message );
    SignalingChannelInfo_t channelInfo;
    SignalingResult_t result;

    result = Signaling_ParseDescribeSignalingChannelResponse( NULL,
                                                              messageLength, &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ParseDescribeSignalingChannelResponse( &( message ),
                                                              messageLength, NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Response functionality for Invalid JSON.
 */
void test_signaling_ParseDescribeSignalingChannelResponse_InvalidJson( void )
{
    const char * message = "{\"ChannelInfo\": {";        /* Missing Closing Braces */
    size_t messageLength = strlen( message );
    SignalingChannelInfo_t channelInfo;
    SignalingResult_t result;

    result = Signaling_ParseDescribeSignalingChannelResponse( message,
                                                              messageLength, &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );

    /* <--------------------------------------------------------------------> */

    const char *message2 = "{"
        "\"ChannelInfo\": {"
            "\"SingleMasterConfiguration\": \"InvalidValue\""
        "}"
    "}";
    size_t messageLength2 = strlen( message2 );

    result = Signaling_ParseDescribeSignalingChannelResponse( message2,
                                                              messageLength2, &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );
}

/*-----------------------------------------------------------*/


/**
 * @brief Validate Signaling Parse Describe Response functionality for Unexpected Response.
 */
void test_signaling_ParseDescribeSignalingChannelResponse_UnexpectedResponse( void )
{
    const char * message = "{\"UnexpectedKey\": {}}";            /* The Key is not known */
    size_t messageLength = strlen( message );
    SignalingChannelInfo_t channelInfo;
    SignalingResult_t result;

    result = Signaling_ParseDescribeSignalingChannelResponse( message,
                                                              messageLength, &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Response functionality for Invalid TTL.
 */
void test_signaling_ParseDescribeSignalingChannelResponse_InvalidTTL_Low( void )
{
    SignalingChannelInfo_t channelInfo;
    SignalingResult_t result;
    const char *message =  "{"
        "\"ChannelInfo\": {"
            "\"SingleMasterConfiguration\": {\"MessageTtlSeconds\": 0}"
        "}"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeSignalingChannelResponse( message,
                                                              messageLength, &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_TTL,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Response functionality for Invalid TTL.
 */
void test_signaling_ParseDescribeSignalingChannelResponse_InvalidTTL_High( void )
{
    SignalingChannelInfo_t channelInfo;
    SignalingResult_t result;
    const char *message =  "{"
        "\"ChannelInfo\": {"
            "\"SingleMasterConfiguration\": {\"MessageTtlSeconds\": 999999999}"
        "}"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeSignalingChannelResponse( message,
                                                              messageLength, &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_TTL,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Response functionality for Invalid Channel Type.
 */
void test_signaling_ParseDescribeSignalingChannelResponse_InvalidChannel_Type( void )
{
    SignalingChannelInfo_t channelInfo;
    SignalingResult_t result;
    const char *message = "{"
        "\"ChannelInfo\": {"
            "\"ChannelType\": \"INVALID_TYPE\""
        "}"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeSignalingChannelResponse( message,
                                                              messageLength, &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_CHANNEL_TYPE,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Response functionality for Invalid Channel Name.
 */
void test_signaling_ParseDescribeSignalingChannelResponse_InvalidChannel_Name( void )
{   
    SignalingChannelInfo_t channelInfo;
    SignalingResult_t result;

    char longChannelName[ SIGNALING_CHANNEL_NAME_MAX_LEN + 10 ];
    memset( longChannelName, 'a', sizeof( longChannelName ) - 1 );
    longChannelName[ sizeof( longChannelName ) - 1 ] = '\0';
    char message[ 1000 ];
    snprintf(message, sizeof(message), "{"
        "\"ChannelInfo\": {"
            "\"ChannelName\": \"%s\""
        "}"
    "}", longChannelName);
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeSignalingChannelResponse( message,
                                                              messageLength, &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_CHANNEL_NAME,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Response functionality.
 */
void test_signaling_ParseDescribeSignalingChannelResponse( void )
{
    SignalingChannelInfo_t channelInfo;
    SignalingResult_t result;
    const char *message = "{"
        "\"ChannelInfo\": {"
            "\"ChannelARN\": \"arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123\","
            "\"ChannelName\": \"test-channel\","
            "\"ChannelStatus\": \"ACTIVE\","
            "\"ChannelType\": \"SINGLE_MASTER\","
            "\"CreationTime\": \"2023-05-01T12:00:00Z\","
            "\"SingleMasterConfiguration\": {\"MessageTtlSeconds\": 60},"
            "\"Version\": \"1\""
        "}"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeSignalingChannelResponse( message,
                                                              messageLength, &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING_LEN( "arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123",
                                  channelInfo.channelArn.pChannelArn,
                                  channelInfo.channelArn.channelArnLength );
    TEST_ASSERT_EQUAL_STRING_LEN( "test-channel",
                                  channelInfo.channelName.pChannelName,
                                  channelInfo.channelName.channelNameLength );
    TEST_ASSERT_EQUAL_STRING_LEN( "ACTIVE", channelInfo.pChannelStatus, channelInfo.channelStatusLength );
    TEST_ASSERT_EQUAL( SIGNALING_TYPE_CHANNEL_SINGLE_MASTER, channelInfo.channelType );
    TEST_ASSERT_EQUAL( 60, channelInfo.messageTtlSeconds );
    TEST_ASSERT_EQUAL_STRING_LEN( "1", channelInfo.pVersion, channelInfo.versionLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Describe Media Storage Config Request fail functionality for Bad Parameters.
 */
void test_signaling_ConstructDescribeMediaStorageConfigRequest_BadParams( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    SignalingChannelArn_t channelArn = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( NULL,
                                                                   &( channelArn ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    awsRegion.pAwsRegion = NULL;
    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );
    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   NULL, &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ), NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pUrl = NULL;
    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pUrl = "https://kinesisvideo.cn-east-1.amazonaws.com.cn/describeSignalingChannel";
    requestBuffer.urlLength = strlen( requestBuffer.pUrl );
    requestBuffer.pBody = NULL;
    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pBody = "{\"ChannelName\":\"Test-Channel-China\"}";
    requestBuffer.bodyLength = strlen( requestBuffer.pBody );
    channelArn.pChannelArn = NULL;
    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Describe Media Storage Config Request functionality.
 */
void test_signaling_ConstructDescribeMediaStorageConfigRequest( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    SignalingChannelArn_t channelArn = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 100 ];
    SignalingResult_t result;

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    channelArn.channelArnLength = strlen( channelArn.pChannelArn );

    requestBuffer.pUrl = urlBuffer;
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = bodyBuffer;
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING( "https://kinesisvideo.us-east-1.amazonaws.com/describeMediaStorageConfiguration", requestBuffer.pUrl );
    TEST_ASSERT_EQUAL_STRING( "{\"ChannelARN\":\"arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123\"}", requestBuffer.pBody );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Describe Media Storage Config Request functionality.
 */
void test_signaling_ConstructDescribeMediaStorageConfigRequest_SmallLengthRegion( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    SignalingChannelArn_t channelArn = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 100 ];
    SignalingResult_t result;

    awsRegion.pAwsRegion = "ca"; /* The Region Length is < 3 */
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelArn.pChannelArn = "arn:aws:kinesisvideo:ca:123456789012:channel/test-channel/1234567890123";
    channelArn.channelArnLength = strlen( channelArn.pChannelArn );

    requestBuffer.pUrl = urlBuffer;
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = bodyBuffer;
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING( "https://kinesisvideo.ca.amazonaws.com/describeMediaStorageConfiguration", requestBuffer.pUrl );
    TEST_ASSERT_EQUAL_STRING( "{\"ChannelARN\":\"arn:aws:kinesisvideo:ca:123456789012:channel/test-channel/1234567890123\"}", requestBuffer.pBody );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Describe Media Storage Config Request functionality for China Region.
 */
void test_signaling_ConstructDescribeMediaStorageConfigRequest_ChinaRegion( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    SignalingChannelArn_t channelArn = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 100 ];
    SignalingResult_t result;

    awsRegion.pAwsRegion = "cn-north-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelArn.pChannelArn = "arn:aws-cn:kinesisvideo:cn-north-1:123456789012:channel/test-channel/1234567890123";
    channelArn.channelArnLength = strlen( channelArn.pChannelArn );

    requestBuffer.pUrl = urlBuffer;
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = bodyBuffer;
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING( "https://kinesisvideo.cn-north-1.amazonaws.com.cn/describeMediaStorageConfiguration", requestBuffer.pUrl );
    TEST_ASSERT_EQUAL_STRING( "{\"ChannelARN\":\"arn:aws-cn:kinesisvideo:cn-north-1:123456789012:channel/test-channel/1234567890123\"}", requestBuffer.pBody );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Describe Media Storage Config Request functionality.
 */
void test_signaling_ConstructDescribeMediaStorageConfigRequest_URLOutOfMemory( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    SignalingChannelArn_t channelArn = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 78 ];     /* The url buffer is small */
    char bodyBuffer[ 100 ];
    SignalingResult_t result;

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    channelArn.channelArnLength = strlen( channelArn.pChannelArn );

    requestBuffer.pUrl = urlBuffer;
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = bodyBuffer;
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Describe Media Storage Config Request functionality.
 */
void test_signaling_ConstructDescribeMediaStorageConfigRequest_BodyOutOfMemory( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    SignalingChannelArn_t channelArn = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 95 ];       /* The body buffer is small */
    SignalingResult_t result;

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    channelArn.channelArnLength = strlen( channelArn.pChannelArn );

    requestBuffer.pUrl = urlBuffer;
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = bodyBuffer;
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Media Storage Config fail functionality for Bad Parameters.
 */
void test_signaling_ParseDescribeMediaStorageConfigResponse_BadParams( void )
{
    const char * message;
    size_t messageLength = sizeof( message );
    SignalingMediaStorageConfig_t mediaStorageConfig;
    SignalingResult_t result;

    result = Signaling_ParseDescribeMediaStorageConfigResponse( NULL,
                                                                messageLength, &( mediaStorageConfig ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ParseDescribeMediaStorageConfigResponse( message,
                                                                messageLength, NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Media Storage Config functionality.
 */
void test_signaling_ParseDescribeMediaStorageConfigResponse_InvalidJson( void )
{
    const char * message = "{\"MediaStorageConfiguration\": {";  /* Missing closing brace */
    size_t messageLength = sizeof( message );
    SignalingMediaStorageConfig_t mediaStorageConfig;
    SignalingResult_t result;

    result = Signaling_ParseDescribeMediaStorageConfigResponse( message,
                                                                messageLength, &( mediaStorageConfig ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Media Storage Config functionality.
 */
void test_signaling_ParseDescribeMediaStorageConfigResponse_UnexpectedResponse( void )
{
    const char * message = "{\"UnexpectedKey\": {}}";        /* Unkown Key */
    size_t messageLength = strlen( message );
    SignalingMediaStorageConfig_t mediaStorageConfig;
    SignalingResult_t result;

    result = Signaling_ParseDescribeMediaStorageConfigResponse( message,
                                                                messageLength, &( mediaStorageConfig ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Media Storage Config functionality.
 */
void test_signaling_ParseDescribeMediaStorageConfigResponse_MissingFields( void )
{
    SignalingMediaStorageConfig_t mediaStorageConfig;
    SignalingResult_t result;
    const char *message = "{"
        "\"MediaStorageConfiguration\": {"
            "\"Status\": \"ENABLED\""
            // Missing StreamARN
        "}"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeMediaStorageConfigResponse( message,
                                                                messageLength, &( mediaStorageConfig ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK, result );
    TEST_ASSERT_EQUAL_STRING_LEN( "ENABLED", mediaStorageConfig.pStatus, mediaStorageConfig.statusLength );
    TEST_ASSERT_NULL( mediaStorageConfig.pStreamArn );
    TEST_ASSERT_EQUAL( 0, mediaStorageConfig.streamArnLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Media Storage Config functionality.
 */
void test_signaling_ParseDescribeMediaStorageConfigResponse( void )
{
    SignalingMediaStorageConfig_t mediaStorageConfig;
    SignalingResult_t result;
    const char *message  = "{"
            "\"MediaStorageConfiguration\": {"
            "\"Status\": \"ENABLED\","
            "\"StreamARN\": \"arn:aws:kinesisvideo:us-west-2:123456789012:stream/test-stream/1234567890123\""
            "}"
            "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeMediaStorageConfigResponse( message,
                                                                messageLength, &( mediaStorageConfig ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING_LEN( "ENABLED", mediaStorageConfig.pStatus, mediaStorageConfig.statusLength );
    TEST_ASSERT_EQUAL_STRING_LEN( "arn:aws:kinesisvideo:us-west-2:123456789012:stream/test-stream/1234567890123",
                                  mediaStorageConfig.pStreamArn,
                                  mediaStorageConfig.streamArnLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Channel Request fail functionality for Bad Parameters.
 */
void test_signaling_ConstructCreateSignalingChannelRequest_BadParams( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    CreateSignalingChannelRequestInfo_t createSignalingChannelRequestInfo = { 0 };
    SignalingTag_t tags[ 2 ] = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;

    result = Signaling_ConstructCreateSignalingChannelRequest( NULL,
                                                               &( createSignalingChannelRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    awsRegion.pAwsRegion = NULL;
    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );
    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               NULL, &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ), NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pUrl = NULL;
    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pUrl = "https://kinesisvideo.cn-east-1.amazonaws.com.cn/describeSignalingChannel";
    requestBuffer.urlLength = strlen( requestBuffer.pUrl );
    requestBuffer.pBody = NULL;

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pBody = "{\"ChannelName\":\"Test-Channel-China\"}";
    requestBuffer.bodyLength = strlen( requestBuffer.pBody );
    createSignalingChannelRequestInfo.numTags = 1;
    createSignalingChannelRequestInfo.pTags = NULL;

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    createSignalingChannelRequestInfo.pTags = &( tags[ 0 ] );
    createSignalingChannelRequestInfo.channelName.channelNameLength = SIGNALING_CHANNEL_NAME_MAX_LEN + 1;
    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Channel Request functionality.
 */
void test_signaling_ConstructCreateSignalingChannelRequest( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    CreateSignalingChannelRequestInfo_t createSignalingChannelRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    SignalingResult_t result;

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    createSignalingChannelRequestInfo.channelName.pChannelName = "Test-Channel";
    createSignalingChannelRequestInfo.channelName.channelNameLength = strlen( createSignalingChannelRequestInfo.channelName.pChannelName );
    createSignalingChannelRequestInfo.channelType = SIGNALING_TYPE_CHANNEL_SINGLE_MASTER;
    createSignalingChannelRequestInfo.messageTtlSeconds = 60;
    createSignalingChannelRequestInfo.numTags = 0;
    createSignalingChannelRequestInfo.pTags = NULL;

    requestBuffer.pUrl = urlBuffer;
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = bodyBuffer;
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING( "https://kinesisvideo.us-east-1.amazonaws.com/createSignalingChannel", requestBuffer.pUrl );
    TEST_ASSERT_EQUAL_STRING( "{\"ChannelName\":\"Test-Channel\",\"ChannelType\":\"SINGLE_MASTER\",\"SingleMasterConfiguration\":{\"MessageTtlSeconds\":60}}", requestBuffer.pBody );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Channel Request functionality.
 */
void test_signaling_ConstructCreateSignalingChannelRequest_SmallLengthRegion( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    CreateSignalingChannelRequestInfo_t createSignalingChannelRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    SignalingResult_t result;

    awsRegion.pAwsRegion = "ca";            /* The Region Length is < 3 */
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    createSignalingChannelRequestInfo.channelName.pChannelName = "Test-Channel";
    createSignalingChannelRequestInfo.channelName.channelNameLength = strlen( createSignalingChannelRequestInfo.channelName.pChannelName );
    createSignalingChannelRequestInfo.channelType = SIGNALING_TYPE_CHANNEL_SINGLE_MASTER;
    createSignalingChannelRequestInfo.messageTtlSeconds = 60;
    createSignalingChannelRequestInfo.numTags = 0;
    createSignalingChannelRequestInfo.pTags = NULL;

    requestBuffer.pUrl = urlBuffer;
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = bodyBuffer;
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING( "https://kinesisvideo.ca.amazonaws.com/createSignalingChannel", requestBuffer.pUrl );
    TEST_ASSERT_EQUAL_STRING( "{\"ChannelName\":\"Test-Channel\",\"ChannelType\":\"SINGLE_MASTER\",\"SingleMasterConfiguration\":{\"MessageTtlSeconds\":60}}", requestBuffer.pBody );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Channel Request functionality.
 */
void test_signaling_ConstructCreateSignalingChannelRequest_ChinaRegion( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    CreateSignalingChannelRequestInfo_t createSignalingChannelRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    SignalingResult_t result;

    awsRegion.pAwsRegion = "cn-north-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    createSignalingChannelRequestInfo.channelName.pChannelName = "Test-Channel";
    createSignalingChannelRequestInfo.channelName.channelNameLength = strlen( createSignalingChannelRequestInfo.channelName.pChannelName );
    createSignalingChannelRequestInfo.channelType = SIGNALING_TYPE_CHANNEL_SINGLE_MASTER;
    createSignalingChannelRequestInfo.messageTtlSeconds = 60;
    createSignalingChannelRequestInfo.numTags = 0;
    createSignalingChannelRequestInfo.pTags = NULL;

    requestBuffer.pUrl = urlBuffer;
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = bodyBuffer;
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING( "https://kinesisvideo.cn-north-1.amazonaws.com.cn/createSignalingChannel", requestBuffer.pUrl );
    TEST_ASSERT_EQUAL_STRING( "{\"ChannelName\":\"Test-Channel\",\"ChannelType\":\"SINGLE_MASTER\",\"SingleMasterConfiguration\":{\"MessageTtlSeconds\":60}}", requestBuffer.pBody );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Channel Request functionality.
 */
void test_signaling_ConstructCreateSignalingChannelRequest_WithTags( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    CreateSignalingChannelRequestInfo_t createSignalingChannelRequestInfo = { 0 };
    SignalingTag_t tags[ 1 ] = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    SignalingResult_t result;

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    tags->pName = "Tag1";
    tags->nameLength = strlen( tags->pName );
    tags->pValue = "Value1";
    tags->valueLength = strlen( tags->pValue );

    createSignalingChannelRequestInfo.channelName.pChannelName = "Test-Channel";
    createSignalingChannelRequestInfo.channelName.channelNameLength = strlen( createSignalingChannelRequestInfo.channelName.pChannelName );
    createSignalingChannelRequestInfo.channelType = SIGNALING_TYPE_CHANNEL_SINGLE_MASTER;
    createSignalingChannelRequestInfo.messageTtlSeconds = 60;
    createSignalingChannelRequestInfo.numTags = 1;
    createSignalingChannelRequestInfo.pTags = tags;

    requestBuffer.pUrl = urlBuffer;
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = bodyBuffer;
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING( "https://kinesisvideo.us-east-1.amazonaws.com/createSignalingChannel", requestBuffer.pUrl );
    TEST_ASSERT_EQUAL_STRING( "{\"ChannelName\":\"Test-Channel\",\"ChannelType\":\"SINGLE_MASTER\",\"SingleMasterConfiguration\":{\"MessageTtlSeconds\":60}"",\"Tags\":[{\"Key\":\"Tag1\",\"Value\":\"Value1\"}]}", requestBuffer.pBody );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Media Storage Config fail functionality for Bad Parameters.
 */
void test_signaling_ParseCreateSignalingChannelResponse_BadParams( void )
{
    const char * message;
    size_t messageLength = sizeof( message );
    SignalingChannelArn_t channelArn = { 0 };
    SignalingResult_t result;

    result = Signaling_ParseCreateSignalingChannelResponse( NULL,
                                                            messageLength, &( channelArn ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ParseCreateSignalingChannelResponse( message,
                                                            messageLength, NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Create Signaling Channel Response functionality.
 */
void test_signaling_ParseCreateSignalingChannelResponse_InvalidJson( void )
{
    const char * message = "{\"ChannelARN\": \"test-arn\"";  /* Missing closing brace */
    size_t messageLength = strlen( message );
    SignalingChannelArn_t channelArn = { 0 };
    SignalingResult_t result;

    result = Signaling_ParseCreateSignalingChannelResponse( message,
                                                            messageLength, &( channelArn ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Create Signaling Channel Response functionality.
 */
void test_signaling_ParseCreateSignalingChannelResponse_UnexpectedResponse( void )
{
    const char * message = "{}";
    size_t messageLength = strlen( message );
    SignalingChannelArn_t channelArn = { 0 };
    SignalingResult_t result;

    result = Signaling_ParseCreateSignalingChannelResponse( message,
                                                            messageLength, &( channelArn ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Create Signaling Channel Response functionality.
 */
void test_signaling_ParseCreateSignalingChannelResponse( void )
{
    const char *message = "{"
        "\"ChannelARN\": \"arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123\""
    "}";
    size_t messageLength = strlen( message );
    SignalingChannelArn_t channelArn = { 0 };
    SignalingResult_t result;

    result = Signaling_ParseCreateSignalingChannelResponse( message,
                                                            messageLength, &( channelArn ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING_LEN( "arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123",
                                  channelArn.pChannelArn,
                                  channelArn.channelArnLength );
    TEST_ASSERT_EQUAL( 78, channelArn.channelArnLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Get Channel Endpoint Request fail functionality for Bad Parameters.
 */
void test_signaling_ConstructGetSignalingChannelEndpointRequest_BadParams( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    GetSignalingChannelEndpointRequestInfo_t getSignalingChannelEndPointRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char channelArn[] = "arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123";
    SignalingResult_t result;

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( NULL,
                                                                    &( getSignalingChannelEndPointRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    awsRegion.pAwsRegion = NULL;
    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );
    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    NULL, &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ), NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pUrl = NULL;
    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pUrl = "https://kinesisvideo.cn-east-1.amazonaws.com.cn/describeSignalingChannel";
    requestBuffer.urlLength = strlen( requestBuffer.pUrl );
    requestBuffer.pBody = NULL;
    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pBody = "{\"ChannelName\":\"Test-Channel\"}";
    requestBuffer.bodyLength = strlen( requestBuffer.pBody );
    getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn = NULL;
    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn = &( channelArn[ 0 ] );
    getSignalingChannelEndPointRequestInfo.channelArn.channelArnLength = strlen( getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn );
    getSignalingChannelEndPointRequestInfo.role = SIGNALING_ROLE_NONE;
    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Get Channel Endpoint Request functionality .
 */
void test_signaling_ConstructGetSignalingChannelEndpointRequest( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    GetSignalingChannelEndpointRequestInfo_t getSignalingChannelEndPointRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    SignalingResult_t result;

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    getSignalingChannelEndPointRequestInfo.channelArn.channelArnLength = strlen( getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn );
    getSignalingChannelEndPointRequestInfo.role = SIGNALING_ROLE_MASTER;
    getSignalingChannelEndPointRequestInfo.protocols = SIGNALING_PROTOCOL_HTTPS;

    requestBuffer.pUrl = urlBuffer;
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = bodyBuffer;
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING( "https://kinesisvideo.us-east-1.amazonaws.com/getSignalingChannelEndpoint", requestBuffer.pUrl );
    TEST_ASSERT_TRUE( strstr( requestBuffer.pBody, "\"ChannelARN\":\"arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123\"" ) != NULL );
    TEST_ASSERT_TRUE( strstr( requestBuffer.pBody, "\"Protocols\":[\"HTTPS\"]" ) != NULL );
    TEST_ASSERT_TRUE( strstr( requestBuffer.pBody, "\"Role\":\"MASTER\"" ) != NULL );
}

/*-----------------------------------------------------------*/
