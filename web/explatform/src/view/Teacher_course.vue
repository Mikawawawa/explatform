<template>
  <md-content class="md-scrollbar page-container md-layout-column" style="min-height:100vh">
    <!-- header -->
    <Header v-bind:show-button="true"></Header>
    <!-- container -->
    <md-content style="height:95vh!important">
      <md-empty-state
        v-if="this.experiment==''"
        md-icon="book"
        md-label="未找到实验"
        md-description="可能是网络质量不佳，请耐心等待">
      </md-empty-state>

      <TeacherList v-else v-bind:info="this.experiment"></TeacherList>
    
    </md-content>
    <md-snackbar :md-position="'center'" :md-active.sync="showToast" md-persistent>
        <span>抱歉，服务器吃饭去了，请重试</span>
        <md-button class="md-primary" @click="showToast = false">重试</md-button>
      </md-snackbar>
    <div class="md-layout md-gutter" style="padding:20px">
    <Card v-for="value in Tcourse" v-bind:name="value.name" info="1"></Card>
    </div>
    <!-- footer -->
    <Footer></Footer>
  </md-content>
</template>

<script>
import Header from "../components/Header.vue";
import Footer from "../components/Footer.vue";
import Card from "../components/Card.vue";

import Tcouse_form from "../template/Tcourse_form";
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
    Tcourse: []
  }),
  methods:async function() {
      if(typeof(this.$store.state.Tcourse)!="undefined"){
        this.Tcourse=this.$store.state.Tcourse
        console.log(this.$store.state.Tcourse)
      }else{
        let data
        let delay=setTimeout(()=>{
          this.showToast=true
          data=""
          data=(data!==""?data:Tcourse_form)
          this.$store.commit("getTcouse",JSON.stringify(data))
          this.Tcourse=this.$store.state.Tcourse
        },2000)
        let user_id = this.$store.state.user_id
        data=await this.$dataSource.tGetCourse(user_id)
        // data=await this.$dataSource.sGetExp(this.$store.state.user_type,this.$route.query.info_id)
        data.status==0
        if(data.status==0){
          clearInterval(delay)
          data=''
          this.showToast=true
          this.$store.commit("getTcourse",JSON.stringify(Tcourse_form))
          this.Tcourse=this.$store.state.Tcourse
        }else{
          clearInterval(delay)
          this.$store.commit("getTcourse",JSON.stringify(data))
        }
      }
  }
};
</script>


