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
                                                                 &( channelName ),
                                                                 &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    awsRegion.pAwsRegion = NULL;

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ),
                                                                 &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 NULL,
                                                                 &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ),
                                                                 NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pUrl = NULL;

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ),
                                                                 &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pUrl = "https://kinesisvideo.cn-east-1.amazonaws.com.cn/describeSignalingChannel";
    requestBuffer.urlLength = strlen( requestBuffer.pUrl );
    requestBuffer.pBody = NULL;

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ),
                                                                 &( requestBuffer ) );

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
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 100 ];
    const char * pExpectedUrl = "https://kinesisvideo.us-east-1.amazonaws.com/describeSignalingChannel";
    const char * pExpectedBody = "{"
                                    "\"ChannelName\":\"Test-Channel\""
                                  "}";

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelName.pChannelName = "Test-Channel";
    channelName.channelNameLength = strlen( channelName.pChannelName );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ),
                                                                 &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING( pExpectedUrl,
                              requestBuffer.pUrl );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING( pExpectedBody,
                              requestBuffer.pBody );
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
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 100 ];
    const char * pExpectedUrl = "https://kinesisvideo.ca.amazonaws.com/describeSignalingChannel";
    const char * pExpectedBody = "{"
                                    "\"ChannelName\":\"Test-Channel-China\""
                                  "}";

    awsRegion.pAwsRegion = "ca"; /* The Region Length is < 3. */
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelName.pChannelName = "Test-Channel-China";
    channelName.channelNameLength = strlen( channelName.pChannelName );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ),
                                                                 &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING( pExpectedUrl,
                              requestBuffer.pUrl );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING( pExpectedBody,
                              requestBuffer.pBody );
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
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 100 ];
    const char * pExpectedUrl = "https://kinesisvideo.cn-east-1.amazonaws.com.cn/describeSignalingChannel";
    const char * pExpectedBody = "{"
                                    "\"ChannelName\":\"Test-Channel-China\""
                                  "}";

    awsRegion.pAwsRegion = "cn-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelName.pChannelName = "Test-Channel-China";
    channelName.channelNameLength = strlen( channelName.pChannelName );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ),
                                                                 &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING( pExpectedUrl,
                              requestBuffer.pUrl );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING( pExpectedBody,
                              requestBuffer.pBody );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Describe Channel Request functionality.
 */
void test_signaling_ConstructDescribeSignalingChannelRequest_UrlOutofMemory( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    SignalingChannelName_t channelName = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 69 ]; /* The url buffer is too small to fit the complete URL. */
    char bodyBuffer[ 100 ];

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelName.pChannelName = "Test-Channel";
    channelName.channelNameLength = strlen( channelName.pChannelName );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ),
                                                                 &( requestBuffer ) );

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
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 30 ]; /* The body buffer is too small to fit the complete body. */

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelName.pChannelName = "Test-Channel";
    channelName.channelNameLength = strlen( channelName.pChannelName );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ),
                                                                 &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Response fail functionality for Bad Parameters.
 */
void test_signaling_ParseDescribeSignalingChannelResponse_BadParams( void )
{
    SignalingChannelInfo_t channelInfo;
    SignalingResult_t result;
    const char * message = "Input Message";
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeSignalingChannelResponse( NULL,
                                                              messageLength,
                                                              &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ParseDescribeSignalingChannelResponse( message,
                                                              messageLength,
                                                              NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Response functionality for Invalid JSON.
 */
void test_signaling_ParseDescribeSignalingChannelResponse_InvalidJson( void )
{
    SignalingChannelInfo_t channelInfo;
    SignalingResult_t result;
    const char * message = "{\"ChannelInfo\": {"; /* Missing Closing Brace. */
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeSignalingChannelResponse( message,
                                                              messageLength,
                                                              &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );

    /* <--------------------------------------------------------------------> */

    const char *message2 =
    "{"
        "\"ChannelInfo\":"
        "{"
            "\"SingleMasterConfiguration\":"
            "{"
                "\"MessbkpTtlSeconds\": 60" /* Invalid key. */
            "}"
        "}"
    "}";
    size_t messageLength2 = strlen( message2 );

    result = Signaling_ParseDescribeSignalingChannelResponse( message2,
                                                              messageLength2,
                                                              &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );

    /* <--------------------------------------------------------------------> */

    const char *message3 = "{}"; /* Empty Message. */
    size_t messageLength3 = strlen( message3 );

    result = Signaling_ParseDescribeSignalingChannelResponse( message3,
                                                              messageLength3,
                                                              &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );

    /* <--------------------------------------------------------------------> */

    const char *message4 =
    "{"
        "\"ChannelInfo\":"
        "{"
            "\"SingleMasterConfiguration\": {}" /* Empty Single Master Configuration. */
        "}"
    "}";
    size_t messageLength4 = strlen( message4 );

    result = Signaling_ParseDescribeSignalingChannelResponse( message4,
                                                              messageLength4,
                                                              &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );
}

/*-----------------------------------------------------------*/


/**
 * @brief Validate Signaling Parse Describe Response functionality for Unexpected Response.
 */
void test_signaling_ParseDescribeSignalingChannelResponse_UnexpectedResponse( void )
{
    SignalingChannelInfo_t channelInfo;
    SignalingResult_t result;
    const char * message =
    "{"
        "\"ChannelInfo\":"
        "[" /* Unexpected JSON array. */
            "{"
                "\"ChannelARN\": \"arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123\""
            "}"
        "]"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeSignalingChannelResponse( message,
                                                              messageLength,
                                                              &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );

    /*<----------------------------------------------------------------->*/

    const char * message2 =
    "{"
        "\"Unkown\":" /* Unexpected key. */
        "{"
            "\"ChannelARN\": \"arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123\""
        "}"
    "}";
    size_t messageLength2 = strlen( message2 );

    result = Signaling_ParseDescribeSignalingChannelResponse( message2,
                                                              messageLength2,
                                                              &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );

    /*<----------------------------------------------------------------->*/

    const char * message3 =
    "{"
        "\"ChannelXXXX\": {}" /* Unexpected key though the length is same as "ChannelInfo". */
    "}";
    size_t messageLength3 = strlen( message3 );

    result = Signaling_ParseDescribeSignalingChannelResponse( message3,
                                                              messageLength3,
                                                              &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Response functionality for Invalid TTL.
 */
void test_signaling_ParseDescribeSignalingChannelResponse_TttLow( void )
{
    SignalingChannelInfo_t channelInfo;
    SignalingResult_t result;
    const char *message =
    "{"
        "\"ChannelInfo\":"
        "{"
            "\"SingleMasterConfiguration\":"
            "{"
                "\"MessageTtlSeconds\": 0" /* The valid range for message TTL is [ 5-120 ] seconds. */
            "}"
        "}"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeSignalingChannelResponse( message,
                                                              messageLength,
                                                              &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_TTL,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Response functionality for Invalid TTL.
 */
void test_signaling_ParseDescribeSignalingChannelResponse_TtlHigh( void )
{
    SignalingChannelInfo_t channelInfo;
    SignalingResult_t result;
    const char *message =
    "{"
        "\"ChannelInfo\":"
        "{"
            "\"SingleMasterConfiguration\":"
            "{"
                "\"MessageTtlSeconds\": 999" /* The valid range for message TTL is [ 5-120 ] seconds. */
            "}"
        "}"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeSignalingChannelResponse( message,
                                                              messageLength,
                                                              &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_TTL,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Response functionality for Invalid TTL.
 */
void test_signaling_ParseDescribeSignalingChannelResponse_InvalidTtl( void )
{
    SignalingChannelInfo_t channelInfo;
    SignalingResult_t result;
    const char *message =
    "{"
        "\"ChannelInfo\":"
        "{"
            "\"SingleMasterConfiguration\":"
            "{"
                "\"MessageTtlSeconds\": 9999999" /* TTL value length larger than SIGNALING_CHANNEL_TTL_SECONDS_BUFFER_MAX ( 5 ). */
            "}"
        "}"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeSignalingChannelResponse( message,
                                                              messageLength,
                                                              &( channelInfo ) );

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
    const char *message =
    "{"
        "\"ChannelInfo\":"
        "{"
            "\"ChannelType\": \"INVALID_TYPE\""
        "}"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeSignalingChannelResponse( message,
                                                              messageLength,
                                                              &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_CHANNEL_TYPE,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Response functionality for too long Channel Name.
 */
void test_signaling_ParseDescribeSignalingChannelResponse_ChannelNameTooLong( void )
{
    SignalingChannelInfo_t channelInfo;
    SignalingResult_t result;
    char longChannelName[ SIGNALING_CHANNEL_NAME_MAX_LEN + 10 ];
    char message[ 1000 ];

    memset( longChannelName, 'a', sizeof( longChannelName ) - 1 );
    longChannelName[ sizeof( longChannelName ) - 1 ] = '\0';

    snprintf( message,
              sizeof( message ),
              "{"
                    "\"ChannelInfo\":"
                    "{"
                        "\"ChannelName\": \"%s\""
                    "}"
               "}",
               longChannelName );
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeSignalingChannelResponse( message,
                                                              messageLength,
                                                              &( channelInfo ) );

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
    const char *message =
    "{"
        "\"ChannelInfo\":"
        "{"
            "\"ChannelARN\": \"arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123\","
            "\"ChannelName\": \"test-channel\","
            "\"ChannelStatus\": \"ACTIVE\","
            "\"ChannelType\": \"SINGLE_MASTER\","
            "\"CreationTime\": \"2023-05-01T12:00:00Z\","
            "\"SingleMasterConfiguration\": {\"MessageTtlSeconds\": 60},"
            "\"Version\": \"1\","
            "\"Unkown\": \"200\"" /* Unkown Tag --> Will be skipped. */
        "}"
    "}";
    size_t messageLength = strlen( message );
    const char * pExpectedChannelArn = "arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123";

    result = Signaling_ParseDescribeSignalingChannelResponse( message,
                                                              messageLength,
                                                              &( channelInfo ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedChannelArn ),
                       channelInfo.channelArn.channelArnLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedChannelArn,
                                  channelInfo.channelArn.pChannelArn,
                                  channelInfo.channelArn.channelArnLength );
    TEST_ASSERT_EQUAL( strlen( "test-channel" ),
                       channelInfo.channelName.channelNameLength );
    TEST_ASSERT_EQUAL_STRING_LEN( "test-channel",
                                  channelInfo.channelName.pChannelName,
                                  channelInfo.channelName.channelNameLength );
    TEST_ASSERT_EQUAL( strlen( "ACTIVE" ),
                       channelInfo.channelStatusLength );
    TEST_ASSERT_EQUAL_STRING_LEN( "ACTIVE",
                                  channelInfo.pChannelStatus,
                                  channelInfo.channelStatusLength );
    TEST_ASSERT_EQUAL( SIGNALING_TYPE_CHANNEL_SINGLE_MASTER,
                       channelInfo.channelType );
    TEST_ASSERT_EQUAL( 60,
                       channelInfo.messageTtlSeconds );
    TEST_ASSERT_EQUAL( strlen( "1" ),
                       channelInfo.versionLength );
    TEST_ASSERT_EQUAL_STRING_LEN( "1",
                                  channelInfo.pVersion,
                                  channelInfo.versionLength );
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
                                                                   &( channelArn ),
                                                                   &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    awsRegion.pAwsRegion = NULL;

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ),
                                                                   &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   NULL,
                                                                   &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ),
                                                                   NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pUrl = NULL;

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ),
                                                                   &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pUrl = "https://kinesisvideo.cn-east-1.amazonaws.com.cn/describeSignalingChannel";
    requestBuffer.urlLength = strlen( requestBuffer.pUrl );
    requestBuffer.pBody = NULL;

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ),
                                                                   &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pBody = "{\"ChannelName\":\"Test-Channel-China\"}";
    requestBuffer.bodyLength = strlen( requestBuffer.pBody );
    channelArn.pChannelArn = NULL;

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ),
                                                                   &( requestBuffer ) );

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
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 100 ];
    const char * pExpectedUrl = "https://kinesisvideo.us-east-1.amazonaws.com/describeMediaStorageConfiguration";
    const char * pExpectedBody =
    "{"
        "\"ChannelARN\":\"arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123\""
    "}";

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    channelArn.channelArnLength = strlen( channelArn.pChannelArn );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ),
                                                                   &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedUrl,
                                  requestBuffer.pUrl,
                                  requestBuffer.urlLength  );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedBody,
                                  requestBuffer.pBody,
                                  requestBuffer.bodyLength );
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
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 100 ];
    const char * pExpectedUrl = "https://kinesisvideo.ca.amazonaws.com/describeMediaStorageConfiguration";
    const char * pExpectedBody =
    "{"
        "\"ChannelARN\":\"arn:aws:kinesisvideo:ca:123456789012:channel/test-channel/1234567890123\""
    "}";

    awsRegion.pAwsRegion = "ca"; /* The Region Length is < 3. */
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelArn.pChannelArn = "arn:aws:kinesisvideo:ca:123456789012:channel/test-channel/1234567890123";
    channelArn.channelArnLength = strlen( channelArn.pChannelArn );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ),
                                                                   &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedUrl,
                                  requestBuffer.pUrl,
                                  requestBuffer.urlLength );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedBody,
                                  requestBuffer.pBody,
                                  requestBuffer.bodyLength );
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
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 100 ];
    const char * pExpectedUrl = "https://kinesisvideo.cn-north-1.amazonaws.com.cn/describeMediaStorageConfiguration";
    const char * pExpectedBody =
    "{"
        "\"ChannelARN\":\"arn:aws-cn:kinesisvideo:cn-north-1:123456789012:channel/test-channel/1234567890123\""
    "}";

    awsRegion.pAwsRegion = "cn-north-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelArn.pChannelArn = "arn:aws-cn:kinesisvideo:cn-north-1:123456789012:channel/test-channel/1234567890123";
    channelArn.channelArnLength = strlen( channelArn.pChannelArn );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ),
                                                                   &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedUrl,
                                  requestBuffer.pUrl,
                                  requestBuffer.urlLength );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedBody,
                                  requestBuffer.pBody,
                                  requestBuffer.bodyLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Describe Media Storage Config Request functionality.
 */
