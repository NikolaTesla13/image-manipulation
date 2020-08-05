@ECHO OFF

g++ -std=gnu++1z src/main.cpp bin/lib/glad.o bin/lib/imgui.o bin/lib/imgui_draw.o bin/lib/imgui_impl_glfw_gl3.o -o bin/debug/game.exe -Iinclude -Lbin/lib -lmingw32 -lglfw3 -lopengl32 -lgdi32 -luser32

cd bin
cd debug
game
cd..
cd..