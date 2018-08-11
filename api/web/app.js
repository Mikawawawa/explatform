const express = require('express');
const app = express();
const express = require('express');
const path = require('path');
const cookieParser = require('cookie-parser');
const logger = require('morgan');

const session = require('express-session');
const RedisStore = require('connect-redis')(session);

const teacherRouter = require('./routes/teacher');
const studentRouter = require('./routes/student');
const subjectRouter = require('./routes/subject');
const adminRouter = require('./routes/admin');


const options = {
    "host": "123.206.176.72",
    "port": "6379",
    "ttl": 60 * 60 * 24 * 30, //Session的有效期为30天
};
  
const domin=''

// 此时req对象还没有session这个属性
  app.use(session({
    store: new RedisStore(options),
    secret: 'explatform',
    resave: true,
    saveUninitialized: true
}));

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({
  extended: false
}));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use(`/${domin}teacher`, teacherRouter);
app.use(`/${domin}student`, studentRouter);
app.use(`/${domin}class`, subjectRouter);
app.use(`/${domin}event`, adminRouter);

// catch 404 and forward to error handler
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

app.listen(8040);