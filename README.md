## amazon-kinesis-video-streams-signaling

The goal of the Signaling library is provide functionalities of control plane
communication with AWS KVS services. Refer to [AWS KVS API Reference](https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_Reference.html) for more detail.

## What is Signaling?

The AWS KVS WebRTC Signaling Service facilitates peer-to-peer communication by providing signaling channels that enable applications to discover, establish, control, and terminate connections through the exchange of signaling messages. It now offers a channel that allows for a single master and multiple viewers to communicate via the AWS cloud service. This library provides useful APIs to construct and parse messages to and from the cloud services.

- Note that this library has a dependency on [coreJSON](https://github.com/FreeRTOS/coreJSON).

## Using the library

For a comprehensive understanding of the functionality and purpose of each API, please refer to the [AWS KVS API Reference](https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/API_Reference.html).

1. Initiate the signaling process by invoking the `Signaling_Init` function, which initiates the creation of a Signaling instance.
2. Utilize the `Signaling_construct*` series APIs, providing the relevant information to format messages for communication with the cloud service.
    - Prior to transmitting these messages to the cloud, authenticate and sign them using the Signature Version 4 (SigV4) [authentication flow](https://docs.aws.amazon.com/AmazonS3/latest/API/sig-v4-authenticating-requests.html).
3. Utilize the `Signaling_parse*` series APIs, supplying the necessary structure to parse messages received from the cloud service.
4. When communicating with the WebSocket endpoint, utilize the `Signaling_constructWssMessage` and `Signaling_parseWssRecvMessage` functions.
    - Authenticate and sign the constructed messages using the Signature Version 4 (SigV4) [authentication flow](https://docs.aws.amazon.com/AmazonS3/latest/API/sig-v4-authenticating-requests.html) before transmitting them to the cloud service.

## License

This project is licensed under the Apache-2.0 License.
