#ifndef SIGNALING_DATA_TYPES_H
#define SIGNALING_DATA_TYPES_H

/* Standard includes. */
#include <stdint.h>
#include <stddef.h>

/*-----------------------------------------------------------*/

/**
 * Default AWS region
 */
#define AWS_DEFAULT_REGION "us-west-2"

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

#define AWS_REGION_MAX_LENGTH ( 50 )
#define AWS_CONTROL_PLANE_URL_MAX_LENGTH ( 256 )
#define AWS_SIGNALING_CLIENT_ID_MAX_LENGTH ( 256 )

/**
 * Max ARN len in chars
 * https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DescribeSignalingChannel.html#API_DescribeSignalingChannel_RequestSyntax
 * https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_CreateStream.html#KinesisVideo-CreateStream-request-KmsKeyId
 */
#define AWS_MAX_ARN_LEN ( 1024 )
#define AWS_MAX_CHANNEL_NAME_LEN ( 256 )

#define AWS_ICE_SERVER_MAX_NUM ( 5 )
#define AWS_ICE_SERVER_MAX_URIS ( 4 )

#define AWS_MESSAGE_CHANNEL_TTL_SECONDS_BUFFER_MAX ( 5 )
#define AWS_MESSAGE_CHANNEL_TTL_SECONDS_MIN ( 5 )
#define AWS_MESSAGE_CHANNEL_TTL_SECONDS_MAX ( 120 )

#define AWS_MESSAGE_ICE_SERVER_TTL_SECONDS_BUFFER_MAX ( 7 )
#define AWS_MESSAGE_ICE_SERVER_TTL_SECONDS_MIN ( 30 )
#define AWS_MESSAGE_ICE_SERVER_TTL_SECONDS_MAX ( 86400 )

typedef enum SignalingResult
{
    SIGNALING_RESULT_OK,
    SIGNALING_RESULT_BASE = 0x52000000,
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
    SIGNALING_RESULT_PARSE_NEXT_LAYER,
} SignalingResult_t;

typedef enum SignalingChannelEndpointProtocol
{
    SIGNALING_ENDPOINT_PROTOCOL_NONE = 0,
    SIGNALING_ENDPOINT_PROTOCOL_WEBSOCKET_SECURE = 1,
    SIGNALING_ENDPOINT_PROTOCOL_HTTPS = 2,
    SIGNALING_ENDPOINT_PROTOCOL_WEBRTC = 4,
    SIGNALING_ENDPOINT_PROTOCOL_MAX = 0xFF,
} SignalingChannelEndpointProtocol_t;

/**
 * @brief Channel type
 */
typedef enum SignalingChannelType {
    SIGNALING_CHANNEL_TYPE_UNKNOWN,       //!< Channel type is unknown
    SIGNALING_CHANNEL_TYPE_SINGLE_MASTER, //!< Channel type is master
} SignalingChannelType_t;

typedef enum SignalingRole
{
    SIGNALING_ROLE_NONE = 0,
    SIGNALING_ROLE_MASTER,
    SIGNALING_ROLE_VIEWER,
} SignalingRole_t;

typedef enum SignalingMessageType
{
    SIGNALING_MESSAGE_TYPE_UNKNOWN = 0,
    SIGNALING_MESSAGE_TYPE_SDP_OFFER,
    SIGNALING_MESSAGE_TYPE_SDP_ANSWER,
    SIGNALING_MESSAGE_TYPE_ICE_CANDIDATE,
    SIGNALING_MESSAGE_TYPE_GO_AWAY,
    SIGNALING_MESSAGE_TYPE_RECONNECT_ICE_SERVER,
    SIGNALING_MESSAGE_TYPE_STATUS_RESPONSE,
} SignalingMessageType_t;

typedef struct SignalingChannelInfo
{
    const char * pChannelArn;
    size_t channelArnLength;
    const char * pChannelName;
    size_t channelNameLength;
    const char * pChannelStatus;
    size_t channelStatusLength;
    SignalingChannelType_t channelType;
    const char * pVersion;
    size_t versionLength;
    const char * pCreationTime;
    size_t creationTimeLength;
    uint32_t messageTtlSeconds;
} SignalingChannelInfo_t;

typedef struct SignalingContext
{
    char region[AWS_REGION_MAX_LENGTH];
    size_t regionLength;
    char controlPlaneUrl[AWS_CONTROL_PLANE_URL_MAX_LENGTH];
    size_t controlPlaneUrlLength;
    char channelName[AWS_MAX_CHANNEL_NAME_LEN];
    size_t channelNameLength;
} SignalingContext_t;

