const app = require("express").Router()

app.get("/login", (req, res) => {
    res.send(JSON.stringify({
        route: "api",
        msg: "ok"
    }))
})
app.get("/get_power", (req, res) => {
    res.send(JSON.stringify({
        route: "api",
        msg: "ok"
    }))
})
module.exports = app