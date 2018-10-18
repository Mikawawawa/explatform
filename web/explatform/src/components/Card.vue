<template>
    <div class="md-layout-item md-size-25 md-medium-size-33 md-small-size-50 md-xsmall-size-100">
        <md-card class="md-primary courese-card stategray" style="width:320px;margin:6px;display:inline-block" md-with-hover>
            <md-card-header>
                <md-card-header-text>
                <div class="md-title">{{name}}</div>
                <div class="md-subhead">{{time}}</div>
                <div class="md-subhead">{{classroom}}</div>
                </md-card-header-text>
                <md-card-media>
                <!-- <img src="qr.png" alt="Avatar"> -->
                </md-card-media>
            </md-card-header>

            <md-card-actions>
                <md-button @click="cardClick()">详情</md-button>
            </md-card-actions>
        </md-card>
    </div>
</template>

<script>
export default {
  props: {
    info:{
      type:String
    },
    name:{
      type:String
    },
    time: {
      type: String,
      default: "暂无时间信息"
    },
    classroom: {
      type: String,
      default: "暂无教室信息"
    }
  },
  data: () => ({
    Dname:[],
    search: null,
    searched: []
  }),
  created() {
    this.searched = this.info;
    this.Dname = this.name;
  },
  methods: {
    cardClick(){
      if(this.info=="1")this.$router.push({
        path:`/teacher_exp`,
        query: { 
          dataobj: this.Dname,
        }})
      else if(this.info=="2") this.$router.push({
        path:`/teacher_info`,
        query: { 
            dataobj: this.Dname,
        }});
      else this.$router.push({
        path:`/student_exp`,
        query: { 
            dataobj: this.Dname,
        }});
  }
  }
};
</script>

<style>
.orange {
  background: orange !important;
}
.stategray {
  background: darkslategray !important;
}
</style>
