# raylib-cpp-template

## Getting Started

Clone this project using:

```bash
git clone https://github.com/spounka/raylib-cpp-template.git --recursive
```

> [!NOTE]
> This will clone both [raylib](https://github.com/raysan5/raylib) and
> [raylib-cpp](https://github.com/RobLoach/raylib-cpp/) repositories

## Generating

To to generate the project files, run the command:

```bash
cmake -B cmake-build-debug . -DCMAKE_BUILD_TYPE=Debug -G "Ninja"
```

> [!NOTE]
> If you want to use Makefiles instead of ninja, substitute "Ninja" with
> "Unix Makefiles"

> [!NOTE]
> The `cmake-build-debug` folder can also be changed to a different folder like
> `build`

> [!NOTE]
> If you want [box2d](https://github.com/erincatto/box2d) you can add the flag
> `-DBUILD_INCLUDE_BOX2D`

## Building

To compile the project, you can run

```bash
cmake --build cmake-build-debug -- -j$(nproc)
```

> [!WARNING]
> This assumes the development environment is GNU/Linux
