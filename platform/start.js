var c = require('child_process');
var config = require("./config.json")
c.exec(`start http://localhost:${config.port}`);