env = SConscript("src/lib/godot-cpp/SConstruct")

sources = Glob("src/*.cpp")

env.Append(CPPPATH=["src/lib/discord_social_sdk/include/"])
env['SHLIBPREFIX'] = ''

if env["target"] == "template_debug":
    discord_lib_path = "src/lib/discord_social_sdk/lib/debug/"
    discord_bin_path = "src/lib/discord_social_sdk/bin/debug/"
else:
    discord_lib_path = "src/lib/discord_social_sdk/lib/release/"
    discord_bin_path = "src/lib/discord_social_sdk/bin/release/"

env.Append(LIBPATH=[discord_lib_path])
env.Append(LIBS=["discord_partner_sdk"])

discord_runtime_src = ""
discord_runtime_dst = ""

if env["platform"] in ("linuxbsd", "linux"):
    suffix = ".linux." + env["target"] + ".x86_64.so"
    bin_dir = "project/addons/NextDiscordRPC/bin/linux/"
    env.Append(LINKFLAGS=["-Wl,-rpath,'$$ORIGIN'"])
    discord_runtime_src = discord_lib_path + "libdiscord_partner_sdk.so"
    discord_runtime_dst = bin_dir + "libdiscord_partner_sdk.so"
elif env["platform"] == "windows":
    suffix = ".windows." + env["target"] + ".x86_64.dll"
    bin_dir = "project/addons/NextDiscordRPC/bin/windows/"
    discord_runtime_src = discord_bin_path + "discord_partner_sdk.dll"
    discord_runtime_dst = bin_dir + "discord_partner_sdk.dll"
elif env["platform"] == "macos":
    suffix = ".macos." + env["target"] + ".universal.dylib"
    bin_dir = "project/addons/NextDiscordRPC/bin/macos/"
    env.Append(LINKFLAGS=["-Wl,-rpath,@loader_path"])
    discord_runtime_src = discord_lib_path + "libdiscord_partner_sdk.dylib"
    discord_runtime_dst = bin_dir + "libdiscord_partner_sdk.dylib"

library = env.SharedLibrary(
    bin_dir + "NextDiscordRPC" + suffix,
    source=sources,
)
Default(library)

if discord_runtime_src and discord_runtime_dst:
    copied_lib = env.Command(discord_runtime_dst, discord_runtime_src, Copy("$TARGET", "$SOURCE"))
    Depends(library, copied_lib)
    Default(copied_lib)

env.Tool('compilation_db')
env.CompilationDatabase('compile_commands.json')
