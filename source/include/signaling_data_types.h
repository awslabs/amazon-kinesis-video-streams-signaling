#ifndef SIGNALING_DATA_TYPES_H
#define SIGNALING_DATA_TYPES_H

/* Standard includes. */
#include <stdint.h>
#include <stddef.h>

#include "signaling_config_defaults.h"

/*-----------------------------------------------------------*/

/**
 * Control plane prefix
 */
#define AWS_CONTROL_PLANE_URI_PREFIX "https://"

/**
 * KVS service name
 */
#define AWS_KINESIS_VIDEO_SERVICE_NAME "kinesisvideo"

/**
 * Control plane postfix
 */
#define AWS_CONTROL_PLANE_URI_POSTFIX ".amazonaws.com"

#define SIGNALING_STRING_UNKNOWN "UNKOWN"
#define SIGNALING_STRING_SINGLE_MASTER "SINGLE_MASTER"
#define SIGNALING_STRING_MASTER "MASTER"
#define SIGNALING_STRING_VIEWER "VIEWER"

#define AWS_DESCRIBE_SIGNALING_CHANNEL_API_POSTFIX "/describeSignalingChannel"

// Parameterized string for Describe Channel API
#define AWS_DESCRIBE_CHANNEL_PARAM_JSON_TEMPLATE    "{\n\t\"ChannelName\": \"%.*s\"\n}"

#define AWS_DESCRIBE_MEDIA_STORAGE_CONF_API_POSTFIX "/describeMediaStorageConfiguration"

// Parameterized string for Desceibe Media Storage Config API
#define AWS_DESCRIBE_MEDIA_STORAGE_CONF_PARAM_JSON_TEMPLATE "{\n\t\"ChannelARN\": \"%.*s\"\n}"

#define AWS_CREATE_SIGNALING_CHANNEL_API_POSTFIX "/createSignalingChannel"

// Parameterized string for Create Channel API
#define AWS_CREATE_CHANNEL_PARAM_JSON_TEMPLATE_PREFIX                                                                                                           \
    "{\n\t\"ChannelName\": \"%.*s\","                                                                                                                  \
    "\n\t\"ChannelType\": \"%s\","                                                                                                                   \
    "\n\t\"SingleMasterConfiguration\": {"                                                                                                           \
    "\n\t\t\"MessageTtlSeconds\": %u\n\t}"

#define AWS_CREATE_CHANNEL_PARAM_JSON_TEMPLATE_POSTFIX "\n}"

#define AWS_CREATE_CHANNEL_PARAM_JSON_TAGS_PREFIX ",\n\t\"Tags\": ["
#define AWS_CREATE_CHANNEL_PARAM_JSON_TAGS_TEMPLATE \
    "\n\t\t{\n\t\t\t\"Key\": \"%.*s\"," \
    "\n\t\t\t\"Value\": \"%.*s\"\n\t\t}"
#define AWS_CREATE_CHANNEL_PARAM_JSON_TAGS_POSTFIX "\n\t]"

#define AWS_GET_SIGNALING_CHANNEL_ENDPOINT_API_POSTFIX "/getSignalingChannelEndpoint"

// Parameterized string for Get Channel Endpoint API
#define AWS_GET_CHANNEL_ENDPOINT_PARAM_JSON_TEMPLATE                                                                                                     \
    "{\n\t\"ChannelARN\": \"%.*s\","                                                                                                                   \
    "\n\t\"SingleMasterChannelEndpointConfiguration\": {"                                                                                            \
    "\n\t\t\"Protocols\": [%s],"                                                                                                                     \
    "\n\t\t\"Role\": \"%s\""                                                                                                                         \
    "\n\t}\n}"

#define AWS_GET_ICE_CONFIG_API_POSTFIX "/v1/get-ice-server-config"

// Parameterized string for Get Ice Server Config API
#define AWS_GET_ICE_CONFIG_PARAM_JSON_TEMPLATE                                                                                                           \
    "{\n\t\"ChannelARN\": \"%.*s\","                                                                                                                   \
    "\n\t\"ClientId\": \"%.*s\","                                                                                                                      \
    "\n\t\"Service\": \"TURN\""                                                                                                                      \
    "\n}"

#define AWS_JOIN_STORAGE_SESSION_API_POSTFIX "/joinStorageSession"

