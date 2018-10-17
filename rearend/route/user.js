const app = require("express").Router()
const user=require("../service/UserService")
var bodyParser = require("body-parser");
app.use(bodyParser.urlencoded({extended:true}));
app.post("/login", async (req, res) => {

    let params=await user.login(req.body.id,req.body.password)
    res.send(JSON.stringify(
        params
    ))
})
app.get("/get_power", async (req, res) => {
    let powers =await user.get_power(req.query.id)
    res.send(JSON.stringify(
        powers
    ))
})

app.get("/get_qrcode",async (req,res)=>{
    res.sendfile(await user.getQrcode(req.query.type,req.query.id))
})
module.exports = app