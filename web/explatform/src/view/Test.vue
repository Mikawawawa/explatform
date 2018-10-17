<template>
    <div>
        <p>{{test}}</p>
        <p>{{login}}</p>
        <p>{{sexp}}</p>
        <p>{{texp}}</p>
        <p>{{tcourse}}</p>
        <p>{{this.$dataSource.request}}</p>
    </div>
</template>

<script>
export default {
    name:"test",
    data:()=>({
        test:"",
        login:"",
        sexp:"",
        tcourse:"",
        texp:""
    }),
    created:async function(){
        //this.test=this.$appName
        this.login=await this.$dataSource.Login("17031803","aptx4869")
        this.test=await this.$dataSource.getExplist("101")
        console.log(this.test)
    }
}
</script>

