<template>
  <md-content class="md-scrollbar page-container md-layout-column" style="min-height:100vh">
    <!-- header -->
    <Header v-bind:show-button="true"></Header>
    <!-- container -->
    <div class="md-layout md-gutter" style="padding:20px">
        <Card v-for="value in course" v-bind:name="value.name" info="2"></Card>
    </div>
    <Footer></Footer>
  </md-content>
</template>

<script>
import Header from "../components/Header.vue";
import Footer from "../components/Footer.vue";
import Card from "../components/Card.vue";
export default {
  name: "Course2",
  components: {
    Header,
    Footer,
    Card
  },
  data: () => ({
    msg:[],
    showToast:false,
    search: null,
    searched: [],
    Tcouse: [],
    course:[
      {name:"获取实验失败"},
      {name:"获取实验失败"},
      {name:"获取实验失败"}
    ]
  }),
methods:async function() {
      if(typeof(this.$store.state.Tcouse)!="undefined"){
        this.experiment=this.$store.state.Tcouse
        console.log(this.$store.state.Tcouse)
      }else{
        let data
        let delay=setTimeout(()=>{
          this.showToast=true
          data=""
          data=(data!==""?data:Tcouse_form)
          this.$store.commit("getTcouse",JSON.stringify(data))
          this.Scouse=this.$store.state.Tcouse
        },2000)
        data=await this.$dataSource.tGetCourse("17041802","101")
        // data=await this.$dataSource.sGetExp(this.$store.state.user_type,this.$route.query.info_id)
        data.status==0
        if(data.status==0){
          clearInterval(delay)
          data=''
          this.showToast=true
          this.$store.commit("getTcouse",JSON.stringify(Tcouse_form))
          this.Tcouse=this.$store.state.Tcouse
        }else{
          clearInterval(delay)
          this.$store.commit("getTcouse",JSON.stringify(data))
        }
      }
  },
  created(){  
    let routerParams = this.$route.query.dataobj
    // 将数据放在当前组件的数据内
    this.msg = routerParams
    for(let i of this.Tcouse.course ){
      if(this.msg==i){
        this.course=[
          {name:this.Tcouse.exp}
        ]
      }
    }

   /* if(this.msg==this.Tcouse.exp){
        this.course=[
          {name:"差分方程"},
          {name:"电路分析"},
          {name:"小信号模型"}
        ]
      }
      else{
        this.course=[
          {name:"差分方程"},
          {name:"模电分析"},
          {name:"小信号模型"}
        ]
      }*/
}
};
</script>


