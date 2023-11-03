#!/usr/bin/env bash

#       _        _             _                
#   ___| |_ __ _| |_ _   _ ___| |__   __ _ _ __ 
#  / __| __/ _` | __| | | / __| '_ \ / _` | '__|
#  \__ \ || (_| | |_| |_| \__ \ |_) | (_| | |   
#  |___/\__\__,_|\__|\__,_|___/_.__/ \__,_|_|   
#

#---> Load color scheme
. ~/.dwm/statusbar/dark_pastels

#---> Battery
battery () {
    # Para identificar a bateria use o comando: ls -1 /sys/class/power_suply/
    # o padrão é BAT0 ou BAT1, troque para o resultado do comando.
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

#---> Clock
clock() {
       printf "^c$LABEL^^b$BG^"
       printf "^c$FG^^b$BG^ $(date '+%a, %R %p')"     # dia da semana + hora
}

#---> cmus status
cmus() {
artist=$(echo -n $(cmus-remote -C status | grep "tag artist" | cut -c 12-))

if [[ $artist = *[!\ ]* ]]; then
        song=$(echo -n $(cmus-remote -C status | grep title | cut -c 11-))
        echo -n "^c$cmus^^b$BG^$artist ^c$LABEL^^b$BG^ﱘ ^c$cmus^^b$BG^$song"

    else
      echo
fi
}

# ---> CPU (%)
cpu() {
        cpu_load=$(grep -o "^[^ ]*" /proc/loadavg)

        printf "^c$LABEL^^b$BG^ "
        printf "^c$FG^^b$BG^ $cpu_load"
}

#---> Pulse Audio
volume_pa() {
        muted=$(pactl list sinks | awk '/Mudo:/ { print $2 }')
        vol=$(pactl list sinks | grep Volume: | awk 'FNR == 1 { print $5 }' | cut -f1 -d '%')

                if [ "$muted" = "sim" ]; then   # se seu sistema estiver em inglês, troque "sim" por "yes"
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

# ---> Memory
memory() {
        printf "^c$LABEL^^b$BG^ ^c$FG^^b$BG^$(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g)"
}

#---> wifi/wired
network() {
        wired=$(cat /sys/class/net/enp2s0/operstate 2>/dev/null)
        wifi=$(cat /sys/class/net/wlp1s0/operstate 2>/dev/null)

                if [ "$wifi" = "up" ]; then
                  echo "^c$LABEL^^b$BG^直 ^c$FG^^b$BG^Up"
        else
                if [ "$wifi" = "down" ]; then
                  echo "^c$LABEL^^b$BG^直 ^c$red^^b$BG^Down"
                elif [ "$wired" = "up" ]; then
                  echo "^c$LABEL^^b$BG^直 ^c$FG^^b$BG^Up"
                elif [ "$wired" = "down" ]; then
                  echo "^c$LABEL^^b$BG^直 ^c$red^^b$BG^Down"
                fi
        fi
 }

#---> wired
network_wired() {
        case "$(cat /sys/class/net/enp1s0/operstate 2>/dev/null)" in
                up) echo "^c$LABEL^^b$BG^直 ^c$FG^^b$BG^Up ";;
                down) echo "^c$magenta^^b$BG^Down ";;
        esac
}

#---> wifi
wifi () {
        case "$(cat /sys/class/net/wlp1s0/operstate 2>/dev/null)" in
                up) echo "^c$LABEL^^b$BG^直 ^c$FG^^b$BG^Up ";;
                down) echo "^c$red^^b$BG^Down ";;
        esac
}

#---> Main
while true; do

  sleep 1 && xsetroot -name "$(cmus) $(volume_pa) $(memory) $(cpu) $(network) $(clock)"

done
