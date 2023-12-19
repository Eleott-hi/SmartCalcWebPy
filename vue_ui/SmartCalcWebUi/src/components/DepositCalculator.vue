<script>
import VueDatePicker from "@vuepic/vue-datepicker";
import "@vuepic/vue-datepicker/dist/main.css";
import { Bar, Pie,Doughnut } from "vue-chartjs";
import {
  Chart as ChartJS,
  ArcElement,
  Title,
  Tooltip,
  Legend,
  BarElement,
  CategoryScale,
  LinearScale,
} from "chart.js";


ChartJS.register(
  Title,
  Tooltip,
  Legend,
  ArcElement,
  BarElement,
  CategoryScale,
  LinearScale
);

export default {
  components: { VueDatePicker, Pie ,Doughnut},
  data() {
    return {
      period_types: ["day", "week", "month", "quarter", "year", "halfyear"],
      result: null,
      tmps:{
        term: 12,
        percent: 5,
        date_start: new Date(),
        percent_max_without_bill: 5,
        percent_bill: 13,
        sum_in: 100000,
        sum_add: 10000,
        sum_sub: 10000,
        cop_period: "month",
        add_period: "month",
        sub_period: "month",
        isActive_cop: false,
        isActive_add: false,
        isActive_sub: false,
      },
    };
  },
  computed: {
    PieData() {
      return {
        labels: ["Sum_In", "Percents", "Income_Sum"],
        datasets: [
          {
            backgroundColor: ["#41B883", "#E46651", "#00D8FF"],
            hoverBackgroundColor: ["#FF5A5E", "#5AD3D1", "#FFC870"],
            data: [ this.tmps.sum_in, this.result.profite, this.result.income_sum ],
          },
        ],
      }
    },

    PieOptions() {
      return {};
    },
  },

  methods: {
    Calculate(){
        let input_data = { ...this.tmps };
        input_data.date_start = new Date(input_data.date_start).toISOString();

        if (!this.tmps.isActive_cop) {
          input_data.cop_period = 'none'
        } 

        if (!this.tmps.isActive_add) {
          input_data.add_period = 'none'
        } 

        if (!this.tmps.isActive_sub) {
          input_data.sub_period = 'none'
        }

        $.ajax({
            url: `http://localhost:8000/deposit_calculator?${$.param(input_data)}`,
            type: "GET",
            success: this.formResult,
            error: this.showErrorAlert
        });
    },
    formResult(data) {
      this.result = {
        profite: data.profite.toFixed(2),
        income_sum:  data.income_sum.toFixed(2),
        bills: data.bills.toFixed(2),
        profit_wb : data.profit_wb.toFixed(2),
        summary : data.summary.toFixed(2),
      };
    },
  }
};
</script>

