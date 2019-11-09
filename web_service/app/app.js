import '../node_modules/materialize-css/dist/js/materialize.min.js'
const axios = require('axios').default
const AColorPicker = require('a-color-picker')
const rgbHex = require('rgb-hex');



/*
// WebSocket debugging in the browser
var socket = new WebSocket(`ws://${window.location.host}`);
socket.onopen = event => {
    console.log("Socket connected")
}
socket.onmessage = event => {
    console.log(event.data)
}
*/


// The color picker
AColorPicker.from('.picker', {
    slBarSize:[600, 400],
    hueBarSize:[500, 40]
}).on('change', (picker, color) => {

    axios.post(`/color/${rgbHex(color)}`)
})

// Button listeners
var buttons = document.getElementsByClassName("btn-large")
for (let button of buttons){
    button.addEventListener("click", ()=> {
        axios.post(`/action/${button.id}`)
    })
}

