const express = require('express');
const router = express.Router();

/* GET users listing. */
router.get('/', function(req, res, next) {
  res.send({
    code:1,
    info:"informations"
  });
});

module.exports = router;
