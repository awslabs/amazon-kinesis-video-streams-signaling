#ifndef SIGNALING_CONFIG_DEFAULTS_H
#define SIGNALING_CONFIG_DEFAULTS_H

/* Signaling includes. */
#ifndef SIGNALING_DO_NOT_USE_CUSTOM_CONFIG
/* Include custom config file before other headers. */
    #include "signaling_config.h"
#endif

/**
 * @brief Default AWS region
 */
#ifndef SIGNALING_AWS_DEFAULT_REGION
    #define SIGNALING_AWS_DEFAULT_REGION "us-west-2"
#endif

/**
 * @brief AWS region buffer size.
 */
#ifndef SIGNALING_AWS_REGION_MAX_LENGTH
    #define SIGNALING_AWS_REGION_MAX_LENGTH ( 50 )
#endif

/**
 * @brief AWS control plane URL buffer size.
 */
#ifndef SIGNALING_AWS_CONTROL_PLANE_URL_MAX_LENGTH
    #define SIGNALING_AWS_CONTROL_PLANE_URL_MAX_LENGTH ( 256 )
#endif

/**
 * @brief AWS signaling client ID buffer size.
 */
#ifndef SIGNALING_AWS_CLIENT_ID_MAX_LENGTH
    #define SIGNALING_AWS_CLIENT_ID_MAX_LENGTH ( 256 )
#endif

/**
 * @brief Max ARN len in chars
 *        Refer https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_DescribeSignalingChannel.html#API_DescribeSignalingChannel_RequestSyntax for details.
 */
#ifndef SIGNALING_AWS_MAX_ARN_LEN
    #define SIGNALING_AWS_MAX_ARN_LEN ( 1024 )
#endif

/**
 * @brief Max channel name len in chars
 */
#ifndef SIGNALING_AWS_MAX_CHANNEL_NAME_LEN
    #define SIGNALING_AWS_MAX_CHANNEL_NAME_LEN ( 256 )
#endif

/**
 * @brief Maximum count of ICE servers.
 */
#ifndef SIGNALING_AWS_ICE_SERVER_MAX_NUM
    #define SIGNALING_AWS_ICE_SERVER_MAX_NUM ( 5 )
#endif

/**
 * @brief Maximum count of URIs in single ICE server configuration.
 */
#ifndef SIGNALING_AWS_ICE_SERVER_MAX_URIS
    #define SIGNALING_AWS_ICE_SERVER_MAX_URIS ( 4 )
#endif

#endif /* SIGNALING_CONFIG_DEFAULTS_H */
