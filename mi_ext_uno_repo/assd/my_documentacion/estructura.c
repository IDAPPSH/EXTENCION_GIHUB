*
https://github.com/IDAPPSH/Ext1_Agenda_Consular.git


📂 Explicación ultra detallada de mi_ext_agenda_consular/
manifest.json
Es el cerebro administrativo de tu extensión.

Le dice a Chrome:

Cómo se llama tu extensión (nombre, versión, descripción).

Qué permisos necesita para funcionar (ej: leer pestañas, modificar páginas, usar almacenamiento).

Qué archivos debe cargar (content.js, background.js, popup.html, íconos).

Cuándo cargar cada parte (por ejemplo, content.js solo se inyecta en ciertas páginas).

Sin este archivo, la extensión ni siquiera se puede instalar. Es el "acta de nacimiento".

content.js
Es el espía que entra a la página web.

Se inyecta directamente en el contenido que ves (como si fuera parte de la página).

¿Qué hace?

Lee la página (por ejemplo, revisa si hay citas disponibles).

Extrae información (meses, días, horas disponibles, mensajes de error).

Modifica el HTML si quieres (por ejemplo: resalta una fecha disponible o cambia textos para avisarte algo).

Puede detectar cambios dinámicos (como que se actualice un calendario sin recargar la página).

Funciona en tiempo real, junto con la página que el usuario ve.

📌 Importante:

Si necesitas interactuar directamente con botones, inputs o mover cosas del sitio web, content.js es quien lo hace.

popup.html
Es la ventana pequeña que aparece al darle clic al ícono de la extensión.

Solo maneja la estructura visual (cómo se ve):

Botones de "Activar búsqueda", "Detener", "Actualizar datos", etc.

Mensajes que dicen "Buscando citas..." o "Citas encontradas".

Inputs o checkboxes para configuraciones rápidas.

No tiene lógica por sí mismo, solo muestra cosas.
(La lógica está en popup.js, ahorita llegamos a eso.)

.vscode/settings.json
No es para la extensión en sí, sino para tu editor de código (Visual Studio Code).

Guarda reglas para que el proyecto esté ordenado:

Ejemplo: usar 2 espacios para tabular, poner comillas simples, formato automático.

Te ayuda a trabajar más rápido, pero no afecta lo que ve el usuario final en Chrome.

images/
Son los íconos que usa tu extensión para representar:

El ícono que ves en el navegador.

El ícono que aparece en el menú de extensiones.

Decoraciones en el popup u opciones.

Hay varios tamaños para adaptarse a diferentes lugares (icon48.png, icon.png, etc).

assd/
Este es como un mini-proyecto dentro del proyecto. Aquí está la maquinaria extra que hace que todo se coordine bonito:

background.js
Es el motor invisible que corre todo el tiempo en segundo plano.

¿Qué hace?

Programar alarmas: por ejemplo, buscar nuevas citas cada 5 minutos aunque no estés viendo el popup.

Recibir mensajes: el popup o content.js pueden pedirle hacer tareas.

Tomar decisiones: por ejemplo, "Si hay nuevas citas, mandar notificación" o "Guardar nueva información".

Manejar permisos de acceso a internet, pestañas, almacenamiento.

No tiene interfaz, todo lo maneja calladito, atrás de todo.

options.html
Es una página de configuración avanzada.

Aquí puedes poner:

Opciones como "Cada cuánto buscar nuevas citas".

Cambiar alertas, modificar notificaciones, ajustar comportamiento.

Es como el "menú de configuración" que ves en extensiones grandes.

styles/popup.css
Define cómo se ve todo lo que está en popup.html.

Cosas como:

Colores de fondo, bordes, botones.

Tamaños de fuentes.

Espaciado entre elementos.

Que todo se vea ordenadito, no feo.

script/popup.js
Aquí sí viene la lógica viva del popup:

¿Qué hace?

Detecta clics en los botones (por ejemplo: "Iniciar búsqueda de citas").

Envía órdenes al background.js ("oye, empieza a buscar ya").

Muestra mensajes dinámicos en el popup ("Citas encontradas en Monterrey").

Guarda configuraciones usando el sistema de almacenamiento de Chrome (storage API).

Recibe respuestas: si background.js encuentra algo, popup.js lo muestra en pantalla.

Es como el control remoto que conecta al usuario con lo que pasa detrás.

