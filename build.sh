sudo pacman -Sy --root=/tmp gtk3 xorg-xcb-util

pacman -S xorg-server xcb-util gtk3
gcc -o yo test.c `pkg-config --cflags --libs gtk+-3.0` -lxcb
