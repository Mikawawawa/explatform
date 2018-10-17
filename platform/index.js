const express = require("express")
const logger = require('morgan');
const cookieParser = require('cookie-parser');
const createError = require("http-errors")

const config = require("./config.json")
const apiRouter = require("./route/router")

const app = express();

app.use("*",(req,res,next)=>{
    console.log(req.url)
    next()
})

app.use("/", apiRouter)


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
