<template>
    <div>
        <!-- header -->
        <md-toolbar class="md-primary header" style="background:rgba(0,0,0,1)">
        <md-button class="md-icon-button" @click="showNavigation = true">
            <md-icon>menu</md-icon>
        </md-button>
        <span class="md-title" @click="goHome()">Explatform</span>

        <!-- <div class="md-toolbar-section-end">
        </div> -->
        <md-menu md-direction="bottom-end" class="md-toolbar-section-end" v-if="showButton">
            <md-button md-menu-trigger class="md-icon-button" >
                <md-icon>add</md-icon>
            </md-button>

            <md-menu-content style="z-index:9998">
                <!-- <md-menu-item @click="goTeacherCourse()">教师课程界面</md-menu-item>
                <md-menu-item @click="goStudentCourse()">学生课程界面</md-menu-item> -->

                <md-menu-item @click="goTeacherCourse()" v-if="this.$store.state.user_type!='3'">教师课程界面</md-menu-item>
                <md-menu-item @click="goStudentCourse()" v-if="this.$store.state.user_type!='2'">学生课程界面</md-menu-item>

                <md-menu-item @click="goMarkdown()">报告编辑</md-menu-item>
                <md-menu-item @click="goArticle()">报告显示</md-menu-item>
                <md-menu-item @click="goLogout()">登出</md-menu-item>
            </md-menu-content>
        </md-menu>
        </md-toolbar>
        <!-- slider -->
        <md-drawer :md-active.sync="showNavigation" style="max-height:100vh;z-index:9999">
        <md-toolbar class="md-transparent" md-elevation="0">
            <span class="md-title">Shortcut</span>
        </md-toolbar>
        <md-card class="md-elevation-0">
            <md-card-media>
            <img v-bind:src="this.qrcode" alt="unlock">
            </md-card-media>

            <md-card-header>
            <div class="md-title">解锁码</div>
            <div class="md-subhead">扫描以解锁功能</div>
            </md-card-header>

            <md-card-expand>
            <md-card-actions md-alignment="space-between">
                <md-card-expand-trigger>
                <md-button>刷新</md-button>
                </md-card-expand-trigger>
            </md-card-actions>
            </md-card-expand>
        </md-card>

        <md-card class="md-elevation-0">
            <!-- <md-card-media>
            <img src="logo.png" alt="unlock">
            </md-card-media> -->

            <md-card-header>
            <div class="md-title">企划</div>
            <div class="md-subhead">国家级电工电子实验示范中心</div>
            <div class="md-title">开发协力</div>
            <div class="md-subhead">杭电微芯大学生科技创新孵化器</div>
            </md-card-header>

            <!-- <md-card-expand>
            <md-card-actions md-alignment="space-between">
                <md-card-expand-trigger>
                <md-button>刷新</md-button>
                </md-card-expand-trigger>
            </md-card-actions>
            </md-card-expand> -->
        </md-card>
        
        </md-drawer>
    </div>
</template>

<script>
export default {
  name: "Header",
  data: () => ({
    showNavigation: false,
    showSidepanel: false,
    qrcode:"",
    userType:""
  }),
  props: {
    showButton: {
      type: Boolean,
      default: true
    }
  },
  created:function(){
      let type="sid"
      if(this.$store.state.user_type=="1"){
          type="aid"
      }else if(this.$store.state.user_type=="2"){
          type="tid"
          console.log("here")
      }
      this.qrcode=`http://101.132.116.211:7071/api/user/get_qrcode?type=${type}&id=${this.$store.state.user_id?this.$store.state.user_id:"17041802"}`
    //   this.qrcode=`http://localhost/api/user/get_qrcode?type=${"sid"}&id=${"17041802"}`
  },
  methods: {
    goStudentCourse: function() {
      this.$router.push("/student_course");
    },
    goTeacherCourse:function(){
        this.$router.push("/teacher_course");
    },
    goLogout:function(){
      this.$store.commit("logout")
      this.$cookie.clear("user_id")
      this.$cookie.clear("user_type")
      this.$router.push("/login")
    },
    goHome: function() {
      this.$router.push("/");
    },
    goLogin: function() {
      this.$router.push("/login");
    },
    goMarkdown: function() {
      this.$router.push("/markdown");
    },
    goArticle:function(){
        this.$router.push("/article")
    }
  }
};
</script>
