#!/bin/bash

# Function to generate a random ANSI color code (bold, bright colors)
random_color() {
    colors=("31" "32" "33" "34" "35" "36" "91" "92" "93" "94" "95" "96")
    echo -e "\033[1;${colors[$((RANDOM % ${#colors[@]}))]}m"
}

# Reset terminal color
reset_color="\033[0m"

# Main loop
while true; do
    color=$(random_color)
    echo -e "${color}СабировДС-КС2203
    ᓚᘏᗢ 
    /\\_/\\
   ( o.o )
    > ^ <${reset_color}"
    sleep 3
done
