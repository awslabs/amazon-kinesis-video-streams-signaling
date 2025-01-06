#ifndef SIGNALING_DATA_TYPES_H
#define SIGNALING_DATA_TYPES_H

/* Standard includes. */
#include <stdint.h>
#include <stddef.h>

/*-----------------------------------------------------------*/

/**
 * Maximum number of URIs for an ICE server.
 */
#define SIGNALING_ICE_SERVER_MAX_URIS ( 4 )

/**
 * Maximum length of a channel name.
 */
#define SIGNALING_CHANNEL_NAME_MAX_LEN ( 256 )

/**
 * Maximum length of a Access Key.
 */
#define ACCESS_KEY_MAX_LEN ( 128 )

/**
 * Maximum length of a Secret Access Key.
 */
#define SECRET_ACCESS_KEY_MAX_LEN ( 128 )

/**
 * Maximum length of a Session Token.
 */
#define SESSION_TOKEN_MAX_LEN ( 2048 )

/**
 * Maximum length of a Expiration.
 */
#define EXPIRATION_MAX_LEN ( 128 )

/*-----------------------------------------------------------*/

/**
 * @brief Constants for signaling channel TTL.
 *        Refer https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_SingleMasterConfiguration.html#KinesisVideo-Type-SingleMasterConfiguration-MessageTtlSeconds for details.
 */
#define SIGNALING_CHANNEL_TTL_SECONDS_BUFFER_MAX    ( 5 ) /* Maximum length of buffer needed to store TTL. */
#define SIGNALING_CHANNEL_TTL_SECONDS_MIN           ( 5 )
#define SIGNALING_CHANNEL_TTL_SECONDS_MAX           ( 120 )

/**
 * @brief Constants for ICE server TTL.
 *        Refer https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_signaling_IceServer.html for details.
 */
#define SIGNALING_ICE_SERVER_TTL_SECONDS_BUFFER_MAX ( 7 ) /* Maximum length of buffer needed to store TTL. */
#define SIGNALING_ICE_SERVER_TTL_SECONDS_MIN        ( 30 )
#define SIGNALING_ICE_SERVER_TTL_SECONDS_MAX        ( 86400 )

/*-----------------------------------------------------------*/

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
    SIGNALING_RESULT_UNEXPECTED_RESPONSE,
    SIGNALING_RESULT_INVALID_TTL,
    SIGNALING_RESULT_INVALID_ENDPOINT,
    SIGNALING_RESULT_INVALID_PROTOCOL,
    SIGNALING_RESULT_INVALID_CHANNEL_NAME,
    SIGNALING_RESULT_INVALID_CHANNEL_TYPE,
    SIGNALING_RESULT_INVALID_ICE_SERVER_COUNT,
    SIGNALING_RESULT_INVALID_ICE_SERVER_URIS_COUNT,
    SIGNALING_RESULT_INVALID_STATUS_RESPONSE,
    SIGNALING_RESULT_REGION_LENGTH_TOO_LARGE,
    SIGNALING_RESULT_ACCESS_KEY_LENGTH_TOO_LARGE,
    SIGNALING_RESULT_SECRET_ACCESS_KEY_LENGTH_TOO_LARGE,
    SIGNALING_RESULT_SESSION_TOKEN_LENGTH_TOO_LARGE,
    SIGNALING_RESULT_EXPIRATION_LENGTH_TOO_LARGE,
} SignalingResult_t;

/**
 * @ingroup signaling_enum_types
 * @brief Protocol type of endpoints while parsing get signaling channel endpoint response.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_GetSignalingChannelEndpoint.html for more detail.
 */
typedef enum SignalingProtocol
{
    SIGNALING_PROTOCOL_NONE = 0,
    SIGNALING_PROTOCOL_WEBSOCKET_SECURE = 1,
    SIGNALING_PROTOCOL_HTTPS = 2,
    SIGNALING_PROTOCOL_WEBRTC = 4,
    SIGNALING_PROTOCOL_MAX = 0xFF,
} SignalingProtocol_t;

