extends DiscordRPC

func _ready() -> void:
	var app_id_str: String = ProjectSettings.get_setting("discord_rpc/application_id", "0")
	if app_id_str == "0" or app_id_str.is_empty():
		push_warning("NextDiscordRPC: application_id is not set in Project Settings")
		return

	var app_id: int = app_id_str.to_int()

	initialize(app_id)
	set_timestamp_start()


func _process(_delta: float) -> void:
	run_callbacks()


func _exit_tree() -> void:
	shutdown()