// Parameterized string for Join Storage Session API
#define AWS_JOIN_STORAGE_SESSION_MASTER_PARAM_JSON_TEMPLATE "{\n\t\"channelArn\": \"%.*s\"\n}"
#define AWS_JOIN_STORAGE_SESSION_VIEWER_PARAM_JSON_TEMPLATE                                                                                    \
    "{\n\t\"channelArn\": \"%.*s\","                                                                                                                   \
    "\n\t\"clientId\": \"%.*s\"\n}"

#define AWS_DELETE_SIGNALING_CHANNEL_API_POSTFIX "/deleteSignalingChannel"

// Parameterized string for Delete Channel API
#define AWS_DELETE_CHANNEL_PARAM_JSON_TEMPLATE                                                                                                           \
    "{\n\t\"ChannelARN\": \"%.*s\","                                                                                                                   \
    "\n\t\"CurrentVersion\": \"%.*s\"\n}"

// Send message JSON template
#define AWS_SIGNALING_SEND_MESSAGE_TEMPLATE_PREFIX                                                                                                              \
    "{\n"                                                                                                                                            \
    "\t\"action\": \"%s\",\n"                                                                                                                        \
    "\t\"RecipientClientId\": \"%.*s\",\n"                                                                                                           \
    "\t\"MessagePayload\": \"%.*s\""

// Correlation id template if it's set.
#define AWS_SIGNALING_SEND_MESSAGE_TEMPLATE_CORRELATION_ID                                                                                          \
    ",\n"                                                                                                                \
    "\t\"CorrelationId\": \"%.*s\""

#define AWS_SIGNALING_ICE_SERVER_LIST_TEMPLATE_PREFIX                                                                                                     \
    ",\n"                                                                                                                                            \
    "\t\"IceServerList\": ["

#define AWS_SIGNALING_ICE_SERVER_LIST_TEMPLATE_POSTFIX "\n\t]"

#define AWS_SIGNALING_ICE_SERVER_TEMPLATE_PREFIX                                                                                                                \
    "\n"                                                                                                                                             \
    "\t\t{\n"                                                                                                                                        \
    "\t\t\t\"Password\": \"%.*s\",\n"                                                                                                                  \
    "\t\t\t\"Ttl\": %u,\n"                                                                                                                  \
    "\t\t\t\"Uris\": ["

#define AWS_SIGNALING_ICE_SERVER_TEMPLATE_POSTFIX                                                                                                                \
    "\n\t\t\t],\n"                                                                                                                        \
    "\t\t\t\"Username\": \"%.*s\"\n"                                                                                                                   \
    "\t\t}"

// Ending curly bracket
#define AWS_SIGNALING_SEND_MESSAGE_TEMPLATE_POSTFIX                                                                                          \
    "\n}"

// Parameter names for Connect Websocket Secure Endpoint
#define AWS_SIGNALING_ROLE_PARAM_NAME         "X-Amz-Role"
#define AWS_SIGNALING_CHANNEL_NAME_PARAM_NAME "X-Amz-ChannelName"
#define AWS_SIGNALING_CHANNEL_ARN_PARAM_NAME  "X-Amz-ChannelARN"
#define AWS_SIGNALING_CLIENT_ID_PARAM_NAME    "X-Amz-ClientId"

/**
 * @brief Maximum size of the character array buffer for the TTL in the describe signaling channel response.
 *        Refer https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_SingleMasterConfiguration.html#KinesisVideo-Type-SingleMasterConfiguration-MessageTtlSeconds for details.
 */
#define AWS_MESSAGE_CHANNEL_TTL_SECONDS_BUFFER_MAX ( 5 )

/**
 * @brief Minimum value of TTL in the describe signaling channel response.
 *        Refer https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_SingleMasterConfiguration.html#KinesisVideo-Type-SingleMasterConfiguration-MessageTtlSeconds for details.
 */
#define AWS_MESSAGE_CHANNEL_TTL_SECONDS_MIN ( 5 )

/**
 * @brief Maximum value of TTL in the describe signaling channel response.
 *        Refer https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_SingleMasterConfiguration.html#KinesisVideo-Type-SingleMasterConfiguration-MessageTtlSeconds for details.
 */
#define AWS_MESSAGE_CHANNEL_TTL_SECONDS_MAX ( 120 )

/**
 * @brief Maximum size of the character array buffer for the TTL in ICE server.
 *        Refer https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_signaling_IceServer.html for details.
 */
#define AWS_MESSAGE_ICE_SERVER_TTL_SECONDS_BUFFER_MAX ( 7 )

