#include "discord_rpc.h"

void DiscordRPC::_bind_methods() {
    ClassDB::bind_method(D_METHOD("initialize", "app_id"), &DiscordRPC::initialize);
    ClassDB::bind_method(D_METHOD("set_activity", "details", "state"), &DiscordRPC::set_activity);
    ClassDB::bind_method(D_METHOD("set_large_image", "key", "text"), &DiscordRPC::set_large_image);
    ClassDB::bind_method(D_METHOD("set_timestamp_start"), &DiscordRPC::set_timestamp_start);
    ClassDB::bind_method(D_METHOD("set_timestamp_end", "time_end_ms"), &DiscordRPC::set_timestamp_end);
    ClassDB::bind_method(D_METHOD("set_timestamps", "time_start_ms", "time_end_ms"), &DiscordRPC::set_timestamps);
    ClassDB::bind_method(D_METHOD("clear_activity"), &DiscordRPC::clear_activity);
    ClassDB::bind_method(D_METHOD("run_callbacks"), &DiscordRPC::run_callbacks);
    ClassDB::bind_method(D_METHOD("shutdown"), &DiscordRPC::shutdown);
}

void DiscordRPC::initialize(int64_t app_id) {
    client = std::make_shared<discordpp::Client>();
    client->SetApplicationId(app_id);
    initialized = true;
}

void DiscordRPC::set_activity(String details, String state) {
    if (!initialized) return;
    current_activity.SetType(discordpp::ActivityTypes::Listening);
    current_activity.SetDetails(details.utf8().get_data());
    current_activity.SetState(state.utf8().get_data());
    current_activity.SetStatusDisplayType(discordpp::StatusDisplayTypes::State);
    client->UpdateRichPresence(current_activity, [](discordpp::ClientResult result) {});
}

void DiscordRPC::set_large_image(String key, String text) {
    if (!initialized) return;
    discordpp::ActivityAssets assets;
    assets.SetLargeImage(key.utf8().get_data());
    assets.SetLargeText(text.utf8().get_data());
    current_activity.SetAssets(assets);
    client->UpdateRichPresence(current_activity, [](discordpp::ClientResult result) {});
}

void DiscordRPC::set_timestamp_start() {
    if (!initialized) return;
    discordpp::ActivityTimestamps timestamps;
    timestamps.SetStart(time(nullptr));
    current_activity.SetTimestamps(timestamps);
    client->UpdateRichPresence(current_activity, [](discordpp::ClientResult result) {});
}

void DiscordRPC::set_timestamp_end(int64_t value) {
    if (!initialized) return;
    discordpp::ActivityTimestamps timestamps;
    timestamps.SetEnd(time(nullptr) + value);
    current_activity.SetTimestamps(timestamps);
    client->UpdateRichPresence(current_activity, [](discordpp::ClientResult result) {});
}

void DiscordRPC::set_timestamps(int64_t value_start, int64_t value_end) {
    if (!initialized) return;
    discordpp::ActivityTimestamps timestamps;
    timestamps.SetStart(time(nullptr) + value_start);
    timestamps.SetEnd(time(nullptr) + value_end);
    current_activity.SetTimestamps(timestamps);
    client->UpdateRichPresence(current_activity, [](discordpp::ClientResult result) {});
}

void DiscordRPC::clear_activity() {
    if (!initialized) return;
    current_activity = discordpp::Activity();
    client->UpdateRichPresence(current_activity, [](discordpp::ClientResult result) {});
}

void DiscordRPC::run_callbacks() {
    if (!initialized) return;
    discordpp::RunCallbacks();
}

void DiscordRPC::shutdown() {
    if (!initialized) return;
    client.reset();
    initialized = false;
}