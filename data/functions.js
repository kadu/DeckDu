let persistKeys = [];
let mcButton = "";

const btnClick = (pressedKey) => {
    persistKeys.push(pressedKey);
    console.log(persistKeys);

    let keys = document.getElementById('displaykeys');

    keys.textContent += addPlus(keys) + pressedKey;
    checkGarbage();
}

const addPlus = (keys) => {
    return keys.textContent.length > 0 ? "+" : "";
}

const btnGarbageClick = () => {
    persistKeys = [];
    document.getElementById('displaykeys').textContent = "";
    checkGarbage();
}

const checkGarbage = () => {
    const mustHide = document.getElementById('displaykeys').textContent.length == 0;
    document.getElementById('garbage').hidden = mustHide;
    document.getElementById('save').hidden = mustHide;

}

const btnSaveClick = () => {

    let obj = {
        button: mcButton,
        keys: persistKeys
    }

    console.log("JSON AQUI");
    console.log(JSON.stringify(obj));
    console.log("JSON AQUI#FIM");

    var url = "/rest/teclado";

    fetch(url, {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(obj)
        })
        .then(function (response) {
            if (response.ok) {
                return response.json();
            }
            throw new Error("Erro na solicitação.");
        })
        .then(function (responseData) {
            console.log(responseData);
        })
        .catch(function (error) {
            console.log(error);
        });
}

document.addEventListener("DOMContentLoaded", function (e) {
    checkGarbage();

    const params = new Proxy(new URLSearchParams(window.location.search), {
        get: (searchParams, prop) => searchParams.get(prop),
    });
    mcButton = params.button;

    document.getElementById("showMcButton").textContent = "Tecla " + mcButton;
});