/**
 * @brief Minimum value of TTL in ICE server.
 *        Refer https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_signaling_IceServer.html for details.
 */
#define AWS_MESSAGE_ICE_SERVER_TTL_SECONDS_MIN ( 30 )

/**
 * @brief Maximum value of TTL in ICE server.
 *        Refer https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_signaling_IceServer.html for details.
 */
#define AWS_MESSAGE_ICE_SERVER_TTL_SECONDS_MAX ( 86400 )

/**
 * @ingroup signaling_enum_types
 * @brief Return code of Signaling component.
 */
typedef enum SignalingResult
{
    SIGNALING_RESULT_OK,
    SIGNALING_RESULT_BAD_PARAM,
    SIGNALING_RESULT_SNPRINTF_ERROR,
    SIGNALING_RESULT_OUT_OF_MEMORY,
    SIGNALING_RESULT_INVALID_JSON,
    SIGNALING_RESULT_NOT_EXPECT_RESPONSE,
    SIGNALING_RESULT_INVALID_TTL,
    SIGNALING_RESULT_INVALID_ENDPOINT,
    SIGNALING_RESULT_INVALID_CHANNEL_NAME,
    SIGNALING_RESULT_INVALID_CHANNEL_TYPE,
    SIGNALING_RESULT_INVALID_ICE_SERVER_COUNT,
    SIGNALING_RESULT_INVALID_ICE_SERVER_URIS_COUNT,
    SIGNALING_RESULT_INVALID_STATUS_RESPONSE,
    SIGNALING_RESULT_REGION_LENGTH_TOO_LARGE,
} SignalingResult_t;

/**
 * @ingroup signaling_enum_types
 * @brief Protocol type of endpoints while parsing get signaling channel endpoint response.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_GetSignalingChannelEndpoint.html for more detail.
 */
typedef enum SignalingChannelEndpointProtocol
{
    SIGNALING_ENDPOINT_PROTOCOL_NONE = 0,
    SIGNALING_ENDPOINT_PROTOCOL_WEBSOCKET_SECURE = 1,
    SIGNALING_ENDPOINT_PROTOCOL_HTTPS = 2,
    SIGNALING_ENDPOINT_PROTOCOL_WEBRTC = 4,
    SIGNALING_ENDPOINT_PROTOCOL_MAX = 0xFF,
} SignalingChannelEndpointProtocol_t;

/**
 * @ingroup signaling_enum_types
 * @brief Type of signaling channel.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_ChannelInfo.html#KinesisVideo-Type-ChannelInfo-ChannelType for more detail.
 */
typedef enum SignalingTypeChannel {
    SIGNALING_TYPE_CHANNEL_UNKNOWN,       //!< Channel type is unknown
    SIGNALING_TYPE_CHANNEL_SINGLE_MASTER, //!< Channel type is single master
} SignalingTypeChannel_t;

/**
 * @ingroup signaling_enum_types
 * @brief Role of current signaling request.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-how-it-works.html for more detail.
 */
typedef enum SignalingRole
{
    SIGNALING_ROLE_NONE = 0,
    SIGNALING_ROLE_MASTER,
    SIGNALING_ROLE_VIEWER,
} SignalingRole_t;

/**
 * @ingroup signaling_enum_types
 * @brief Type of signaling message.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis-7.html for more detail.
 */
typedef enum SignalingTypeMessage
{
    SIGNALING_TYPE_MESSAGE_UNKNOWN = 0,
    SIGNALING_TYPE_MESSAGE_SDP_OFFER,
    SIGNALING_TYPE_MESSAGE_SDP_ANSWER,
    SIGNALING_TYPE_MESSAGE_ICE_CANDIDATE,
    SIGNALING_TYPE_MESSAGE_GO_AWAY,
    SIGNALING_TYPE_MESSAGE_RECONNECT_ICE_SERVER,
    SIGNALING_TYPE_MESSAGE_STATUS_RESPONSE,
} SignalingTypeMessage_t;

/**
 * @ingroup signaling_enum_types
 * @brief A structure that encapsulates a signaling channel's metadata and properties.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_ChannelInfo.html for more detail.
 */
typedef struct SignalingChannelInfo
{
    const char * pChannelArn;
    size_t channelArnLength;
    const char * pChannelName;
    size_t channelNameLength;
    const char * pChannelStatus;
    size_t channelStatusLength;
    SignalingTypeChannel_t type;
    const char * pVersion;
    size_t versionLength;
    const char * pCreationTime;
    size_t creationTimeLength;
    uint32_t messageTtlSeconds;
} SignalingChannelInfo_t;