<template>
  <div class="container mt-5">
    <div class="container">
      <label for="amount" class="form-label">Amount:</label>
      <div class="input-group mb-4">
        <!-- tooltip -->
        <span class="input-group-text">
          <i class="bi bi-cash-stack text-secondary"></i>
        </span>
        <input
          v-model="tmps.sum_in"
          id="amount"
          type="number"
          min="10000"
          class="form-control"
          placeholder="e.g. 100000"
          required
        />
        <!-- tooltip -->
        <span class="input-group-text">
          <span
            class="tt"
            data-bs-placement="bottom"
            title="Enter an amount of money you want to borrow"
          >
            <i class="bi bi-question-circle text-muted"></i>
          </span>
        </span>
      </div>
      <label for="period" class="form-label">Period (month):</label>
      <div class="input-group mb-4">
        <!-- tooltip -->
        <span class="input-group-text">
          <i class="bi bi-cash-stack text-secondary"></i>
        </span>
        <input
          v-model="tmps.term"
          id="period"
          type="number"
          min="1"
          class="form-control"
          placeholder="e.g. 100000"
          required
        />
        <!-- tooltip -->
        <span class="input-group-text">
          <span
            class="tt"
            data-bs-placement="bottom"
            title="Enter an amount of money you want to borrow" >
            <i class="bi bi-question-circle text-muted"></i>
          </span>
        </span>
      </div>
      <label for="start_day" class="form-label">Start Day:</label>
      <div class="mb-4 input-group">
        <VueDatePicker
          v-model="tmps.date_start"
          text-input
          placeholder="Enter date (mm/dd/yyyy)"
        ></VueDatePicker>
      </div>
      <label for="rate" class="form-label">Interest rate, %:</label>
      <div class="mb-4 input-group">
        <span class="input-group-text">
          <i class="bi bi-percent text-secondary"></i>
        </span>
        <input
          v-model="tmps.percent"
          type="number"
          id="rate"
          min="1"
          step="1"
          class="form-control"
          placeholder="e.g. 5"
          required
        />
        <!-- tooltip -->
        <span class="input-group-text">
          <span
            class="tt"
            data-bs-placement="bottom"
            title="The interest rate at which you are going to repay the loan" >
            <i class="bi bi-question-circle text-muted"></i>
          </span>
        </span>
      </div>
      <div class="row">
        <div class="col">
          <div class="mb-4 input-group">
            <div class="form-check form-switch">
              <input
                v-model="tmps.isActive_cop"
                class="form-check-input"
                type="checkbox"
                id="CapitalizationCheckBox"
                checked
              />
              <label class="form-check-label" for="CapitalizationCheckBox">Interest Capitalization</label>
            </div>
          </div>
        </div>
        <div class="col" v-if="tmps.isActive_cop">
          <label for="period-payments" class="form-label"
            >Capitalization Frequency:</label
          >
          <div class="mb-4 input-group">
            <span class="input-group-text">
              <i class="bi bi-wallet2 text-secondary"></i>
            </span>
            <select v-model="tmps.cop_period" class="form-select">
              <option v-for="item in period_types" :value="item" :key="item">
                Every {{ item }}
              </option>
            </select>
          </div>
        </div>
      </div>
      <div class="mb-4 input-group">
        <div class="form-check form-switch">
          <input
            v-model="tmps.isActive_add"
            class="form-check-input"
            type="checkbox"
            id="IncomeCheckBox"
            checked
          />
          <label class="form-check-label" for="IncomeCheckBox">
            Income</label
          >
        </div>
      </div>
      <div class="row" v-if="tmps.isActive_add">
        <div class="col">
          <label for="income" class="form-label">Income:</label>
          <div class="input-group mb-4">
            <!-- tooltip -->
            <span class="input-group-text">
              <i class="bi bi-cash-stack text-secondary"></i>
            </span>
            <input
              v-model="tmps.sum_add"
              id="period"
              type="number"
              min="10000"
              class="form-control"
              placeholder="e.g. 100000"
              required
            />
            <!-- tooltip -->
            <span class="input-group-text">
              <span
                class="tt"
                data-bs-placement="bottom"
                title="Enter an amount of money you want to borrow"
              >
                <i class="bi bi-question-circle text-muted"></i>
              </span>
            </span>
          </div>
        </div>
        <div class="col">
          <label for="period-payments" class="form-label">Capitalization Frequency:</label>
          <div class="mb-4 input-group">
            <span class="input-group-text">
              <i class="bi bi-wallet2 text-secondary"></i>
            </span>
            <select v-model="tmps.add_period" class="form-select">
              <option v-for="item in period_types" :value="item" :key="item">
                Every {{ item }}
              </option>
            </select>
          </div>
        </div>
      </div>
      <div class="mb-4 input-group">
        <div class="form-check form-switch">
          <input
            v-model="tmps.isActive_sub"
            class="form-check-input"
            type="checkbox"
            id="OutcomeCheckBox"
            checked />
          <label class="form-check-label" for="OutcomeCheckBox">Outcome</label>
        </div>
      </div>
      <div class="row" v-if="tmps.isActive_sub">
        <div class="col">
          <label for="income" class="form-label">Outcome:</label>
          <div class="input-group mb-4">
            <!-- tooltip -->
            <span class="input-group-text">
              <i class="bi bi-cash-stack text-secondary"></i>
            </span>
            <input
              v-model="tmps.sum_sub"
              id="period"
              type="number"
              min="10000"
              class="form-control"
              placeholder="e.g. 100000"
              required
            />
            <!-- tooltip -->
            <span class="input-group-text">
              <span
                class="tt"
                data-bs-placement="bottom"
                title="Enter an amount of money you want to borrow"
              >
                <i class="bi bi-question-circle text-muted"></i>
              </span>
            </span>
          </div>
        </div>
        <div class="col">
          <label for="period-payments" class="form-label"
            >Capitalization Frequency:</label
          >
          <div class="mb-4 input-group">
            <span class="input-group-text">
              <i class="bi bi-wallet2 text-secondary"></i>
            </span>
            <select v-model="tmps.sub_period" class="form-select">
              <option v-for="item in period_types" :value="item" :key="item">
                Every {{ item }}
              </option>
            </select>
          </div>
        </div>
      </div>
    </div>
          <div class="mb-4 text-center">
                        <button type="submit" class="btn " :class="$store.state.primaryBtnBootstrapType" @click="Calculate">Calculate</button>
          </div>
    <div >
    
    <div class="row mt-5" v-if="result">
      <div class="col-md-6">
        <p>Interest charges: {{ result["profite"] }}</p>
        <p>Bills: {{ result["bills"] }}</p>
        <p>Interest charges without bills: {{ result["profit_wb"] }}</p>
        <p>Income: {{ result["income_sum"] }}</p>
        <p>Deposit amount with interest: {{ result["summary"] }}</p>
      </div>
      <div class="col-md-6">
        <div class="container">
          <div class="container justify-content-center align-items-center">
            <Doughnut class="mt-5" :data="PieData" :options="PieOptions" />
          </div>
        </div>
      </div>
    </div>
    </div>
  </div>
</template>



<style></style>