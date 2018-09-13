<template>
  <md-content class="md-scrollbar page-container md-layout-column">
    <!-- header -->
    <md-toolbar class="md-primary header" style="background:rgba(0,0,0,1)">
      <md-button class="md-icon-button" @click="showNavigation = true">
        <md-icon>menu</md-icon>
      </md-button>
      <span class="md-title">Explatform</span>

      <div class="md-toolbar-section-end">
        <md-button @click="start()">开始实验</md-button>
      </div>
    </md-toolbar>

    <!-- slider -->
    <md-drawer :md-active.sync="showNavigation">
      <md-toolbar class="md-transparent" md-elevation="0">
        <span class="md-title">功能</span>
      </md-toolbar>
      <md-card>
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
      
    </md-drawer>

    <!-- swiper -->
    <!-- <md-content class="swiper-container">
      <swiper :options="swiperOption">
        <swiper-slide v-for="i in text" class="full" :key="i">
          <img :src="i" alt="" srcset="">
        </swiper-slide>
      </swiper>
    </md-content> -->

    <!-- part one -->
    <div class="md-layout md-gutter md-alignment-top dark md-elevation-10">
      <div class="md-layout-item md-size-60 md-medium-size-100 md-small-size-100 md-xsmall-size-100">
        <span>
          <md-content>
            <div class="list dark">
              <h2 class="md-display-2">开放式实验平台</h2>
              <p>This text will follow the default color of the documentation, which is a nice red color.</p>
            </div>
          </md-content>
        </span>
      </div>
      <div class="md-layout-item md-medium-hide">
        <span>
          <md-card style="width=100%;height:100%;margin:0px" class="dark">
            <md-card-media-cover md-solid>
              <md-card-media>
                <img src="/background/1.jpg" alt="Skyscraper">
              </md-card-media>
              <md-card-area>
                <md-card-header>
                  <span class="md-title">Solid background</span>
                  <span class="md-subhead">1/1 image</span>
                </md-card-header>

                <md-card-actions>
                  <md-button class="md-icon-button">
                    <md-icon>favorite</md-icon>
                  </md-button>

                  <md-button class="md-icon-button">
                    <md-icon>share</md-icon>
                  </md-button>
                </md-card-actions>
              </md-card-area>
            </md-card-media-cover>
          </md-card>
        </span>
      </div>
    </div>

    <!-- part two -->
    <div class="md-layout md-gutter md-alignment-top md-elevation-4">
      <div class="md-layout-item md-size-30 md-medium-hide">
        <span>
          <md-card style="width=100%;height:100%;margin:0px" class="dark">
            <md-card-media-cover md-solid>
              <md-card-media>
                <img src="/background/1.jpg" alt="Skyscraper">
              </md-card-media>
              <md-card-area>
                <md-card-header>
                  <span class="md-title">Solid background</span>
                  <span class="md-subhead">1/1 image</span>
                </md-card-header>

                <md-card-actions>
                  <md-button class="md-icon-button">
                    <md-icon>favorite</md-icon>
                  </md-button>

                  <md-button class="md-icon-button">
                    <md-icon>share</md-icon>
                  </md-button>
                </md-card-actions>
              </md-card-area>
            </md-card-media-cover>
          </md-card>
        </span>
      </div>
      <div class="md-layout-item md-medium-size-100 md-small-size-100 md-xsmall-size-100">
        <span>
          <md-content>
            <div class="list">
              <h2 class="md-display-2">快速开始</h2>
              <p>请开始你的表演</p>
              <p>请开始我的表演</p>
              <p>请开始他的表演</p>
              <p>请开始她的表演</p>
              <p>请开始它的表演</p>
            </div>
          </md-content>
        </span>
      </div>
    </div>

    <!-- footer -->
    <div class="md-layout md-gutter md-alignment-center dark md-elevation-10" style="margin-bottom:0px">
      <div class="md-layout-item md-size-40 md-medium-size-100 md-small-size-100 md-xsmall-size-100">
        <md-content>
          <div class="list dark">
            <h2 class="md-display-1">开放式实验平台</h2>
            <p>企划：国家级电工电子实验教学示范中心</p>
            <p>开发：杭电-微芯孵化器实验室</p>
          </div>
        </md-content>
      </div>
      <div class="md-layout-item md-size-10 md-medium-hide">
        <img src="logo.png" alt="" srcset="" style="height:100%;width:100%">
      </div>
    </div>

  </md-content>
</template>

<script>
export default {
  name: "App",
  data: () => ({
    showNavigation: false,
    showSidepanel: false,
    text: ["background/1.jpg", "background/1.jpg"],
    swiperOption: {
      slidesPerView: 1,
      spaceBetween: 0,
      autoplay: {
        delay: 1500,
        disableOnInteraction: false
      },
      loop: true,
      pagination: {
        el: ".swiper-pagination",
        clickable: true
      },
      navigation: {
        nextEl: ".swiper-button-next",
        prevEl: ".swiper-button-prev"
      }
    }
  }),
  methods:{
    start:function(){
      this.$router.push('/login')
    }
  }
};
</script>

<style>
.page-container {
  height: 100%;
  overflow: hidden;
  border: 1px solid rgba(#000, 0.12);
}

.md-drawer {
  width: 230px;
  max-width: calc(100vw - 125px);
}
.md-layout{
  margin-bottom:30px;
}
.md-layout-item{
  margin: 0px!important;
  padding: 0px!important;
}

.swiper-container {
  padding: 16px;
  margin-top:-5vh;
  width: 75%;
  /* height: 90%; */
}

swiper {
  height: 100%;
  padding: 0px;
}

.header {
  height: 2vh;
}

.full {
  height: 90%;
  padding: 0px;
}

.list {
  width: 100%;
  padding: 30px!important;
  min-height: 250px;
}
p {
  font-size: 1rem;
}

.dark {
  background: #303033!important;
}

.dark *{
  color:#ccc!important
}
</style>