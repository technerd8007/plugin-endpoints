//
// Created by Aidan on 3/11/2021.
//

// Howdy! This file contains unverified endpoints so they may need touching up.
// Sorry for the mess, I just don't have the time to verify everything by hand,
// especially with the volatile nature of a live service like Discord. If
// something doesn't work come swing by #🔚endpoints on the Discord++ server and
// someone'll help you out! If the endpoints work fine swing by that same
// channel with proof of credit for the @Endpoint Verifier role!

#ifndef ENDPOINT_BREAKOUTS
#error This header should only be included in plugin-endpoints.hh
#endif

// https://discord.com/developers/docs/resources/channel#get-channel
// TODO unverified
#define Bot PluginEndpoints
#define Parent Call
#define Class GetChannelCall
#define function getChannel
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    STATIC_FIELD(std::string, method, "GET")                                   \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Get Channel needs an ID");
    return std::make_shared<const std::string>("/channels/" +
                                               std::to_string(*_channel_id));
}
#include <discordpp/macros/defineCallClose.hh>

enum ChannelType {
    // a text channel within a server
    GUILD_TEXT = 0,
    // a direct message between users
    DM = 1,
    // a voice channel within a server
    GUILD_VOICE = 2,
    // a direct message between multiple users
    GROUP_DM = 3,
    // an organizational category that contains up to 50 channels
    GUILD_CATEGORY = 4,
    // a channel that users can follow and crosspost into their own server
    GUILD_NEWS = 5,
    // a channel in which game developers can sell their game on Discord
    GUILD_STORE = 6
};

// https://discord.com/developers/docs/resources/channel#modify-channel
// TODO unverified
#define Bot PluginEndpoints
#define Parent JsonCall
#define Class ModifyChannelCall
#define function modifyChannel
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(std::string, name, USEDBY(payload))                              \
    NEW_FIELD(int, channel_type, USEDBY(payload))                              \
    NEW_FIELD(int, position, USEDBY(payload))                                  \
    NEW_FIELD(std::string, topic, USEDBY(payload))                             \
    NEW_FIELD(bool, nsfw, USEDBY(payload))                                     \
    NEW_FIELD(int, rate_limit_per_user, USEDBY(payload))                       \
    NEW_FIELD(int, bitrate, USEDBY(payload))                                   \
    NEW_FIELD(int, user_limit, USEDBY(payload))                                \
    NEW_FIELD(std::vector<json>, permission_overwrites, USEDBY(payload))       \
    NEW_FIELD(snowflake, parent_id, USEDBY(payload))                           \
    HIDE_FIELD(payload)                                                        \
    STATIC_FIELD(std::string, method, "PATCH")                                 \
    HIDE_FIELD(target)                                                         \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id) {
        throw std::logic_error("Modify Channel needs an ID");
    }
    return std::make_shared<const std::string>("/channels/" +
                                               std::to_string(*_channel_id));
}
sptr<const json> render_payload() override {
    json out;

    out["name"] = *_name;

    if (_channel_type)
        out["type"] = *_channel_type;

    if (_position)
        out["position"] = *_position;

    if (_topic)
        out["topic"] = *_topic;

    if (_nsfw)
        out["nsfw"] = *_nsfw;

    if (_rate_limit_per_user)
        out["rate_limit_per_user"] = *_rate_limit_per_user;

    if (_bitrate)
        out["bitrate"] = *_bitrate;

    if (_user_limit)
        out["user_limit"] = *_user_limit;

    if (_permission_overwrites)
        out["permission_overwrites"] = *_permission_overwrites;

    if (_parent_id)
        out["parent_id"] = std::to_string(*_parent_id);

    return std::make_shared<const json>(std::move(out));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#deleteclose-channel
// TODO unverified
#define Bot PluginEndpoints
#define Parent Call
#define Class DeleteChannelCall
#define function deleteChannel, closeChannel
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    STATIC_FIELD(std::string, method, "DELETE")                                \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Delete/Close Channel needs an ID");
    return std::make_shared<const std::string>("/channels/" +
                                               std::to_string(*_channel_id));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#get-channel-messages
// TODO unverified
#define Bot PluginEndpoints
#define Parent Call
#define Class GetChannelMessagesCall
#define function getChannelMessages
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(snowflake, around, USEDBY(target))                               \
    NEW_FIELD(snowflake, before, USEDBY(target))                               \
    NEW_FIELD(snowflake, after, USEDBY(target))                                \
    NEW_FIELD(int, limit, USEDBY(target))                                      \
    STATIC_FIELD(std::string, method, "GET")                                   \
    HIDE_FIELD(target)                                                         \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id) {
        throw std::logic_error("Get Channel Messages needs an ID");
    }
    std::string out =
        fmt::format("/channels/{}/messages", std::to_string(*_channel_id));
    bool first = true;
    if (_around) {
        out += fmt::format("{}around={}", first ? "?" : "&", *_around);
        first = false;
    }
    if (_before) {
        out += fmt::format("{}before={}", first ? "?" : "&", *_before);
        first = false;
    }
    if (_after) {
        out += fmt::format("{}after={}", first ? "?" : "&", *_after);
        first = false;
    }
    if (_limit) {
        out += fmt::format("{}limit={}", first ? "?" : "&", *_limit);
        first = false;
    }
    return std::make_shared<const std::string>(std::move(out));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#get-channel
