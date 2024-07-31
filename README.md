# pipex

## Descripción

`pipex` es una implementación en C del comportamiento de los pipes en sistemas UNIX. El objetivo de este proyecto es reproducir el funcionamiento de la instrucción `|` de la shell, permitiendo conectar la salida estándar de un comando a la entrada estándar de otro.

## Instalación

Para compilar el proyecto, simplemente ejecuta:

```bash
make
```

## Uso

El programa se ejecuta con la siguiente sintaxis:

```bash
./pipex archivo1 comando1 comando2 archivo2
```

- `archivo1`: Archivo de entrada.
- `comando1`: Primer comando a ejecutar.
- `comando2`: Segundo comando a ejecutar.
- `archivo2`: Archivo de salida.

Ejemplo:

```bash
./pipex infile "ls -l" "wc -l" outfile
```

Este comando tomará el contenido de `infile`, lo pasará al comando `ls -l`, cuyo resultado será pasado a `wc -l`, y finalmente el resultado se guardará en `outfile`.

## Estructura del Proyecto

- `src/`: Contiene los archivos fuente del proyecto.
- `lib/`: Contiene las bibliotecas necesarias para el proyecto.
- `Makefile`: Script para la compilación del proyecto.

## Contribuciones

Las contribuciones son bienvenidas. Por favor, crea un issue para reportar bugs o discutir mejoras, y envía un pull request para tus cambios.

## Licencia

Este proyecto está bajo la Licencia MIT. Consulta el archivo LICENSE para más detalles.
```

Designed and developed by 2022 adrian-reh (Adrian Ramon Elias Herrera)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.