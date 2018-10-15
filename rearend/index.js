const express = require("express")
const logger = require('morgan');
const cookieParser = require('cookie-parser');
const createError = require("http-errors")

const config = require("./config.json")

const userRouter = require("./route/user")
const studentRouter = require("./route/student")
const teacherRouter = require("./route/teacher")

const app = express();

app.all('*', function(req, res, next) {
    res.header("Access-Control-Allow-Origin", "*");
    res.header('Access-Control-Allow-Methods', 'PUT, GET, POST, DELETE, OPTIONS');
    res.header("Access-Control-Allow-Headers", "X-Requested-With");
    res.header('Access-Control-Allow-Headers', 'Content-Type');
    next();
});

app.use("/api/user", userRouter)
app.use("/api/student", studentRouter)
app.use("/api/teacher", teacherRouter)

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({
    extended: false
}));
app.use(cookieParser());

app.use(express.static(config.static));

app.use(function (req, res, next) {
    createError(404)
    next();
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

app.listen(config.port);