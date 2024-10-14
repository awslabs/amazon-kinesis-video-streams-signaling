## amazon-kinesis-video-streams-signaling

The goal of the Signaling library is to enable communication with the Amazon
Kinesis Video Signaling Service. Refer to
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
    - Ensure to authenticate and sign the constructed requests using the Signature
      Version 4 (SigV4) [authentication flow](https://docs.aws.amazon.com/AmazonS3/latest/API/sig-v4-authenticating-requests.html)
      before sending them.
2. Use the `Signaling_Parse*` APIs to parse the responses from the Signaling
   Service.
3. Use `Signaling_ConstructWssMessage` and `Signaling_ParseWssRecvMessage` APIs
   to communicate with the WSS endpoint.
    - Ensure to authenticate and sign the constructed messages using the
      Signature Version 4 (SigV4) [authentication flow](https://docs.aws.amazon.com/AmazonS3/latest/API/sig-v4-authenticating-requests.html)
      before sending them.
      
## Building Unit Tests

### Platform Prerequisites

- For running unit tests:
    - C99 compiler like gcc.
    - CMake 3.13.0 or later.
    - Ruby 2.0.0 or later (It is required for the CMock test framework that we
      use).
- For running the coverage target, gcov and lcov are required.


### Steps to Build Unit Tests

1. The following command in STEP 2 also ensures that the Submodules ( CMock and coreJSON ) are added.
2. Run the following command to generate Makefiles:

    ```sh
    cmake -S test/unit-test -B build/ -G "Unix Makefiles" \
     -DCMAKE_BUILD_TYPE=Debug \
     -DBUILD_CLONE_SUBMODULES=ON \
     -DCMAKE_C_FLAGS='--coverage -Wall -Wextra -Werror -DNDEBUG'
    ```

### Steps to Generate Code Coverage Report and Run Unit Tests

1. Run Unit Tests in [Steps to Build Unit Tests](#steps-to-build-unit-tests).
2. Generate coverage report in the `build/coverage` folder:

    ```
    cd build && make coverage
    ```

### Script to Run Unit Test and Generate Code Coverage Report

```sh
cmake -S test/unit-test -B build/ -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug -DBUILD_CLONE_SUBMODULES=ON -DCMAKE_C_FLAGS='--coverage -Wall -Wextra -Werror -DNDEBUG -DLIBRARY_LOG_LEVEL=LOG_DEBUG'
cd build && make coverage
```
## License

This project is licensed under the Apache-2.0 License.
