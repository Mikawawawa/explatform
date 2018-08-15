const express = require('express');
const app = express();
// const path = require('path');
const createError = require('http-errors');
const cookieParser = require('cookie-parser');
const logger = require('morgan');

const session = require('express-session');
const RedisStore = require('connect-redis')(session);

const teacherRouter = require('./routes/teacher');
const studentRouter = require('./routes/student');
const managerRouter = require('./routes/manager');
const adminRouter = require('./routes/admin');
// 把所有的配置参数移动到config.json
const config = require("./config.json")
const domin = config.domin

app.use(session({
  // redis可能被玩坏了，明天我部署一个docker版的再开，暂时存在内存
  // store: new RedisStore(config.session),
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
// 这次估计没有静态文件
// app.use(express.static(path.join(__dirname, 'public')));

app.use(`/teacher`, teacherRouter);
app.use(`/student`, studentRouter);
app.use(`/manager`, managerRouter);
app.use('/admin', adminRouter);

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

app.listen(config.port);