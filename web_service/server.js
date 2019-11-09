const webpack = require('webpack')
const express = require('express')
const ws = require('express-ws')
const { param, validationResult } = require('express-validator')
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


// Send data to all devices
function SendCommand(command, server)
{
    server.getWss().clients.forEach(client => {
        if (client.readyState === 1)
            client.send(command)
    })
}


function StartServer() {

    // Express http server
    const app = express()


    // WebSocket server to communicate with Staff device
    const socketServer = ws(app)
    app.ws(argv.ressource, (socket, req) => {
        console.log('Client socket open')
    })


    // Routing ressources
    app.use(argv.ressource, express.static('dist'))


    // Color Change request
    app.post(
        argv.ressource+'color/:color',
        param('color').isHexColor(),
        (req, res) => {
            if (!validationResult(req).isEmpty())
                return res.status(400).send()

            console.log(`New color request: #${req.params.color}`)

            // Sending color to staff
            SendCommand('#'+req.params.color, socketServer)

            res.send()
        })

    // Action request
    app.post(
        argv.ressource+'action/:action',
        param('action').isInt({min:1,max:5}),
        (req, res) => {
            if (!validationResult(req).isEmpty())
                return res.status(400).send()

            console.log(`New action request: ${req.params.action}`)

            // Sending action to staff
            SendCommand(req.params.action, socketServer)

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
        process.exit(1)
    }

    StartServer()
})