// TODO unverified
#define Bot PluginEndpoints
#define Parent Call
#define Class GetChannelMessageCall
#define function getChannelMessage
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(snowflake, message_id, USEDBY(target))                           \
    STATIC_FIELD(std::string, method, "GET")                                   \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Get Channel Message needs a Channel ID");
    if (!_message_id)
        throw std::logic_error("Get Channel Message needs a Message ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/messages/" +
        std::to_string(*_message_id));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#create-message
// UndarkAido/Aido#8614 verified channel_id, content, filename, filetype, file
// Westlanderz/SenpaiR6#1717 verified embed
// Deathwillcome800#0950 replaced embed with embeds
// TODO nonce, tts, allowed_mentions, and message_reference are unverified
#define Bot PluginEndpoints
#define Parent FileCall
#define Class CreateMessageCall
#define function createMessage
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(std::string, content, USEDBY(payload))                           \
    NEW_FIELD(Nonce, nonce, USEDBY(payload))                                   \
    NEW_FIELD(bool, tts, USEDBY(payload))                                      \
    NEW_FIELD(std::vector<json>, embeds, USEDBY(payload))                                    \
    NEW_FIELD(json, allowed_mentions, USEDBY(payload))                         \
    NEW_FIELD(json, message_reference, USEDBY(payload))                        \
    FORWARD_FIELD(std::string, filename, )                                     \
    FORWARD_FIELD(std::string, filetype, )                                     \
    FORWARD_FIELD(std::string, file, )                                         \
    FORWARD_FIELD(json, payload, )                                             \
    FORWARD_FIELD(std::string, target, )                                       \
    FORWARD_FIELD(handleWrite, onWrite, ) FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id) {
        throw std::logic_error("Create Message needs an ID");
    }
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/messages");
}
sptr<const json> render_payload() override {
    json out;

    if (_content)
        out["content"] = *_content;

    if (_nonce)
        out["nonce"] = *_nonce;

    if (_tts)
        out["tts"] = *_tts;

    if (_embeds)
        out["embeds"] = *_embeds;

    if (_allowed_mentions)
        out["allowed_mentions"] = *_allowed_mentions;

    if (_message_reference)
        out["message_reference"] = *_message_reference;

    return std::make_shared<const json>(std::move(out));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#crosspost-message
// TODO unverified
#define Bot PluginEndpoints
#define Parent Call
#define Class CrosspostMessageCall
#define function crosspostMessage
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(snowflake, message_id, USEDBY(target))                           \
    STATIC_FIELD(std::string, method, "POST")                                  \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Crosspost Message needs a Channel ID");
    if (!_message_id)
        throw std::logic_error("Crosspost Message needs a Message ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/messages/" +
        std::to_string(*_message_id) + "/crosspost");
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#create-reaction
// TODO unverified
#define Bot PluginEndpoints
#define Parent Call
#define Class CreateReactionCall
#define function createReaction
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(snowflake, message_id, USEDBY(target))                           \
    NEW_FIELD(std::string, emoji, USEDBY(target))                              \
    STATIC_FIELD(std::string, method, "PUT")                                   \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Create Reaction needs a Channel ID");
    if (!_message_id)
        throw std::logic_error("Create Reaction needs a Message ID");
    if (!_emoji)
        throw std::logic_error("Create Reaction needs an emoji");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/messages/" +
        std::to_string(*_message_id) + "/reactions/" +
        util::url_encode(*_emoji) + "/@me");
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#delete-own-reaction
// https://discord.com/developers/docs/resources/channel#delete-user-reaction
// TODO unverified
#define Bot PluginEndpoints
#define Parent Call
#define Class DeleteOwnReactionCall
#define function deleteOwnReaction
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(snowflake, message_id, USEDBY(target))                           \
    NEW_FIELD(std::string, emoji, USEDBY(target))                              \
    NEW_FIELD(snowflake, user_id, USEDBY(target))                              \
    STATIC_FIELD(std::string, method, "DELETE")                                \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Delete Own Reaction needs a Channel ID");
    if (!_message_id)
        throw std::logic_error("Delete Own Reaction needs a Message ID");
    if (!_emoji)
        throw std::logic_error("Delete Own Reaction needs an emoji");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/messages/" +
        std::to_string(*_message_id) + "/reactions/" +
        util::url_encode(*_emoji) + "/" +
        (!_user_id ? "@me" : std::to_string(*_user_id)));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#get-reactions
