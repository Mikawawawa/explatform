const mysql = require('mysql');
const config = require('../config.json');
const connection = mysql.createConnection(config.mysql);
connection.connect();
connection.on("connect", () => {
    console.log("ok")
})

module.exports = connection