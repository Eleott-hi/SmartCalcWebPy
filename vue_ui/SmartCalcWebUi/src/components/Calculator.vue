<script>
import { ref } from "vue";
export default {
  data() {
    return {
      expressions: {
        main: "",
        x: "",
      },
      activeInput: "main",
      historySelected: null,
      history: [],
    };
  },

  mounted() { this.GetHistory(); },

  methods: {
    Calculate() {
      const expression_main = encodeURIComponent(this.expressions["main"]);
      const expression_x = encodeURIComponent(this.expressions["x"]);

      $.ajax({
        url: `http://localhost:8000/calculate?expression=${expression_main}&x=${expression_x}`,
        type: "GET",
        success: (data) => {
          console.log(data);

          this.history.push({
            expression_main: this.expressions["main"],
            expression_x: this.expressions["x"],
          })

          this.expressions["main"] = data.result;
        },
        error: this.showErrorAlert,
      });
    },

    showErrorAlert(xhr, status, error) {
      if (xhr.responseJSON && xhr.responseJSON.error) {
        alert(
          "Status: " +
          status +
          "\nError: " +
          error +
          "\nMessage: " +
          xhr.responseJSON.error
        );
      } else {
        alert("An error occurred. Status Code: " + xhr.status);
      }
    },

    FocusInput(input) {
      this.activeInput = input;
    },

    SetExpressions() {
      this.expressions["main"] = this.historySelected.expression_main;
      this.expressions["x"] = this.historySelected.expression_x;
    },

    GetHistory() {
      $.ajax({
        url: `http://localhost:8000/history`,
        type: "GET",
        success: (data) => {
          console.log(data);
          this.history = data.history;
        },
        error: this.showErrorAlert,
      });
    },

    DeleteHistory() {
      $.ajax({
        url: `http://localhost:8000/history`,
        type: "DELETE",
        headers: {
          'X-CSRFToken': document.querySelector('[name=csrfmiddlewaretoken]').value,
        },
        success: (data) => {
          console.log(data);
          this.history = data.history
        },
        error: this.showErrorAlert,
      });
    },
  },
};
</script>