// TODO unverified
#define Bot PluginEndpoints
#define Parent Call
#define Class GetReactionsCall
#define function getReactions
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(snowflake, message_id, USEDBY(target))                           \
    NEW_FIELD(std::string, emoji, USEDBY(target))                              \
    NEW_FIELD(snowflake, before, USEDBY(target))                               \
    NEW_FIELD(snowflake, after, USEDBY(target))                                \
    NEW_FIELD(int, limit, USEDBY(target))                                      \
    STATIC_FIELD(std::string, method, "GET")                                   \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Get Reactions needs a Channel ID");
    if (!_message_id)
        throw std::logic_error("Get Reactions needs a Message ID");
    if (!_emoji)
        throw std::logic_error("Get Reactions needs an emoji");
    std::string out = fmt::format(
        "/channels/{}/messages/{}/reactions/{}", std::to_string(*_channel_id),
        std::to_string(*_message_id), util::url_encode(*_emoji));
    bool first = true;
    if (_after) {
        out += fmt::format("{}after={}", first ? "?" : "&", *_after);
        first = false;
    }
    if (_limit) {
        out += fmt::format("{}limit={}", first ? "?" : "&", *_limit);
        first = false;
    }
    return std::make_shared<const std::string>(std::move(out));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#delete-all-reactions
// https://discord.com/developers/docs/resources/channel#delete-all-reactions-for-emoji
// TODO unverified
#define Bot PluginEndpoints
#define Parent Call
#define Class DeleteAllReactionsCall
#define function deleteAllReactions
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(snowflake, message_id, USEDBY(target))                           \
    NEW_FIELD(std::string, emoji, USEDBY(target))                              \
    STATIC_FIELD(std::string, method, "DELETE")                                \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Get Reactions needs a Channel ID");
    if (!_message_id)
        throw std::logic_error("Get Reactions needs a Message ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/messages/" +
        std::to_string(*_message_id) + "/reactions" +
        (_emoji ? "/" + util::url_encode(*_emoji) : ""));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#edit-message
