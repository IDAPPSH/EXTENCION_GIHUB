document.addEventListener("DOMContentLoaded", () => {
    console.log("🔹 Popup cargado.");

    // Cargar valores guardados
    chrome.storage.sync.get(["id", "locationAsc", "MAX_MONTHS", "MULTIPLOS", "MILIISEG", "ejecutar"], (config) => {
        document.getElementById("id_consulado").value = config.id || "";
        document.getElementById("id_asc").value = config.locationAsc || "";
        document.getElementById("max_months").value = config.MAX_MONTHS || "";
        document.getElementById("multiplo").value = config.MULTIPLOS || "";
        document.getElementById("milisegundos").value = config.MILIISEG || "";

        // Cambiar el estado del botón según si está ejecutando o no
        actualizarBoton(config.ejecutar);
    });

    // Botón para guardar y ejecutar
    document.getElementById("guardar").addEventListener("click", async () => {
        console.log("🔹 Guardando configuración...");

        // Obtener valores ingresados
        const id = document.getElementById("id_consulado").value;
        const locationAsc = document.getElementById("id_asc").value;
        const MAX_MONTHS = document.getElementById("max_months").value;
        const MULTIPLOS = document.getElementById("multiplo").value;
        const MILIISEG = document.getElementById("milisegundos").value;

        // Guardar en almacenamiento de Chrome y activar ejecución
        chrome.storage.sync.set({
            id,
            locationAsc,
            MAX_MONTHS,
            MULTIPLOS,
            MILIISEG,
            ejecutar: true // Indicar que debe ejecutarse el script
        }, () => {
            console.log("✅ Configuración guardada correctamente.");

            // Verificar que se guardó correctamente
            chrome.storage.sync.get(["id", "locationAsc", "MAX_MONTHS", "MULTIPLOS", "MILIISEG", "ejecutar"], (config) => {
                console.log("🔹 Configuración almacenada:", config);
            });

            // Ejecutar el script en la página activa
            chrome.tabs.query({ active: true, currentWindow: true }, (tabs) => {
                if (tabs.length === 0) {
                    console.error("❌ No se encontró una pestaña activa.");
                    return;
                }

                chrome.scripting.executeScript({
                    target: { tabId: tabs[0].id },
                    files: ["content.js"]
                }).then(() => {
                    console.log("✅ Script ejecutado en la página.");
                    actualizarBoton(true);
                }).catch((err) => {
                    console.error("❌ Error al ejecutar script:", err);
                });
            });
        });
    });

    // Botón para detener la ejecución
    document.getElementById("detener").addEventListener("click", () => {
        console.log("⏹️ Deteniendo ejecución...");
        chrome.storage.sync.set({ ejecutar: false }, () => {
            console.log("✅ Ejecución detenida.");
            actualizarBoton(false);
        });
    });

    // Función para actualizar el texto del botón según estado de ejecución
    function actualizarBoton(enEjecucion) {
        const botonGuardar = document.getElementById("guardar");
        const botonDetener = document.getElementById("detener");

        if (enEjecucion) {
            botonGuardar.textContent = "Ejecutando...";
            botonGuardar.disabled = true;
            botonDetener.disabled = false;
        } else {
            botonGuardar.textContent = "Guardar y Ejecutar";
            botonGuardar.disabled = false;
            botonDetener.disabled = true;
        }
    }
});
