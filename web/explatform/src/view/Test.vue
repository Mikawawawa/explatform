<template>
    <div>
        <p>{{test}}</p>
        <p>{{login}}</p>
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
        <p>{{sexp}}</p>
        <p>{{texp}}</p>
        <p>{{tcourse}}</p>
>>>>>>> 19d29b0579a86b37a16392588f532cf7468eec2b
>>>>>>> 8cf7668cac1e37fcf928adc96b6ca26c1c4ec96f
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
<<<<<<< HEAD
=======
=======
        this.test=this.$appName
        // console.log(this.$dataSource)
        this.login=await this.$dataSource.Login("17031803","aptx4869")
        this.sexp=await this.$dataSource.sGetExp("17041802","101")
        this.tcourse=await this.$dataSource.tGetCourse("17031803")
        this.texp=await this.$dataSource.tCourseDetail("17040318")
        // console.log(this.sexp)
>>>>>>> 19d29b0579a86b37a16392588f532cf7468eec2b
>>>>>>> 8cf7668cac1e37fcf928adc96b6ca26c1c4ec96f
    }
}
</script>

