<template>
  <md-content class="md-scrollbar page-container md-layout-column">
    <!-- header -->
    <Header v-bind:show-button="true"></Header>
    <!-- swiper -->
    <!-- <Swipe></Swipe> -->
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
          <md-card style="width=100%;height:100%;margin:0px">
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
    <Footer></Footer>
  </md-content>
</template>

<script>
import Header from "../components/Header.vue";
import Swipe from "../components/Swipe.vue";
import Footer from "../components/Footer.vue";
export default {
  name: "App",
  components: {
    Header,
    Swipe,
    Footer
  },
  data: () => ({
    showNavigation: false,
    showSidepanel: false
  })
  // methods: {
  // }
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
.md-layout {
  margin-bottom: 30px;
}
.md-layout-item {
  margin: 0px !important;
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
  padding: 30px !important;
  min-height: 250px;
}
p {
  font-size: 1rem;
}

.dark {
  background: #303033 !important;
}

.dark * {
  color: #ccc !important;
}
</style>