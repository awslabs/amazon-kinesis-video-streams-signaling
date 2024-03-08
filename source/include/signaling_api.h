#ifndef SIGNALING_API_H
#define SIGNALING_API_H

/* Standard includes. */
#include "signaling_data_types.h"

/*-----------------------------------------------------------*/

SignalingResult_t Signaling_createSignaling( SignalingContext_t *pCtx, SignalingCreate_t *pCreate );

SignalingResult_t Signaling_constructDescribeSignalingChannelRequest( SignalingContext_t *pCtx, SignalingDescribeSignalingChannelRequest_t * pDescribeSignalingChannelRequest, SignalingRequest_t *pRequestBuffer );

SignalingResult_t Signaling_parseDescribeSignalingChannelResponse( SignalingContext_t *pCtx, char * pMessage, size_t messageLength, SignalingDescribeSignalingChannelResponse_t *pDescribeSignalingChannelResponse );

SignalingResult_t Signaling_constructDescribeMediaStorageConfigRequest( SignalingContext_t *pCtx, SignalingDescribeMediaStorageConfigRequest_t * pDescribeMediaStorageConfigRequest, SignalingRequest_t *pRequestBuffer );

SignalingResult_t Signaling_parseDescribeMediaStorageConfigResponse( SignalingContext_t *pCtx, char * pMessage, size_t messageLength, SignalingDescribeMediaStorageConfigResponse_t *pDescribeMediaStorageConfigResponse );

SignalingResult_t Signaling_constructCreateSignalingChannelRequest( SignalingContext_t *pCtx, SignalingCreateSignalingChannelRequest_t * pCreateSignalingChannelRequest, SignalingRequest_t *pRequestBuffer );

SignalingResult_t Signaling_parseCreateSignalingChannelResponse( SignalingContext_t *pCtx, char * pMessage, size_t messageLength, SignalingCreateSignalingChannelResponse_t *pCreateSignalingChannelResponse );

SignalingResult_t Signaling_constructGetSignalingChannelEndpointRequest( SignalingContext_t *pCtx, SignalingGetSignalingChannelEndpointRequest_t * pGetSignalingChannelEndpointRequest, SignalingRequest_t *pRequestBuffer );

SignalingResult_t Signaling_parseGetSignalingChannelEndpointResponse( SignalingContext_t *pCtx, char * pMessage, size_t messageLength, SignalingGetSignalingChannelEndpointResponse_t * pGetSignalingChannelEndpointResponse );

SignalingResult_t Signaling_constructGetIceServerConfigRequest( SignalingContext_t *pCtx, SignalingGetIceServerConfigRequest_t * pGetIceServerConfigReqeust, SignalingRequest_t *pRequestBuffer);

SignalingResult_t Signaling_parseGetIceServerConfigResponse( SignalingContext_t *pCtx, char * pMessage, size_t messageLength, SignalingGetIceServerConfigResponse_t *pGetIceConfigResponse );

SignalingResult_t Signaling_constuctJoinStorageSessionRequest( SignalingContext_t *pCtx, SignalingJoinStorageSessionRequest_t * pJoinStorageSessionRequest, SignalingRequest_t *pRequestBuffer );

SignalingResult_t Signaling_constructDeleteSignalingChannelRequest( SignalingContext_t *pCtx, SignalingDeleteSignalingChannelRequest_t * pDeleteSignalingChannelRequest, SignalingRequest_t *pRequestBuffer );

SignalingResult_t Signaling_constructConnectWssEndpointRequest( SignalingContext_t *pCtx, SignalingConnectWssEndpointRequest_t * pConnectWssEndpointRequest, SignalingRequest_t *pRequestBuffer );

SignalingResult_t Signaling_constructWssMessage( SignalingWssSendMessage_t * pWssSendMessage, char * pBuffer, size_t * pBufferLength );

SignalingResult_t Signaling_parseWssRecvMessage( char * pMessage, size_t messageLength, SignalingWssRecvMessage_t * pWssRecvMessage );

/*-----------------------------------------------------------*/

#endif /* SIGNALING_API_H */
