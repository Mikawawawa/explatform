<template>
    <div>
        <Header></Header>
        <div id="editor" @paste="answer">
            <textarea :value="input" @input="update" ></textarea>
            <div v-html="compiledMarkdown"></div>
        </div>
    </div>
</template>

<script>
import Header from "../components/Header.vue";
import marked from "marked";
import _ from "lodash";

export default {
  components: {
    Header
  },
  data: () => ({
    input: "#hello"
  }),
  computed: {
    compiledMarkdown: function() {
      return marked(this.input, { sanitize: true });
    }
  },
  methods: {
    update: _.debounce(function(e) {
      this.input = e.target.value;
    }, 300),
    answer: function(e) {
      var cbd = e.clipboardData;
      var ua = window.navigator.userAgent;

      // 如果是 Safari 直接 return
      if (!(e.clipboardData && e.clipboardData.items)) {
        return;
      }

      // Mac平台下Chrome49版本以下 复制Finder中的文件的Bug Hack掉
      if (
        cbd.items &&
        cbd.items.length === 2 &&
        cbd.items[0].kind === "string" &&
        cbd.items[1].kind === "file" &&
        cbd.types &&
        cbd.types.length === 2 &&
        cbd.types[0] === "text/plain" &&
        cbd.types[1] === "Files" &&
        ua.match(/Macintosh/i) &&
        Number(ua.match(/Chrome\/(\d{2})/i)[1]) < 49
      ) {
        return;
      }

      for (var i = 0; i < cbd.items.length; i++) {
        var item = cbd.items[i];
        if (item.kind == "file") {
          console.log(item);
          var blob = item.getAsFile();
          if (blob.size === 0) {
            return;
          }
          console.log(blob.size);
          // blob 就是从剪切板获得的文件 可以进行上传或其他操作
        }
      }
    }
  }
};
</script>
 <style>
#editor {
  margin: 0;
  height: 95vh;
  font-family: "Helvetica Neue", Arial, sans-serif;
  color: #333;
}

textarea,
#editor div {
  display: inline-block;
  width: 49%;
  height: 100%;
  vertical-align: top;
  box-sizing: border-box;
  padding: 0 20px;
}

textarea {
  border: none;
  border-right: 1px solid #ccc;
  resize: none;
  outline: none;
  background-color: #f6f6f6;
  font-size: 14px;
  font-family: "Monaco", courier, monospace;
  padding: 20px;
}

code {
  color: #f66;
}
</style>
 