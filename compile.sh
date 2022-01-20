if
    g++ -o result/backgammon.linux \
        src/main.cpp src/column.cpp src/board.cpp src/graphics.cpp \
        -lsfml-graphics -lsfml-window -lsfml-system \
        -pedantic-errors -Wall -Wextra
then
    echo "compiled successfully"
    ./result/backgammon.linux
fi

# if g++ -o result/backgammon main.cpp column.cpp board.cpp \
#     -lsfml-graphics -lsfml-window -lsfml-system \
#     -pedantic-errors -Wall -Weffc++ -Wextra -Wsign-conversion; then
#     echo "compiled successfully"
#     ./result/backgammon
# fi