void test_signaling_ConstructDescribeMediaStorageConfigRequest_UrlOutOfMemory( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    SignalingChannelArn_t channelArn = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 78 ]; /* The url buffer is too small to fit the complete URL. */
    char bodyBuffer[ 100 ];

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    channelArn.channelArnLength = strlen( channelArn.pChannelArn );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ),
                                                                   &( requestBuffer ) );

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
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 95 ]; /* The body buffer is too small to fit the complete body. */

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    channelArn.channelArnLength = strlen( channelArn.pChannelArn );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDescribeMediaStorageConfigRequest( &( awsRegion ),
                                                                   &( channelArn ),
                                                                   &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Media Storage Config fail functionality for Bad Parameters.
 */
void test_signaling_ParseDescribeMediaStorageConfigResponse_BadParams( void )
{
    SignalingMediaStorageConfig_t mediaStorageConfig;
    SignalingResult_t result;
    const char * message = "Valid-Message";
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeMediaStorageConfigResponse( NULL,
                                                                messageLength,
                                                                &( mediaStorageConfig ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ParseDescribeMediaStorageConfigResponse( message,
                                                                messageLength,
                                                                NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Media Storage Config functionality.
 */
void test_signaling_ParseDescribeMediaStorageConfigResponse_InvalidJson( void )
{
    SignalingMediaStorageConfig_t mediaStorageConfig;
    SignalingResult_t result;
    const char * message = "{\"MediaStorageConfiguration\": {";  /* Missing closing brace. */
    size_t messageLength = sizeof( message );

    result = Signaling_ParseDescribeMediaStorageConfigResponse( message,
                                                                messageLength,
                                                                &( mediaStorageConfig ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );

    /* <--------------------------------------------------------------------> */

    const char * message2 = "{}"; /* Empty JSON. */
    size_t messageLength2 = strlen( message2 );

    result = Signaling_ParseDescribeMediaStorageConfigResponse( message2,
                                                                messageLength2,
                                                                &( mediaStorageConfig ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Media Storage Config functionality.
 */
void test_signaling_ParseDescribeMediaStorageConfigResponse_UnexpectedResponse( void )
{
    SignalingMediaStorageConfig_t mediaStorageConfig;
    SignalingResult_t result;
    const char * message =
    "{"
        "\"MediaStorageConfiguration\":"
        "[" /* Unexpected JSON array. */
            "{"
                "\"StreamARN\": \"arn:aws:kinesisvideo:us-west-2:123456789012:stream/test-stream/1234567890123\""
            "}"
        "]"
    "}";
    size_t messageLength = strlen( message );


    result = Signaling_ParseDescribeMediaStorageConfigResponse( message,
                                                                messageLength, &( mediaStorageConfig ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );

    /*<----------------------------------------------------------------->*/

    const char * message2 =
    "{"
        "\"Unkown\":" /* Unkown Key. */
        "{"
            "\"Status\": \"ENABLED\","
            "\"StreamARN\": \"arn:aws:kinesisvideo:us-west-2:123456789012:stream/test-stream/1234567890123\""
        "}"
    "}";
    size_t messageLength2 = strlen( message2 );


    result = Signaling_ParseDescribeMediaStorageConfigResponse( message2,
                                                                messageLength2,
                                                                &( mediaStorageConfig ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );

    /*<----------------------------------------------------------------->*/

    const char * message3 =
    "{"
        "\"PediaStorageConfiguration\":" /* Unknown key even though length of the key is same as "MediaStorageConfiguration". */
        "{"
            "\"Status\": \"ENABLED\","
            "\"StreamARN\": \"arn:aws:kinesisvideo:us-west-2:123456789012:stream/test-stream/1234567890123\""
        "}"
    "}";
    size_t messageLength3 = strlen( message3 );

    result = Signaling_ParseDescribeMediaStorageConfigResponse( message3,
                                                                messageLength3,
                                                                &( mediaStorageConfig ) );

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
    const char *message =
    "{"
        "\"MediaStorageConfiguration\":"
        "{"
            "\"Status\": \"ENABLED\""
            /* Missing StreamARN. */
        "}"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseDescribeMediaStorageConfigResponse( message,
                                                                messageLength,
                                                                &( mediaStorageConfig ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( "ENABLED" ),
                       mediaStorageConfig.statusLength );
    TEST_ASSERT_EQUAL_STRING_LEN( "ENABLED",
                                  mediaStorageConfig.pStatus,
                                  mediaStorageConfig.statusLength );
    TEST_ASSERT_NULL( mediaStorageConfig.pStreamArn );
    TEST_ASSERT_EQUAL( 0,
                       mediaStorageConfig.streamArnLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Media Storage Config functionality.
 */
void test_signaling_ParseDescribeMediaStorageConfigResponse( void )
{
    SignalingMediaStorageConfig_t mediaStorageConfig;
    SignalingResult_t result;
    const char * message =
    "{"
        "\"MediaStorageConfiguration\":"
        "{"
            "\"Status\": \"ENABLED\","
            "\"StreamARN\": \"arn:aws:kinesisvideo:us-west-2:123456789012:stream/test-stream/1234567890123\","
            "\"Unkown\": \"Unkown Value\"" /* This will be ignored. */
        "}"
    "}";
    size_t messageLength = strlen( message );
    const char * pExpectedStreamArn = "arn:aws:kinesisvideo:us-west-2:123456789012:stream/test-stream/1234567890123";

    result = Signaling_ParseDescribeMediaStorageConfigResponse( message,
                                                                messageLength,
                                                                &( mediaStorageConfig ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( "ENABLED" ),
                       mediaStorageConfig.statusLength );
    TEST_ASSERT_EQUAL_STRING_LEN( "ENABLED",
                                  mediaStorageConfig.pStatus,
                                  mediaStorageConfig.statusLength );
    TEST_ASSERT_EQUAL( strlen( pExpectedStreamArn ),
                       mediaStorageConfig.streamArnLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedStreamArn,
                                  mediaStorageConfig.pStreamArn,
                                  strlen( pExpectedStreamArn ) );
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
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    awsRegion.pAwsRegion = NULL;

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               NULL,
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pUrl = NULL;

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pUrl = "https://kinesisvideo.cn-east-1.amazonaws.com.cn/describeSignalingChannel";
    requestBuffer.urlLength = strlen( requestBuffer.pUrl );
    requestBuffer.pBody = NULL;

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pBody = "{\"ChannelName\":\"Test-Channel-China\"}";
    requestBuffer.bodyLength = strlen( requestBuffer.pBody );
    createSignalingChannelRequestInfo.numTags = 1;
    createSignalingChannelRequestInfo.pTags = NULL;

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    createSignalingChannelRequestInfo.pTags = &( tags[ 0 ] );
    createSignalingChannelRequestInfo.channelName.channelNameLength = SIGNALING_CHANNEL_NAME_MAX_LEN + 1;

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Channel Request functionality.
 */
void test_signaling_ConstructCreateSignalingChannelRequest_UrlOutofMemory( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    CreateSignalingChannelRequestInfo_t createSignalingChannelRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 20 ]; /* URL buffer too small to fit the complete URL. */
    char bodyBuffer[ 500 ];

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    createSignalingChannelRequestInfo.channelName.pChannelName = "Test-Channel";
    createSignalingChannelRequestInfo.channelName.channelNameLength = strlen( createSignalingChannelRequestInfo.channelName.pChannelName );
    createSignalingChannelRequestInfo.channelType = SIGNALING_TYPE_CHANNEL_SINGLE_MASTER;
    createSignalingChannelRequestInfo.messageTtlSeconds = 60;
    createSignalingChannelRequestInfo.numTags = 0;
    createSignalingChannelRequestInfo.pTags = NULL;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Channel Request functionality.
 */
void test_signaling_ConstructCreateSignalingChannelRequest_BodyOutofMemory( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    CreateSignalingChannelRequestInfo_t createSignalingChannelRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 100 ]; /* Body buffer too small to fit the complete body. */

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    createSignalingChannelRequestInfo.channelName.pChannelName = "Test-Channel";
    createSignalingChannelRequestInfo.channelName.channelNameLength = strlen( createSignalingChannelRequestInfo.channelName.pChannelName );
    createSignalingChannelRequestInfo.channelType = SIGNALING_TYPE_CHANNEL_SINGLE_MASTER;
    createSignalingChannelRequestInfo.messageTtlSeconds = 60;
    createSignalingChannelRequestInfo.numTags = 0;
    createSignalingChannelRequestInfo.pTags = NULL;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Channel Request functionality.
 */
void test_signaling_ConstructCreateSignalingChannelRequest_BodyClosingBraceOutofMemory( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    CreateSignalingChannelRequestInfo_t createSignalingChannelRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 113 ]; /* Body buffer does not have space for the closing "}" in the body. */

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    createSignalingChannelRequestInfo.channelName.pChannelName = "Test-Channel";
    createSignalingChannelRequestInfo.channelName.channelNameLength = strlen( createSignalingChannelRequestInfo.channelName.pChannelName );
    createSignalingChannelRequestInfo.channelType = SIGNALING_TYPE_CHANNEL_SINGLE_MASTER;
    createSignalingChannelRequestInfo.messageTtlSeconds = 60;
    createSignalingChannelRequestInfo.numTags = 0;
    createSignalingChannelRequestInfo.pTags = NULL;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
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
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    const char * pExpectedUrl = "https://kinesisvideo.us-east-1.amazonaws.com/createSignalingChannel";
    const char * pExpectedBody =
    "{"
        "\"ChannelName\":\"Test-Channel\","
        "\"ChannelType\":\"SINGLE_MASTER\","
        "\"SingleMasterConfiguration\":"
        "{"
            "\"MessageTtlSeconds\":60"
        "}"
    "}";

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    createSignalingChannelRequestInfo.channelName.pChannelName = "Test-Channel";
    createSignalingChannelRequestInfo.channelName.channelNameLength = strlen( createSignalingChannelRequestInfo.channelName.pChannelName );
    createSignalingChannelRequestInfo.channelType = SIGNALING_TYPE_CHANNEL_SINGLE_MASTER;
    createSignalingChannelRequestInfo.messageTtlSeconds = 60;
    createSignalingChannelRequestInfo.numTags = 0;
    createSignalingChannelRequestInfo.pTags = NULL;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedUrl,
                                  requestBuffer.pUrl,
                                  requestBuffer.urlLength );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedBody,
                                  requestBuffer.pBody,
                                  requestBuffer.bodyLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Channel Request functionality.
 */
void test_signaling_ConstructCreateSignalingChannelRequest_UnkownChannelType( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    CreateSignalingChannelRequestInfo_t createSignalingChannelRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    const char * pExpectedUrl = "https://kinesisvideo.us-east-1.amazonaws.com/createSignalingChannel";
    const char * pExpectedBody =
    "{"
        "\"ChannelName\":\"Test-Channel\","
        "\"ChannelType\":\"UNKOWN\","
        "\"SingleMasterConfiguration\":"
        "{"
            "\"MessageTtlSeconds\":60"
        "}"
    "}";

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    createSignalingChannelRequestInfo.channelName.pChannelName = "Test-Channel";
    createSignalingChannelRequestInfo.channelName.channelNameLength = strlen( createSignalingChannelRequestInfo.channelName.pChannelName );
    createSignalingChannelRequestInfo.channelType = SIGNALING_TYPE_CHANNEL_UNKNOWN;
    createSignalingChannelRequestInfo.messageTtlSeconds = 60;
    createSignalingChannelRequestInfo.numTags = 0;
    createSignalingChannelRequestInfo.pTags = NULL;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedUrl,
                                  requestBuffer.pUrl,
                                  requestBuffer.urlLength );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedBody,
                                  requestBuffer.pBody,
                                  requestBuffer.bodyLength );
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
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    const char * pExpectedUrl = "https://kinesisvideo.ca.amazonaws.com/createSignalingChannel";
    const char * pExpectedBody =
    "{"
        "\"ChannelName\":\"Test-Channel\","
        "\"ChannelType\":\"SINGLE_MASTER\","
        "\"SingleMasterConfiguration\":"
        "{"
            "\"MessageTtlSeconds\":60"
        "}"
    "}";

    awsRegion.pAwsRegion = "ca"; /* The Region Length is < 3. */
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    createSignalingChannelRequestInfo.channelName.pChannelName = "Test-Channel";
    createSignalingChannelRequestInfo.channelName.channelNameLength = strlen( createSignalingChannelRequestInfo.channelName.pChannelName );
    createSignalingChannelRequestInfo.channelType = SIGNALING_TYPE_CHANNEL_SINGLE_MASTER;
    createSignalingChannelRequestInfo.messageTtlSeconds = 60;
    createSignalingChannelRequestInfo.numTags = 0;
    createSignalingChannelRequestInfo.pTags = NULL;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedUrl,
                                  requestBuffer.pUrl,
                                  requestBuffer.urlLength );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedBody,
                                  requestBuffer.pBody,
                                  requestBuffer.bodyLength );
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
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    const char * pExpectedUrl = "https://kinesisvideo.cn-north-1.amazonaws.com.cn/createSignalingChannel";
    const char * pExpectedBody =
    "{"
        "\"ChannelName\":\"Test-Channel\","
        "\"ChannelType\":\"SINGLE_MASTER\","
        "\"SingleMasterConfiguration\":"
        "{"
            "\"MessageTtlSeconds\":60"
        "}"
    "}";

    awsRegion.pAwsRegion = "cn-north-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    createSignalingChannelRequestInfo.channelName.pChannelName = "Test-Channel";
    createSignalingChannelRequestInfo.channelName.channelNameLength = strlen( createSignalingChannelRequestInfo.channelName.pChannelName );
    createSignalingChannelRequestInfo.channelType = SIGNALING_TYPE_CHANNEL_SINGLE_MASTER;
    createSignalingChannelRequestInfo.messageTtlSeconds = 60;
    createSignalingChannelRequestInfo.numTags = 0;
    createSignalingChannelRequestInfo.pTags = NULL;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedUrl,
                                  requestBuffer.pUrl,
                                  requestBuffer.urlLength );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedBody,
                                  requestBuffer.pBody,
                                  requestBuffer.bodyLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Channel Request functionality.
 */
void test_signaling_ConstructCreateSignalingChannelRequest_WithTagsLeftArrayBracketOutofMemory( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    CreateSignalingChannelRequestInfo_t createSignalingChannelRequestInfo = { 0 };
    SignalingTag_t tags[ 1 ] = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 121 ]; /* Buffer not large enough to contain "[" in the body. */

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    tags[ 0 ].pName = "Tag1";
    tags[ 0 ].nameLength = strlen( tags->pName );
    tags[ 0 ].pValue = "Value1";
    tags[ 0 ].valueLength = strlen( tags->pValue );

    createSignalingChannelRequestInfo.channelName.pChannelName = "Test-Channel";
    createSignalingChannelRequestInfo.channelName.channelNameLength = strlen( createSignalingChannelRequestInfo.channelName.pChannelName );
    createSignalingChannelRequestInfo.channelType = SIGNALING_TYPE_CHANNEL_SINGLE_MASTER;
    createSignalingChannelRequestInfo.messageTtlSeconds = 60;
    createSignalingChannelRequestInfo.numTags = 1;
    createSignalingChannelRequestInfo.pTags = tags;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Channel Request functionality.
 */
void test_signaling_ConstructCreateSignalingChannelRequest_WithTagsOutofMemory( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    CreateSignalingChannelRequestInfo_t createSignalingChannelRequestInfo = { 0 };
    SignalingTag_t tags[ 2 ] = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 170 ]; /* Buffer not large enough to contain tags in the body. */

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    tags[ 0 ].pName = "Tag1";
    tags[ 0 ].nameLength = strlen( tags[ 0 ].pName );
    tags[ 0 ].pValue = "Value1";
    tags[ 0 ].valueLength = strlen( tags[ 0 ].pValue );

    tags[ 1 ].pName = "Tag2";
    tags[ 1 ].nameLength = strlen( tags[ 1 ].pName );
    tags[ 1 ].pValue = "Value2";
    tags[ 1 ].valueLength = strlen( tags[ 1 ].pValue );

    createSignalingChannelRequestInfo.channelName.pChannelName = "Test-Channel";
    createSignalingChannelRequestInfo.channelName.channelNameLength = strlen( createSignalingChannelRequestInfo.channelName.pChannelName );
    createSignalingChannelRequestInfo.channelType = SIGNALING_TYPE_CHANNEL_SINGLE_MASTER;
    createSignalingChannelRequestInfo.messageTtlSeconds = 60;
    createSignalingChannelRequestInfo.numTags = 2;
    createSignalingChannelRequestInfo.pTags = tags;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Channel Request functionality.
 */
void test_signaling_ConstructCreateSignalingChannelRequest_WithTagsRightArrayBracketOutofMemory( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    CreateSignalingChannelRequestInfo_t createSignalingChannelRequestInfo = { 0 };
    SignalingTag_t tags[ 2 ] = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 185 ]; /* Buffer not large enough to contain "]" in the body. */

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    tags[ 0 ].pName = "Tag1";
    tags[ 0 ].nameLength = strlen( tags[ 0 ].pName );
    tags[ 0 ].pValue = "Value1";
    tags[ 0 ].valueLength = strlen( tags[ 0 ].pValue );

    tags[ 1 ].pName = "Tag2";
    tags[ 1 ].nameLength = strlen( tags[ 1 ].pName );
    tags[ 1 ].pValue = "Value2";
    tags[ 1 ].valueLength = strlen( tags[ 1 ].pValue );

    createSignalingChannelRequestInfo.channelName.pChannelName = "Test-Channel";
    createSignalingChannelRequestInfo.channelName.channelNameLength = strlen( createSignalingChannelRequestInfo.channelName.pChannelName );
    createSignalingChannelRequestInfo.channelType = SIGNALING_TYPE_CHANNEL_SINGLE_MASTER;
    createSignalingChannelRequestInfo.messageTtlSeconds = 60;
    createSignalingChannelRequestInfo.numTags = 2;
    createSignalingChannelRequestInfo.pTags = tags;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Channel Request functionality.
 */
void test_signaling_ConstructCreateSignalingChannelRequest_WithTags( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    CreateSignalingChannelRequestInfo_t createSignalingChannelRequestInfo = { 0 };
    SignalingTag_t tags[ 2 ] = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    const char * pExpectedUrl = "https://kinesisvideo.us-east-1.amazonaws.com/createSignalingChannel";
    const char * pExpectedBody =
    "{"
        "\"ChannelName\":\"Test-Channel\","
        "\"ChannelType\":\"SINGLE_MASTER\","
        "\"SingleMasterConfiguration\":"
        "{"
            "\"MessageTtlSeconds\":60"
        "},"
        "\"Tags\":"
        "["
            "{"
                "\"Key\":\"Tag1\","
                "\"Value\":\"Value1\""
            "},"
            "{"
                "\"Key\":\"Tag2\","
                "\"Value\":\"Value2\""
            "}"
        "]"
    "}";

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    tags[ 0 ].pName = "Tag1";
    tags[ 0 ].nameLength = strlen( tags[ 0 ].pName );
    tags[ 0 ].pValue = "Value1";
    tags[ 0 ].valueLength = strlen( tags[ 0 ].pValue );

    tags[ 1 ].pName = "Tag2";
    tags[ 1 ].nameLength = strlen( tags[ 1 ].pName );
    tags[ 1 ].pValue = "Value2";
    tags[ 1 ].valueLength = strlen( tags[ 1 ].pValue );

    createSignalingChannelRequestInfo.channelName.pChannelName = "Test-Channel";
    createSignalingChannelRequestInfo.channelName.channelNameLength = strlen( createSignalingChannelRequestInfo.channelName.pChannelName );
    createSignalingChannelRequestInfo.channelType = SIGNALING_TYPE_CHANNEL_SINGLE_MASTER;
    createSignalingChannelRequestInfo.messageTtlSeconds = 60;
    createSignalingChannelRequestInfo.numTags = 2;
    createSignalingChannelRequestInfo.pTags = tags;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructCreateSignalingChannelRequest( &( awsRegion ),
                                                               &( createSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedUrl,
                                  requestBuffer.pUrl,
                                  requestBuffer.urlLength );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedBody,
                                  requestBuffer.pBody,
                                  requestBuffer.bodyLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Describe Media Storage Config fail functionality for Bad Parameters.
 */
void test_signaling_ParseCreateSignalingChannelResponse_BadParams( void )
{
    SignalingChannelArn_t channelArn = { 0 };
    SignalingResult_t result;
    const char * message = "Valid-Message";
    size_t messageLength = strlen( message );

    result = Signaling_ParseCreateSignalingChannelResponse( NULL,
                                                            messageLength,
                                                            &( channelArn ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ParseCreateSignalingChannelResponse( message,
                                                            messageLength,
                                                            NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Create Signaling Channel Response functionality.
 */
void test_signaling_ParseCreateSignalingChannelResponse_InvalidJson( void )
{
    SignalingChannelArn_t channelArn = { 0 };
    SignalingResult_t result;
    const char * message = "{\"ChannelARN\": \"test-arn\"";  /* Missing closing brace. */
    size_t messageLength = strlen( message );

    result = Signaling_ParseCreateSignalingChannelResponse( message,
                                                            messageLength,
                                                            &( channelArn ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Create Signaling Channel Response functionality.
 */
void test_signaling_ParseCreateSignalingChannelResponse_UnexpectedResponse( void )
{
    SignalingChannelArn_t channelArn = { 0 };
    SignalingResult_t result;
    const char * message = "{}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseCreateSignalingChannelResponse( message,
                                                            messageLength,
                                                            &( channelArn ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Create Signaling Channel Response functionality.
 */
void test_signaling_ParseCreateSignalingChannelResponse_UnkownKey( void )
{
    SignalingChannelArn_t channelArn = { 0 };
    SignalingResult_t result;
    const char * message =
    "{"
        "\"Unkown\": \"arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123\""
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseCreateSignalingChannelResponse( message,
                                                            messageLength,
                                                            &( channelArn ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Create Signaling Channel Response functionality.
 */
void test_signaling_ParseCreateSignalingChannelResponse( void )
{
    SignalingChannelArn_t channelArn = { 0 };
    SignalingResult_t result;
    const char *message =
    "{"
        "\"ChannelARN\": \"arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123\""
    "}";
    size_t messageLength = strlen( message );
    const char * pExpectedChannelArn = "arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123";

    result = Signaling_ParseCreateSignalingChannelResponse( message,
                                                            messageLength,
                                                            &( channelArn ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedChannelArn ),
                       channelArn.channelArnLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedChannelArn,
                                  channelArn.pChannelArn,
                                  channelArn.channelArnLength );
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
    SignalingResult_t result;
    const char * channelArn = "arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123";

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( NULL,
                                                                    &( getSignalingChannelEndPointRequestInfo ),
                                                                    &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    awsRegion.pAwsRegion = NULL;

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ),
                                                                    &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ),
                                                                    NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    NULL,
                                                                    &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pUrl = NULL;

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ),
                                                                    &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pUrl = "https://kinesisvideo.cn-east-1.amazonaws.com.cn/describeSignalingChannel";
    requestBuffer.urlLength = strlen( requestBuffer.pUrl );
    requestBuffer.pBody = NULL;

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ),
                                                                    &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    requestBuffer.pBody = "{\"ChannelName\":\"Test-Channel\"}";
    requestBuffer.bodyLength = strlen( requestBuffer.pBody );
    getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn = NULL;

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ),
                                                                    &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn = channelArn;
    getSignalingChannelEndPointRequestInfo.channelArn.channelArnLength = strlen( getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn );
    getSignalingChannelEndPointRequestInfo.role = SIGNALING_ROLE_NONE;

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ),
                                                                    &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Get Channel Endpoint Request functionality .
 */
void test_signaling_ConstructGetSignalingChannelEndpointRequest_UrlOutofMemory( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    GetSignalingChannelEndpointRequestInfo_t getSignalingChannelEndPointRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 72 ]; /* Buffer too small to fit the complete URL. */
    char bodyBuffer[ 500 ];

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    getSignalingChannelEndPointRequestInfo.channelArn.channelArnLength = strlen( getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn );
    getSignalingChannelEndPointRequestInfo.role = SIGNALING_ROLE_VIEWER;
    getSignalingChannelEndPointRequestInfo.protocols = SIGNALING_PROTOCOL_WEBRTC | SIGNALING_PROTOCOL_WEBSOCKET_SECURE;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ),
                                                                    &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Get Channel Endpoint Request functionality .
 */
void test_signaling_ConstructGetSignalingChannelEndpointRequest_BodyOutofMemory( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    GetSignalingChannelEndpointRequestInfo_t getSignalingChannelEndPointRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 184 ]; /* Body buffer too small to fit the complete body. */

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    getSignalingChannelEndPointRequestInfo.channelArn.channelArnLength = strlen( getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn );
    getSignalingChannelEndPointRequestInfo.role = SIGNALING_ROLE_MASTER;
    getSignalingChannelEndPointRequestInfo.protocols = SIGNALING_PROTOCOL_HTTPS | SIGNALING_PROTOCOL_WEBSOCKET_SECURE;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ),
                                                                    &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Get Channel Endpoint Request functionality .
 */
void test_signaling_ConstructGetSignalingChannelEndpointRequest_Https( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    GetSignalingChannelEndpointRequestInfo_t getSignalingChannelEndPointRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    const char * pExpectedUrl = "https://kinesisvideo.us-east-1.amazonaws.com/getSignalingChannelEndpoint";
    const char * pExpectedBody =
    "{"
        "\"ChannelARN\":\"arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123\","
        "\"SingleMasterChannelEndpointConfiguration\":"
        "{"
            "\"Protocols\":[\"HTTPS\"],"
            "\"Role\":\"MASTER\""
        "}"
    "}";

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    getSignalingChannelEndPointRequestInfo.channelArn.channelArnLength = strlen( getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn );
    getSignalingChannelEndPointRequestInfo.role = SIGNALING_ROLE_MASTER;
    getSignalingChannelEndPointRequestInfo.protocols = SIGNALING_PROTOCOL_HTTPS;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ),
                                                                    &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedUrl,
                                  requestBuffer.pUrl,
                                  requestBuffer.urlLength );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedBody,
                                  requestBuffer.pBody,
                                  requestBuffer.bodyLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Get Channel Endpoint Request functionality .
 */
void test_signaling_ConstructGetSignalingChannelEndpointRequest_ChinaRegion( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    GetSignalingChannelEndpointRequestInfo_t getSignalingChannelEndPointRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    const char * pExpectedUrl = "https://kinesisvideo.cn-east-1.amazonaws.com.cn/getSignalingChannelEndpoint";
    const char * pExpectedBody =
    "{"
        "\"ChannelARN\":\"arn:aws-cn:kinesisvideo:cn-east-1:123456789012:channel/test-channel/1234567890123\","
        "\"SingleMasterChannelEndpointConfiguration\":"
        "{"
            "\"Protocols\":[\"WSS\",\"HTTPS\"],"
            "\"Role\":\"VIEWER\""
        "}"
    "}";

    awsRegion.pAwsRegion = "cn-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn = "arn:aws-cn:kinesisvideo:cn-east-1:123456789012:channel/test-channel/1234567890123";
    getSignalingChannelEndPointRequestInfo.channelArn.channelArnLength = strlen( getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn );
    getSignalingChannelEndPointRequestInfo.role = SIGNALING_ROLE_VIEWER;
    getSignalingChannelEndPointRequestInfo.protocols = SIGNALING_PROTOCOL_HTTPS | SIGNALING_PROTOCOL_WEBSOCKET_SECURE;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ),
                                                                    &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedUrl,
                                  requestBuffer.pUrl,
                                  requestBuffer.urlLength );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedBody,
                                  requestBuffer.pBody,
                                  requestBuffer.bodyLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Get Channel Endpoint Request functionality .
 */
void test_signaling_ConstructGetSignalingChannelEndpointRequest_SmallLengthRegion( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    GetSignalingChannelEndpointRequestInfo_t getSignalingChannelEndPointRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    const char * pExpectedUrl = "https://kinesisvideo.ca.amazonaws.com/getSignalingChannelEndpoint";
    const char * pExpectedBody =
    "{"
        "\"ChannelARN\":\"arn:aws:kinesisvideo:ca:123456789012:channel/test-channel/1234567890123\","
        "\"SingleMasterChannelEndpointConfiguration\":"
        "{"
            "\"Protocols\":[\"WSS\",\"HTTPS\"],"
            "\"Role\":\"MASTER\""
        "}"
    "}";

    awsRegion.pAwsRegion = "ca"; /* The Region Length is < 3. */
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:ca:123456789012:channel/test-channel/1234567890123";
    getSignalingChannelEndPointRequestInfo.channelArn.channelArnLength = strlen( getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn );
    getSignalingChannelEndPointRequestInfo.role = SIGNALING_ROLE_MASTER;
    getSignalingChannelEndPointRequestInfo.protocols = SIGNALING_PROTOCOL_WEBSOCKET_SECURE | SIGNALING_PROTOCOL_HTTPS;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ),
                                                                    &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedUrl,
                                  requestBuffer.pUrl,
                                  requestBuffer.urlLength );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedBody,
                                  requestBuffer.pBody,
                                  requestBuffer.bodyLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Get Channel Endpoint Request functionality .
 */
void test_signaling_ConstructGetSignalingChannelEndpointRequest_WebSocketsOrWebRtc( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    GetSignalingChannelEndpointRequestInfo_t getSignalingChannelEndPointRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    const char * pExpectedUrl = "https://kinesisvideo.us-east-1.amazonaws.com/getSignalingChannelEndpoint";
    const char * pExpectedBody =
    "{"
        "\"ChannelARN\":\"arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123\","
        "\"SingleMasterChannelEndpointConfiguration\":"
        "{"
            "\"Protocols\":[\"WSS\",\"WEBRTC\"],"
            "\"Role\":\"MASTER\""
        "}"
    "}";

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    getSignalingChannelEndPointRequestInfo.channelArn.channelArnLength = strlen( getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn );
    getSignalingChannelEndPointRequestInfo.role = SIGNALING_ROLE_MASTER;
    getSignalingChannelEndPointRequestInfo.protocols = SIGNALING_PROTOCOL_WEBRTC | SIGNALING_PROTOCOL_WEBSOCKET_SECURE;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ),
                                                                    &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedUrl,
                                  requestBuffer.pUrl,
                                  requestBuffer.urlLength );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedBody,
                                  requestBuffer.pBody,
                                  requestBuffer.bodyLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Get Channel Endpoint Request functionality .
 */
void test_signaling_ConstructGetSignalingChannelEndpointRequest_WebRtc( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    GetSignalingChannelEndpointRequestInfo_t getSignalingChannelEndPointRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    const char * pExpectedUrl = "https://kinesisvideo.us-east-1.amazonaws.com/getSignalingChannelEndpoint";
    const char * pExpectedBody =
    "{"
        "\"ChannelARN\":\"arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123\","
        "\"SingleMasterChannelEndpointConfiguration\":"
        "{"
            "\"Protocols\":[\"WEBRTC\"],"
            "\"Role\":\"MASTER\""
        "}"
    "}";

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    getSignalingChannelEndPointRequestInfo.channelArn.channelArnLength = strlen( getSignalingChannelEndPointRequestInfo.channelArn.pChannelArn );
    getSignalingChannelEndPointRequestInfo.role = SIGNALING_ROLE_MASTER;
    getSignalingChannelEndPointRequestInfo.protocols = SIGNALING_PROTOCOL_WEBRTC;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructGetSignalingChannelEndpointRequest( &( awsRegion ),
                                                                    &( getSignalingChannelEndPointRequestInfo ),
                                                                    &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedUrl,
                                  requestBuffer.pUrl,
                                  requestBuffer.urlLength );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedBody,
                                  requestBuffer.pBody,
                                  requestBuffer.bodyLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Get Endpoint Response fail functionality for Bad Parameters.
 */
void test_signaling_ParseGetSignalingChannelEndpointResponse_BadParams( void )
{
    SignalingChannelEndpoints_t endpoints;
    SignalingResult_t result;
    const char * message = "Valid-Message";
    size_t messageLength = strlen( message );

    result = Signaling_ParseGetSignalingChannelEndpointResponse( NULL,
                                                                 messageLength,
                                                                 &( endpoints ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ParseGetSignalingChannelEndpointResponse( message,
                                                                 messageLength,
                                                                 NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Get Endpoint Response functionality for Invalid JSON.
 */
void test_signaling_ParseGetSignalingChannelEndpointResponse_InvalidJson( void )
{
    SignalingChannelEndpoints_t endpoints;
    SignalingResult_t result;
    const char * message = "{\"ResourceEndpointList\": [";  /* Missing closing bracket. */
    size_t messageLength = strlen( message );

    result = Signaling_ParseGetSignalingChannelEndpointResponse( message,
                                                                 messageLength,
                                                                 &( endpoints ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );

    /* <--------------------------------------------------------------------> */

    const char * message2 = "{}"; /* Empty JSON. */
    size_t messageLength2 = strlen( message2 );

    result = Signaling_ParseGetSignalingChannelEndpointResponse( message2,
                                                                 messageLength2,
                                                                 &( endpoints ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );
}

/*-----------------------------------------------------------*/


/**
 * @brief Validate Signaling Parse Get Endpoint Response functionality for Unexpected Response.
 */
void test_signaling_ParseGetSignalingChannelEndpointResponse_UnexpectedResponse( void )
{
    SignalingChannelEndpoints_t endpoints;
    SignalingResult_t result;
    const char * message =
    "{"
        "\"ResourceEndpointList\":"
        "{" /* Not JSON Array Type. */
            "{\"Protocol\": \"WSS\", \"ResourceEndpoint\": \"wss://example.com\"},"
            "{\"Protocol\": \"HTTPS\", \"ResourceEndpoint\": \"https://example.com\"},"
            "{\"Protocol\": \"WEBRTC\", \"ResourceEndpoint\": \"webrtc://example.com\"}"
        "}"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseGetSignalingChannelEndpointResponse( message,
                                                                 messageLength, &( endpoints ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );

    /*<----------------------------------------------------------------->*/

    const char * message2 =
    "{"
        "\"Unkown\":" /* Unkown key. */
        "["
            "{\"Protocol\": \"WSS\", \"ResourceEndpoint\": \"wss://example.com\"},"
            "{\"Protocol\": \"HTTPS\", \"ResourceEndpoint\": \"https://example.com\"},"
            "{\"Protocol\": \"WEBRTC\", \"ResourceEndpoint\": \"webrtc://example.com\"}"
        "]"
    "}";
    size_t messageLength2 = strlen( message2 );

    result = Signaling_ParseGetSignalingChannelEndpointResponse( message2,
                                                                 messageLength2,
                                                                 &( endpoints ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );

    /*<----------------------------------------------------------------->*/

    const char * message3 = "{\"ResourceEndpointBist\": []}"; /* Unknown key. */
    size_t messageLength3 = strlen( message3 );

    result = Signaling_ParseGetSignalingChannelEndpointResponse( message3,
                                                                 messageLength3,
                                                                 &( endpoints ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Get Endpoint Response functionality for Invalid Protocol.
 */
void test_signaling_ParseGetSignalingChannelEndpointResponse_InvalidProtocol( void )
{
    SignalingChannelEndpoints_t endpoints;
    SignalingResult_t result;
    const char * message =
    "{"
        "\"ResourceEndpointList\":"
        "["
            "{"
                "\"Protocol\": \"INVALID\","
                "\"ResourceEndpoint\": \"invalid://example.com\""
            "}"
        "]"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseGetSignalingChannelEndpointResponse( message,
                                                                 messageLength,
                                                                 &( endpoints ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_PROTOCOL,
                       result );

    /*<----------------------------------------------------------------->*/

    const char * message2 =
    "{"
        "\"ResourceEndpointList\":"
        "["
            "{"
                "\"Protocol\": \"ABS\"," /* Protocol length == 3  but protocol != WSS. */
                "\"ResourceEndpoint\": \"abs://example.com\""
            "}"
        "]"
    "}";
    size_t messageLength2 = strlen( message2 );

    result = Signaling_ParseGetSignalingChannelEndpointResponse( message2,
                                                                 messageLength2,
                                                                 &( endpoints ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_PROTOCOL,
                       result );

    /*<----------------------------------------------------------------->*/

    const char * message3 =
    "{"
        "\"ResourceEndpointList\":"
        "["
            "{"
                "\"Protocol\": \"HTTPA\"," /* Protocol length == 5  but protocol != HTTPS. */
                "\"ResourceEndpoint\": \"httpa://example.com\""
            "}"
        "]"
    "}";
    size_t messageLength3 = strlen( message3 );

    result = Signaling_ParseGetSignalingChannelEndpointResponse( message3,
                                                                 messageLength3,
                                                                 &( endpoints ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_PROTOCOL,
                       result );

    /*<----------------------------------------------------------------->*/

    const char * message4 =
    "{"
        "\"ResourceEndpointList\":"
        "["
            "{"
                "\"Protocol\": \"WEBRTA\"," /* Protocol length == 6  but protocol != WEBRTC. */
                "\"ResourceEndpoint\": \"webrta://example.com\""
            "}"
        "]"
    "}";
    size_t messageLength4 = strlen( message4 );

    result = Signaling_ParseGetSignalingChannelEndpointResponse( message4,
                                                                 messageLength4,
                                                                 &( endpoints ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_PROTOCOL,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Get Endpoint Response functionality.
 */
void test_signaling_ParseGetSignalingChannelEndpointResponse( void )
{
    SignalingChannelEndpoints_t endpoints;
    SignalingResult_t result;
    const char *message =
    "{"
        "\"ResourceEndpointList\":"
        "["
            "{\"Protocol\": \"WSS\", \"ResourceEndpoint\": \"wss://example.com\"},"
            "{\"Protocol\": \"HTTPS\", \"ResourceEndpoint\": \"https://example.com\"},"
            "{\"Protocol\": \"WEBRTC\", \"ResourceEndpoint\": \"webrtc://example.com\"},"
            "{\"Unkown\": \"WEBRTC\", \"ResourceEndpoint\": \"webrtc://example.com\"},"      /* Unkown Tag is ignored. */
            "{\"Protocol\": \"WEBRTC\", \"Unkown\": \"webrtc://example.com\"}"               /* Unkown Tag is ignored. */
        "]"
    "}";
    size_t messageLength = strlen( message );
    const char * expectedWssURL = "wss://example.com";
    const char * expectedHttpsURL = "https://example.com";
    const char * expectedWebrtcURL = "webrtc://example.com";

    result = Signaling_ParseGetSignalingChannelEndpointResponse( message,
                                                                 messageLength,
                                                                 &( endpoints ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( expectedWssURL ),
                       endpoints.wssEndpoint.endpointLength );
    TEST_ASSERT_EQUAL_STRING_LEN( expectedWssURL,
                                  endpoints.wssEndpoint.pEndpoint,
                                   endpoints.wssEndpoint.endpointLength );
    TEST_ASSERT_EQUAL( strlen( expectedHttpsURL ),
                       endpoints.httpsEndpoint.endpointLength );
    TEST_ASSERT_EQUAL_STRING_LEN( expectedHttpsURL,
                                  endpoints.httpsEndpoint.pEndpoint,
                                  endpoints.httpsEndpoint.endpointLength );
    TEST_ASSERT_EQUAL( strlen( expectedWebrtcURL ),
                       endpoints.webrtcEndpoint.endpointLength );
    TEST_ASSERT_EQUAL_STRING_LEN( expectedWebrtcURL,
                                  endpoints.webrtcEndpoint.pEndpoint,
                                  endpoints.webrtcEndpoint.endpointLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Get Endpoint Response functionality.
 */
void test_signaling_ParseGetSignalingChannelEndpointResponse_SmallCaps( void )
{
    SignalingChannelEndpoints_t endpoints;
    SignalingResult_t result;
    const char *message =
    "{"
        "\"ResourceEndpointList\":"
        "["
            "{\"Protocol\": \"wss\", \"ResourceEndpoint\": \"wss://example.com\"},"
            "{\"Protocol\": \"https\", \"ResourceEndpoint\": \"https://example.com\"},"
            "{\"Protocol\": \"webrtc\", \"ResourceEndpoint\": \"webrtc://example.com\"}"
        "]"
    "}";
    size_t messageLength = strlen( message );
    const char * expectedWssURL = "wss://example.com";
    const char * expectedHttpsURL = "https://example.com";
    const char * expectedWebrtcURL = "webrtc://example.com";

    result = Signaling_ParseGetSignalingChannelEndpointResponse( message,
                                                                 messageLength,
                                                                 &( endpoints ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( expectedWssURL ),
                       endpoints.wssEndpoint.endpointLength );
    TEST_ASSERT_EQUAL_STRING_LEN( expectedWssURL,
                                  endpoints.wssEndpoint.pEndpoint,
                                  endpoints.wssEndpoint.endpointLength );
    TEST_ASSERT_EQUAL( strlen( expectedHttpsURL ),
                       endpoints.httpsEndpoint.endpointLength );
    TEST_ASSERT_EQUAL_STRING_LEN( expectedHttpsURL,
                                  endpoints.httpsEndpoint.pEndpoint,
                                  endpoints.httpsEndpoint.endpointLength );
    TEST_ASSERT_EQUAL( strlen( expectedWebrtcURL ),
                       endpoints.webrtcEndpoint.endpointLength );
    TEST_ASSERT_EQUAL_STRING_LEN( expectedWebrtcURL,
                                  endpoints.webrtcEndpoint.pEndpoint,
                                  endpoints.webrtcEndpoint.endpointLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Get Ice Server Config Request fail functionality for Bad Parameters.
 */
void test_signaling_ConstructGetIceServerConfigRequest_BadParams( void )
{
    SignalingChannelEndpoint_t endpoint = { 0 };
    GetIceServerConfigRequestInfo_t iceServerConfigRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;

    result = Signaling_ConstructGetIceServerConfigRequest( NULL,
                                                           &( iceServerConfigRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    endpoint.pEndpoint = NULL;

    result = Signaling_ConstructGetIceServerConfigRequest( &( endpoint ),
                                                           &( iceServerConfigRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    endpoint.pEndpoint = "https://example.com";

    result = Signaling_ConstructGetIceServerConfigRequest( &( endpoint ),
                                                           &( iceServerConfigRequestInfo ),
                                                           NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    result = Signaling_ConstructGetIceServerConfigRequest( &( endpoint ),
                                                           NULL,
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    requestBuffer.pUrl = NULL;

    result = Signaling_ConstructGetIceServerConfigRequest( &( endpoint ),
                                                           &( iceServerConfigRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    requestBuffer.pUrl = "https://kinesisvideo.cn-east-1.amazonaws.com.cn/describeSignalingChannel";
    requestBuffer.urlLength = strlen( requestBuffer.pUrl );
    requestBuffer.pBody = NULL;

    result = Signaling_ConstructGetIceServerConfigRequest( &( endpoint ),
                                                           &( iceServerConfigRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    requestBuffer.pBody = "{\"ChannelName\":\"Test-Channel-China\"}";
    requestBuffer.bodyLength = strlen( requestBuffer.pBody );
    iceServerConfigRequestInfo.pClientId = NULL;

    result = Signaling_ConstructGetIceServerConfigRequest( &( endpoint ),
                                                           &( iceServerConfigRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Get Ice Server Config Request functionality.
 */
void test_signaling_ConstructGetIceServerConfigRequest_URLOutofMemory( void )
{
    SignalingChannelEndpoint_t endpoint = { 0 };
    GetIceServerConfigRequestInfo_t iceServerConfigRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 20 ]; /* The url buffer is too small to fit the complete URL. */
    char bodyBuffer[ 500 ];

    endpoint.pEndpoint = "https://example.com";
    endpoint.endpointLength = strlen( endpoint.pEndpoint );

    iceServerConfigRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    iceServerConfigRequestInfo.channelArn.channelArnLength = strlen( iceServerConfigRequestInfo.channelArn.pChannelArn );
    iceServerConfigRequestInfo.pClientId = "Test-Client-Id";
    iceServerConfigRequestInfo.clientIdLength = strlen( iceServerConfigRequestInfo.pClientId );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructGetIceServerConfigRequest( &( endpoint ),
                                                           &( iceServerConfigRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Get Ice Server Config Request functionality.
 */
void test_signaling_ConstructGetIceServerConfigRequest_BodyOutofMemory( void )
{
    SignalingChannelEndpoint_t endpoint = { 0 };
    GetIceServerConfigRequestInfo_t iceServerConfigRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 10 ]; /* The body buffer is too small to fit the complete body. */

    endpoint.pEndpoint = "https://example.com";
    endpoint.endpointLength = strlen( endpoint.pEndpoint );

    iceServerConfigRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    iceServerConfigRequestInfo.channelArn.channelArnLength = strlen( iceServerConfigRequestInfo.channelArn.pChannelArn );
    iceServerConfigRequestInfo.pClientId = "Test-Client-Id";
    iceServerConfigRequestInfo.clientIdLength = strlen( iceServerConfigRequestInfo.pClientId );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructGetIceServerConfigRequest( &( endpoint ),
                                                           &( iceServerConfigRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Get Ice Server Config Request functionality.
 */
void test_signaling_ConstructGetIceServerConfigRequest( void )
{
    SignalingChannelEndpoint_t endpoint = { 0 };
    GetIceServerConfigRequestInfo_t iceServerConfigRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    const char * pExpectedUrl = "https://example.com/v1/get-ice-server-config";
    const char * pExpectedBody =
    "{"
        "\"ChannelARN\":\"arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123\","
        "\"ClientId\":\"Test-Client-Id\","
        "\"Service\":\"TURN\""
    "}";

    endpoint.pEndpoint = "https://example.com";
    endpoint.endpointLength = strlen( endpoint.pEndpoint );

    iceServerConfigRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    iceServerConfigRequestInfo.channelArn.channelArnLength = strlen( iceServerConfigRequestInfo.channelArn.pChannelArn );
    iceServerConfigRequestInfo.pClientId = "Test-Client-Id";
    iceServerConfigRequestInfo.clientIdLength = strlen( iceServerConfigRequestInfo.pClientId );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructGetIceServerConfigRequest( &( endpoint ),
                                                           &( iceServerConfigRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedUrl,
                                  requestBuffer.pUrl,
                                  requestBuffer.urlLength );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedBody,
                                  requestBuffer.pBody,
                                  requestBuffer.bodyLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Ice Server Config Response fail functionality for Bad Parameters.
 */
void test_signaling_ParseGetIceServerConfigResponse_BadParams( void )
{
    SignalingIceServer_t iceServers;
    size_t numIceServers;
    SignalingResult_t result;
    const char * message = "Valid-Message";
    size_t messageLength = strlen( message );

    result = Signaling_ParseGetIceServerConfigResponse( NULL,
                                                        messageLength,
                                                        &( iceServers ),
                                                        &( numIceServers ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ParseGetIceServerConfigResponse( message,
                                                        messageLength,
                                                        NULL,
                                                        &( numIceServers ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    result = Signaling_ParseGetIceServerConfigResponse( message,
                                                        messageLength,
                                                        &( iceServers ),
                                                        NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Ice Server Config Response functionality.
 */
void test_signaling_ParseGetIceServerConfigResponse_InvalidJson( void )
{
    SignalingIceServer_t iceServers[ 1 ];
    size_t numIceServers = 1;
    SignalingResult_t result;
    const char * message = "{\"IceServerList\": ["; /* Missing closing bracket. */
    size_t messageLength = strlen( message );


    result = Signaling_ParseGetIceServerConfigResponse( message,
                                                        messageLength,
                                                        &( iceServers[ 0 ] ),
                                                        &( numIceServers ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );

    /*<----------------------------------------------------------------->*/

    const char * message2 = "{}"; /* Empty JSON. */
    size_t messageLength2 = strlen( message2 );

    result = Signaling_ParseGetIceServerConfigResponse( message2,
                                                        messageLength2,
                                                        &( iceServers[ 0 ] ),
                                                        &( numIceServers ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Ice Server Config Response functionality.
 */
void test_signaling_ParseGetIceServerConfigResponse_UnexpectedResponse( void )
{
    SignalingIceServer_t iceServers[ 1 ];
    size_t numIceServers = 1;
    SignalingResult_t result;
    const char * message =
    "{"
        "\"IceServerList\":"
        "{" /* Not JSON Array Type. */
            "{"
                "\"Password\": \"password123\","
                "\"Ttl\": 300,"
                "\"Uris\": [\"turn:example.com:3478\"],"
                "\"Username\": \"username123\""
            "}"
        "}"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseGetIceServerConfigResponse( message,
                                                        messageLength,
                                                        &( iceServers[ 0 ] ),
                                                        &( numIceServers ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );

    /*<----------------------------------------------------------------->*/

    const char * message2 =
    "{"
        "\"Unkown\":" /* Unkown key. */
        "["
            "{"
                "\"Password\": \"password123\","
                "\"Ttl\": 300,"
                "\"Uris\": [\"turn:example.com:3478\"],"
                "\"Username\": \"username123\""
            "}"
        "]"
    "}";
    size_t messageLength2 = strlen( message2 );

    result = Signaling_ParseGetIceServerConfigResponse( message2,
                                                        messageLength2,
                                                        &( iceServers[ 0 ] ),
                                                        &( numIceServers ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );

    /*<----------------------------------------------------------------->*/

    const char * message3 = "{\"UnexpectedKey\": []}"; /* Unkown Key Though the length of "IceServerList" == "UnexpectedKey". */
    size_t messageLength3 = strlen( message3 );

    result = Signaling_ParseGetIceServerConfigResponse( message3,
                                                        messageLength3,
                                                        &( iceServers[ 0 ] ),
                                                        &( numIceServers ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Ice Server Config Response functionality.
 */
void test_signaling_ParseGetIceServerConfigResponse_InvalidTtl( void )
{
    SignalingIceServer_t iceServers[ 1 ];
    size_t numIceServers = 1;
    SignalingResult_t result;
    const char * message =
    "{"
        "\"IceServerList\":"
        "["
            "{"
                "\"Password\": \"password123\","
                "\"Ttl\": 30000000," /* TTL value length > SIGNALING_ICE_SERVER_TTL_SECONDS_BUFFER_MAX ( 7 ). */
                "\"Uris\": [\"turn:example.com:3478\"],"
                "\"Username\": \"username123\""
            "}"
        "]"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseGetIceServerConfigResponse( message,
                                                        messageLength,
                                                        &( iceServers[ 0 ] ),
                                                        &( numIceServers ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_TTL,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Ice Server Config Response functionality.
 */
void test_signaling_ParseGetIceServerConfigResponse_LowTtl( void )
{
    SignalingIceServer_t iceServers[ 1 ];
    size_t numIceServers = 1;
    SignalingResult_t result;
    const char * message =
    "{"
        "\"IceServerList\":"
        "["
            "{"
                "\"Password\": \"password123\","
                "\"Ttl\": 15," /* TTL value < SIGNALING_ICE_SERVER_TTL_SECONDS_MIN (30). */
                "\"Uris\": [\"turn:example.com:3478\"],"
                "\"Username\": \"username123\""
            "}"
        "]"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseGetIceServerConfigResponse( message,
                                                        messageLength,
                                                        &( iceServers[ 0 ] ),
                                                        &( numIceServers ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_TTL,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Ice Server Config Response functionality.
 */
void test_signaling_ParseGetIceServerConfigResponse_HighTtl( void )
{
    SignalingIceServer_t iceServers[ 1 ];
    size_t numIceServers = 1;
    SignalingResult_t result;
    const char * message =
    "{"
        "\"IceServerList\":"
        "["
            "{"
                "\"Password\": \"password123\","
                "\"Ttl\": 86411," /* TTL value > SIGNALING_ICE_SERVER_TTL_SECONDS_MAX ( 86400 ). */
                "\"Uris\": [\"turn:example.com:3478\"],"
                "\"Username\": \"username123\""
            "}"
        "]"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseGetIceServerConfigResponse( message,
                                                        messageLength,
                                                        &( iceServers[ 0 ] ),
                                                        &( numIceServers ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_TTL,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Ice Server Config Response functionality.
 */
void test_signaling_ParseGetIceServerConfigResponse( void )
{
    SignalingIceServer_t iceServers[ 1 ];
    size_t numIceServers = 1;
    SignalingResult_t result;
    const char * message =
    "{"
        "\"IceServerList\":"
        "["
            "{"
                "\"Password\": \"password123\","
                "\"Ttl\": 300,"
                "\"Uris\": [\"turn:example.com:3478\"],"
                "\"Username\": \"username123\","
                "\"Unkown\": \"Unkown-Value\"" /* This Unkown Tag will be ignored. */
            "}"
        "]"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseGetIceServerConfigResponse( message,
                                                        messageLength,
                                                        &( iceServers[ 0 ] ),
                                                        &( numIceServers ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( 1,
                       numIceServers );
    TEST_ASSERT_EQUAL( strlen( "password123" ),
                       iceServers[ 0 ].passwordLength );
    TEST_ASSERT_EQUAL_STRING_LEN( "password123",
                                  iceServers[ 0 ].pPassword,
                                  iceServers[ 0 ].passwordLength );
    TEST_ASSERT_EQUAL( 300,
                       iceServers[ 0 ].messageTtlSeconds );
    TEST_ASSERT_EQUAL( 1,
                        iceServers[ 0 ].urisNum );
    TEST_ASSERT_EQUAL( strlen( "turn:example.com:3478" ),
                       iceServers[ 0 ].urisLength[ 0 ] );
    TEST_ASSERT_EQUAL_STRING_LEN( "turn:example.com:3478",
                                  iceServers[ 0 ].pUris[ 0 ],
                                  iceServers[ 0 ].urisLength[ 0 ] );
    TEST_ASSERT_EQUAL( strlen( "username123" ),
                       iceServers[ 0 ].userNameLength );
    TEST_ASSERT_EQUAL_STRING_LEN( "username123",
                                  iceServers[ 0 ].pUserName,
                                  iceServers[ 0 ].userNameLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Ice Server Config Response functionality.
 */
void test_signaling_ParseGetIceServerConfigResponse_Empty( void )
{
    SignalingIceServer_t iceServers[ 1 ];
    size_t numIceServers = 1;
    SignalingResult_t result;
    const char * message =
    "{"
        "\"IceServerList\":"
        "["
            /* Empty Buffer will be ignored. */
        "]"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseGetIceServerConfigResponse( message,
                                                        messageLength,
                                                        &( iceServers[ 0 ] ),
                                                        &( numIceServers ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( 0,
                       numIceServers );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Join Storage Session Request fail functionality for Bad Parameters.
 */
void test_signaling_ConstructJoinStorageSessionRequest_BadParams( void )
{
    SignalingChannelEndpoint_t webrtcEndpoint = { 0 };
    JoinStorageSessionRequestInfo_t joinStorageSessionRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;

    result = Signaling_ConstructJoinStorageSessionRequest( NULL,
                                                           &( joinStorageSessionRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    webrtcEndpoint.pEndpoint = NULL;

    result = Signaling_ConstructJoinStorageSessionRequest( &( webrtcEndpoint ),
                                                           &( joinStorageSessionRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    webrtcEndpoint.pEndpoint = "webrtc://example.com";
    webrtcEndpoint.endpointLength = strlen( webrtcEndpoint.pEndpoint );

    result = Signaling_ConstructJoinStorageSessionRequest( &( webrtcEndpoint ),
                                                           &( joinStorageSessionRequestInfo ),
                                                           NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */



    result = Signaling_ConstructJoinStorageSessionRequest( &( webrtcEndpoint ),
                                                           NULL,
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    requestBuffer.pUrl = NULL;

    result = Signaling_ConstructJoinStorageSessionRequest( &( webrtcEndpoint ),
                                                           &( joinStorageSessionRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    requestBuffer.pUrl = "https://kinesisvideo.cn-east-1.amazonaws.com.cn/describeSignalingChannel";
    requestBuffer.urlLength = strlen( requestBuffer.pUrl );
    requestBuffer.pBody = NULL;

    result = Signaling_ConstructJoinStorageSessionRequest( &( webrtcEndpoint ),
                                                           &( joinStorageSessionRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    requestBuffer.pBody = "{\"ChannelName\":\"Test-Channel-China\"}";
    requestBuffer.bodyLength = strlen( requestBuffer.pBody );
    joinStorageSessionRequestInfo.channelArn.pChannelArn = NULL;

    result = Signaling_ConstructJoinStorageSessionRequest( &( webrtcEndpoint ),
                                                           &( joinStorageSessionRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Join Storage Session Request functionality.
 */
void test_signaling_ConstructJoinStorageSessionRequest_Master( void )
{
    SignalingChannelEndpoint_t webrtcEndpoint = { 0 };
    JoinStorageSessionRequestInfo_t joinStorageSessionRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    const char * pExpectedUrl = "webrtc://example.com/joinStorageSession";
    const char * pExpectedBody =
    "{"
        "\"channelArn\":\"arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123\""
    "}";

    webrtcEndpoint.pEndpoint = "webrtc://example.com";
    webrtcEndpoint.endpointLength = strlen( webrtcEndpoint.pEndpoint );

    joinStorageSessionRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    joinStorageSessionRequestInfo.channelArn.channelArnLength = strlen( joinStorageSessionRequestInfo.channelArn.pChannelArn );
    joinStorageSessionRequestInfo.pClientId = NULL;
    joinStorageSessionRequestInfo.clientIdLength = 0;
    joinStorageSessionRequestInfo.role = SIGNALING_ROLE_MASTER;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructJoinStorageSessionRequest( &( webrtcEndpoint ),
                                                           &( joinStorageSessionRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_NULL( strstr( requestBuffer.pBody, "\"clientId\"" ) );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedUrl,
                                  requestBuffer.pUrl,
                                  requestBuffer.urlLength );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedBody,
                                  requestBuffer.pBody,
                                  requestBuffer.bodyLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Join Storage Session Request functionality.
 */
void test_signaling_ConstructJoinStorageSessionRequest_Viewer( void )
{
    SignalingChannelEndpoint_t webrtcEndpoint = { 0 };
    JoinStorageSessionRequestInfo_t joinStorageSessionRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    const char * pExpectedUrl = "webrtc://example.com/joinStorageSession";
    const char * pExpectedBody =
    "{"
        "\"channelArn\":\"arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123\","
        "\"clientId\":\"TestClient\""
    "}";

    webrtcEndpoint.pEndpoint = "webrtc://example.com";
    webrtcEndpoint.endpointLength = strlen( webrtcEndpoint.pEndpoint );

    joinStorageSessionRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    joinStorageSessionRequestInfo.channelArn.channelArnLength = strlen( joinStorageSessionRequestInfo.channelArn.pChannelArn );
    joinStorageSessionRequestInfo.pClientId = "TestClient";
    joinStorageSessionRequestInfo.clientIdLength = strlen( joinStorageSessionRequestInfo.pClientId );
    joinStorageSessionRequestInfo.role = SIGNALING_ROLE_VIEWER;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructJoinStorageSessionRequest( &( webrtcEndpoint ),
                                                           &( joinStorageSessionRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedUrl,
                                  requestBuffer.pUrl,
                                  requestBuffer.urlLength );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING_LEN( pExpectedBody,
                                  requestBuffer.pBody,
                                  requestBuffer.bodyLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Join Storage Session Request functionality.
 */
void test_signaling_ConstructJoinStorageSessionRequest_UrlOutofMemory( void )
{
    SignalingChannelEndpoint_t webrtcEndpoint = { 0 };
    JoinStorageSessionRequestInfo_t joinStorageSessionRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 10 ]; /* The url buffer is too small to fit the complete URL. */
    char bodyBuffer[ 500 ];

    webrtcEndpoint.pEndpoint = "webrtc://example.com";
    webrtcEndpoint.endpointLength = strlen( webrtcEndpoint.pEndpoint );

    joinStorageSessionRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    joinStorageSessionRequestInfo.channelArn.channelArnLength = strlen( joinStorageSessionRequestInfo.channelArn.pChannelArn );
    joinStorageSessionRequestInfo.pClientId = "TestClient";
    joinStorageSessionRequestInfo.clientIdLength = strlen( joinStorageSessionRequestInfo.pClientId );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructJoinStorageSessionRequest( &( webrtcEndpoint ),
                                                           &( joinStorageSessionRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY, result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Join Storage Session Request functionality.
 */
void test_signaling_ConstructJoinStorageSessionRequest_BodyOutofMemory( void )
{
    SignalingChannelEndpoint_t webrtcEndpoint = { 0 };
    JoinStorageSessionRequestInfo_t joinStorageSessionRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;
    char urlBuffer[ 200 ];
    char bodyBuffer[ 10 ]; /* The body buffer is too small to fit the complete body. */

    webrtcEndpoint.pEndpoint = "webrtc://example.com";
    webrtcEndpoint.endpointLength = strlen( webrtcEndpoint.pEndpoint );

    joinStorageSessionRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    joinStorageSessionRequestInfo.channelArn.channelArnLength = strlen( joinStorageSessionRequestInfo.channelArn.pChannelArn );
    joinStorageSessionRequestInfo.pClientId = "TestClient";
    joinStorageSessionRequestInfo.clientIdLength = strlen( joinStorageSessionRequestInfo.pClientId );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructJoinStorageSessionRequest( &( webrtcEndpoint ),
                                                           &( joinStorageSessionRequestInfo ),
                                                           &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Delete Signaling Channel Request fail functionality for Bad Parameters.
 */
void test_signaling_ConstructDeleteSignalingChannelRequest_BadParams( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    DeleteSignalingChannelRequestInfo_t deleteSignalingChannelRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;

    result = Signaling_ConstructDeleteSignalingChannelRequest( NULL,
                                                               &( deleteSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    awsRegion.pAwsRegion = NULL;

    result = Signaling_ConstructDeleteSignalingChannelRequest( &( awsRegion ),
                                                               &( deleteSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    result = Signaling_ConstructDeleteSignalingChannelRequest( &( awsRegion ),
                                                               &( deleteSignalingChannelRequestInfo ),
                                                               NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    result = Signaling_ConstructDeleteSignalingChannelRequest( &( awsRegion ),
                                                               NULL,
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    requestBuffer.pUrl = NULL;

    result = Signaling_ConstructDeleteSignalingChannelRequest( &( awsRegion ),
                                                               &( deleteSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    requestBuffer.pUrl = "https://kinesisvideo.cn-east-1.amazonaws.com.cn/describeSignalingChannel";
    requestBuffer.urlLength = strlen( requestBuffer.pUrl );
    requestBuffer.pBody = NULL;

    result = Signaling_ConstructDeleteSignalingChannelRequest( &( awsRegion ),
                                                               &( deleteSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    requestBuffer.pBody = "{\"ChannelName\":\"Test-Channel-China\"}";
    requestBuffer.bodyLength = strlen( requestBuffer.pBody );
    deleteSignalingChannelRequestInfo.channelArn.pChannelArn = NULL;

    result = Signaling_ConstructDeleteSignalingChannelRequest( &( awsRegion ),
                                                               &( deleteSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    deleteSignalingChannelRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    deleteSignalingChannelRequestInfo.channelArn.channelArnLength = strlen( deleteSignalingChannelRequestInfo.channelArn.pChannelArn );
    deleteSignalingChannelRequestInfo.pVersion = NULL;

    result = Signaling_ConstructDeleteSignalingChannelRequest( &( awsRegion ),
                                                               &( deleteSignalingChannelRequestInfo ),
                                                               &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Delete Signaling Channel Request functionality.
 */
void test_signaling_ConstructDeleteSignalingChannelRequest( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    DeleteSignalingChannelRequestInfo_t deleteSignalingChannelRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    SignalingResult_t result;
    const char * pExpectedUrl = "https://kinesisvideo.us-east-1.amazonaws.com/deleteSignalingChannel";
    const char * pExpectedBody = "{"
                                    "\"ChannelARN\":\"arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123\","
                                    "\"CurrentVersion\":\"1.0.0\""
                                  "}";

    awsRegion.pAwsRegion = "us-east-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    deleteSignalingChannelRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    deleteSignalingChannelRequestInfo.channelArn.channelArnLength = strlen( deleteSignalingChannelRequestInfo.channelArn.pChannelArn );
    deleteSignalingChannelRequestInfo.pVersion = "1.0.0";
    deleteSignalingChannelRequestInfo.versionLength = strlen( deleteSignalingChannelRequestInfo.pVersion );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDeleteSignalingChannelRequest( &( awsRegion ),
                                                               &( deleteSignalingChannelRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING( pExpectedUrl,
                              requestBuffer.pUrl );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING( pExpectedBody,
                              requestBuffer.pBody );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Delete Signaling Channel Request functionality.
 */
void test_signaling_ConstructDeleteSignalingChannelRequest_ChinaRegion( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    DeleteSignalingChannelRequestInfo_t deleteSignalingChannelRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    SignalingResult_t result;
    const char * pExpectedUrl = "https://kinesisvideo.cn-north-1.amazonaws.com.cn/deleteSignalingChannel";
    const char * pExpectedBody = "{"
                                    "\"ChannelARN\":\"arn:aws-cn:kinesisvideo:cn-north-1:123456789012:channel/test-channel/1234567890123\","
                                    "\"CurrentVersion\":\"2.0.0\""
                                  "}";

    awsRegion.pAwsRegion = "cn-north-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    deleteSignalingChannelRequestInfo.channelArn.pChannelArn = "arn:aws-cn:kinesisvideo:cn-north-1:123456789012:channel/test-channel/1234567890123";
    deleteSignalingChannelRequestInfo.channelArn.channelArnLength = strlen( deleteSignalingChannelRequestInfo.channelArn.pChannelArn );
    deleteSignalingChannelRequestInfo.pVersion = "2.0.0";
    deleteSignalingChannelRequestInfo.versionLength = strlen( deleteSignalingChannelRequestInfo.pVersion );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDeleteSignalingChannelRequest( &( awsRegion ),
                                                               &( deleteSignalingChannelRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING( pExpectedUrl,
                              requestBuffer.pUrl );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING( pExpectedBody,
                              requestBuffer.pBody );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Delete Signaling Channel Request functionality.
 */
void test_signaling_ConstructDeleteSignalingChannelRequest_SmallLengthRegion( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    DeleteSignalingChannelRequestInfo_t deleteSignalingChannelRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 500 ];
    SignalingResult_t result;
    const char * pExpectedUrl = "https://kinesisvideo.ca.amazonaws.com/deleteSignalingChannel";
    const char * pExpectedBody = "{"
                                    "\"ChannelARN\":\"arn:aws:kinesisvideo:ca:123456789012:channel/test-channel/1234567890123\","
                                    "\"CurrentVersion\":\"2.0.0\""
                                  "}";

    awsRegion.pAwsRegion = "ca";            /* The Region Length is < 3 */
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    deleteSignalingChannelRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:ca:123456789012:channel/test-channel/1234567890123";
    deleteSignalingChannelRequestInfo.channelArn.channelArnLength = strlen( deleteSignalingChannelRequestInfo.channelArn.pChannelArn );
    deleteSignalingChannelRequestInfo.pVersion = "2.0.0";
    deleteSignalingChannelRequestInfo.versionLength = strlen( deleteSignalingChannelRequestInfo.pVersion );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDeleteSignalingChannelRequest( &( awsRegion ),
                                                               &( deleteSignalingChannelRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING( pExpectedUrl,
                              requestBuffer.pUrl );
    TEST_ASSERT_EQUAL( strlen( pExpectedBody ),
                       requestBuffer.bodyLength );
    TEST_ASSERT_EQUAL_STRING( pExpectedBody,
                              requestBuffer.pBody );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Delete Signaling Channel Request functionality.
 */
void test_signaling_ConstructDeleteSignalingChannelRequest_URL_OutofMemory( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    DeleteSignalingChannelRequestInfo_t deleteSignalingChannelRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 20 ];                   /* The url buffer is small */
    char bodyBuffer[ 500 ];
    SignalingResult_t result;

    awsRegion.pAwsRegion = "cn-north-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    deleteSignalingChannelRequestInfo.channelArn.pChannelArn = "arn:aws-cn:kinesisvideo:cn-north-1:123456789012:channel/test-channel/1234567890123";
    deleteSignalingChannelRequestInfo.channelArn.channelArnLength = strlen( deleteSignalingChannelRequestInfo.channelArn.pChannelArn );
    deleteSignalingChannelRequestInfo.pVersion = "2.0.0";
    deleteSignalingChannelRequestInfo.versionLength = strlen( deleteSignalingChannelRequestInfo.pVersion );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDeleteSignalingChannelRequest( &( awsRegion ),
                                                               &( deleteSignalingChannelRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Delete Signaling Channel Request functionality.
 */
void test_signaling_ConstructDeleteSignalingChannelRequest_Body_OutofMemory( void )
{
    SignalingAwsRegion_t awsRegion = { 0 };
    DeleteSignalingChannelRequestInfo_t deleteSignalingChannelRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 200 ];
    char bodyBuffer[ 50 ];              /* The body buffer is small */
    SignalingResult_t result;

    awsRegion.pAwsRegion = "cn-north-1";
    awsRegion.awsRegionLength = strlen( awsRegion.pAwsRegion );

    deleteSignalingChannelRequestInfo.channelArn.pChannelArn = "arn:aws-cn:kinesisvideo:cn-north-1:123456789012:channel/test-channel/1234567890123";
    deleteSignalingChannelRequestInfo.channelArn.channelArnLength = strlen( deleteSignalingChannelRequestInfo.channelArn.pChannelArn );
    deleteSignalingChannelRequestInfo.pVersion = "2.0.0";
    deleteSignalingChannelRequestInfo.versionLength = strlen( deleteSignalingChannelRequestInfo.pVersion );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = &( bodyBuffer[ 0 ] );
    requestBuffer.bodyLength = sizeof( bodyBuffer );

    result = Signaling_ConstructDeleteSignalingChannelRequest( &( awsRegion ),
                                                               &( deleteSignalingChannelRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Connect Web-Sockets Endpoint Request fail functionality for Bad Parameters.
 */
void test_signaling_ConstructConnectWssEndpointRequest_BadParams( void )
{
    SignalingChannelEndpoint_t wssEndpoint = { 0 };
    ConnectWssEndpointRequestInfo_t connectWssEndpointRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    SignalingResult_t result;

    result = Signaling_ConstructConnectWssEndpointRequest( NULL,
                                                           &( connectWssEndpointRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    wssEndpoint.pEndpoint = NULL;
    result = Signaling_ConstructConnectWssEndpointRequest( &( wssEndpoint ),
                                                           &( connectWssEndpointRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    wssEndpoint.pEndpoint = "wss://example.com";
    wssEndpoint.endpointLength = strlen( wssEndpoint.pEndpoint );

    result = Signaling_ConstructConnectWssEndpointRequest( &( wssEndpoint ),
                                                           &( connectWssEndpointRequestInfo ), NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */



    result = Signaling_ConstructConnectWssEndpointRequest( &( wssEndpoint ),
                                                           NULL, &( requestBuffer ) );
    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    requestBuffer.pUrl = NULL;
    result = Signaling_ConstructConnectWssEndpointRequest( &( wssEndpoint ),
                                                           &( connectWssEndpointRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    requestBuffer.pUrl = "https://kinesisvideo.cn-east-1.amazonaws.com.cn/describeSignalingChannel";
    requestBuffer.urlLength = strlen( requestBuffer.pUrl );
    connectWssEndpointRequestInfo.channelArn.pChannelArn = NULL;

    result = Signaling_ConstructConnectWssEndpointRequest( &( wssEndpoint ),
                                                           &( connectWssEndpointRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    connectWssEndpointRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-east-1:123456789012:channel/test-channel/1234567890123";
    connectWssEndpointRequestInfo.channelArn.channelArnLength = strlen( connectWssEndpointRequestInfo.channelArn.pChannelArn );
    connectWssEndpointRequestInfo.role = SIGNALING_ROLE_NONE;

    result = Signaling_ConstructConnectWssEndpointRequest( &( wssEndpoint ),
                                                           &( connectWssEndpointRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    connectWssEndpointRequestInfo.role = SIGNALING_ROLE_VIEWER;
    connectWssEndpointRequestInfo.pClientId = NULL;

    result = Signaling_ConstructConnectWssEndpointRequest( &( wssEndpoint ),
                                                           &( connectWssEndpointRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Connect Web-Sockets Endpoint Request fail functionality for Bad Parameters.
 */
void test_signaling_ConstructConnectWssEndpointRequest_Master( void )
{
    SignalingChannelEndpoint_t wssEndpoint = { 0 };
    ConnectWssEndpointRequestInfo_t connectWssEndpointRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 300 ];
    SignalingResult_t result;
    const char * pExpectedUrl = "wss://example.com?X-Amz-ChannelARN=arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123";

    wssEndpoint.pEndpoint = "wss://example.com";
    wssEndpoint.endpointLength = strlen( wssEndpoint.pEndpoint );

    connectWssEndpointRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123";
    connectWssEndpointRequestInfo.channelArn.channelArnLength = strlen( connectWssEndpointRequestInfo.channelArn.pChannelArn );
    connectWssEndpointRequestInfo.role = SIGNALING_ROLE_MASTER;
    connectWssEndpointRequestInfo.pClientId = NULL;
    connectWssEndpointRequestInfo.clientIdLength = 0;

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = NULL;
    requestBuffer.bodyLength = 0;

    result = Signaling_ConstructConnectWssEndpointRequest( &( wssEndpoint ),
                                                           &( connectWssEndpointRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_TRUE( strstr( requestBuffer.pUrl, "X-Amz-ClientId" ) == NULL );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING( pExpectedUrl,
                              requestBuffer.pUrl );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Connect Web-Sockets Endpoint Request fail functionality for Bad Parameters.
 */
void test_signaling_ConstructConnectWssEndpointRequest_Viewer( void )
{
    SignalingChannelEndpoint_t wssEndpoint = { 0 };
    ConnectWssEndpointRequestInfo_t connectWssEndpointRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 300 ];
    SignalingResult_t result;
    const char * pExpectedUrl = "wss://example.com?X-Amz-ChannelARN=arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123&X-Amz-ClientId=TestClient";

    wssEndpoint.pEndpoint = "wss://example.com";
    wssEndpoint.endpointLength = strlen( wssEndpoint.pEndpoint );

    connectWssEndpointRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123";
    connectWssEndpointRequestInfo.channelArn.channelArnLength = strlen( connectWssEndpointRequestInfo.channelArn.pChannelArn );
    connectWssEndpointRequestInfo.role = SIGNALING_ROLE_VIEWER;
    connectWssEndpointRequestInfo.pClientId = "TestClient";
    connectWssEndpointRequestInfo.clientIdLength = strlen( connectWssEndpointRequestInfo.pClientId );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = NULL;
    requestBuffer.bodyLength = 0;

    result = Signaling_ConstructConnectWssEndpointRequest( &( wssEndpoint ),
                                                           &( connectWssEndpointRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_TRUE( strstr( requestBuffer.pUrl, "X-Amz-ClientId=TestClient" ) != NULL );
    TEST_ASSERT_EQUAL( strlen( pExpectedUrl ),
                       requestBuffer.urlLength );
    TEST_ASSERT_EQUAL_STRING( pExpectedUrl,
                              requestBuffer.pUrl );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Connect Web-Sockets Endpoint Request fail functionality for Bad Parameters.
 */
void test_signaling_ConstructConnectWssEndpointRequest_Url_OutofMemory( void )
{
    SignalingChannelEndpoint_t wssEndpoint = { 0 };
    ConnectWssEndpointRequestInfo_t connectWssEndpointRequestInfo = { 0 };
    SignalingRequest_t requestBuffer = { 0 };
    char urlBuffer[ 30 ];                     /* The url buffer is small */
    SignalingResult_t result;

    wssEndpoint.pEndpoint = "wss://example.com";
    wssEndpoint.endpointLength = strlen( wssEndpoint.pEndpoint );

    connectWssEndpointRequestInfo.channelArn.pChannelArn = "arn:aws:kinesisvideo:us-west-2:123456789012:channel/test-channel/1234567890123";
    connectWssEndpointRequestInfo.channelArn.channelArnLength = strlen( connectWssEndpointRequestInfo.channelArn.pChannelArn );
    connectWssEndpointRequestInfo.role = SIGNALING_ROLE_VIEWER;
    connectWssEndpointRequestInfo.pClientId = "TestClient";
    connectWssEndpointRequestInfo.clientIdLength = strlen( connectWssEndpointRequestInfo.pClientId );

    requestBuffer.pUrl = &( urlBuffer[ 0 ] );
    requestBuffer.urlLength = sizeof( urlBuffer );
    requestBuffer.pBody = NULL;
    requestBuffer.bodyLength = 0;

    result = Signaling_ConstructConnectWssEndpointRequest( &( wssEndpoint ),
                                                           &( connectWssEndpointRequestInfo ), &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Web-Socket Message fail functionality for Bad Parameters.
 */
void test_signaling_ConstructWssMessage_BadParams( void )
{
    WssSendMessage_t wssSendMessage = { 0 };
    char messageBuffer[ 300 ];
    size_t messageBufferLength = sizeof( messageBuffer );
    SignalingResult_t result;

    result = Signaling_ConstructWssMessage( NULL,
                                            &( messageBuffer[ 0 ] ), &( messageBufferLength ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    result = Signaling_ConstructWssMessage( &( wssSendMessage ),
                                            NULL, &( messageBufferLength ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    wssSendMessage.pBase64EncodedMessage = NULL;

    result = Signaling_ConstructWssMessage( &( wssSendMessage ),
                                            &( messageBuffer[ 0 ] ), &( messageBufferLength ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    wssSendMessage.pBase64EncodedMessage = "TestMessage";
    wssSendMessage.base64EncodedMessageLength = strlen( wssSendMessage.pBase64EncodedMessage );
    wssSendMessage.pRecipientClientId = NULL;

    result = Signaling_ConstructWssMessage( &( wssSendMessage ),
                                            &( messageBuffer[ 0 ] ), &( messageBufferLength ) );
    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Web-Socket Message functionality.
 */
void test_signaling_ConstructWssMessage_SdpOffer( void )
{
    WssSendMessage_t wssSendMessage = { 0 };
    char messageBuffer[ 300 ];
    size_t messageBufferLength = sizeof( messageBuffer );
    SignalingResult_t result;
    const char * pExpectedMessage = "{"
                                        "\"action\":\"SDP_OFFER\","
                                        "\"RecipientClientId\":\"TestClientId\","
                                        "\"MessagePayload\":\"base64encodedmessage\","
                                        "\"CorrelationId\":\"TestCorrelationId\""
                                    "}";

    wssSendMessage.messageType = SIGNALING_TYPE_MESSAGE_SDP_OFFER;
    wssSendMessage.pBase64EncodedMessage = "base64encodedmessage";
    wssSendMessage.base64EncodedMessageLength = strlen( wssSendMessage.pBase64EncodedMessage );
    wssSendMessage.pRecipientClientId = "TestClientId";
    wssSendMessage.recipientClientIdLength = strlen( wssSendMessage.pRecipientClientId );
    wssSendMessage.pCorrelationId = "TestCorrelationId";
    wssSendMessage.correlationIdLength = strlen( wssSendMessage.pCorrelationId );

    result = Signaling_ConstructWssMessage( &( wssSendMessage ),
                                            messageBuffer, &( messageBufferLength ) );
    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedMessage ),
                       strlen( messageBuffer ) );
    TEST_ASSERT_EQUAL_STRING( pExpectedMessage,
                              messageBuffer );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Web-Socket Message functionality.
 */
void test_signaling_ConstructWssMessage_SdpAnswer( void )
{
    WssSendMessage_t wssSendMessage = { 0 };
    char messageBuffer[ 300 ];
    size_t messageBufferLength = sizeof( messageBuffer );
    SignalingResult_t result;
    const char * pExpectedMessage = "{"
                                        "\"action\":\"SDP_ANSWER\","
                                        "\"RecipientClientId\":\"TestClientId\","
                                        "\"MessagePayload\":\"base64encodedmessage\","
                                        "\"CorrelationId\":\"TestCorrelationId\""
                                    "}";

    wssSendMessage.messageType = SIGNALING_TYPE_MESSAGE_SDP_ANSWER;
    wssSendMessage.pBase64EncodedMessage = "base64encodedmessage";
    wssSendMessage.base64EncodedMessageLength = strlen( wssSendMessage.pBase64EncodedMessage );
    wssSendMessage.pRecipientClientId = "TestClientId";
    wssSendMessage.recipientClientIdLength = strlen( wssSendMessage.pRecipientClientId );
    wssSendMessage.pCorrelationId = "TestCorrelationId";
    wssSendMessage.correlationIdLength = strlen( wssSendMessage.pCorrelationId );

    result = Signaling_ConstructWssMessage( &( wssSendMessage ),
                                            messageBuffer, &( messageBufferLength ) );
    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedMessage ),
                       strlen( messageBuffer ) );
    TEST_ASSERT_EQUAL_STRING( pExpectedMessage,
                              messageBuffer );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Web-Socket Message functionality.
 */
void test_signaling_ConstructWssMessage_IceCandidate( void )
{
    WssSendMessage_t wssSendMessage = { 0 };
    char messageBuffer[ 300 ];
    size_t messageBufferLength = sizeof( messageBuffer );
    SignalingResult_t result;
    const char * pExpectedMessage = "{"
                                        "\"action\":\"ICE_CANDIDATE\","
                                        "\"RecipientClientId\":\"TestClientId\","
                                        "\"MessagePayload\":\"base64encodedmessage\","
                                        "\"CorrelationId\":\"TestCorrelationId\""
                                    "}";

    wssSendMessage.messageType = SIGNALING_TYPE_MESSAGE_ICE_CANDIDATE;
    wssSendMessage.pBase64EncodedMessage = "base64encodedmessage";
    wssSendMessage.base64EncodedMessageLength = strlen( wssSendMessage.pBase64EncodedMessage );
    wssSendMessage.pRecipientClientId = "TestClientId";
    wssSendMessage.recipientClientIdLength = strlen( wssSendMessage.pRecipientClientId );
    wssSendMessage.pCorrelationId = "TestCorrelationId";
    wssSendMessage.correlationIdLength = strlen( wssSendMessage.pCorrelationId );

    result = Signaling_ConstructWssMessage( &( wssSendMessage ),
                                            messageBuffer, &( messageBufferLength ) );
    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedMessage ),
                       strlen( messageBuffer ) );
    TEST_ASSERT_EQUAL_STRING( pExpectedMessage,
                              messageBuffer );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Web-Socket Message functionality.
 */
void test_signaling_ConstructWssMessage_Unkown( void )
{
    WssSendMessage_t wssSendMessage = { 0 };
    char messageBuffer[ 300 ];
    size_t messageBufferLength = sizeof( messageBuffer );
    SignalingResult_t result;
    const char * pExpectedMessage = "{"
                                        "\"action\":\"UNKNOWN\","
                                        "\"RecipientClientId\":\"TestClientId\","
                                        "\"MessagePayload\":\"base64encodedmessage\","
                                        "\"CorrelationId\":\"TestCorrelationId\""
                                    "}";

    wssSendMessage.messageType = SIGNALING_TYPE_MESSAGE_UNKNOWN;
    wssSendMessage.pBase64EncodedMessage = "base64encodedmessage";
    wssSendMessage.base64EncodedMessageLength = strlen( wssSendMessage.pBase64EncodedMessage );
    wssSendMessage.pRecipientClientId = "TestClientId";
    wssSendMessage.recipientClientIdLength = strlen( wssSendMessage.pRecipientClientId );
    wssSendMessage.pCorrelationId = "TestCorrelationId";
    wssSendMessage.correlationIdLength = strlen( wssSendMessage.pCorrelationId );

    result = Signaling_ConstructWssMessage( &( wssSendMessage ),
                                            messageBuffer, &( messageBufferLength ) );
    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedMessage ),
                       strlen( messageBuffer ) );
    TEST_ASSERT_EQUAL_STRING( pExpectedMessage,
                              messageBuffer );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Web-Socket Message functionality.
 */
void test_signaling_ConstructWssMessage_OutofMemory( void )
{
    WssSendMessage_t wssSendMessage = { 0 };
    char messageBuffer[ 100 ];                  /* Correlation ID is not added in the buffer properly */
    size_t messageBufferLength = sizeof( messageBuffer );
    SignalingResult_t result;

    wssSendMessage.messageType = SIGNALING_TYPE_MESSAGE_SDP_OFFER;
    wssSendMessage.pBase64EncodedMessage = "base64encodedmessage";
    wssSendMessage.base64EncodedMessageLength = strlen( wssSendMessage.pBase64EncodedMessage );
    wssSendMessage.pRecipientClientId = "TestClientId";
    wssSendMessage.recipientClientIdLength = strlen( wssSendMessage.pRecipientClientId );
    wssSendMessage.pCorrelationId = "TestCorrelationId";
    wssSendMessage.correlationIdLength = strlen( wssSendMessage.pCorrelationId );

    result = Signaling_ConstructWssMessage( &( wssSendMessage ),
                                            messageBuffer, &( messageBufferLength ) );
    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Web-Socket Message functionality.
 */
void test_signaling_ConstructWssMessage_OutofMemory_ClosingBracket( void )
{
    WssSendMessage_t wssSendMessage = { 0 };
    char messageBuffer[ 133 ];                  /* Closing is not added in the buffer properly */
    size_t messageBufferLength = sizeof( messageBuffer );
    SignalingResult_t result;

    wssSendMessage.messageType = SIGNALING_TYPE_MESSAGE_SDP_OFFER;
    wssSendMessage.pBase64EncodedMessage = "base64encodedmessage";
    wssSendMessage.base64EncodedMessageLength = strlen( wssSendMessage.pBase64EncodedMessage );
    wssSendMessage.pRecipientClientId = "TestClientId";
    wssSendMessage.recipientClientIdLength = strlen( wssSendMessage.pRecipientClientId );
    wssSendMessage.pCorrelationId = "TestCorrelationId";
    wssSendMessage.correlationIdLength = strlen( wssSendMessage.pCorrelationId );

    result = Signaling_ConstructWssMessage( &( wssSendMessage ),
                                            messageBuffer, &( messageBufferLength ) );
    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Web-Socket Message functionality.
 */
void test_signaling_ConstructWssMessage_NoCorrelationId( void )
{
    WssSendMessage_t wssSendMessage = { 0 };
    char messageBuffer[ 300 ];
    size_t messageBufferLength = sizeof( messageBuffer );
    SignalingResult_t result;
    const char * pExpectedMessage = "{"
                                        "\"action\":\"SDP_OFFER\","
                                        "\"RecipientClientId\":\"TestClientId\","
                                        "\"MessagePayload\":\"base64encodedmessage\""
                                    "}";

    wssSendMessage.messageType = SIGNALING_TYPE_MESSAGE_SDP_OFFER;
    wssSendMessage.pBase64EncodedMessage = "base64encodedmessage";
    wssSendMessage.base64EncodedMessageLength = strlen( wssSendMessage.pBase64EncodedMessage );
    wssSendMessage.pRecipientClientId = "TestClientId";
    wssSendMessage.recipientClientIdLength = strlen( wssSendMessage.pRecipientClientId );
    wssSendMessage.pCorrelationId = NULL;
    wssSendMessage.correlationIdLength = 0;

    result = Signaling_ConstructWssMessage( &( wssSendMessage ),
                                            messageBuffer, &( messageBufferLength ) );
    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( strlen( pExpectedMessage ),
                       strlen( messageBuffer ) );
    TEST_ASSERT_EQUAL_STRING( pExpectedMessage,
                              messageBuffer );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Construct Web-Socket Message functionality.
 */
void test_signaling_ConstructWssMessage_SmallBuffer( void )
{
    WssSendMessage_t wssSendMessage = { 0 };
    char messageBuffer[ 10 ];                           /* A small Message Buffer */
    size_t messageBufferLength = sizeof( messageBuffer );
    SignalingResult_t result;

    wssSendMessage.messageType = SIGNALING_TYPE_MESSAGE_SDP_OFFER;
    wssSendMessage.pBase64EncodedMessage = "base64encodedmessage";
    wssSendMessage.base64EncodedMessageLength = strlen( wssSendMessage.pBase64EncodedMessage );
    wssSendMessage.pRecipientClientId = "TestClientId";
    wssSendMessage.recipientClientIdLength = strlen( wssSendMessage.pRecipientClientId );
    wssSendMessage.pCorrelationId = "correlation123";
    wssSendMessage.correlationIdLength = strlen( wssSendMessage.pCorrelationId );

    result = Signaling_ConstructWssMessage( &( wssSendMessage ),
                                            messageBuffer, &( messageBufferLength ) );
    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OUT_OF_MEMORY,
                       result );
}
/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Web-Socket Receive Message fail functionality for Bad Parameters.
 */
void test_signaling_ParseWssRecvMessage_BadParams( void )
{
    WssRecvMessage_t wssRecvMessage = { 0 };
    const char message[ 300 ] = "XXXXXXXXXXX";
    size_t messageLength = strlen( message );
    SignalingResult_t result;

    result = Signaling_ParseWssRecvMessage( NULL,
                                            messageLength, &( wssRecvMessage ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );

    /*      <------------------------------------------------------------------------------------------>      */

    result = Signaling_ParseWssRecvMessage( message,
                                            messageLength, NULL );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Web-Socket Receive Message functionality.
 */
void test_signaling_ParseWssRecvMessage_Sdp_Offer( void )
{
    SignalingResult_t result;
    WssRecvMessage_t wssRecvMessage = { 0 };
    const char * message = "{"
        "\"senderClientId\":\"sender123\","
        "\"messageType\":\"SDP_OFFER\","
        "\"messagePayload\":\"base64encodedpayload\""
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseWssRecvMessage( message,
                                            messageLength, &( wssRecvMessage ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING_LEN( "sender123", wssRecvMessage.pSenderClientId, wssRecvMessage.senderClientIdLength );
    TEST_ASSERT_EQUAL( SIGNALING_TYPE_MESSAGE_SDP_OFFER, wssRecvMessage.messageType );
    TEST_ASSERT_EQUAL_STRING_LEN( "base64encodedpayload", wssRecvMessage.pBase64EncodedPayload, wssRecvMessage.base64EncodedPayloadLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Web-Socket Receive Message functionality.
 */
void test_signaling_ParseWssRecvMessage_Sdp_Answer( void )
{
    SignalingResult_t result;
    WssRecvMessage_t wssRecvMessage = { 0 };
    const char *message = "{"
        "\"senderClientId\":\"sender123\","
        "\"messageType\":\"SDP_ANSWER\","
        "\"messagePayload\":\"base64encodedpayload\""
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseWssRecvMessage( message,
                                            messageLength, &( wssRecvMessage ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING_LEN( "sender123", wssRecvMessage.pSenderClientId, wssRecvMessage.senderClientIdLength );
    TEST_ASSERT_EQUAL( SIGNALING_TYPE_MESSAGE_SDP_ANSWER, wssRecvMessage.messageType );
    TEST_ASSERT_EQUAL_STRING_LEN( "base64encodedpayload", wssRecvMessage.pBase64EncodedPayload, wssRecvMessage.base64EncodedPayloadLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Web-Socket Receive Message functionality.
 */
void test_signaling_ParseWssRecvMessage_IceCandidate( void )
{
    SignalingResult_t result;
    WssRecvMessage_t wssRecvMessage = { 0 };
    const char *message = "{"
        "\"senderClientId\":\"sender123\","
        "\"messageType\":\"ICE_CANDIDATE\","
        "\"messagePayload\":\"base64encodedpayload\""
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseWssRecvMessage( message,
                                            messageLength, &( wssRecvMessage ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING_LEN( "sender123", wssRecvMessage.pSenderClientId, wssRecvMessage.senderClientIdLength );
    TEST_ASSERT_EQUAL( SIGNALING_TYPE_MESSAGE_ICE_CANDIDATE, wssRecvMessage.messageType );
    TEST_ASSERT_EQUAL_STRING_LEN( "base64encodedpayload", wssRecvMessage.pBase64EncodedPayload, wssRecvMessage.base64EncodedPayloadLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Web-Socket Receive Message functionality.
 */
void test_signaling_ParseWssRecvMessage_GoAway( void )
{
    SignalingResult_t result;
    WssRecvMessage_t wssRecvMessage = { 0 };
    const char *message = "{"
        "\"senderClientId\":\"sender123\","
        "\"messageType\":\"GO_AWAY\","
        "\"messagePayload\":\"base64encodedpayload\""
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseWssRecvMessage( message,
                                            messageLength, &( wssRecvMessage ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING_LEN( "sender123", wssRecvMessage.pSenderClientId, wssRecvMessage.senderClientIdLength );
    TEST_ASSERT_EQUAL( SIGNALING_TYPE_MESSAGE_GO_AWAY, wssRecvMessage.messageType );
    TEST_ASSERT_EQUAL_STRING_LEN( "base64encodedpayload", wssRecvMessage.pBase64EncodedPayload, wssRecvMessage.base64EncodedPayloadLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Web-Socket Receive Message functionality.
 */
void test_signaling_ParseWssRecvMessage_ExcludeNullTerminator( void )
{
    SignalingResult_t result;
    WssRecvMessage_t wssRecvMessage = { 0 };
    const char *message = "{"
        "\"senderClientId\":\"sender123\","
        "\"messageType\":\"RECONNECT_ICE_SERVER\","
        "\"messagePayload\":\"base64encodedpayload\""
    "}\0";          // Explicitly include null terminator
    size_t messageLength = strlen(message) + 1 ;                 // Length including null terminator

    result = Signaling_ParseWssRecvMessage( message,
                                            messageLength, &( wssRecvMessage ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING_LEN( "sender123", wssRecvMessage.pSenderClientId, wssRecvMessage.senderClientIdLength );
    TEST_ASSERT_EQUAL( SIGNALING_TYPE_MESSAGE_RECONNECT_ICE_SERVER, wssRecvMessage.messageType );
    TEST_ASSERT_EQUAL_STRING_LEN( "base64encodedpayload", wssRecvMessage.pBase64EncodedPayload, wssRecvMessage.base64EncodedPayloadLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Web-Socket Receive Message functionality.
 */
void test_signaling_ParseWssRecvMessage_ReconnectIceServer( void )
{
    SignalingResult_t result;
    WssRecvMessage_t wssRecvMessage = { 0 };
    const char *message = "{"
        "\"senderClientId\":\"sender123\","
        "\"messageType\":\"RECONNECT_ICE_SERVER\","
        "\"messagePayload\":\"base64encodedpayload\""
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseWssRecvMessage( message,
                                            messageLength, &( wssRecvMessage ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL_STRING_LEN( "sender123", wssRecvMessage.pSenderClientId, wssRecvMessage.senderClientIdLength );
    TEST_ASSERT_EQUAL( SIGNALING_TYPE_MESSAGE_RECONNECT_ICE_SERVER, wssRecvMessage.messageType );
    TEST_ASSERT_EQUAL_STRING_LEN( "base64encodedpayload", wssRecvMessage.pBase64EncodedPayload, wssRecvMessage.base64EncodedPayloadLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Web-Socket Receive Message functionality.
 */
void test_signaling_ParseWssRecvMessage_StatusResponse( void )
{
    SignalingResult_t result;
    WssRecvMessage_t wssRecvMessage = { 0 };
    const char *message = "{"
        "\"messageType\":\"STATUS_RESPONSE\","
        "\"statusResponse\":{"
            "\"correlationId\":\"corr123\","
            "\"errorType\":\"None\","
            "\"statusCode\":\"200\","
            "\"description\":\"OK\","
            "\"Unkown\":\"value\""                   /* Unkown Tags are ignored. */
        "}"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseWssRecvMessage( message,
                                            messageLength, &( wssRecvMessage ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( SIGNALING_TYPE_MESSAGE_STATUS_RESPONSE, wssRecvMessage.messageType );
    TEST_ASSERT_EQUAL_STRING_LEN( "corr123", wssRecvMessage.statusResponse.pCorrelationId, wssRecvMessage.statusResponse.correlationIdLength );
    TEST_ASSERT_EQUAL_STRING_LEN( "None", wssRecvMessage.statusResponse.pErrorType, wssRecvMessage.statusResponse.errorTypeLength );
    TEST_ASSERT_EQUAL_STRING_LEN( "200", wssRecvMessage.statusResponse.pStatusCode, wssRecvMessage.statusResponse.statusCodeLength );
    TEST_ASSERT_EQUAL_STRING_LEN( "OK", wssRecvMessage.statusResponse.pDescription, wssRecvMessage.statusResponse.descriptionLength );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Web-Socket Receive Message functionality.
 */
void test_signaling_ParseWssRecvMessage_InvalidJson( void )
{
    SignalingResult_t result;
    WssRecvMessage_t wssRecvMessage = { 0 };
    const char * message = "{\"senderClientId\":\"sender123\",";  /* Missing closing brace */
    size_t messageLength = strlen( message );

    result = Signaling_ParseWssRecvMessage( message,
                                            messageLength, &( wssRecvMessage ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Web-Socket Receive Message functionality.
 */
void test_signaling_ParseWssRecvMessage_UnkownMessageType( void )
{
    SignalingResult_t result;
    WssRecvMessage_t wssRecvMessage = { 0 };
    const char *message  = "{"
        "\"senderClientId\":\"sender123\","
        "\"messageType\":\"UNKNOWN_TYPE\","                 /* Unkown Message Type */
        "\"messagePayload\":\"base64encodedpayload\","
        "\"Unkown\":\"unkown-value\""                       /* This Unkown Tag is ignored */
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseWssRecvMessage( message,
                                            messageLength, &( wssRecvMessage ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_OK,
                       result );
    TEST_ASSERT_EQUAL( SIGNALING_TYPE_MESSAGE_UNKNOWN, wssRecvMessage.messageType );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Web-Socket Receive Message functionality.
 */
void test_signaling_ParseWssRecvMessage_UnexpectedStatusResponse( void )
{
    SignalingResult_t result;
    WssRecvMessage_t wssRecvMessage = { 0 };
    const char *message  = "{"
        "\"messageType\":\"STATUS_RESPONSE\","
        "\"statusResponse\":\"invalid\""            /* Invalid Status Response */
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseWssRecvMessage( message,
                                            messageLength, &( wssRecvMessage ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_UNEXPECTED_RESPONSE,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Web-Socket Receive Message functionality.
 */
void test_signaling_ParseWssRecvMessage_InvalidStatusResponse( void )
{
    SignalingResult_t result;
    WssRecvMessage_t wssRecvMessage = { 0 };
    const char *message  = "{"
        "\"messageType\":\"STATUS_RESPONSE\","
        "\"statusResponse\":{"                                      /* Empty Status Response */
        "}"
    "}";
    size_t messageLength = strlen( message );

    result = Signaling_ParseWssRecvMessage( message,
                                            messageLength, &( wssRecvMessage ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_STATUS_RESPONSE,
                       result );
}

/*-----------------------------------------------------------*/

/**
 * @brief Validate Signaling Parse Web-Socket Receive Message functionality.
 */
void test_signaling_ParseWssRecvMessage_Empty( void )
{
    SignalingResult_t result;
    WssRecvMessage_t wssRecvMessage = { 0 };
    const char *message  = "";
    size_t messageLength = 0;

    result = Signaling_ParseWssRecvMessage( message,
                                            messageLength, &( wssRecvMessage ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_INVALID_JSON,
                       result );
}

/*-----------------------------------------------------------*/