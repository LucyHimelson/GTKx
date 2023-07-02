pacman -S xorg-server xcb-util gtk3
gcc -o yo test.c `pkg-config --cflags --libs gtk+-3.0` -lxcb
