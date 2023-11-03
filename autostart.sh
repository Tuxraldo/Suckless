#!/usr/bin/env bash

# Clipboard plugin (xfce) ---------------------------------------------#
xfce4-clipman &

# Compositor ----------------------------------------------------------#
picom --config $HOME/.dwm/picom-dwm.conf &

# Gnome polkit --------------------------------------------------------#
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &

# Hotkey daemon -------------------------------------------------------#
sxhkd -c ~/.dwm/sxhkdrc &

# Notification Daemon -------------------------------------------------#
/usr/lib/x86_64-linux-gnu/xfce4/notifyd/xfce4-notifyd &

# Statusbar -----------------------------------------------------------#
$HOME/.dwm/statusbar/status-bar.sh &

# System Monitor ------------------------------------------------------#
psensor &

# Wallpaper -----------------------------------------------------------#
$HOME/.fehbg &

# Load Xresources -----------------------------------------------------#
xrdb ~/.Xresources &
