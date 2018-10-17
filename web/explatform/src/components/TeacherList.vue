<template>
        <div>
        <md-table v-model="searched" md-sort="name" md-sort-order="asc" md-fixed-header  style="height:100%!important">
          <md-table-toolbar>
              <div class="md-toolbar-section-start">
                <h1 class="md-title">{{searched[0].id}}</h1>
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
              <md-table-cell md-label="学号" md-sort-by="id" md-numeric>{{ item.student_id }}</md-table-cell>
              <md-table-cell md-label="操作分" md-sort-by="exp_grade">
                <showGrade v-bind:grade="item.score.action?item.score.action:'0'"></showGrade>
              </md-table-cell>
              <md-table-cell md-label="报告分" md-sort-by="exp_grade">
                <showGrade v-bind:grade="item.score&&item.score.report?item.score.report:'0'"></showGrade>
              </md-table-cell>
              <md-table-cell md-label="查看报告" md-sort-by="report">
                <md-button class="md-size-1x md-icon-button" style="padding:0px" @click="goMarkdown(item.id,item.student_id)">
                  <md-icon>visibility</md-icon>
                </md-button>
              </md-table-cell>
          </md-table-row>
          
        </md-table>
    </div>
</template>

<script>
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
    goEdit(){
      this.$router.push({
          path:"/markdown",
          query:{
            exp:exp,
            student:student
          }
        })
    },
    goMarkdown(exp,student) {
      this.$router.push({
        path:"/article",
        query:{
          exp:exp,
          student:student
        }
      });
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

