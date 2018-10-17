<template>
    <div>
        <Header></Header>
        <md-content class="article">
            <md-card>
                <md-card-header>
                    <div class="md-title">{{exp?exp:"123"}}</div>
                </md-card-header>
                <md-card-content v-html="compiledMarkdown"></md-card-content>
    
            </md-card>
        </md-content>
    </div>
</template>

<script>
import Header from "../components/Header.vue";
import marked from "marked";

import article from "../template/article";

export default {
  components: {
    Header
  },
  data: () => ({
    content: "",
    exp:"",
    student:"",
    // test:""
  }),
  computed: {
    compiledMarkdown: function() {
      return marked(this.student, { sanitize: true });
    }
  },
  created:async function() {
    //this.exp = this.$route.query.exp
    //this.student=this.$route.query.student
    let data=await this.$dataSource.hello()
    if(data.status == 0){
      this.student = "error!!"
    }
    else if(data.length == 0){
      this.student = "Null"
    }
    else{
      this.student = data
    }
    console.log(this.exp)
    // this.student = await this.$dataSource.hello()
    // this.content = await this.$dataSource.hello()
    //console.log(this.student)
    // console.log(this.content)
  },
  methods: {}
};
</script>
<style>
@media (max-width: 600px) {
  .article {
    width: 100% !important;
  }
}
.article {
  width: 75%;
  margin: auto;
}
</style>
 