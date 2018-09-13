<template>
  <md-content class="page-container md-layout-column md-scrollbar">
    <!-- header -->
    <md-toolbar class="md-primary header ">
      <md-button class="md-icon-button" @click="showNavigation = true">
        <md-icon>menu</md-icon>
      </md-button>
      <span class="md-title">Explatform</span>

      <!-- <div class="md-toolbar-section-end">
        <md-button @click="showSidepanel = true">Favorites</md-button>
      </div> -->
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
    <md-content class="swiper-container">
      <swiper :options="swiperOption">
        <swiper-slide v-for="i in text" class="full" :key="i">
          <img :src="i" alt="" srcset="">
        </swiper-slide>
      </swiper>
    </md-content>

    <!-- part one -->
    <md-content>
      <div class="list dark">
        <h2 class="md-display-3">开放式实验平台</h2>
        <p>This text will follow the default color of the documentation, which is a nice red color.</p>
      </div>
    </md-content>
  </md-content>
</template>

<script>
export default {
  name: "App",
  data: () => ({
    showNavigation: false,
    showSidepanel: false,
    text: ["background/1.jpg", "background/2.png"],
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
  })
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

.swiper-container {
  /* padding: 16px; */
  height: 0.95 * 9/16vw;
}

swiper {
  height: 100%;
  padding: 0px;
}

.header {
  height: 5vh;
}

.full {
  height: 100%;
  padding: 0px;
}

.list {
  width: 100%;
  padding: 20px;
  min-height: 250px;
}
p {
  font-size: 1rem;
}

.p60 {
  width: 60%;
  min-height: 100px;
  padding: 0px;
}
.p40 {
  width: 40%;
  min-height: 100px;
  padding: 0px;
}

.dark {
  background: #303033;
}
</style>