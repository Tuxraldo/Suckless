#!/usr/bin/env bash

# Display -------------------------------------------------------------#
xrandr -s 1360x768 &

# Keyboard layout -----------------------------------------------------#
setxkbmap br &

# System Monitor ------------------------------------------------------#
psensor &

# Wallpaper -----------------------------------------------------------#
feh --bg-fill $HOME/Imagens/droid-gray.png &
#feh --bg-fill $HOME/Imagens/dwm-logo-gray.png &

# Statusbar -----------------------------------------------------------#
$HOME/.dwm/status-bar.sh &

# Notification Daemon -------------------------------------------------#
/usr/lib/x86_64-linux-gnu/xfce4/notifyd/xfce4-notifyd &

# Gnome polkit --------------------------------------------------------#
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &

# Compositor ----------------------------------------------------------#
picom --config $HOME/.dwm/picom-dwm.conf &

# Hotkey daemon -------------------------------------------------------#
sxhkd -c ~/.dwm/sxhkdrc &
