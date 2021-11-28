1) установка компилятора clang, если его нет или вы не знаете что это такое

https://github.com/llvm/llvm-project/releases/tag/llvmorg-12.0.0

Скачать LLVM-12.0.0-win64.exe
И установить в 
C:/Program Files/LLVM 
(дефолтная директория)

2) распакуйте ChessECS.rar в диске D
Дальше будет предполагаться, что вы распаковали архив в D:\ChessECS

3) добавить D:\ChessECS\BuildTools\Ninja в переменную PATH среды пользователя

4) Если у вас нет Visual Studio, то установите Visual studio (только с++ пакет) - самый простой способ получить windows специфик либы.

5) компиляция

откройте командную строку

C:\Users\Admin>d: // переходим в диск D.

D:\>cd ChessECS // переходим в папку ChessECS

D:\Chess>build_script.bat Chess dbg
//запускаем батник компиляции
//аргумент может быть либо dbg (дебажная сборка, без оптимизаций) либо rel (релизная, с оптимизациями)

Вы должны будете увидеть следующее:
Codegen finished work

-- The C compiler identification is Clang 12.0.0 with GNU-like command-line
-- The CXX compiler identification is Clang 12.0.0 with GNU-like command-line
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/Program Files/LLVM/bin/clang.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: C:/Program Files/LLVM/bin/clang++.exe - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done
-- Generating done
-- Build files have been written to: D:/Chess/Builds/win/dbg
[2/47] Building CXX object Common/CMakeFiles/Engine.dir/Sources/Engine/Render/world_renderer.cpp.obj     

4) запуск

D:\Arcade>run_script.bat dbg


5) VScode
Для быстрой разработки советуем использовать VScode
Это по сути просто тектсовый редактор, но который можно полностью настроить под себя и пользоваться им также как и VisualStudio.

https://code.visualstudio.com/download

Необходимые расширения:
https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools
https://marketplace.visualstudio.com/items?itemName=AlexandrShcherbakov.launchoption

После их установки сэмпл можно будет собирать через ctrl+Shift+B (хоткей меняется)
и запускать через F5
