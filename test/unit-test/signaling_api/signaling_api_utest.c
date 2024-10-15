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
    awsRegion.awsRegionLength = sizeof( awsRegion.pAwsRegion );

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

    requestBuffer.pUrl = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
    requestBuffer.urlLength = sizeof( requestBuffer.pUrl );
    requestBuffer.pBody = NULL;

    result = Signaling_ConstructDescribeSignalingChannelRequest( &( awsRegion ),
                                                                 &( channelName ),
                                                                 &( requestBuffer ) );

    TEST_ASSERT_EQUAL( SIGNALING_RESULT_BAD_PARAM,
                       result );
}

/*-----------------------------------------------------------*/
