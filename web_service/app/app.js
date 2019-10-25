import '../node_modules/materialize-css/dist/js/materialize.min.js'
const axios = require('axios').default
const AColorPicker = require('a-color-picker')




AColorPicker.from('.picker', {
    slBarSize:[600, 400],
    hueBarSize:[500, 40]
}).on('change', (picker, color) => {

    axios.post('/', { "color": color })
})

var buttons = document.getElementsByClassName("btn-large")
for (let button of buttons){
    button.addEventListener("click", ()=> {
        axios.post('/', { "action": button.name })
    })
}

