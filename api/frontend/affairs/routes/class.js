const express = require('express');
const router = express.Router();

/* GET users listing. */
router.get('/', function (req, res, next) {
  if (req.session.key) {
    res.send({
      code: 1,
      info: req.session.key
    });
  } else {
    res.send({
      code: 0,
      info: "has not logined"
    });
  }
});

module.exports = router;