📋 Resumen de lógicas

Archivo	Qué maneja	Qué modifica o ejecuta
manifest.json	Registro de la extensión.	Define permisos, scripts, íconos y comportamientos.
content.js	Interacción con páginas web reales.	Lee/modifica contenido del sitio (DOM).
popup.html	Interfaz visual del popup.	No ejecuta lógica, solo muestra.
settings.json	Configuración del editor de texto (Visual Studio Code).	Solo afecta al programador, no al usuario.
images/	Íconos y recursos gráficos.	No ejecuta nada, solo muestra imágenes.
background.js	Motor invisible que corre en segundo plano.	Escucha eventos, programa alarmas, manda notificaciones.
options.html	Página de configuración avanzada.	Permite cambiar ajustes de funcionamiento de la extensión.
popup.css	Apariencia visual del popup y opciones.	Modifica estilos (colores, tamaños, márgenes).
popup.js	Lógica de interacción del popup.	Maneja eventos del usuario, manda mensajes, guarda configuraciones.
🧠 En pocas palabras:
manifest.json organiza todo.

background.js mantiene trabajando la extensión aunque no la veas.

content.js mete mano a las páginas de internet.

popup.js conecta tus botones con la maquinaria.

popup.html se ve bonito.

images/, popup.css y options.html lo decoran y configuran.

🚀
¿Quieres que ahora te haga también una especie de "flujo de cómo se comunican entre ellos"?
Así como:
Popup -> Background -> Content -> Página visualmente con flechitas?

¿Te lo paso también tipo archivo .md (Markdown bonito) para que lo tengas documentado?
👉 Dime wey, no te awites, tú manda. 🔥

**************************************************************************************








Ok WEY, mira WEY, te voy a hacer el mismo esquema que me diste, pero todavía **más detallado** y **explicadito**, bien machín, para que entiendas qué maneja, qué modifica, qué ejecuta, **qué pedo trae cada archivo**.  
**Agárrate WEY, ahí va:**  

---

