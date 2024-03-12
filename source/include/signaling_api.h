/**
 * @file signaling_api.h
 * @brief API list for Signaling component.
 */
#ifndef SIGNALING_API_H
#define SIGNALING_API_H

/* *INDENT-OFF* */
#ifdef __cplusplus
    extern "C" {
#endif
/* *INDENT-ON* */

#include "signaling_data_types.h"

/*-----------------------------------------------------------*/

/**
 * @brief A initialization function that creates Signaling instance with AWS basic information.
 *
 * @param[out] pCtx The context of Signaling instance.
 * @param[in] pAwsControlPlaneInfo AWS control plane information.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if memory space is not enough to store control plane URL.
 */
SignalingResult_t Signaling_Init( SignalingContext_t *pCtx, SignalingAwsControlPlaneInfo_t *pAwsControlPlaneInfo );

/**
 * @brief This function is used to construct request to query signaling channel information.
 *
 * @param[in] pCtx The pointer of signaling context.
 * @param[in] pDescribeSignalingChannelRequest The parameters that needed to construct request to query signaling channel information.
 * @param[out] pRequestBuffer The output structure includes URI, body buffers, and their sizes.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if buffer is not enough to store constructed message.
 * 
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DescribeSignalingChannel.html for details.
 */
SignalingResult_t Signaling_constructDescribeSignalingChannelRequest( SignalingContext_t *pCtx, SignalingDescribeSignalingChannelRequest_t * pDescribeSignalingChannelRequest, SignalingRequest_t *pRequestBuffer );

/**
 * @brief This function is used to parse response of describe signaling channel.
 *
 * @param[in] pCtx The pointer of signaling context.
 * @param[in] pMessage Raw response from the URL of getting signaling channel endpoints.
 * @param[in] messageLength Length of raw message.
 * @param[out] pDescribeSignalingChannelResponse The output structure includes the signaling channel information.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_INVALID_JSON, if raw message is not a valid JSON message.
 * - #SIGNALING_RESULT_NOT_EXPECT_RESPONSE, if the message isn't the expected one.
 * - #SIGNALING_RESULT_INVALID_CHANNEL_NAME, if the channel name is longer than array size.
 * - #SIGNALING_RESULT_INVALID_CHANNEL_TYPE, if the channel type is longer than array size.
 * - #SIGNALING_RESULT_INVALID_TTL, if the TTL is longer than array size.
 * 
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DescribeSignalingChannel.html for details.
 */
SignalingResult_t Signaling_parseDescribeSignalingChannelResponse( SignalingContext_t *pCtx, char * pMessage, size_t messageLength, SignalingDescribeSignalingChannelResponse_t *pDescribeSignalingChannelResponse );

/**
 * @brief This function is used to construct request to query media storage configuration.
 *
 * @param[in] pCtx The pointer of signaling context.
 * @param[in] pDescribeMediaStorageConfigRequest The parameters that needed to construct request to query media storage configuration.
 * @param[out] pRequestBuffer The output structure includes URI, body buffers, and their sizes.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if buffer is not enough to store constructed message.
 * 
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DescribeMediaStorageConfiguration.html for details.
 */
SignalingResult_t Signaling_constructDescribeMediaStorageConfigRequest( SignalingContext_t *pCtx, SignalingDescribeMediaStorageConfigRequest_t * pDescribeMediaStorageConfigRequest, SignalingRequest_t *pRequestBuffer );

/**
 * @brief This function is used to parse response of describe media storage configurations.
 *
 * @param[in] pCtx The pointer of signaling context.
 * @param[in] pMessage Raw response from the URL of getting signaling channel endpoints.
 * @param[in] messageLength Length of raw message.
 * @param[out] pDescribeMediaStorageConfigResponse The output structure includes the media storage configuration properties.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_INVALID_JSON, if raw message is not a valid JSON message.
 * - #SIGNALING_RESULT_NOT_EXPECT_RESPONSE, if the message isn't the expected one.
 * 
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DescribeMediaStorageConfiguration.html for details.
 */
SignalingResult_t Signaling_parseDescribeMediaStorageConfigResponse( SignalingContext_t *pCtx, char * pMessage, size_t messageLength, SignalingDescribeMediaStorageConfigResponse_t *pDescribeMediaStorageConfigResponse );

/**
 * @brief This function is used to construct request to create signaling channel.
 *
 * @param[in] pCtx The pointer of signaling context.
 * @param[in] pCreateSignalingChannelRequest The parameters that needed to construct request to create signaling channel.
 * @param[out] pRequestBuffer The output structure includes URI, body buffers, and their sizes.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if buffer is not enough to store constructed message.
 * 
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_CreateSignalingChannel.html for details.
 */
SignalingResult_t Signaling_constructCreateSignalingChannelRequest( SignalingContext_t *pCtx, SignalingCreateSignalingChannelRequest_t * pCreateSignalingChannelRequest, SignalingRequest_t *pRequestBuffer );

/**
 * @brief This function is used to parse response of creating signaling channel.
 *
 * @param[in] pCtx The pointer of signaling context.
 * @param[in] pMessage Raw response from the URL of getting signaling channel endpoints.
 * @param[in] messageLength Length of raw message.
 * @param[out] pCreateSignalingChannelResponse The output structure includes the ARN of created channel.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_INVALID_JSON, if raw message is not a valid JSON message.
 * - #SIGNALING_RESULT_NOT_EXPECT_RESPONSE, if the message isn't the expected one.
 * - #SIGNALING_RESULT_INVALID_TTL, if the TTL of ICE server config is invalid.
 * 
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_CreateSignalingChannel.html for details.
 */
SignalingResult_t Signaling_parseCreateSignalingChannelResponse( SignalingContext_t *pCtx, char * pMessage, size_t messageLength, SignalingCreateSignalingChannelResponse_t *pCreateSignalingChannelResponse );

/**
 * @brief This function is used to construct request to query signaling channel endpoints.
 *
 * @param[in] pCtx The pointer of signaling context.
 * @param[in] pGetSignalingChannelEndpointRequest The parameters that needed to construct request to query signaling channel endpoints.
 * @param[out] pRequestBuffer The output structure includes URI, body buffers, and their sizes.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if buffer is not enough to store constructed message.
 * 
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_GetSignalingChannelEndpoint.html for details.
 */
SignalingResult_t Signaling_constructGetSignalingChannelEndpointRequest( SignalingContext_t *pCtx, SignalingGetSignalingChannelEndpointRequest_t * pGetSignalingChannelEndpointRequest, SignalingRequest_t *pRequestBuffer );

/**
 * @brief This function is used to parse response of get signaling channel endpoints.
 *
 * @param[in] pCtx The pointer of signaling context.
 * @param[in] pMessage Raw response from the URL of getting signaling channel endpoints.
 * @param[in] messageLength Length of raw message.
 * @param[out] pGetSignalingChannelEndpointResponse The output structure includes endpoints of the signaling channel for websocket secure, HTTPS and WebRTC.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_INVALID_JSON, if raw message is not a valid JSON message.
 * - #SIGNALING_RESULT_NOT_EXPECT_RESPONSE, if the message isn't the expected one.
 * 
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_GetSignalingChannelEndpoint.html for details.
 */
SignalingResult_t Signaling_parseGetSignalingChannelEndpointResponse( SignalingContext_t *pCtx, char * pMessage, size_t messageLength, SignalingGetSignalingChannelEndpointResponse_t * pGetSignalingChannelEndpointResponse );

/**
 * @brief This function is used to construct request to get ICE server configs.
 *
 * @param[in] pCtx The pointer of signaling context.
 * @param[in] pGetIceServerConfigReqeust The parameters that needed to construct request to get ICE server configs.
 * @param[out] pRequestBuffer The output structure includes URI, body buffers, and their sizes.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if buffer is not enough to store constructed message.
 * 
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_signaling_GetIceServerConfig.html for details.
 */
SignalingResult_t Signaling_constructGetIceServerConfigRequest( SignalingContext_t *pCtx, SignalingGetIceServerConfigRequest_t * pGetIceServerConfigReqeust, SignalingRequest_t *pRequestBuffer);

/**
 * @brief This function is used to parse response of get signaling channel endpoints.
 *
 * @param[in] pCtx The pointer of signaling context.
 * @param[in] pMessage Raw response from the URL of getting signaling channel endpoints.
 * @param[in] messageLength Length of raw message.
 * @param[out] pGetIceConfigResponse The output structure includes a list of ICE server information.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_INVALID_JSON, if raw message is not a valid JSON message.
 * - #SIGNALING_RESULT_NOT_EXPECT_RESPONSE, if the message isn't the expected one.
 * - #SIGNALING_RESULT_INVALID_TTL, if the TTL of ICE server config is invalid.
 * 
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_signaling_GetIceServerConfig.html for details.
 */
SignalingResult_t Signaling_parseGetIceServerConfigResponse( SignalingContext_t *pCtx, char * pMessage, size_t messageLength, SignalingGetIceServerConfigResponse_t *pGetIceConfigResponse );

/**
 * @brief This function is used to construct request to join storage session.
 *
 * @param[in] pCtx The pointer of signaling context.
 * @param[in] pJoinStorageSessionRequest The parameters that needed to construct request to join storage session.
 * @param[out] pRequestBuffer The output structure includes URI, body buffers, and their sizes.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if buffer is not enough to store constructed message.
 * 
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_webrtc_JoinStorageSession.html for details.
 */
SignalingResult_t Signaling_constuctJoinStorageSessionRequest( SignalingContext_t *pCtx, SignalingJoinStorageSessionRequest_t * pJoinStorageSessionRequest, SignalingRequest_t *pRequestBuffer );

/**
 * @brief This function is used to construct request to delete signaling channel.
 *
 * @param[in] pCtx The pointer of signaling context.
 * @param[in] pDeleteSignalingChannelRequest The parameters that needed to construct request to delete signaling channel.
 * @param[out] pRequestBuffer The output structure includes URI, body buffers, and their sizes.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if buffer is not enough to store constructed message.
 * 
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis-7.html for details.
 */
SignalingResult_t Signaling_constructDeleteSignalingChannelRequest( SignalingContext_t *pCtx, SignalingDeleteSignalingChannelRequest_t * pDeleteSignalingChannelRequest, SignalingRequest_t *pRequestBuffer );

/**
 * @brief This function is used to construct request to connect with websocket secure endpoint.
 *
 * @param[in] pCtx The pointer of signaling context.
 * @param[in] pConnectWssEndpointRequest The parameters that needed to construct request.
 * @param[out] pRequestBuffer The output structure includes URI, body buffers, and their sizes.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if buffer is not enough to store constructed message.
 * 
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis.html for details.
 */
SignalingResult_t Signaling_constructConnectWssEndpointRequest( SignalingContext_t *pCtx, SignalingConnectWssEndpointRequest_t * pConnectWssEndpointRequest, SignalingRequest_t *pRequestBuffer );

/**
 * @brief This function is used to construct event message to websocket secure endpoint.
 *
 * @param[in] pWssSendMessage The event structre to construct message.
 * @param[out] pBuffer The buffer to store constructed message.
 * @param[out] pBufferLength The length of the buffer that stores the constructed message.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if buffer is not enough to store constructed message.
 * 
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis.html for details.
 */
SignalingResult_t Signaling_constructWssMessage( SignalingWssSendMessage_t * pWssSendMessage, char * pBuffer, size_t * pBufferLength );

/**
 * @brief This function is used to parse event message from websocket secure endpoint.
 *
 * @param[in] pMessage Raw event message from websocket secure endpoint.
 * @param[in] messageLength Length of raw event message.
 * @param[out] pWssRecvMessage The parsed message is encapsulated within a structure that
 *                             employs pointers and size fields to represent the data.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_INVALID_JSON, if raw message is not a valid JSON message.
 * - #SIGNALING_RESULT_NOT_EXPECT_RESPONSE, if the message isn't the expected one.
 * - #SIGNALING_RESULT_INVALID_STATUS_RESPONSE, if statusResponse doesn't contain correct formatted message.
 * - #SIGNALING_RESULT_INVALID_TTL, if the TTL of ICE server config is invalid.
 * 
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis-7.html for details.
 */
SignalingResult_t Signaling_parseWssRecvMessage( char * pMessage, size_t messageLength, SignalingWssRecvMessage_t * pWssRecvMessage );

/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#ifdef __cplusplus
    }
#endif
/* *INDENT-ON* */

#endif /* SIGNALING_API_H */
