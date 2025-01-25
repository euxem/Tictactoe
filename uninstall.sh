#!/bin/bash

sudo rm -f /usr/bin/tictactoe

rm $HOME/.local/share/applications/tictactoe.desktop

rm -rf $HOME/.local/app_perso/Tictactoe/

rmdir app_perso/ 2> /dev/null
