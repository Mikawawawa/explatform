<template>
    <div>
        <p>{{test}}</p>
        <p>{{login}}</p>
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
    created:function(){
        this.test=this.$appName
        // console.log(this.$dataSource)
        this.login=this.$dataSource.Login("17031803","aptx4869")
    }
}
</script>

