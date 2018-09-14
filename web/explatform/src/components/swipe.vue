<template>
  <md-content class="swiper-container">
    <swiper :options="swiperOption">
      <swiper-slide v-for="i in text" class="full" :key="i">
        <img :src="i" alt="" srcset="">
      </swiper-slide>
    </swiper>
  </md-content>
</template>
<script>
export default {
  data() {
    return {
      dom: "",
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
    };
  }
};
</script>

<style>
.swiper-container {
  padding: 16px;
  margin-top: -5vh;
  width: 75%;
  /* height: 90%; */
}

swiper {
  height: 100%;
  padding: 0px;
}
</style>
