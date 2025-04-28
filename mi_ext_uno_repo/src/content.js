// content.js
chrome.runtime.onMessage.addListener((message, sender, sendResponse) => {
    if (message.action === 'startScript') {
        const CONFIGURACION = message.config;
        console.log("Configuración recibida en content.js:", CONFIGURACION);

        (async () => {
            console.log("AutoAgenda Visa - Extensión activada");

            const BASE_URL_TEMPLATE = "https://ais.usvisa-info.com/es-mx/niv/schedule/{id}/appointment";
            const locationId = CONFIGURACION.id;
            const locationAsc = CONFIGURACION.locationAsc;
            const MAX_MONTHS = CONFIGURACION.MAX_MONTHS;
            const MULTIPLOS = CONFIGURACION.MULTIPLOS;
            const MILIISEG = CONFIGURACION.MILIISEG;

            const MAX_REINTENTOS = 3;
            const RETRY_DELAY_ERROR = 1000;
            const RETRY_DELAY_NO_RESULTS = 1303;

            const botToken = '8146370620:AAHOD-4rLVys2xkkLXIsto9JH8O0a68J-Vs';
            const chatIds = ['-1002482067568'];

            let detenerEjecucion = false;
            let scriptListo = false;

            const notificacion = async (mensaje) => {
                for (const chatId of chatIds) {
                    await fetch(`https://api.telegram.org/bot${botToken}/sendMessage`, {
                        method: 'POST',
                        headers: { 'Content-Type': 'application/json' },
                        body: JSON.stringify({ chat_id: chatId, text: mensaje }),
                    });
                }
            };

            const obtenerId = () => {
                const formElement = document.querySelector("#appointment-form");
                if (!formElement) throw new Error("Formulario no encontrado.");
                const actionUrl = formElement.getAttribute("action");
                if (!actionUrl) throw new Error("Atributo 'action' no encontrado.");
                const match = actionUrl.match(/\/schedule\/(\d+)\//);
                if (!match || !match[1]) throw new Error("ID no extraído.");
                return match[1];
            };

            const configurarUrl = () => {
                return BASE_URL_TEMPLATE.replace("{id}", obtenerId());
            };

            async function waitForAddressUpdate() {
                return new Promise((resolve) => {
                    const addressNode = document.getElementById('appointments_consulate_address');
                    const observer = new MutationObserver((mutations) => {
                        for (const mutation of mutations) {
                            if (mutation.type === 'childList' || mutation.type === 'characterData' || mutation.type === 'subtree') {
                                observer.disconnect();
                                resolve();
                                break;
                            }
                        }
                    });
                    observer.observe(addressNode, { childList: true, subtree: true, characterData: true });
                });
            }

            const fetchData = async (url) => {
                const locationSelect = document.getElementById("appointments_consulate_appointment_facility_id");
                if (locationSelect) {
                    locationSelect.value = locationId;
                    locationSelect.dispatchEvent(new Event("change", { bubbles: true }));
                    await waitForAddressUpdate();
                } else {
                    console.error(`${locationId} NO SE ACTUALIZO`);
                }

                try {
                    const response = await fetch(url, {
                        headers: {
                            "X-Requested-With": "XMLHttpRequest",
                            "Content-Type": "application/json",
                        },
                        credentials: "include",
                        timeout: 3000
                    });

                    if (!response.ok) {
                        throw new Error(`Error al cargar ${url} - Estado: ${response.status}`);
                    }

                    const data = await response.json();
                    return data;
                } catch (error) {
                    console.error(`Error en fetchData: ${error.message}`);
                    return null;
                }
            };

            const realizarSolicitud = async (url, maxReintentos = 2) => {
                let intento = 0;

                while (intento < maxReintentos) {
                    try {
                        const response = await fetch(url, {
                            method: "GET",
                            headers: {
                                "X-Requested-With": "XMLHttpRequest",
                            },
                            timeout: 2000
                        });

                        if (!response.ok) {
                            throw new Error(`Error HTTP: ${response.status}`);
                        }

                        const data = await response.json();
                        return data;

                    } catch (error) {
                        intento++;

                        if (intento < maxReintentos) {
                            await new Promise(resolve => setTimeout(resolve, 1300));
                        } else {
                            location.reload();
                            return null;
                        }
                    }
                }
            };

            const seleccionarFechaYHora = async (fecha) => {
                const dateInput = document.getElementById("appointments_consulate_appointment_date");
                if (!dateInput) return console.error("No se encontró el campo de fecha.");
                dateInput.value = fecha;
                dateInput.dispatchEvent(new Event("input", { bubbles: true }));
                dateInput.dispatchEvent(new Event("change", { bubbles: true }));
                await new Promise((resolve) => setTimeout(resolve, 200));

                document.querySelector("#appointments_consulate_appointment_date").click();
                await new Promise((resolve) => setTimeout(resolve, 200));

                const celdasFecha = document.querySelectorAll('td[data-handler="selectDay"]:not(.ui-datepicker-unselectable)');
                const mes = document.querySelector('.ui-datepicker-month').innerText;
                const año = document.querySelector('.ui-datepicker-year').innerText;

                const fechasDisponibles = Array.from(celdasFecha).map(celda => {
                    const enlace = celda.querySelector('a');
                    if (enlace) {
                        const dia = enlace.innerText.padStart(2, '0');
                        const mesFormato = (new Date(Date.parse(mes + " 1, 2025"))).getMonth() + 1;
                        const fechaCompleta = `${año}-${mesFormato.toString().padStart(2, '0')}-${dia}`;
                        return { fechaCompleta, enlace };
                    }
                }).filter(Boolean);

                if (fechasDisponibles.length > 1) {
                    const segundaFecha = fechasDisponibles[1];
                    segundaFecha.enlace.click();
                    await new Promise((resolve) => setTimeout(resolve, 300));
                } else if (fechasDisponibles.length === 1) {
                    const unicaFecha = fechasDisponibles[0];
                    unicaFecha.enlace.click();
                    await new Promise((resolve) => setTimeout(resolve, 300));
                }
            };

            const intentarObtenerFechaYHora = async (id) => {
                const BASE_URL = configurarUrl();

                while (!scriptListo) {
                    for (let intento = 1; intento <= MAX_REINTENTOS; intento++) {
                        try {
                            const fechasURL = `${BASE_URL}/days/${id}.json?appointments[expedite]=false`;
                            const fechas = await fetchData(fechasURL);

                            if (fechas?.length > 0) {
                                const hoy = new Date();
                                const limite = new Date(hoy);
                                limite.setMonth(hoy.getMonth() + MAX_MONTHS);
                                const fechasValidas = fechas.filter((fecha) => {
                                    const fechaDate = new Date(fecha.date);
                                    return fechaDate >= hoy && fechaDate <= limite;
                                });
                                const primeraFecha = fechasValidas.length > 1 ? fechasValidas[1].date : fechasValidas[0].date;
                                await seleccionarFechaYHora(primeraFecha);

                                const timesUrl = `${BASE_URL}/times/${locationId}.json?date=${primeraFecha}&appointments[expedite]=false`;
                                const horarios = await realizarSolicitud(timesUrl);
                                if (horarios?.length > 0) {
                                    return horarios[0].time;
                                }
                            }
                        } catch (error) {
                            console.error(`Error en intentarObtenerFechaYHora: ${error.message}`);
                        }
                    }
                    await new Promise(resolve => setTimeout(resolve, RETRY_DELAY_ERROR));
                }
            };

            await intentarObtenerFechaYHora(CONFIGURACION.id);
        })();
    }
});
