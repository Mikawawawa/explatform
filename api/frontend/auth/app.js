const express = require('express');
const createError = require('http-errors');
const cookieParser = require('cookie-parser');

var session = require('express-session');
var RedisStore = require('connect-redis')(session);

const app = express();
const options = {
    "host": "123.206.176.72",
    "port": "6379",
    "ttl": 60 * 60 * 24 * 30, //Session的有效期为30天
};

// 此时req对象还没有session这个属性
app.use(session({
    store: new RedisStore(options),
    secret: 'explatform',
    resave: true,
    saveUninitialized: true
}));

const router = require('./route');

app.use(express.json());
app.use(express.urlencoded({
    extended: false
}));
app.use(cookieParser());

app.use('/', router);

app.use(function (req, res, next) {
    next(createError(404));
});

// error handler
app.use(function (err, req, res, next) {
    // set locals, only providing error in development
    res.locals.message = err.message;
    res.locals.error = req.app.get('env') === 'development' ? err : {};

    // render the error page
    let status = err.message == "Not Found" ? 404 : 500
    res.status(status);
    res.send({
        code: status,
        info: err.message
    })
});

const server = app.listen(3001, function () {
    const host = server.address().address;
    const port = server.address().port;

    console.log('Start listening at http://%s:%s', host, port);
});