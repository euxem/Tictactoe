#!/bin/bash

make

printf "#!/usr/bin/env xdg-open\n\
[Desktop Entry]\n\
Version=1.0\n\
Terminal=false\n\
Type=Application\n\
Name=Tictactoe\n\
Exec=tictactoe --graphical\n\
Icon=$HOME/.local/app_perso/Tictactoe/tictactoe.svg\n" > ~/.local/share/applications/tictactoe.desktop
sudo mv tictactoe /usr/bin/tictactoe

if [[ ! -d ~/.local/app_perso ]]
then
    mkdir ~/.local/app_perso
fi

if [[ ! -d ~/.local/app_perso/Tictactoe ]]
then
mkdir ~/.local/app_perso/Tictactoe
fi

sudo cp tictactoe.svg ~/.local/app_perso/Tictactoe/.

make clean
