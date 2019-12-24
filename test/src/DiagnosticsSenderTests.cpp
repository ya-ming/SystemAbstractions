/**
 * @file DiagnosticsSenderTests.cpp
 *
 * This module contains the unit tests of the
 * SystemAbstractions::DiagnosticsSender class.
 */

#include <gtest/gtest.h>
#include <SystemAbstractions/DiagnosticsSender.hpp>
#include <vector>

/**
 * This is used to store a message received from a diagnostics sender.
 */
struct ReceivedMessage {
    // Properties

    /**
     * This identifies the origin of the diagnostic information.
     */
    std::string senderName;

    /**
     * Importance of the message
     */
    size_t level;

    /**
     * This is the content of the message.
     */
    std::string message;

    // Methods

    /**
     * This constructor is used to initialize all the fields
     * of the structure.
     *
     * @param[in] newSenderName
     *     This identifies the origin of the diagnostic information.
     *
     * @param[in] newLevel
     *     This is used to filter out less-important information.
     *     The level is higher the more important the information is.
     *
     * @param[in] newMessage
     *     This is the content of the message.
     */
    ReceivedMessage(std::string newSenderName, size_t newLevel, std::string newMessage)
        : senderName(newSenderName), level(newLevel), message(newMessage)
    {

    }

    /**
     * This is the equality operator for the class.
     *
     * @param[in] other
     *     This is the other instance to which to compare this instance.
     *
     * @return
     *     An indication of whether or not the two instances are equal
     *     is returned.
     */
    bool operator==(const ReceivedMessage& other) const noexcept {
        return (senderName == other.senderName)
            && (level == other.level)
            && (message == other.message);
    }
};

/**
 * This is used to capture diagnostic messages sent
 * by the unit under test.
 */
struct Subscriber
    :public SystemAbstractions::DiagnosticsReceiver
{
    // Properties

    /**
     * These are the messages received by this subscriber.
     */
    std::vector<ReceivedMessage> receivedMessages;

    // SystemAbstractions::DiagnosticsReceiver

    virtual void ReceiveDiagnosticInformation(
        std::string senderName,
        size_t level,
        std::string message
    ) override {
        receivedMessages.emplace_back(senderName, level, message);
    }
};

TEST(DiagnosticsSenderTests, BasicSubscriptionAndTransmission) {
    SystemAbstractions::DiagnosticsSender sender("Joe");
    sender.SendDiagnosticInformationString(100, "Very important message nobody will hear; FeelsBadMan");
    Subscriber subscriber;

    sender.SubscribeToDiagnostics(&subscriber, 5);
    ASSERT_EQ(5, sender.GetMinLevel());

    sender.SendDiagnosticInformationString(10, "PogChamp");
    sender.SendDiagnosticInformationString(3, "Did you hear that?");
    sender.PushContext("spam");

    sender.SendDiagnosticInformationString(4, "Level 4 whisper...");
    sender.SendDiagnosticInformationString(5, "Level 5, can you dig it?");
    sender.PopContext();

    sender.SendDiagnosticInformationString(6, "Level 6 FOR THE WIN");
    sender.UnsubscribeFromDiagnostics(&subscriber);
    sender.SendDiagnosticInformationString(5, "Are you still there?");

    ASSERT_EQ(
        subscriber.receivedMessages,
        (std::vector<ReceivedMessage> {
            {"Joe", 10, "PogChamp"},
            { "Joe", 5, "spam: Level 5, can you dig it?" },
            { "Joe", 6, "Level 6 FOR THE WIN" }
    })
    );
}

TEST(DiagnosticsSenderTests, FormattedMessage) {
    SystemAbstractions::DiagnosticsSender sender("Joe");
    Subscriber subscriber;
    sender.SubscribeToDiagnostics(&subscriber);
    sender.SendDiagnosticInformationFormatted(0, "The answer is %d.", 42);
    ASSERT_EQ(
        subscriber.receivedMessages,
        (std::vector<ReceivedMessage> {
            {"Joe", 0, "The answer is 42."},
    })
    );
}
