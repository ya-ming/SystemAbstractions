#ifndef SYSTEM_ABSTRACTIONS_NETWORK_CONNECTION_IMPL_HPP
#define SYSTEM_ABSTRACTIONS_NETWORK_CONNECTION_IMPL_HPP

/**
 * @file NetworkConnectionImpl.hpp
 *
 * This module declares the SystemAbstractions::NetworkConnectionImpl
 * structure.
 *
 * Copyright (c) 2016 by Richard Walters
 */

#include <SystemAbstractions/DiagnosticsSender.hpp>
#include <SystemAbstractions/NetworkConnection.hpp>

#include <memory>
#include <stdint.h>
#include <vector>

namespace SystemAbstractions {

    /**
     * This structure contains the private properties of the
     * NetworkConnection class.
     */
    struct NetworkConnection::Impl {
        // Properties

        /**
         * This contains any platform-specific private properties
         * of the class.
         */
        std::unique_ptr< Platform > platform;

        /**
         * This is the callback issued whenever more data
         * is received from the peer of the connection.
         */
        MessageReceivedDelegate messageReceivedDelegate;

        /**
         * This is the callback issued whenever the connection is broken.
         */
        BrokenDelegate brokenDelegate;

        /**
         * This is the IPv4 address of the peer, if there is a connection
         * established.
         */
        uint32_t peerAddress = 0;

        /**
         * This is the port number of the peer, if there is a connection
         * established.
         */
        uint16_t peerPort = 0;

        /**
         * This is a helper object used to publish diagnostic messages.
         */
        DiagnosticsSender diagnosticsSender;

        // Lifecycle Management

        ~Impl() noexcept;
        Impl(const Impl&) noexcept = delete;
        Impl(Impl&&) noexcept = delete;
        Impl& operator=(const Impl&) noexcept = delete;
        Impl& operator=(Impl&&) noexcept = delete;

        // Methods

        /**
         * This is the instance constructor.
         */
        Impl();

        /**
         * This method attempts to establish a connection to the remote peer.
         *
         * @return
         *     An indication of whether or not the connection was successfully
         *     established is returned.
         */
        bool Connect();

        /**
         * This method starts message processing on the connection,
         * listening for incoming messages and sending outgoing messages.
         *
         * @return
         *     An indication of whether or not the method was
         *     successful is returned.
         */
        bool Process();

        /**
         * This is the main function called for the worker thread
         * of the object.  It does all the actual sending and
         * receiving of messages, using the underlying operating
         * system network handle.
         */
        void Processor();

        /**
         * This method returns an indication of whether or not there
         * is a connection currently established with a peer.
         *
         * @return
         *     An indication of whether or not there
         *     is a connection currently established with a peer
         *     is returned.
         */
        bool IsConnected() const;

        /**
         * This method appends the given data to the queue of data
         * currently being sent to the peer.  The actual sending
         * is performed by the processor worker thread.
         *
         * @param[in] message
         *     This holds the data to be appended to the send queue.
         */
        void SendMessage(const std::vector< uint8_t >& message);

        /**
         * This method immediately breaks the connection to the peer.
         */
        void Close(bool stopProcessing);
    };

}

#endif /* SYSTEM_ABSTRACTIONS_NETWORK_CONNECTION_IMPL_HPP */
