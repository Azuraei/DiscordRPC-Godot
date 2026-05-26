@tool
extends EditorPlugin

var export_plugin: EditorExportPlugin


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
	
	export_plugin = DiscordRPCExportPlugin.new()
	add_export_plugin(export_plugin)
	
	add_autoload_singleton("Discord", "res://addons/NextDiscordRPC/discord_rpc_autoload.gd")


func _exit_tree() -> void:
	remove_export_plugin(export_plugin)
	remove_autoload_singleton("Discord")


class DiscordRPCExportPlugin extends EditorExportPlugin:
	func _get_name() -> String:
		return "NextDiscordRPC"
	
	func _export_begin(features: PackedStringArray, is_debug: bool, path: String, flags: int) -> void:
		if "linux" in features or "linuxbsd" in features:
			add_shared_object("res://addons/NextDiscordRPC/bin/linux/libdiscord_partner_sdk.so", PackedStringArray(), "")
		elif "windows" in features:
			add_shared_object("res://addons/NextDiscordRPC/bin/windows/discord_partner_sdk.dll", PackedStringArray(), "")
