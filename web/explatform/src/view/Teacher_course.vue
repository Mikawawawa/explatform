<template>
  <md-content class="md-scrollbar page-container md-layout-column" style="min-height:100vh">
    <!-- header -->
    <Header v-bind:show-button="true"></Header>
    <!-- container -->
    <div class="md-layout md-gutter" style="padding:20px">
    <Card v-for="value in course" v-bind:name="value.name" info="1"></Card>
    </div>
    <!-- footer -->
    <Footer></Footer>
  </md-content>
</template>

<script>
import Header from "../components/Header.vue";
import Footer from "../components/Footer.vue";
import Card from "../components/Card.vue";

import Tcouse_form from "../template/Tcouse_form";
export default {
  name: "Course1",
  components: {
    Header,
    Footer,
    Card
  },
  data: () => ({
    showToast:false,
    search: null,
    searched: [],
    Tcouse: [],
    course:[
      {name:Tcouse[0]},
      {name:Tcouse[1]},
      {name:Tcouse[2]}
    ],
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
  }
};
</script>


