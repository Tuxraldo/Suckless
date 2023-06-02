#!/usr/bin/env bash

# Load interval
interval=0

# Load color scheme
. ~/.dwm/dark_pastel-colors

battery () {
    # Change BAT1 to whatever your battery is identified as. Typically BAT0 or BAT1
    CHARGE=$(cat /sys/class/power_supply/BAT1/capacity)
    STATUS=$(cat /sys/class/power_supply/BAT1/status)

    printf "%s" "$SEP1"
    if [ "$IDENTIFIER" = "unicode" ]; then
        if [ "$STATUS" = "Charging" ]; then
            printf "^c$LABEL^^b$BG^ %s%% %s" ^c$FG^^b$BG^"$CHARGE" "$STATUS"
        else
            printf "^c$red^^b$BG^ﮤ %s%% %s" "$CHARGE" "$STATUS"
        fi
    else
        printf "^c$LABEL^^b$BG^ %s%% %s" ^c$FG^^b$BG^"$CHARGE"
    fi
    printf "%s\n" "$SEP2"
}

clock() {
        printf "^c$LABEL^^b$BG^"
#        printf "^c$FG^^b$BG^ $(date '+%a, %R %p')"     # dia da semana + hora
        printf "^c$FG^^b$BG^ $(date '+%R %p')"      # somente hora
}

## cmus status
cmus() {
        title=$(cmus-remote -Q | grep 'title' | cut -c 11-)
        artist=$(cmus-remote -Q | grep 'tag artist' | cut -c 12-)
        printf " ^c$cmus^^b$BG^$artist ^c$cmus^^b$BG^ ^c$cmus^^b$BG^ $title |"
#	     printf " $artist ^c$BG^^b$BG^ ^c$FG^^b$BG^ $title |"
#	      printf " ^c$LABEL^^b$BG^ﱘ ^c$FG^^b$BG^$title |"
}

## Volume PulseAudio
volume_pa() {
        muted=$(pactl list sinks | awk '/Mudo:/ { print $2 }')
        vol=$(pactl list sinks | grep Volume: | awk 'FNR == 1 { print $5 }' | cut -f1 -d '%')

                if [ "$muted" = "sim" ]; then
               echo "^c$red^^b$BG^mudo "
        else
               if [ "$vol" -ge 65 ]; then
                       echo "^c$LABEL^^b$BG^墳 ^c$FG^^b$BG^$vol% "
               elif [ "$vol" -ge 40 ]; then
                       echo "^c$LABEL^^b$BG^墳 ^c$FG^^b$BG^$vol% "
               elif [ "$vol" -ge 0 ]; then
                       echo "^c$LABEL^^b$BG^墳 ^c$FG^^b$BG^$vol% "
               fi
        fi
}

## Wired Network
network() {
        case "$(cat /sys/class/net/enp1s0/operstate 2>/dev/null)" in
                up) echo "^c$LABEL^^b$BG^直 ^c$FG^^b$BG^Up ";;
                down) echo "^c$red^^b$BG^Down ";;
        esac
}

## Main
while true; do
#  [ "$interval" == 0 ] || [ $(("$interval" % 3600)) == 0 ] && updates=$(updates)
#  interval=$((interval + 1))

sleep 1 && xsetroot -name "$(cmus) $(volume_pa) $(battery) $(clock)"
done
