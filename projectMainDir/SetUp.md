# Instrukcje dla setup'u poza tymi w ReadMe, bardziej precyzyjne pewnie
# Dodane ze wzgledu na problemy przez zmiane wersji lib SFML

## Windows
```bash
# Zainstalowac vcpkg lub ewentualnie wykorzystac
#   wbudowane binaries.
# Następnie przejsc i dodac do CMAKE:
cmake -B build -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake
cmake --build build
```

## Linux - na ubuntu 24 LTS testowane
```bash
sudo apt-get install libsfml-dev libtgui-dev
cmake -B build
cmake --build build
```

## macOS
```bash
brew install sfml tgui
cmake -B build
cmake --build build
```