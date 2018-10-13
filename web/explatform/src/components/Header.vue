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
                <md-menu-item @click="goTeacherCourse()">教师课程界面</md-menu-item>
                <md-menu-item @click="goStudentCourse()">学生课程界面</md-menu-item>
                <md-menu-item @click="goLogin()">登录</md-menu-item>
                <md-menu-item @click="goMarkdown()">报告编辑</md-menu-item>
                <md-menu-item @click="goArticle()">报告显示</md-menu-item>
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
            <img src="qr.png" alt="unlock">
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
    showSidepanel: false
  }),
  props: {
    showButton: {
      type: Boolean,
      default: true
    }
  },
  methods: {
    goStudentCourse: function() {
      this.$router.push("/student_course");
    },
    goTeacherCourse:function(){
        this.$router.push("/teacher_course");
    },
    // goStudentExp:function(){
    //     this.$router.push("/student_exp");
    // },
    // goTeacherExp:function(){
    //     this.$router.push("/teacher_exp");
    // },
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
