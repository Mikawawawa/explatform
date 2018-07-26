const createError = require('http-errors');
const express = require('express');
const path = require('path');
const cookieParser = require('cookie-parser');
const logger = require('morgan');

const teacherRouter = require('./routes/teacher');
const studentRouter = require('./routes/student');
const classRouter = require('./routes/class');
const eventRouter = require('./routes/event');

const app = express();

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser());
app.use(express.static(path.join(__dirname, 'public')));

app.use('/teacher', teacherRouter);
app.use('/student', studentRouter);
app.use('/class',classRouter);
app.use('/event',eventRouter);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  let status=err.message=="Not Found"?404:500
  res.status(status);
  res.send({
    code:status,
    info:err.message
  })
});

module.exports = app;
