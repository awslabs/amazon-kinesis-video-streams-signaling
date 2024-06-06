## amazon-kinesis-video-streams-signaling

The goal of the Signaling library is to enable control plane communication
with the Amazon Kinesis Video Streams (KVS) service. Refer to
[AWS KVS API Reference](https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_Reference.html)
and [WebRTC Websocket APIs](https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/kvswebrtc-websocket-apis.html)
for more details.

## What is Signaling?

The Amazon Kinesis Video Signaling Service facilitates peer-to-peer
communication by providing signaling channels that enable applications to
discover, establish, control, and terminate connections through the exchange of
signaling messages. This library provides APIs to construct requests to send to
the Signaling Service and to parse responses from the Signaling Service.

- Note that this library has a dependency on [coreJSON](https://github.com/FreeRTOS/coreJSON).

## Using the library

1. Use the `Signaling_Construct*` APIs to construct requests to send to the
   Signaling Service.
    - Ensure authenticate to sign the constructed requests using the Signature
      Version 4 (SigV4) [authentication flow](https://docs.aws.amazon.com/AmazonS3/latest/API/sig-v4-authenticating-requests.html)
      before sending them.
3. Use the `Signaling_Parse*` APIs to parse the responses from the Signaling
   Service.
4. Use `Signaling_ConstructWssMessage` and `Signaling_ParseWssRecvMessage` APIs
   to communicate with the WSS endpoint.
    - Ensure to authenticate and sign the constructed messages using the
      Signature Version 4 (SigV4) [authentication flow](https://docs.aws.amazon.com/AmazonS3/latest/API/sig-v4-authenticating-requests.html)
      before sending them.

## License

This project is licensed under the Apache-2.0 License.