**mi_ext_agenda_consular/**  
│  
├── **manifest.json**  
│   # Es el "cerebro administrativo" de la extensión,
│   # Archivo esencial que define toda la extensión: nombre, descripción, versión, permisos que necesita 
│   # (como acceso a pestañas o almacenamiento), archivos que usa (scripts, íconos) y comportamientos 
│   # (qué se ejecuta en segundo plano, en el popup o en las páginas web).
│   # - Dice cómo se llama, qué versión es, qué permisos ocupa (leer pestañas, guardar cosas, modificar páginas, etc.).  
│   # - Le dice al navegador qué archivos debe cargar: scripts, iconos, configuraciones.  
│   # - Define qué scripts se ejecutan en:  
│     - El **contenido** de las páginas (content.js).  
│     - El **fondo** siempre activo (background.js).  
│     - El **popup** cuando el usuario interactúa (popup.html + popup.js).  
│   # **Sin este archivo, la extensión ni se instala ni jala.**  
│  
├── **content.js**  
│   # Este script se **inyecta** en las páginas web donde tú quieres que haga algo (por ejemplo, la página de citas).
    # Script que se inyecta directamente en las páginas web que visitas.
│   # Su función principal es interactuar con el contenido de esas páginas:
│   # - Detecta la disponibilidad de citas consulares.
│   # - Extrae y analiza información relevante del sitio.
│   # - Puede modificar el DOM (texto, botones, alertas) según la lógica que programes.|  
│   # ¿Qué hace el cabrón?  
│   # - **Detecta cambios** en la página: si aparecen citas, mensajes nuevos, estados.  
│   # - **Extrae información**: lee textos, fechas, ubicaciones, etc.  
│   # - **Modifica el DOM** si quieres: por ejemplo, cambiar un botón de "No hay citas" por "¡Sí hay!"  
│   # - **Envía mensajes** al background.js o al popup si se necesita avisar de algo.  
│   # **Es el que interactúa DIRECTAMENTE con el mundo exterior, con la página real.**  
│  
├── **popup.html**  
│   # El popup es la **ventanita** que se abre al picarle al ícono de tu extensión.  
│   # Archivo HTML que define la ventana emergente ("popup") que ves al hacer click en el ícono de la extensión.
│   # Aquí están los elementos visuales:
│   # - Botones para activar o detener funciones.
│   # - Mensajes de estado o instrucciones.
│   # - Inputs o selectores si quieres pedirle algo al usuario.
│   # Archivo HTML que define la ventana emergente ("popup") que ves al hacer click en el ícono de la extensión.
│   # Aquí están los elementos visuales:
│   # - Botones para activar o detener funciones.
│   # - Mensajes de estado o instrucciones.
│   # - Inputs o selectores si quieres pedirle algo al usuario.
│   # Este archivo define su **estructura visual**:  
│   # - Botones ("Iniciar búsqueda", "Detener búsqueda").  
│   # - Textos ("Estado: buscando citas", "Configuraciones").  
│   # - Inputs (por ejemplo, para que elijas el intervalo de tiempo entre revisiones).  
│   # **Es puro HTML, todavía no hay lógica, sólo acomoda los elementos.**  
│  
├── **.vscode/**  
│   └── **settings.json**  
│       # Configuración de tu editor de código (Visual Studio Code), nada que afecte la extensión.  
│       # Sirve para que tu editor se vea y trabaje como te gusta:  
│       # - ¿Usas 2 espacios o 4 espacios?  
│       # - ¿Te gusta que autoformatee el código?  
│       # - ¿Quieres que te detecte errores automáticos?  
│       # Solo es para **tu comodidad al programar**, no se distribuye ni pesa.  
│  
├── **images/**  
│   ├── **128X128TL1.png**  
│   ├── **128X128TV1.png**  
│   ├── **client_ico_256.ico**  
│   ├── **icon.png**  
│   ├── **icon48.png**  
│   ├── **icono.ico**  
│   └── **iconr.png**  
│   # Carpeta de **iconos e imágenes** de la extensión:  
│   # - Los íconos aparecen en la barra de Chrome.  
│   # - También puedes usarlos dentro del popup o para notificaciones.  
│   # **Tienen diferentes tamaños** porque Chrome a veces te los pide en 16x16, 48x48, 128x128 o más.  
│   # No ejecutan nada, son puro "look bonito".  
│  
└── **assd/**  
    ├── **background.js**  
    │   # Este script es el "fantasma" que **siempre corre aunque no abras nada**.
    │   # Script que corre en segundo plano de manera invisible, siempre que Chrome esté abierto.
    │   # Su función es:
    │   # - Escuchar eventos (como alarmas programadas, cambios de conexión, mensajes internos de la extensión).
    │   # - Lanzar acciones automáticas sin necesidad de que el usuario abra el popup.
    │   # Ideal para tareas que deben seguir funcionando aunque el popup esté cerrado.
      
    │   # ¿Qué hace el pinche background?  
    │   # - Recibe alarmas programadas ("cada 10 minutos, busca citas").  
    │   # - Escucha mensajes de content.js o popup.js.  
    │   # - Puede lanzar notificaciones ("¡Nueva cita disponible!").  
    │   # - Puede guardar datos (como estados, logs).  
    │   # **Es el encargado de la inteligencia a largo plazo.**  
    │  
    ├── **options.html**  
    │   # Página de **configuraciones** de la extensión.  
    │   # Página HTML de configuración avanzada de la extensión.
    │   # Permite que el usuario ajuste preferencias (por ejemplo: activar notificaciones, cambiar intervalos de búsqueda, etc).
    │   # Normalmente se accede a esta página haciendo clic derecho en el ícono de la extensión -> "Opciones".
    │
    │   # Aquí el usuario puede:  
    │   # - Activar o desactivar funciones automáticas.  
    │   # - Cambiar intervalos de tiempo entre revisiones.  
    │   # - Ajustar qué tipo de citas buscar.  
    │   # Se accede con clic derecho → "Opciones" en el ícono de la extensión.  
    │  
    ├── **styles/**  
    │   └── **popup.css**  
    │       # La **ropa** de tu popup:  
    │       # Hoja de estilos CSS que da formato visual al popup y a las páginas de la extensión:
    │       # - Define colores, tamaños de letra, márgenes, bordes, etc.
    │       # - Hace que el popup se vea más profesional y no como una página HTML simple. 
    │       # - Colores de fondo, tipos de letra, márgenes.  
    │       # - Botones más bonitos.  
    │       # - Estilos de inputs y mensajes.  
    │       # **Solo cambia cómo se ve todo, no la lógica.**  
    │  
    └── **script/**  
        └── **popup.js**  
            # Este es el **cerebro** de la ventanita popup:  
            # Script que controla toda la lógica de comportamiento dentro del popup:
            # - Detecta clics en botones o cambios en inputs.
            # - Manda mensajes al background.js o content.js si es necesario.
            # - Guarda configuraciones en el almacenamiento de Chrome.
            # - Actualiza el contenido del popup en tiempo real (como cambiar un estado de "Activo" a "Detenido").
            # - Detecta cuando das click en un botón ("Iniciar búsqueda").  
            # - Cambia mensajes ("Estado: Activo" o "Estado: Detenido").  
            # - Manda órdenes a background.js ("oye wey, empieza a buscar citas").  
            # - Lee o guarda configuraciones en el almacenamiento de Chrome.  
            # - Puede actualizar dinámicamente la información del popup en tiempo real.  
            # **Se conecta con todo el backend de la extensión.**

---

¿Así o más explicado, pinche vato? 😂  
¿Quieres que también te haga un esquema de **cómo se comunican entre ellos** (tipo flechitas de mensajes popup → background → content) para que quede todavía más mamalón? 🚀  
¿Te lo paso?

******************************************************************************************


******************************
🔗 Comunicación en la extensión:

[Pantalla del usuario]
        ↓ (hace clic en ícono)
[popup.html]  →  [popup.js]
    - Muestra botones e inputs
    - Captura acciones del usuario
        ↓ (cuando haces clic)
  Manda mensaje a ➡ [background.js]
    - "Inicia búsqueda"
    - "Detén búsqueda"
    - "Guarda configuración"

[background.js]
    - Recibe el mensaje
    - Programa alarmas
    - Toma acciones automáticas
    - A veces, manda mensaje a ➡ [content.js]
      ("actualiza algo en la página")
    - O manda notificaciones al usuario

[content.js]
    - Vive dentro de las páginas web
    - Modifica o lee la página
    - Detecta cambios (por ejemplo: hay cita disponible)
        ↓
    - Puede mandar mensaje de regreso a ➡ [background.js]
      ("¡Detecté cita disponible!")

[background.js]
    - Recibe aviso de content.js
    - Puede:
        - Lanzar notificación
        - Activar una acción
        - Guardar datos

[popup.js]
    - Puede actualizarse en tiempo real si background le avisa
      (por ejemplo: mostrar "¡Nueva cita!" en la ventanita)

[options.html + opciones guardadas]
    - Almacenadas en Chrome Storage
    - Las usan popup.js, background.js y content.js para actuar diferente según configuraciones del usuario
⚡Resumen rapidito:

¿Quién?	¿Qué hace?	¿Con quién habla?
popup.js	Recibe clicks y manda órdenes	background.js
background.js	Administra alarmas, lógica, escucha todo	popup.js, content.js
content.js	Lee y cambia la página web	background.js
options.html	Guarda configuraciones	Todos leen la configuración
popup.css	Solo da estilo visual	Nadie (solo viste al popup)
imágenes	Solo decoran	Nadie (nomás adornan)
**********************************************************















1. Archivo manifest.json
Este archivo es como el cerebro de la extensión. Le dice a Chrome qué hacer con los archivos de la extensión (popup, content.js, background.js, etc.). No se puede ocultar, pero solo define los permisos y archivos que se usan.

2. content.js
Este archivo es el que se inyecta en las páginas donde quieres que tu extensión haga algo (como extraer citas o modificar contenido). Este es el que se ve en la consola de Chrome cuando alguien inspecciona la página, porque está funcionando directamente sobre la web. Este es el más "peligroso", porque puede ser copiado fácilmente.

3. popup.js y background.js
Estos archivos se ejecutan en segundo plano y no tienen acceso directo a la página web, por lo que no pueden ser copiados directamente desde la consola del navegador.







mi_ext_uno/
│
├── assd/
│   ├── images/
│   │   ├── 128X128TV1.png
│   │   ├── 128X128TL1.png
│   │   └── iconr.png
│   ├── styles/
│   │   └── popup.css
│   └── script/
│       └── popup.js
│
├── src/
│   ├── background.js
│   ├── content.js
│   ├── popup.html
│   └── options.html
├── manifest.json
├── .gitignore
├── README.md
