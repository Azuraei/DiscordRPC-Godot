#include "register_types.h"
#include "discord_rpc.h"

void initialize_discord_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) return;
    ClassDB::register_class<DiscordRPC>();
}

void uninitialize_discord_module(ModuleInitializationLevel p_level) {}

extern "C" {
    GDExtensionBool GDE_EXPORT discord_rpc_init(
        GDExtensionInterfaceGetProcAddress p_get_proc_address,
        const GDExtensionClassLibraryPtr p_library,
        GDExtensionInitialization *r_initialization)
    {
        GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
        init_obj.register_initializer(initialize_discord_module);
        init_obj.register_terminator(uninitialize_discord_module);
        init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
        return init_obj.init();
    }
}