/**
 * @ingroup signaling_enum_types
 * @brief AWS control plane information of the signaling channel.
 */
typedef struct SignalingContext
{
    char region[SIGNALING_AWS_REGION_MAX_LENGTH];
    size_t regionLength;
    char controlPlaneUrl[SIGNALING_AWS_CONTROL_PLANE_URL_MAX_LENGTH];
    size_t controlPlaneUrlLength;
    char channelName[SIGNALING_AWS_MAX_CHANNEL_NAME_LEN];
    size_t channelNameLength;
} SignalingContext_t;

/**
 * @ingroup signaling_enum_types
 * @brief Basic output format of the signaling request.
 */
typedef struct SignalingRequest
{
    char * pUrl;
    size_t urlLength;
    char * pBody;
    size_t bodyLength;
} SignalingRequest_t;

/**
 * @ingroup signaling_enum_types
 * @brief Tags to create signaling channel.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_Tag.html for more detail.
 */
typedef struct SignalingTag {
    char * pName;
    size_t nameLength;
    char * pValue;
    size_t valueLength;
} SignalingTag_t;

/**
 * @ingroup signaling_enum_types
 * @brief The control plane information of a signaling channel.
 */
typedef struct SignalingAwsControlPlaneInfo {
    char * pRegion;
    size_t regionLength;
    char * pControlPlaneUrl;
    size_t controlPlaneUrlLength;
} SignalingAwsControlPlaneInfo_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of CreateSignalingChannel request.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_CreateSignalingChannel.html for more detail.
 */
typedef struct SignalingCreateSignalingChannelRequest {
    SignalingChannelInfo_t channelInfo;
    SignalingTag_t * pTags;
    size_t tagsCount;
} SignalingCreateSignalingChannelRequest_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of CreateSignalingChannel response.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_CreateSignalingChannel.html for more detail.
 */
typedef struct SignalingCreateSignalingChannelResponse {
    const char * pChannelArn;
    size_t channelArnLength;
} SignalingCreateSignalingChannelResponse_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of DescribeSignalingChannel request.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DescribeSignalingChannel.html for more detail.
 */
typedef struct SignalingDescribeSignalingChannelRequest
{
    char * pChannelName;
    size_t channelNameLength;
} SignalingDescribeSignalingChannelRequest_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of DescribeSignalingChannel response.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DescribeSignalingChannel.html for more detail.
 */
typedef struct SignalingDescribeSignalingChannelResponse
{
    const char * pChannelArn;
    size_t channelArnLength;
    const char * pChannelName;
    size_t channelNameLength;
    const char * pChannelStatus;
    size_t channelStatusLength;
    const char * pChannelType;
    size_t channelTypeLength;
    const char * pVersion;
    size_t versionLength;
    const char * pCreationTime;
    size_t creationTimeLength;
    uint32_t messageTtlSeconds;
} SignalingDescribeSignalingChannelResponse_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of DescribeMediaStorageConfiguration request.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DescribeMediaStorageConfiguration.html for more detail.
 */
typedef struct SignalingDescribeMediaStorageConfigRequest
{
    char * pChannelArn;
    size_t channelArnLength;
} SignalingDescribeMediaStorageConfigRequest_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of DescribeMediaStorageConfiguration response.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DescribeMediaStorageConfiguration.html for more detail.
 */
typedef struct SignalingDescribeMediaStorageConfigResponse
{
    const char * pStatus;
    size_t statusLength;
    const char * pStreamArn;
    size_t streamArnLength;
} SignalingDescribeMediaStorageConfigResponse_t;

/**
 * @ingroup signaling_enum_types
 * @brief A structure for the ICE server connection data.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_signaling_IceServer.html for more detail.
 */
typedef struct SignalingIceServer
{
    const char * pPassword;
    size_t passwordLength;
    uint32_t messageTtlSeconds;
    const char * pUris[SIGNALING_AWS_ICE_SERVER_MAX_URIS];
    size_t urisLength[SIGNALING_AWS_ICE_SERVER_MAX_URIS];
    uint32_t urisNum;
    const char * pUserName;
    size_t userNameLength;
} SignalingIceServer_t;

/**
 * @ingroup signaling_enum_types
 * @brief The list of ICE server information objects.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_signaling_GetIceServerConfig.html for more detail.
 */
