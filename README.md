# ESP-IDF Project

This is an ESP-IDF project. It was created using [Espressif's ESP-IDF framework](https://github.com/espressif/esp-idf).

---

## Requirements

- [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html) installed
- `IDF_PATH` environment variable set (source the `export.sh` script)

---

## Common `idf.py` Commands

Inside the project folder, use the following commands:

### Create a new project

```sh
idf.py create-project project_name
```

This generates a minimal ESP-IDF project with:
- `CMakeLists.txt`
- `main/project_name.c`
- `main/CMakeLists.txt`

### Set target chip

```sh
idf.py set-target esp32
```

### Build firmware

```sh
idf.py build
```

### Flash firmware to device

```sh
idf.py flash
```

### Monitor serial output

```sh
idf.py monitor
```

### Clean build files

```sh
idf.py fullyclean
```