/**
 * @ingroup signaling_enum_types
 * @brief Type of signaling channel.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_ChannelInfo.html#KinesisVideo-Type-ChannelInfo-ChannelType for more detail.
 */
/* We cannot name it SignalingChannelType_t in order to avoid naming conflict
 * with a data type in the existing KVS SDK. */
typedef enum SignalingTypeChannel
{
    SIGNALING_TYPE_CHANNEL_UNKNOWN,
    SIGNALING_TYPE_CHANNEL_SINGLE_MASTER,
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
/* We cannot name it SignalingMessageType_t in order to avoid naming conflict
 * with a data type in the existing KVS SDK. */
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

/*-----------------------------------------------------------*/

/**
 * @ingroup signaling_enum_types
 * @brief Basic format of the signaling request.
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
 * @brief Basic format of the AWS region name.
 */
typedef struct SignalingAwsRegion
{
    const char * pAwsRegion;
    size_t awsRegionLength;
} SignalingAwsRegion_t;

/**
 * @ingroup signaling_enum_types
 * @brief Basic format of the channel name.
 */
typedef struct SignalingChannelName
{
    const char * pChannelName;
    size_t channelNameLength;
} SignalingChannelName_t;

/**
 * @ingroup signaling_enum_types
 * @brief Basic format of the signaling channel ARN.
 */
typedef struct SignalingChannelArn
{
    const char * pChannelArn;
    size_t channelArnLength;
} SignalingChannelArn_t;

/**
 * @ingroup signaling_enum_types
 * @brief A structure to represent credentials used to accesss KVS.
 */
typedef struct SignalingCredential
{
    const char * pAccessKeyId;
    size_t accessKeyIdLength;

    const char * pSecretAccessKey;
    size_t secretAccessKeyLength;

    const char * pSessionToken;
    size_t sessionTokenLength;

    const char * pExpiration;
    size_t expirationLength;
} SignalingCredential_t;

/**
 * @ingroup signaling_enum_types
 * @brief A structure that encapsulates a signaling channel's metadata and properties.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_ChannelInfo.html for more detail.
 */
typedef struct SignalingChannelInfo
{
    SignalingChannelArn_t channelArn;
    SignalingChannelName_t channelName;
    const char * pChannelStatus;
    size_t channelStatusLength;
    SignalingTypeChannel_t channelType;
    const char * pVersion;
    size_t versionLength;
    const char * pCreationTime;
    size_t creationTimeLength;
    uint32_t messageTtlSeconds;
} SignalingChannelInfo_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of DescribeMediaStorageConfiguration response.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DescribeMediaStorageConfiguration.html for more detail.
 */
typedef struct SignalingMediaStorageConfig
{
    const char * pStatus;
    size_t statusLength;
    const char * pStreamArn;
    size_t streamArnLength;
} SignalingMediaStorageConfig_t;

/**
 * @ingroup signaling_enum_types
 * @brief Tags to create signaling channel.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_Tag.html for more detail.
 */
typedef struct SignalingTag
{
    char * pName;
    size_t nameLength;
    char * pValue;
    size_t valueLength;
} SignalingTag_t;

/**
 * @ingroup signaling_enum_types
 * @brief Basic endpoint structure.
 */
typedef struct SignalingChannelEndpoint
{
    const char * pEndpoint;
    size_t endpointLength;
} SignalingChannelEndpoint_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of GetSignalingChannelEndpoint response.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_GetSignalingChannelEndpoint.html for more detail.
 */
typedef struct SignalingChannelEndpoints
{
    SignalingChannelEndpoint_t wssEndpoint;
    SignalingChannelEndpoint_t httpsEndpoint;
    SignalingChannelEndpoint_t webrtcEndpoint;
} SignalingChannelEndpoints_t;

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
    const char * pUris[ SIGNALING_ICE_SERVER_MAX_URIS ];
    size_t urisLength[ SIGNALING_ICE_SERVER_MAX_URIS ];
    uint32_t urisNum;
    const char * pUserName;
    size_t userNameLength;
} SignalingIceServer_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of CreateSignalingChannel request.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_CreateSignalingChannel.html for more detail.
 */
