const webpack = require('webpack')
const bodyParser = require('body-parser')
const express = require('express')
const ws = require('express-ws')
const argv = require('yargs')
    // Options
    .alias('p', 'port')
    .default('port', '80')
    .alias('r', 'ressource')
    .default('ressource', '/')
    .argv

// Ensuring ressource path starts with '/'
if (argv.ressource[0] !== '/')
    argv.ressource = '/' + argv.ressource


function StartServer() {

    // Express http server
    const app = express()


    // WebSocket server to communicate with Staff device
    const staffSocket = ws(app)


    // Routing ressources
    app.use(argv.ressource, express.static('dist'))


    // Usr commands
    app.post(argv.ressource, bodyParser.json(), (req, res)=> {
        console.log(req.body)
        res.send()
    })


    // Attaching to port
    app.listen(argv.port, () =>
        console.info('Started Staff server <hostname>:%d%s', argv.port, argv.ressource))
}


// Build web app
webpack(require('./webpack.config'), (err, stats) => {
    if (err || stats.hasErrors()) {
        console.error('Failed to build web page')
    }

    StartServer()
})