typedef struct SignalingRequest
{
    char *pUrl;
    size_t urlLength;
    char *pBody;
    size_t bodyLength;
} SignalingRequest_t;

/**
 * Tag declaration
 */
typedef struct SignalingTag {
    char * pName;
    size_t nameLength;
    char * pValue;
    size_t valueLength;
} SignalingTag_t;

typedef struct SignalingCreate {
    char * pRegion;
    size_t regionLength;
    char * pControlPlaneUrl;
    size_t controlPlaneUrlLength;
} SignalingCreate_t;

typedef struct SignalingCreateChannel {
    SignalingChannelInfo_t channelInfo;
    SignalingTag_t * pTags;
    size_t tagsCount;
} SignalingCreateChannel_t;

typedef SignalingCreateChannel_t SignalingCreateSignalingChannelRequest_t;
typedef SignalingCreateChannel_t SignalingCreateSignalingChannelResponse_t;

typedef struct SignalingDescribeSignalingChannelRequest
{
    char * pChannelName;
    size_t channelNameLength;
} SignalingDescribeSignalingChannelRequest_t;

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

typedef struct SignalingDescribeMediaStorageConfigRequest
{
    char * pChannelArn;
    size_t channelArnLength;
} SignalingDescribeMediaStorageConfigRequest_t;

typedef struct SignalingDescribeMediaStorageConfigResponse
{
    const char * pStatus;
    size_t statusLength;
    const char * pStreamArn;
    size_t streamArnLength;
} SignalingDescribeMediaStorageConfigResponse_t;

typedef struct SignalingIceServer
{
    const char * pPassword;
    size_t passwordLength;
    uint32_t messageTtlSeconds;
    const char * pUris[AWS_ICE_SERVER_MAX_URIS];
    size_t urisLength[AWS_ICE_SERVER_MAX_URIS];
    uint32_t urisNum;
    const char * pUserName;
    size_t userNameLength;
} SignalingIceServer_t;

typedef struct SignalingIceServerList
{
    SignalingIceServer_t iceServer[AWS_ICE_SERVER_MAX_NUM];
    uint32_t iceServerNum;
} SignalingIceServerList_t;

typedef SignalingIceServerList_t SignalingGetIceServerConfigResponse_t;

typedef struct SignalingGetSignalingChannelEndpointRequest
{
    char * pChannelArn;
    size_t channelArnLength;
    uint8_t protocolsBitsMap; /* support multiple propocols. */
    SignalingRole_t role;
} SignalingGetSignalingChannelEndpointRequest_t;

typedef struct SignalingGetSignalingChannelEndpointResponse
{
    const char * pEndpointWebsocketSecure;
    size_t endpointWebsocketSecureLength;
    const char * pEndpointHttps;
    size_t endpointHttpsLength;
    const char * pEndpointWebrtc;
    size_t endpointWebrtcLength;
} SignalingGetSignalingChannelEndpointResponse_t;

typedef struct SignalingGetIceServerConfigRequest
{
    char * pChannelArn;
    size_t channelArnLength;
    char * pEndpointHttps;
    size_t endpointHttpsLength;
    char * pClientId;
    size_t clientIdLength;
} SignalingGetIceServerConfigRequest_t;

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

typedef struct SignalingDeleteSignalingChannelRequest
{
    char * pChannelArn;
    size_t channelArnLength;
    char * pVersion;
    size_t versionLength;
} SignalingDeleteSignalingChannelRequest_t;

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

typedef struct SignalingWssSendMessage
{
    SignalingMessageType_t messageType;
    const char * pRecipientClientId;
    size_t recipientClientIdLength;
    const char * pBase64EncodedMessage;
    size_t base64EncodedMessageLength;
    const char * pCorrelationId;
    size_t correlationIdLength;
    SignalingIceServerList_t iceServerList;
} SignalingWssSendMessage_t;

/* Follow https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis-7.html
 * in structures SignalingWssStatusResponse_t and SignalingWssRecvMessage_t. */
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

typedef struct SignalingWssRecvMessages
{
    const char * pSenderClientId;
    size_t senderClientIdLength;
    SignalingMessageType_t messageType;
    const char * pBase64EncodedPayload;
    size_t base64EncodedPayloadLength;
    SignalingWssStatusResponse_t statusResponse;
    SignalingIceServerList_t iceServerList;
} SignalingWssRecvMessage_t;

/*-----------------------------------------------------------*/

#endif /* SIGNALING_DATA_TYPES_H */