// Westlanderz/SenpaiR6#1717 verified channel_id, message_id, content, embed and flags
// Deathwillcome800#0950 replaced embed with embeds
// TODO allowed_mentions is unverified
#define Bot PluginEndpoints
#define Parent JsonCall
#define Class EditMessageCall
#define function editMessage
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(snowflake, message_id, USEDBY(target))                           \
    NEW_FIELD(std::string, content, USEDBY(payload))                           \
    NEW_FIELD(std::vector<json>, embeds, USEDBY(payload))                                    \
    NEW_FIELD(int, flags, USEDBY(payload))                                     \
    NEW_FIELD(json, allowed_mentions, USEDBY(payload))                         \
    STATIC_FIELD(std::string, method, "PATCH")                                 \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    HIDE_FIELD(payload)                                                        \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Edit Message needs a Channel ID");
    if (!_message_id)
        throw std::logic_error("Edit Message needs a Message ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/messages/" +
        std::to_string(*_message_id));
}
sptr<const json> render_payload() override {
    json out;

    if (_content)
        out["content"] = *_content;

    if (_embeds)
        out["embeds"] = *_embeds;

    if (_flags)
        out["flags"] = *_flags;

    if (_allowed_mentions)
        out["allowed_mentions"] = *_allowed_mentions;

    return std::make_shared<const json>(std::move(out));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#delete-message
// Verified by Westlanderz/SenpaiR6#1717
#define Bot PluginEndpoints
#define Parent Call
#define Class DeleteMessageCall
#define function deleteMessage
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(snowflake, message_id, USEDBY(target))                           \
    STATIC_FIELD(std::string, method, "DELETE")                                \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Delete Message needs a Channel ID");
    if (!_message_id)
        throw std::logic_error("Delete Message needs a Message ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/messages/" +
        std::to_string(*_message_id));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#bulk-delete-messages
// TODO unverified
#define Bot PluginEndpoints
#define Parent JsonCall
#define Class BulkDeleteMessagesCall
#define function bulkDeleteMessages
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(std::vector<snowflake>, messages, USEDBY(payload))               \
    STATIC_FIELD(std::string, method, "DELETE")                                \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    HIDE_FIELD(payload)                                                        \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Bulk Delete Messages needs a Channel ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/messages/bulk-delete");
}
sptr<const json> render_payload() override {
    json out;

    if (!_messages)
        throw std::logic_error(
            "Bulk Delete Messages needs an array of messages");
    out["messages"] = *_messages;

    return std::make_shared<const json>(std::move(out));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#edit-channel-permissions
// TODO unverified
#define Bot PluginEndpoints
#define Parent JsonCall
#define Class EditChannelPermissionsCall
#define function editChannelPermissions
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(snowflake, overwrite_id, USEDBY(target))                         \
    NEW_FIELD(std::string, allow, USEDBY(payload))                             \
    NEW_FIELD(std::string, deny, USEDBY(payload))                              \
    NEW_FIELD(int, permission_type, USEDBY(payload))                           \
    STATIC_FIELD(std::string, method, "PUT")                                   \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    HIDE_FIELD(payload)                                                        \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Edit Channel Permissions needs a Channel ID");
    if (!_overwrite_id)
        throw std::logic_error(
            "Edit Channel Permissions needs an Overwrite ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/permissions/" +
        std::to_string(*_overwrite_id));
}
sptr<const json> render_payload() override {
    json out;

    if (_allow)
        out["allow"] = *_allow;

    if (_deny)
        out["deny"] = *_deny;

    if (_permission_type)
        out["type"] = *_permission_type;

    return std::make_shared<const json>(std::move(out));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#get-channel-invites
// TODO unverified
#define Bot PluginEndpoints
#define Parent Call
#define Class GetChannelInvitesCall
#define function getChannelInvites
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    STATIC_FIELD(std::string, method, "GET")                                   \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Get Channel Invites needs an ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/invites");
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#create-channel-invite
// TODO unverified
#define Bot PluginEndpoints
#define Parent JsonCall
#define Class CreateChannelInviteCall
#define function createChannelInvite
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(int, max_age, USEDBY(payload))                                   \
    NEW_FIELD(int, max_uses, USEDBY(payload))                                  \
    NEW_FIELD(bool, temporary, USEDBY(payload))                                \
    NEW_FIELD(bool, unique, USEDBY(payload))                                   \
    NEW_FIELD(std::string, target_user, USEDBY(payload))                       \
    NEW_FIELD(int, target_user_type, USEDBY(payload))                          \
    STATIC_FIELD(std::string, method, "PUT")                                   \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    HIDE_FIELD(payload)                                                        \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Create Channel Invite needs a Channel ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/invites");
}
sptr<const json> render_payload() override {
    json out;

    if (_max_age)
        out["max_age"] = *_max_age;

    if (_max_uses)
        out["max_uses"] = *_max_uses;

    if (_temporary)
        out["temporary"] = *_temporary;

    if (_unique)
        out["unique"] = *_unique;

    if (_target_user)
        out["target_user"] = *_target_user;

    if (_target_user_type)
        out["target_user_type"] = *_target_user_type;

    return std::make_shared<const json>(std::move(out));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#delete-channel-permission
// TODO unverified
#define Bot PluginEndpoints
#define Parent Call
#define Class DeleteChannelPermissionCall
#define function deleteChannelPermissions
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(snowflake, overwrite_id, USEDBY(target))                         \
    STATIC_FIELD(std::string, method, "DELETE")                                \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Delete Channel Permission needs a Channel ID");
    if (!_overwrite_id)
        throw std::logic_error(
            "Delete Channel Permission needs an Overwrite ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/permissions/" +
        std::to_string(*_overwrite_id));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#follow-news-channel
// TODO unverified
#define Bot PluginEndpoints
#define Parent JsonCall
#define Class FollowNewsChannelCall
#define function followNewsChannel
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(snowflake, webhook_channel_id, USEDBY(payload))                  \
    STATIC_FIELD(std::string, method, "POST")                                  \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    HIDE_FIELD(payload)                                                        \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )
