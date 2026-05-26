#pragma once
#include <godot_cpp/classes/node.hpp>
#include <discordpp.h>

using namespace godot;

class DiscordRPC : public Node {
    GDCLASS(DiscordRPC, Node)

    std::shared_ptr<discordpp::Client> client;
    discordpp::Activity current_activity;
    bool initialized = false;

protected:
    static void _bind_methods();

public:
    void initialize(int64_t app_id);
    void set_activity(String details, String state);
    void set_large_image(String key, String text);
    void set_timestamp_start();
    void clear_activity();
    void run_callbacks();
    void shutdown();
};