typedef struct CreateSignalingChannelRequestInfo
{
    SignalingChannelName_t channelName;
    SignalingTypeChannel_t channelType;
    uint32_t messageTtlSeconds;
    SignalingTag_t * pTags;
    size_t numTags;
} CreateSignalingChannelRequestInfo_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of GetSignalingChannelEndpoint request.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_GetSignalingChannelEndpoint.html for more detail.
 */
typedef struct GetSignalingChannelEndpointRequestInfo
{
    SignalingChannelArn_t channelArn;
    uint8_t protocols; /* Bitwise OR of SignalingProtocol_t values. */
    SignalingRole_t role;
} GetSignalingChannelEndpointRequestInfo_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of GetIceServerConfig request.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_signaling_GetIceServerConfig.html for more detail.
 */
typedef struct GetIceServerConfigRequestInfo
{
    SignalingChannelArn_t channelArn;
    char * pClientId;
    size_t clientIdLength;
} GetIceServerConfigRequestInfo_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of JoinStorageSession request.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_webrtc_JoinStorageSession.html for more detail.
 */
typedef struct JoinStorageSessionRequestInfo
{
    SignalingChannelArn_t channelArn;
    SignalingRole_t role;
    char * pClientId;
    size_t clientIdLength;
} JoinStorageSessionRequestInfo_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of DeleteSignalingChannel request.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DeleteSignalingChannel.html for more detail.
 */
typedef struct DeleteSignalingChannelRequestInfo
{
    SignalingChannelArn_t channelArn;
    char * pVersion;
    size_t versionLength;
} DeleteSignalingChannelRequestInfo_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure of GetSignalingChannelEndpoint request.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_GetSignalingChannelEndpoint.html for more detail.
 */
typedef struct ConnectWssEndpointRequestInfo
{
    SignalingChannelArn_t channelArn;
    SignalingRole_t role;
    const char * pClientId;
    size_t clientIdLength;
} ConnectWssEndpointRequestInfo_t;

/**
 * @ingroup signaling_enum_types
 * @brief The structure to send message to websocket secure endpoint.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis3.html,
 *        https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis4.html,
 *        https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis5.html and
 *        https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis6.html for more detail.
 */
typedef struct WssSendMessage
{
    SignalingTypeMessage_t messageType;
    const char * pRecipientClientId;
    size_t recipientClientIdLength;
    const char * pBase64EncodedMessage;
    size_t base64EncodedMessageLength;
    const char * pCorrelationId;
    size_t correlationIdLength;
} WssSendMessage_t;

/**
 * @ingroup signaling_enum_types
 * @brief The status response structure in receive event message from websocket secure endpoint.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis-7.html for more detail.
 */
typedef struct WssStatusResponse
{
    const char * pCorrelationId;
    size_t correlationIdLength;
    const char * pErrorType;
    size_t errorTypeLength;
    const char * pStatusCode;
    size_t statusCodeLength;
    const char * pDescription;
    size_t descriptionLength;
} WssStatusResponse_t;

/**
 * @ingroup signaling_enum_types
 * @brief The event message structure from websocket secure endpoint. Note that when received message is a SDP offer, it might append ICE servers
 *        configurations in the message. So user can update the server configuration by this information.
 *        Refer to https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis-7.html for more detail.
 */
typedef struct WssRecvMessage
{
    const char * pSenderClientId;
    size_t senderClientIdLength;
    SignalingTypeMessage_t messageType;
    const char * pBase64EncodedPayload;
    size_t base64EncodedPayloadLength;
    WssStatusResponse_t statusResponse;
} WssRecvMessage_t;

/*-----------------------------------------------------------*/

#endif /* SIGNALING_DATA_TYPES_H */
