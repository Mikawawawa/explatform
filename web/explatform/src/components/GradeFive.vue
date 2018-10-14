<template>
    <md-autocomplete v-model="selectGrade" :md-options="grades" class="grade_5">
        <label>grade</label>
    </md-autocomplete>
</template>

<script>
export default {
  data: () => ({
    selectGrade: 1,
    grades: [1, 2, 3, 4, 5]
  })
};
</script>

<style>
.grade_5{
  max-width: 100px;
}
</style>
