<template>
        <div>
        <md-table v-model="searched" md-sort="name" md-sort-order="asc" md-fixed-header  style="height:100%!important">
          <md-table-toolbar>
              <div class="md-toolbar-section-start">
                <h1 class="md-title">大物实验A2</h1>
              </div>

              <md-field md-clearable class="md-toolbar-section-end">
                <md-input placeholder="Search by experiment_name..." v-model="search" @input="searchOnTable" />
              </md-field>
          </md-table-toolbar>

          <md-table-empty-state
              md-label="No experiment found"
              :md-description="`No experiment found for this '${search}' query.`">
              <md-button class="md-primary md-raised" @click="newUser">Create New User</md-button>
          </md-table-empty-state>

          <md-table-row slot="md-table-row" slot-scope="{ item }">
              <md-table-cell md-label="实验号" md-sort-by="id" md-numeric>{{ item.id }}</md-table-cell>
              <md-table-cell md-label="实验名称" md-sort-by="name">{{ item.name }}</md-table-cell>
              <md-table-cell md-label="实验分" md-sort-by="exp_grade">
                <!-- {{ item.exp_grade }} -->
                <showGrade v-bind:info="item.exp_grade"></showGrade>
              </md-table-cell>
              <md-table-cell md-label="实验报告" md-sort-by="report">
                <md-button class="md-size-1x md-icon-button" style="padding:0px" @click="goMarkdown()">
                  <md-icon>visibility</md-icon>
                </md-button>
                <!-- {{ item.title }} -->
              </md-table-cell>
          </md-table-row>
          
        </md-table>
    </div>
</template>

<script>
import student from "api/platform/http/doc/nodejs-server-server/controllers/Default.js"
import showGrade from "./ShowGrade.vue"
export default {
  components:{
    showGrade
  },
  props: {
    info: {
      type: Array
    }
  },
  data: () => ({
    search: null,
    searched: []
  }),
  methods: {
    goMarkdown() {
      this.$router.push("/article");
    },
    newUser() {
      window.alert("Noop");
    },
    searchOnTable() {
      this.searched = this.searchByName(this.experiment, this.search);
    },
    searchByName(experiment, search) {
      return search == ""
        ? this.info
        : [
           {
                id: 1,
                name: "示波器的使用",
                exp_grade: "93",
                rep_grade: "87",
                title: "One More Time"
            },
            {
                id: 2,
                name: "用扭摆法测量刚体的转动惯量",
                exp_grade: "90",
                rep_grade: "83",
                title: "Assistant Media Planner"
            }
          ];
    }
  },
  created() {
    this.searched = this.info;
  }
};
</script>

<style>
.md-table-content {
  max-height: 90vh !important;
  height: 90vh !important;
}
</style>

