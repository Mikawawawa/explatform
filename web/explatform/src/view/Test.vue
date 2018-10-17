<template>
    <div>
        <p>{{test}}</p>
        <p>{{login}}</p>
        <p>{{course}}</p>
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
        course:"",
        texp:""
    }),
    created:async function(){
        this.test=this.$appName
        // console.log(this.$dataSource)
        this.login=await this.$dataSource.Login("17031803","aptx4869")
        this.test=await this.$dataSource.getExplist("101")
        this.course=await this.$dataSource.sGetCourse("17041803")
        console.log(this.test)
    }
}
</script>

