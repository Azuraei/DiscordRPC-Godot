# Getting Discord SDK

First, you need to login in [Discord Developer Portal](https://discord.com/developers/home).
1. Create new application (yeah, it's important, no other ways)
2. Navigate to **Games -> Social SDK** using the left sidebar
3. Complete the form (just a formality)
4. Go to downloads and install the latest *DiscordSocialSdk-x.x.xxxxx.zip*
    - I'd recomend to use **1.9.15780**, as it's the version that plugin actually uses.
5. Simply unpack the archive into ``src/lib/``. You should get this hierachy:
```text
NextDiscordRPC
└── scr
    └── lib
        |   discord_social_sdk
        └── godot-cpp
```