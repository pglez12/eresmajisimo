## Compila
- Utiliza ~ make -n ~ para verificar que la compilación utilice -Wall-Werror-Wextra, si no utiliza el flag de compilacióon inválida
- ~ minishell ~ compila sin errores, si no, utiliza el flag apropiado
- El Makefile no debe hacer relink. Si no, utiliza el flag apropiado
## Comandos simples y la variable global
- Ejecuta un comando sencillo con una ruta absoluta de la forma /bin/ls, o cualquier otr comando sin argumentos.
- ¿Cuántas variables globales utiliza?¿Por qué? Debe dar un ejemplo concreto de por qué le parece necesario o lógico.
- Compruebe la variable global. Esta variable global no puede proporcionar otra información o acceso a datos que el número de una señal recibida.
- Prueba un comando vacío.
- Prueba solo tabuladores o espacios.
## Argumentos
- Ejecuta un comando simple con una ruta absouta como /bin/ls, u otro comando con argumentos pero sin comillas simples y comillas dobles
- Hazlo varias veces con distintos comandos y argumentos
## Echo
- Ejecuta el comando echo con o sin argumentos, y con o sin -n.
- Hazlo multiples veces con distintos argumentos
## Exit
- Ejecuta el comando exit con o sin argumentos.
- Hazlo varias veces con distintos argumentos.
## Valor de retorno de un proceso
- Ejecuta una prueba simple con una ruta absoluta del tipo /bin/ls, o algún otro comando cono argumentos pero sin comillas simples o dobles. Después ejecuta echo $?
- Comprueba el valor devuelto. Puedes hacer lo mismo en bash y comparar ambos resultados.
- Hazlo varias veces, con distintos comandos y argumentos. Ejecuta algunos comandos que fallen como '/bin/ls archi_quenoexiste'
- Algo como 'expr $? + $?'
## Señales
## Comillas dobles
- Ejecuta un comando simple con argumentos, esta vez con comillas dobles (deberias probar a incluir espacios en blanco también).
- Un comando como echo "cat lol.c | cat > lol.c"
- Cualquier cosa, salvo $
## Comillas simples
- Ejecuta comandos con comillas simpres como argumento
- Prueba argumentos vacios
- Prueba variables de entorno, espacios en blanco, pipes y redirecciones en las comillas simples
- echo '$USER' debe imprimir $USER
- Nada debe interpretarse
## ENV
- Comprueba si env muestra las variables de entorno actuales
## EXPORT
- Exporta variables de entorno, crea nuevas y reemplaza viejas
- Comprueba que funcione correctamente con env
## UNSET
- Exporta variables de entorno, crea nuevas y reemplaza viejas
- Utiliza unset para eliminar algunas de ellas
- Verifica el resultado con env
## CD
- Utiliza el comando cd para cambiar de directorio de trabajo, y asegurate de que estás en el directorio correcto con /bin/ls
- Repite esto varias veces, algunas que funcionen y otras que no
- Prueba '.' y '..' como argumentos
## PWD
- Utiliza el comando pwd
- Repite esto varias veces en múltiples directorios
## Rutas Relativas
- Ejecuta comandos, pero esta vez con rutas relativas
- Repite esto múltiples veces en múltiples directorios con rutas relativas complejas(muchos ..)
## La variable de entorno PATH
- Ejecuta comandos, pero esta vez sin rutas (ls, wc, awk, etc)
- Elimina $PATH y verifica que ya no funcionen
- Establece $PATH para varios directorios (dir1:dir2) y valida que los directorios se comprueban de izquierda a derecha
## Redirecciones
- Ejecuta comandos con redirecciones < y >
- Repite esto varias veces con diferentes comandos y argumentos, cambia de vez en cuando > por >>
- Comprueba si varias redirecciones del mismo tipo fallan.
- Prueba la redireccion << (no necesita actualizar el historial)
## Pipes
- Ejecuta comandos con pipes como 'cat file | grep bla | more'
- Haz esto varias veces cambiando comandos y argumentos.
- Prueba algunos comandos que fallen como 'ls noexist | grep bla | more'
- Prueba a mezclar pipes y redirecciones
## Historial
- Escribe una linea de comandos, utiliza Ctrl+C y pulsa enter. El buffer deberá estar vacio y nada deberá ejecutarse
- ¿Pueds navegar en el historial con las flechas de arriba y abajo?¿Puedes volver a probar algun comando?
- Ejecuta comandos que no deberian funcionar como 'asdaddada' y verifica que minishell no termina y muestra un error.
- "cat | cat | ls" se comporta de forma normal
- Prueba a ejecutar un comando largo con muchísimos argumentos.
## Variables de entorno
- Ejecuta echo con alguna $ variables como argumentos
- Verifica que $ se interpreta como una variable de entorno
- Verifica que las comillas dobles interpolan $
- Verifica que $USER existe o crealo
- echo "$USER" debera imprimir el valor de USER

Revisar heredoc con  espaccios->ya
revisar despliegue cconn espaccios->ya
REvisar odigo de salida 0., por err->ya

ver "" ls = $no ls -> bash no pero imposible no puedo saber si "" != $no
cd "" no dir -> bash no hace nada
cd leaks no se cuando pero puede que en cd "" o cd ..... o cd o algo asi ---> YA

$no; echo $? -> 0 solucionado
>file; echo $? -> 1