#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Follow News Channel needs a Channel ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/followers");
}
sptr<const json> render_payload() override {
    json out;

    if (!_webhook_channel_id)
        throw std::logic_error(
            "Follow News Channel needs an Webhook Channel ID");
    out["webhook_channel_id"] = *_webhook_channel_id;

    return std::make_shared<const json>(std::move(out));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#trigger-typing-indicator
// TODO unverified
#define Bot PluginEndpoints
#define Parent Call
#define Class TriggerTypingIndicatorCall
#define function triggerTypingIndicator
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    STATIC_FIELD(std::string, method, "POST")                                  \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Trigger Typing Indicator needs a Channel ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/typing");
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#get-pinned-messages
// TODO unverified
#define Bot PluginEndpoints
#define Parent Call
#define Class GetPinnedMessagesCall
#define function getPinnedMessages
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    STATIC_FIELD(std::string, method, "GET")                                   \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Get Pinned Messages needs a Channel ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/pins");
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#add-pinned-channel-message
// TODO unverified
#define Bot PluginEndpoints
#define Parent Call
#define Class AddPinnedChannelMessageCall
#define function addPinnedChannelMessage
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(snowflake, message_id, USEDBY(target))                           \
    STATIC_FIELD(std::string, method, "PUT")                                   \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Add Pinned Channel Message needs a Channel ID");
    if (!_message_id)
        throw std::logic_error("Add Pinned Channel Message needs a Message ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/pins/" +
        std::to_string(*_message_id));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#delete-pinned-channel-message
// TODO unverified
#define Bot PluginEndpoints
#define Parent Call
#define Class DeletePinnedChannelMessageCall
#define function deletePinnedChannelMessage
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(snowflake, message_id, USEDBY(target))                           \
    STATIC_FIELD(std::string, method, "DELETE")                                \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Add Pinned Channel Message needs a Channel ID");
    if (!_message_id)
        throw std::logic_error("Add Pinned Channel Message needs a Message ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/pins/" +
        std::to_string(*_message_id));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#group-dm-add-recipient
// TODO unverified
#define Bot PluginEndpoints
#define Parent JsonCall
#define Class AddGroupDMRecipientCall
#define function addGroupDMRecipient
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(snowflake, user_id, USEDBY(target))                              \
    NEW_FIELD(std::string, access_token, USEDBY(payload))                      \
    NEW_FIELD(std::string, nick, USEDBY(payload))                              \
    STATIC_FIELD(std::string, method, "PUT")                                   \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    HIDE_FIELD(payload)                                                        \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Add Group DM Recipient needs a Channel ID");
    if (!_user_id)
        throw std::logic_error("Add Group DM Recipient needs a User ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/recipients/" +
        std::to_string(*_user_id));
}
sptr<const json> render_payload() override {
    json out;

    if (!_access_token)
        throw std::logic_error("Add Group DM Recipient needs an Access Token");
    out["access_token"] = *_access_token;

    if (_nick)
        out["access_token"] = *_nick;

    return std::make_shared<const json>(std::move(out));
}
#include <discordpp/macros/defineCallClose.hh>

// https://discord.com/developers/docs/resources/channel#group-dm-remove-recipient
// TODO unverified
#define Bot PluginEndpoints
#define Parent Call
#define Class RemoveGroupDMRecipientCall
#define function removeGroupDMRecipient
#define Fields                                                                 \
    NEW_FIELD(snowflake, channel_id, USEDBY(target))                           \
    NEW_FIELD(snowflake, user_id, USEDBY(target))                              \
    STATIC_FIELD(std::string, method, "DELETE")                                \
    HIDE_FIELD(target)                                                         \
    HIDE_FIELD(type)                                                           \
    HIDE_FIELD(body)                                                           \
    FORWARD_FIELD(handleWrite, onWrite, )                                      \
    FORWARD_FIELD(handleRead, onRead, )

#include <discordpp/macros/defineCallOpen.hh>
protected:
sptr<const std::string> render_target() override {
    if (!_channel_id)
        throw std::logic_error("Add Group DM Recipient needs a Channel ID");
    if (!_user_id)
        throw std::logic_error("Add Group DM Recipient needs a User ID");
    return std::make_shared<const std::string>(
        "/channels/" + std::to_string(*_channel_id) + "/recipients/" +
        std::to_string(*_user_id));
}
#include <discordpp/macros/defineCallClose.hh>
