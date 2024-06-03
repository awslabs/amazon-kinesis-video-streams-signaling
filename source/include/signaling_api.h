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
 * Helper macros to create URLs for various requests.
 */

#define SIGNALING_IS_CHINA_REGION( region ) ( strncmp( "cn-", region, 3 ) == 0 )

#define SIGNALING_CONTROL_PLANE_URL( region ) \
    "https://kinesisvideo." region ".amazonaws.com"

#define SIGNALING_CONTROL_PLANE_URL_CN( region ) \
    "https://kinesisvideo." region ".amazonaws.com.cn"

#define SIGNALING_DESCRIBE_SIGNALING_CHANNEL_URL( region ) \
    SIGNALING_CONTROL_PLANE_URL( region ) "/describeSignalingChannel"

#define SIGNALING_DESCRIBE_SIGNALING_CHANNEL_URL_CN( region ) \
    SIGNALING_CONTROL_PLANE_URL_CN( region ) "/describeSignalingChannel"

#define SIGNALING_DESCRIBE_MEDIA_STORAGE_CONFIG_URL( region ) \
    SIGNALING_CONTROL_PLANE_URL( region ) "/describeMediaStorageConfiguration"

#define SIGNALING_DESCRIBE_MEDIA_STORAGE_CONFIG_URL_CN( region ) \
    SIGNALING_CONTROL_PLANE_URL_CN( region ) "/describeMediaStorageConfiguration"

#define SIGNALING_CREATE_SIGNALING_CHANNEL_URL( region ) \
    SIGNALING_CONTROL_PLANE_URL( region ) "/createSignalingChannel"

#define SIGNALING_CREATE_SIGNALING_CHANNEL_URL_CN( region ) \
    SIGNALING_CONTROL_PLANE_URL_CN( region ) "/createSignalingChannel"

#define SIGNALING_GET_SIGNALING_CHANNEL_ENDPOINT_URL( region ) \
    SIGNALING_CONTROL_PLANE_URL( region ) "/getSignalingChannelEndpoint"

#define SIGNALING_GET_SIGNALING_CHANNEL_ENDPOINT_URL_CN( region ) \
    SIGNALING_CONTROL_PLANE_URL_CN( region ) "/getSignalingChannelEndpoint"

#define SIGNALING_GET_ICE_SERVER_CONFIG_URL( channelEndpoint ) \
    channelEndpoint "/v1/get-ice-server-config"

#define SIGNALING_JOIN_STORAGE_SESSION_URL( channelEndpoint ) \
    channelEndpoint "/joinStorageSession"

#define SIGNALING_DELETE_SIGNALING_CHANNEL_URL( region ) \
    SIGNALING_CONTROL_PLANE_URL( region ) "/deleteSignalingChannel"

#define SIGNALING_DELETE_SIGNALING_CHANNEL_URL_CN( region ) \
    SIGNALING_CONTROL_PLANE_URL_CN( region ) "/deleteSignalingChannel"

#define SIGNALING_CONNECT_AS_MASTER_URL( channelWssEndpoint, channelArn ) \
    channelWssEndpoint "?X-Amz-ChannelARN=" channelArn

#define SIGNALING_CONNECT_AS_VIEWER_URL( channelWssEndpoint, channelArn, clientId ) \
    channelWssEndpoint "?X-Amz-ChannelARN=" channelArn "&X-Amz-ClientId=" clientId

/*-----------------------------------------------------------*/

/**
 * @brief This function is used to construct request to query signaling channel information.
 *
 * @param[in] pChannelName The channel name set in AWS account.
 * @param[out] pRequestBuffer The output structure includes body buffer, and size.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if buffer is not enough to store constructed message.
 *
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DescribeSignalingChannel.html for details.
 */
SignalingResult_t Signaling_ConstructDescribeSignalingChannelRequest( SignalingChannelName_t * pChannelName,
                                                                      SignalingRequest_t * pRequestBuffer );

/**
 * @brief This function is used to parse response of describe signaling channel.
 *
 * @param[in] pMessage Raw response from the URL of getting signaling channel endpoints.
 * @param[in] messageLength Length of raw message.
 * @param[out] pChannelInfo The output structure includes the signaling channel information.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_INVALID_JSON, if raw message is not a valid JSON message.
 * - #SIGNALING_RESULT_UNEXPECTED_RESPONSE, if the message isn't the expected one.
 * - #SIGNALING_RESULT_INVALID_CHANNEL_NAME, if the channel name is longer than array size.
 * - #SIGNALING_RESULT_INVALID_CHANNEL_TYPE, if the channel type is longer than array size.
 * - #SIGNALING_RESULT_INVALID_TTL, if the TTL is longer than array size.
 *
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DescribeSignalingChannel.html for details.
 */
