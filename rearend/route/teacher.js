const app = require("express").Router()

app.get("/get_exp", (req, res) => {
    res.send(JSON.stringify({
        route: "api",
        msg: "ok"
    }))
})
app.get("/set_grade", (req, res) => {
    res.send(JSON.stringify({
        route: "api",
        msg: "ok"
    }))
})
app.get("/get_report", (req, res) => {
    res.send(JSON.stringify({
        route: "api",
        msg: "ok"
    }))
})
app.get("/get_course", (req, res) => {
    res.send(JSON.stringify({
        route: "api",
        msg: "ok"
    }))
})
app.get("/start_exp", (req, res) => {
    res.send(JSON.stringify({
        route: "api",
        msg: "ok"
    }))
})

module.exports = app