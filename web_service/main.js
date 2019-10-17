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



// Express http server
const app = express()


// WebSocket server to communicate with Staff device
const staffSocket = ws(app)


// Routing ressources
app.get(argv.ressource, (req,res)=> res.send('Hello'))


// Attaching to port
app.listen(argv.port, () =>
    console.info('Started Staff server <hostname>:%d%s', argv.port, argv.ressource))
