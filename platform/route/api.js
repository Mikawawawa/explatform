const app = require("express").Router()

app.get("/", (req, res) => {
    res.send(JSON.stringify({
        route: "api",
        msg: "ok"
    }))
})

module.exports = app