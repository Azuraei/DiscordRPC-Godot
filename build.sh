#!/bin/bash
DEBUG_COLOR='\033[1;33m' # Yellow
NC='\033[0m' # No Color
# Linux
echo -e "${DEBUG_COLOR}Building for Linux\nLinux Debug${NC}"
scons platform=linux target=template_debug
echo -e "${DEBUG_COLOR}Linux Release${NC}"
scons platform=linux target=template_release
# Windows
#echo -e "${DEBUG_COLOR}Building for Windows\nWindows Debug${NC}"
#scons platform=windows target=template_debug
#echo -e "${DEBUG_COLOR}Windows Release${NC}"
#scons platform=windows target=template_release
echo -e "${DEBUG_COLOR}Everything is compiled. Yay!${NC}"
