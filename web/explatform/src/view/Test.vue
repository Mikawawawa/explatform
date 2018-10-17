<template>
    <div>
        <p>{{test}}</p>
        <p>{{login}}</p>
        <p>{{sexp}}</p>
        <p>{{this.$dataSource.request}}</p>
    </div>
</template>

<script>
export default {
    name:"test",
    data:()=>({
        test:"",
        login:""
    }),
    created:async function(){
        this.test=this.$appName
        // console.log(this.$dataSource)
        this.login=await this.$dataSource.Login("17031803","aptx4869")
        this.sexp=await this.$dataSource.sGetExp("17041802","101")
    }
}
</script>