typedef struct SignalingIceServerList
{
    SignalingIceServer_t iceServer[SIGNALING_AWS_ICE_SERVER_MAX_NUM];
    uint32_t iceServerNum;
} SignalingIceServerList_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of GetIceServerConfig response.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_signaling_GetIceServerConfig.html for more detail.
 */
typedef SignalingIceServerList_t SignalingGetIceServerConfigResponse_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of GetSignalingChannelEndpoint request.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_GetSignalingChannelEndpoint.html for more detail.
 */
typedef struct SignalingGetSignalingChannelEndpointRequest
{
    char * pChannelArn;
    size_t channelArnLength;
    uint8_t protocolsBitsMap; /* support multiple propocols. */
    SignalingRole_t role;
} SignalingGetSignalingChannelEndpointRequest_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of GetSignalingChannelEndpoint response.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_GetSignalingChannelEndpoint.html for more detail.
 */
typedef struct SignalingGetSignalingChannelEndpointResponse
{
    const char * pEndpointWebsocketSecure;
    size_t endpointWebsocketSecureLength;
    const char * pEndpointHttps;
    size_t endpointHttpsLength;
    const char * pEndpointWebrtc;
    size_t endpointWebrtcLength;
} SignalingGetSignalingChannelEndpointResponse_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of GetIceServerConfig request.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_signaling_GetIceServerConfig.html for more detail.
 */
typedef struct SignalingGetIceServerConfigRequest
{
    char * pChannelArn;
    size_t channelArnLength;
    char * pEndpointHttps;
    size_t endpointHttpsLength;
    char * pClientId;
    size_t clientIdLength;
} SignalingGetIceServerConfigRequest_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of JoinStorageSession request.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_webrtc_JoinStorageSession.html for more detail.
 */
typedef struct SignalingJoinStorageSessionRequest
{
    const char * pEndpointWebrtc;
    size_t endpointWebrtcLength;
    char * pChannelArn;
    size_t channelArnLength;
    SignalingRole_t role;
    char * pClientId;
    size_t clientIdLength;
} SignalingJoinStorageSessionRequest_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of DeleteSignalingChannel request.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DeleteSignalingChannel.html for more detail.
 */
typedef struct SignalingDeleteSignalingChannelRequest
{
    char * pChannelArn;
    size_t channelArnLength;
    char * pVersion;
    size_t versionLength;
} SignalingDeleteSignalingChannelRequest_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure to connect with websocket secure endpoint.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis-1.html and
 *        https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis-2.html for more detail.
 */
typedef struct SignalingConnectWssEndpointRequest
{
    const char * pEndpointWebsocketSecure;
    size_t endpointWebsocketSecureLength;
    char * pChannelArn;
    size_t channelArnLength;
    SignalingRole_t role;
    char * pClientId;
    size_t clientIdLength;
} SignalingConnectWssEndpointRequest_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure to send message to websocket secure endpoint.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis3.html,
 *        https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis4.html,
 *        https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis5.html and
 *        https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis6.html for more detail.
 */
typedef struct SignalingWssSendMessage
{
    SignalingTypeMessage_t messageType;
    const char * pRecipientClientId;
    size_t recipientClientIdLength;
    const char * pBase64EncodedMessage;
    size_t base64EncodedMessageLength;
    const char * pCorrelationId;
    size_t correlationIdLength;
    SignalingIceServerList_t iceServerList;
} SignalingWssSendMessage_t;

/**
 * @ingroup signaling_enum_types
 * @brief The status response structure in receive event message from websocket secure endpoint.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis-7.html for more detail.
 */
typedef struct SignalingWssStatusResponse
{
    const char * pCorrelationId;
    size_t correlationIdLength;
    const char * pErrorType;
    size_t errorTypeLength;
    const char * pStatusCode;
    size_t statusCodeLength;
    const char * pDescription;
    size_t descriptionLength;
} SignalingWssStatusResponse_t;

/**
 * @ingroup signaling_enum_types
 * @brief The event message structure from websocket secure endpoint.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis-7.html for more detail.
 */
typedef struct SignalingWssRecvMessages
{
    const char * pSenderClientId;
    size_t senderClientIdLength;
    SignalingTypeMessage_t messageType;
    const char * pBase64EncodedPayload;
    size_t base64EncodedPayloadLength;
    SignalingWssStatusResponse_t statusResponse;
    SignalingIceServerList_t iceServerList;
} SignalingWssRecvMessage_t;

/*-----------------------------------------------------------*/

#endif /* SIGNALING_DATA_TYPES_H */
