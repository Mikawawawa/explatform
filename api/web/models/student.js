const connection = require("./connect")

function test(config, callback) {
    console.log(callback)
    connection.query("select * FROM `user`", (err, rows, fields) => {
        console.log(rows)
        console.log(err)
        callback(rows)
    })
}

module.exports = {
    'test': test
}