<template>
  <div class="container calculator">
    <div class="container mt-5">
      <!-- 1 Row -->
      <div class="row mb-2">
        <div class="col-12 btn-group" role="group">
          <input type="text" class="form-control" v-model="expressions['main']" @focus="FocusInput('main')"
            @keyup.enter="Calculate" placeholder="Enter expression" />
        </div>
      </div>
      <!-- 2 Row -->
      <div class="row mb-2">
        <div class="col-4 btn-group" role="group">
          <button class="btn " :class="$store.state.primaryBtnBootstrapType" @click="expressions[activeInput] += 'x'">
            x
          </button>
        </div>
        <div class="col-8">
          <input class="form-control w-100" v-model="expressions['x']" @focus="FocusInput('x')" @keyup.enter="Calculate"
            placeholder="Enter x value or expression" />
        </div>
      </div>

      <!-- 3 Row -->
      <div class="row mb-2 justify-content-end">
        <div class="col-4 btn-group d-flex ml-auto" role="group">
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType" @click="expressions[activeInput] = ''">
            C
          </button>
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType" @click="
            expressions[activeInput] = expressions[activeInput].slice(0, -1)
            ">
            ⌫
          </button>
        </div>
      </div>

      <!-- 4 Row -->
      <div class="row mb-2">
        <div class="col-4 btn-group d-flex" role="group">
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType"
            @click="expressions[activeInput] += 'sqrt('">
            sqrt
          </button>
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType" @click="expressions[activeInput] += '^'">
            pow
          </button>
        </div>
        <div class="col-4 btn-group d-flex" role="group">
          <button class="btn " :class="$store.state.primaryBtnBootstrapType" @click="expressions[activeInput] += 7">
            7
          </button>
          <button class="btn " :class="$store.state.primaryBtnBootstrapType" @click="expressions[activeInput] += 8">
            8
          </button>
          <button class="btn " :class="$store.state.primaryBtnBootstrapType" @click="expressions[activeInput] += 9">
            9
          </button>
        </div>
        <div class="col-4 btn-group d-flex" role="group">
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType" @click="expressions[activeInput] += '('">
            (
          </button>
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType" @click="expressions[activeInput] += ')'">
            )
          </button>
        </div>
      </div>

      <!-- 5 Row -->
      <div class="row mb-2">
        <div class="col-4 btn-group d-flex" role="group">
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType"
            @click="expressions[activeInput] += 'asin('">
            asin
          </button>
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType"
            @click="expressions[activeInput] += 'sin('">
            sin
          </button>
        </div>

        <div class="col-4 btn-group d-flex" role="group">
          <button class="btn " :class="$store.state.primaryBtnBootstrapType" @click="expressions[activeInput] += 4">
            4
          </button>
          <button class="btn " :class="$store.state.primaryBtnBootstrapType" @click="expressions[activeInput] += 5">
            5
          </button>
          <button class="btn " :class="$store.state.primaryBtnBootstrapType" @click="expressions[activeInput] += 6">
            6
          </button>
        </div>

        <div class="col-4 btn-group d-flex" role="group">
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType" @click="expressions[activeInput] += '/'">
            /
          </button>
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType" @click="expressions[activeInput] += '%'">
            %
          </button>
        </div>
      </div>

      <!-- 6 Row -->
      <div class="row mb-2">
        <div class="col-4 btn-group d-flex" role="group">
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType"
            @click="expressions[activeInput] += 'acos('">
            acos
          </button>
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType"
            @click="expressions[activeInput] += 'cos('">
            cos
          </button>
        </div>

        <div class="col-4 btn-group d-flex" role="group">
          <button class="btn " :class="$store.state.primaryBtnBootstrapType" @click="expressions[activeInput] += 1">
            1
          </button>
          <button class="btn " :class="$store.state.primaryBtnBootstrapType" @click="expressions[activeInput] += 2">
            2
          </button>
          <button class="btn " :class="$store.state.primaryBtnBootstrapType" @click="expressions[activeInput] += 3">
            3
          </button>
        </div>

        <div class="col-4 btn-group d-flex" role="group">
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType" @click="expressions[activeInput] += '*'">
            *
          </button>
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType" @click="expressions[activeInput] += '-'">
            -
          </button>
        </div>
      </div>

      <!-- 7 Row -->
      <div class="row mb-2">
        <div class="col-4 btn-group d-flex" role="group">
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType"
            @click="expressions[activeInput] += 'atan('">
            atan
          </button>
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType"
            @click="expressions[activeInput] += 'tan('">
            tan
          </button>
        </div>

        <div class="col-4 btn-group d-flex" role="group">
          <button class="btn " :class="$store.state.primaryBtnBootstrapType" @click="expressions[activeInput] += 'e'">
            e
          </button>
          <button class="btn " :class="$store.state.primaryBtnBootstrapType" @click="expressions[activeInput] += 0">
            0
          </button>
          <button class="btn " :class="$store.state.primaryBtnBootstrapType" @click="expressions[activeInput] += '.'">
            .
          </button>
        </div>

        <div class="col-4 btn-group d-flex" role="group">
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType" @click="expressions[activeInput] += '+'">
            +
          </button>
          <button class="btn " :class="$store.state.secondaryBtnBootstrapType" @click="Calculate">=</button>
        </div>
      </div>

      <div class="mb-4 input-group">
        <span class="input-group-text">
          <i class="bi bi-clock-history"></i>
        </span>
        <select v-model="historySelected" class="form-select" id="history" @change="SetExpressions">
          <option v-for="item in history" :value="item" :key="item.id">
            expression={{ item.expression_main }}; x={{ item.expression_x }}
          </option>
        </select>
        <button class="btn" :class="$store.state.primaryBtnBootstrapType" @click="DeleteHistory">Delete All</button>
      </div>
    </div>
  </div>
</template>

