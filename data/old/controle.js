function executa(numTecla) {
  let linha = document.createElement("div")
  linha.setAttribute("class", "row")

  let div_input = document.createElement("div")
  div_input.setAttribute("class", "input-field col s7")

  let input_text = document.createElement("input")
  input_text.setAttribute("type", "text")
  input_text.setAttribute("placeholder", "Letras a enviar")
  input_text.setAttribute("id", "tecla"+numTecla)
  input_text.setAttribute("name", "tecla"+numTecla)

  let label = document.createElement("label")
  label.setAttribute("for", "tecla"+numTecla)
  label.setAttribute("class", "active")
  label.textContent = "Tecla "+numTecla

  div_input.appendChild(input_text)
  div_input.appendChild(label)


  let checkbox_ctrl = document.createElement("input")
  checkbox_ctrl.setAttribute("type","checkbox")
  checkbox_ctrl.setAttribute("class","filled-in col s6")
  checkbox_ctrl.setAttribute("checked","")
  checkbox_ctrl.setAttribute("name","teclactrl_"+numTecla)

  let span_ctrl = document.createElement("span")
  span_ctrl.textContent = "CTRL"

  let checkbox_alt = document.createElement("input")
  checkbox_alt.setAttribute("type","checkbox")
  checkbox_alt.setAttribute("class","filled-in col s6")
  checkbox_alt.setAttribute("checked","")
  checkbox_alt.setAttribute("name","teclaalt_"+numTecla)
  let span_alt = document.createElement("span")
  span_alt.textContent = "ALT"

  let checkbox_shift = document.createElement("input")
  checkbox_shift.setAttribute("type","checkbox")
  checkbox_shift.setAttribute("class","filled-in col s6")
  checkbox_shift.setAttribute("checked","")
  checkbox_shift.setAttribute("name","teclashift_"+numTecla)
  let span_shift = document.createElement("span")
  span_shift.textContent = "SHIFT"

  let genericLabel1 = document.createElement("label")
  genericLabel1.appendChild(checkbox_ctrl)
  genericLabel1.appendChild(span_ctrl)

  let genericLabel2 = document.createElement("label")
  genericLabel2.appendChild(checkbox_alt)
  genericLabel2.appendChild(span_alt)

  let genericLabel3 = document.createElement("label")
  genericLabel3.appendChild(checkbox_shift)
  genericLabel3.appendChild(span_shift)

  linha.appendChild(div_input)
  linha.appendChild(genericLabel1)
  linha.appendChild(genericLabel2)
  linha.appendChild(genericLabel3)

  let substitui = document.getElementById("aqui")
  substitui.appendChild(linha);
}

function perfil(adicionaCor) {
  let teclas = document.getElementById("teclas")

  teclas.className = "card-content"
  if(Array.isArray(adicionaCor.split(" "))) {
    adicionaCor.split(" ").forEach((cor) => teclas.classList.add(cor))
  } else {
    teclas.classList.add(adicionaCor)
  }
}

document.addEventListener("DOMContentLoaded", function(event) {
  for (let index = 1; index <= 11; index++) {
    executa(index)
  }
});
