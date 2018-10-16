<template>
  <md-content class="md-scrollbar page-container md-layout-column" style="min-height:100vh">
    <!-- header -->
    <Header v-bind:show-button="true"></Header>
    <!-- container -->
    <div class="md-layout md-gutter" style="padding:20px">
        <Card v-for="value in course" v-bind:name="value.name"></Card>
    </div>
    <Footer></Footer>
  </md-content>
</template>

<script>
import Header from "../components/Header.vue";
import Footer from "../components/Footer.vue";
import Card from "../components/Card.vue";

import Scouse_form from "../template/Scouse_form";
export default {
  name: "Student_course",
  components: {
    Header,
    Footer,
    Card
  },
  data: () => ({
    showToast:false,
    search: null,
    searched: [],
    Scouse: [],
    course:[
      {
        "name":this.Scouse[0]
      },
      {
        "name":this.Scouse[1]
      },
      {
        "name":this.Scouse[2]
      }
    ]
  }),
  methods: async function() {
      if(typeof(this.$store.state.Scouse)!="undefined"){
        this.experiment=this.$store.state.Scouse
        console.log(this.$store.state.Scouse)
      }else{
        let data
        let delay=setTimeout(()=>{
          this.showToast=true
          data=""
          data=(data!==""?data:Scouse_form)
          this.$store.commit("getScouse",JSON.stringify(data))
          this.Scouse=this.$store.state.Scouse
        },2000)
        data=await this.$dataSource.sGetCourse("17041802","101")
        // data=await this.$dataSource.sGetExp(this.$store.state.user_type,this.$route.query.info_id)
        data.status==0
        if(data.status==0){
          clearInterval(delay)
          data=''
          this.showToast=true
          this.$store.commit("getScouse",JSON.stringify(Scouse_form))
          this.Scouse=this.$store.state.Scouse
        }else{
          clearInterval(delay)
          this.$store.commit("getScouse",JSON.stringify(data))
        }
      }
  }
};
</script>