SignalingResult_t Signaling_ParseDescribeSignalingChannelResponse( const char * pMessage,
                                                                   size_t messageLength,
                                                                   SignalingChannelInfo_t * pChannelInfo );

/**
 * @brief This function is used to construct request to query media storage configuration.
 *
 * @param[in] pChannelArn The channel ARN which gets from Signaling_ConstructDescribeSignalingChannelRequest.
 * @param[out] pRequestBuffer The output structure includes body buffer, and size.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if buffer is not enough to store constructed message.
 *
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DescribeMediaStorageConfiguration.html for details.
 */
SignalingResult_t Signaling_ConstructDescribeMediaStorageConfigRequest( SignalingChannelArn_t * pChannelArn,
                                                                        SignalingRequest_t * pRequestBuffer );

/**
 * @brief This function is used to parse response of describe media storage configurations.
 *
 * @param[in] pMessage Raw response from the URL of getting signaling channel endpoints.
 * @param[in] messageLength Length of raw message.
 * @param[out] pMediaStorageConfig The output structure includes the media storage configuration properties.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_INVALID_JSON, if raw message is not a valid JSON message.
 * - #SIGNALING_RESULT_UNEXPECTED_RESPONSE, if the message isn't the expected one.
 *
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DescribeMediaStorageConfiguration.html for details.
 */
SignalingResult_t Signaling_ParseDescribeMediaStorageConfigResponse( const char * pMessage,
                                                                     size_t messageLength,
                                                                     SignalingMediaStorageConfig_t * pMediaStorageConfig );

/**
 * @brief This function is used to construct request to create signaling channel.
 *
 * @param[in] pCreateSignalingChannelRequestInfo The parameters that needed to construct request to create signaling channel.
 * @param[out] pRequestBuffer The output structure includes body buffer, and size.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if buffer is not enough to store constructed message.
 *
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_CreateSignalingChannel.html for details.
 */
SignalingResult_t Signaling_ConstructCreateSignalingChannelRequest( CreateSignalingChannelRequestInfo_t * pCreateSignalingChannelRequestInfo,
                                                                    SignalingRequest_t * pRequestBuffer );

/**
 * @brief This function is used to parse response of creating signaling channel.
 *
 * @param[in] pMessage Raw response from the URL of getting signaling channel endpoints.
 * @param[in] messageLength Length of raw message.
 * @param[out] pChannelArn The output structure includes the ARN of created channel.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_INVALID_JSON, if raw message is not a valid JSON message.
 * - #SIGNALING_RESULT_UNEXPECTED_RESPONSE, if the message isn't the expected one.
 * - #SIGNALING_RESULT_INVALID_TTL, if the TTL of ICE server config is invalid.
 *
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_CreateSignalingChannel.html for details.
 */
SignalingResult_t Signaling_ParseCreateSignalingChannelResponse( const char * pMessage,
                                                                 size_t messageLength,
                                                                 SignalingChannelArn_t * pChannelArn );

/**
 * @brief This function is used to construct request to query signaling channel endpoints.
 *
 * @param[in] pGetSignalingChannelEndpointRequestInfo The parameters that needed to construct request to query signaling channel endpoints.
 * @param[out] pRequestBuffer The output structure includes body buffer, and size.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if buffer is not enough to store constructed message.
 *
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_GetSignalingChannelEndpoint.html for details.
 */
SignalingResult_t Signaling_ConstructGetSignalingChannelEndpointRequest( GetSignalingChannelEndpointRequestInfo_t * pGetSignalingChannelEndpointRequestInfo,
                                                                         SignalingRequest_t * pRequestBuffer );

/**
 * @brief This function is used to parse response of get signaling channel endpoints.
 *
 * @param[in] pMessage Raw response from the URL of getting signaling channel endpoints.
 * @param[in] messageLength Length of raw message.
 * @param[out] pSignalingChannelEndpoints The output structure includes endpoints of the signaling channel for websocket secure, HTTPS and WebRTC.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_INVALID_JSON, if raw message is not a valid JSON message.
 * - #SIGNALING_RESULT_UNEXPECTED_RESPONSE, if the message isn't the expected one.
 * - #SIGNALING_RESULT_INVALID_PROTOCOL, if protocol type in endpoint is invalid.
 *
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_GetSignalingChannelEndpoint.html for details.
 */
