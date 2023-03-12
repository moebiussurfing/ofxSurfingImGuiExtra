#!/bin/bash

# Obtener la ruta del directorio del script
folder_path="$(dirname "$0")"

# Crear un archivo README.mk en cada carpeta con archivos PNG o JPG y escribir la línea "[](Capture.PNG)"
echo "Creando archivos README.mk..."
find "$folder_path" -maxdepth 2 \( -iname "*.png" -o -iname "*.jpg" \) -printf "%h\n" | sort -u | while read dir; do
    echo "[](Capture.PNG)" > "$dir/README.md"
done
echo "Hecho."
