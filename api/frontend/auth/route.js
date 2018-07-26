const express = require('express');
const md5 = require('md5');
const router = express.Router();

router.get('/', function (req, res) {
    if (req.session.key) {
        res.send({
            code: 1,
            info: req.session.key
        });
    } else {
        res.send("Not login")
    }
});

router.get('/login', function (req, res) {
    if (!req.session.key) {
        req.session.key = md5(new Date().getDate())
        res.send("login")
    } else {
        res.send("has login")
    }
})

module.exports = router;