SignalingResult_t Signaling_ParseGetSignalingChannelEndpointResponse( const char * pMessage,
                                                                      size_t messageLength,
                                                                      SignalingChannelEndpoints_t * pSignalingChannelEndpoints );

/**
 * @brief This function is used to construct request to get ICE server configs.
 *
 * @param[in] pGetIceServerConfigRequestInfo The parameters that needed to construct request to get ICE server configs.
 * @param[out] pRequestBuffer The output structure includes body buffer, and size.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if buffer is not enough to store constructed message.
 *
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_signaling_GetIceServerConfig.html for details.
 */
SignalingResult_t Signaling_ConstructGetIceServerConfigRequest( GetIceServerConfigRequestIfo_t * pGetIceServerConfigRequestInfo,
                                                                SignalingRequest_t * pRequestBuffer );

/**
 * @brief This function is used to parse response of get signaling channel endpoints.
 *
 * @param[in] pMessage Raw response from the URL of getting signaling channel endpoints.
 * @param[in] messageLength Length of raw message.
 * @param[out] pIceServers The output structures include a list of ICE servers' information, user must provide memory to store this information.
 * @param[in, out] pIceServers The maximum number of ICE servers the memory can store, provide the exact ICE server number while return.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_INVALID_JSON, if raw message is not a valid JSON message.
 * - #SIGNALING_RESULT_UNEXPECTED_RESPONSE, if the message isn't the expected one.
 * - #SIGNALING_RESULT_INVALID_TTL, if the TTL of ICE server config is invalid.
 *
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_signaling_GetIceServerConfig.html for details.
 */
SignalingResult_t Signaling_ParseGetIceServerConfigResponse( const char * pMessage,
                                                             size_t messageLength,
                                                             SignalingIceServer_t * pIceServers,
                                                             size_t * pNumIceServers );

/**
 * @brief This function is used to construct request to join storage session.
 *
 * @param[in] pJoinStorageSessionRequestInfo The parameters that needed to construct request to join storage session.
 * @param[out] pRequestBuffer The output structure includes body buffer, and size.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if buffer is not enough to store constructed message.
 *
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_webrtc_JoinStorageSession.html for details.
 */
SignalingResult_t Signaling_ConstructJoinStorageSessionRequest( JoinStorageSessionRequestInfo_t * pJoinStorageSessionRequestInfo,
                                                                SignalingRequest_t * pRequestBuffer );

/**
 * @brief This function is used to construct request to delete signaling channel.
 *
 * @param[in] pDeleteSignalingChannelRequestInfo The parameters that needed to construct request to delete signaling channel.
 * @param[out] pRequestBuffer The output structure includes body buffer, and size.
 *
 * @return Returns one of the following:
 * - #SIGNALING_RESULT_OK, if initialization was performed without error.
 * - #SIGNALING_RESULT_BAD_PARAM, if any mandatory parameters is NULL.
 * - #SIGNALING_RESULT_SNPRINTF_ERROR, if snprintf returns negative value.
 * - #SIGNALING_RESULT_OUT_OF_MEMORY, if buffer is not enough to store constructed message.
 *
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis-7.html for details.
 */
SignalingResult_t Signaling_ConstructDeleteSignalingChannelRequest( DeleteSignalingChannelRequestInfo_t * pDeleteSignalingChannelRequestInfo,
                                                                    SignalingRequest_t * pRequestBuffer );

/**
 * @brief This function is used to construct event message to websocket secure endpoint.
 *
 * @param[in] pWssSendMessage The event structure to construct message.
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
SignalingResult_t Signaling_ConstructWssMessage( WssSendMessage_t * pWssSendMessage,
                                                 char * pBuffer,
                                                 size_t * pBufferLength );

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
 * - #SIGNALING_RESULT_UNEXPECTED_RESPONSE, if the message isn't the expected one.
 * - #SIGNALING_RESULT_INVALID_STATUS_RESPONSE, if statusResponse doesn't contain correct formatted message.
 * - #SIGNALING_RESULT_INVALID_TTL, if the TTL of ICE server config is invalid.
 *
 * @note Refer to https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis-7.html for details.
 */
SignalingResult_t Signaling_ParseWssRecvMessage( const char * pMessage,
                                                 size_t messageLength,
                                                 WssRecvMessage_t * pWssRecvMessage );

/*-----------------------------------------------------------*/

/* *INDENT-OFF* */
#ifdef __cplusplus
}
#endif
/* *INDENT-ON* */

#endif /* SIGNALING_API_H */
