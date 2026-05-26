@tool
extends EditorPlugin

func _enter_tree() -> void:
	if not ProjectSettings.has_setting("discord_rpc/application_id"):
		ProjectSettings.set_setting("discord_rpc/application_id", "0")
		ProjectSettings.save()
	ProjectSettings.set_initial_value("discord_rpc/application_id", "0")
	ProjectSettings.add_property_info({
		"name": "discord_rpc/application_id",
		"type": TYPE_STRING,
		"hint": PROPERTY_HINT_NONE,
	})
	add_autoload_singleton("Discord", "res://addons/NextDiscordRPC/discord_rpc_autoload.gd")

func _exit_tree() -> void:
	remove_autoload_singleton("Discord")
