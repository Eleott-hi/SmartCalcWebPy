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
      amount: 100000,
      period: 12,
      rate: 5,
      date: new Date(),
      period_types: ["day", "week", "month", "quarter", "year", "halfyear"],
      capitalizationInfo: {
        isActive: false,
        period: "year",
      },
      incomeInfo: {
        isActive: false,
        amount: 10000,
        period: "month",
      },
      outcomeInfo: {
        isActive: false,
        amount: 10000,
        period: "month",
      },
      pieData: {
        labels: ["VueJs", "EmberJs", "ReactJs", "AngularJs"],
        datasets: [
          {
            backgroundColor: ["#41B883", "#E46651", "#00D8FF", "#DD1B16"],
            hoverBackgroundColor: ["#FF5A5E", "#5AD3D1", "#FFC870", "#A8B3C5"],
            data: [40, 20, 80, 10],
          },
        ],
      },
      result: {
        charges: 300,
        table: [
          {
            date: "2023-01-01",
            interest_charges: 300,
            balance_change: 10000,
            pay: 0,
            balance: 0,
          },
          {
            date: "2023-02-01",
            interest_charges: 301,
            balance_change: 10001,
            pay: 1,
            balance: 1,
          },
          {
            date: "2023-03-01",
            interest_charges: 302,
            balance_change: 10002,
            pay: 2,
            balance: 2,
          },
        ],
      },
    };
  },
  computed: {
    PieData() {
      return this.pieData;
    },

    PieOptions() {
      return {};
    },
  },

  methods: {
    Calculate(){
      console.log("Calculate");
    }
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
          v-model="amount"
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
          v-model="period"
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
            title="Enter an amount of money you want to borrow"
          >
            <i class="bi bi-question-circle text-muted"></i>
          </span>
        </span>
      </div>
      <label for="start_day" class="form-label">Start Day:</label>
      <div class="mb-4 input-group">
        <VueDatePicker
          v-model="date"
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
          v-model="rate"
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
            title="The interest rate at which you are going to repay the loan"
          >
            <i class="bi bi-question-circle text-muted"></i>
          </span>
        </span>
      </div>
      <div class="row">
        <div class="col">
          <div class="mb-4 input-group">
            <div class="form-check form-switch">
              <input
                v-model="capitalizationInfo['isActive']"
                class="form-check-input"
                type="checkbox"
                id="flexSwitchCheckChecked"
                checked
              />
              <label class="form-check-label" for="flexSwitchCheckChecked">Interest Capitalization</label>
            </div>
          </div>
        </div>
        <div class="col" v-if="capitalizationInfo['isActive']">
          <label for="period-payments" class="form-label"
            >Capitalization Frequency:</label
          >
          <div class="mb-4 input-group">
            <span class="input-group-text">
              <i class="bi bi-wallet2 text-secondary"></i>
            </span>
            <select v-model="capitalizationInfo['period']" class="form-select">
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
            v-model="incomeInfo['isActive']"
            class="form-check-input"
            type="checkbox"
            id="flexSwitchCheckChecked"
            checked
          />
          <label class="form-check-label" for="flexSwitchCheckChecked">
            Income</label
          >
        </div>
      </div>
      <div class="row" v-if="incomeInfo['isActive']">
        <div class="col">
          <label for="income" class="form-label">Income:</label>
          <div class="input-group mb-4">
            <!-- tooltip -->
            <span class="input-group-text">
              <i class="bi bi-cash-stack text-secondary"></i>
            </span>
            <input
              v-model="incomeInfo['amount']"
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
            <select v-model="incomeInfo['period']" class="form-select">
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
            v-model="outcomeInfo['isActive']"
            class="form-check-input"
            type="checkbox"
            id="flexSwitchCheckChecked"
            checked />
          <label class="form-check-label" for="flexSwitchCheckChecked">Outcome</label>
        </div>
      </div>
      <div class="row" v-if="outcomeInfo['isActive']">
        <div class="col">
          <label for="income" class="form-label">Outcome:</label>
          <div class="input-group mb-4">
            <!-- tooltip -->
            <span class="input-group-text">
              <i class="bi bi-cash-stack text-secondary"></i>
            </span>
            <input
              v-model="outcomeInfo['amount']"
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
            <select v-model="outcomeInfo['period']" class="form-select">
              <option v-for="item in period_types" :value="item" :key="item">
                Every {{ item }}
              </option>
            </select>
          </div>
        </div>
      </div>
    </div>
          <div class="mb-4 text-center">
                        <button type="submit" class="btn btn-secondary" @click="Calculate">Calculate</button>
                    </div>
    <div >
    <div class="row mt-5">
      <div class="col-md-6">
        <p>Interest charges: {{ result["charges"] }}</p>
        <p>
          Deposit amount with interest:
          {{ incomeInfo["amount"] + result["charges"] }}
        </p>
        <p>
          Capital gains:
          {{
            ((outcomeInfo["amount"] + result["charges"]) * 100) /
              outcomeInfo["amount"] -
            100
          }}
          %
        </p>
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

    <div class="container">
      <br /><br />
      <p>Amount: {{ amount }}</p>
      <p>Period: {{ period }}</p>
      <p>Rate: {{ rate }}</p>
      <p>Date: {{ date }}</p>

      <p>Capitalization isActive: {{ capitalizationInfo["isActive"] }}</p>
      <p>Capitalization period: {{ capitalizationInfo["period"] }}</p>
      <p>Income isActive: {{ incomeInfo["isActive"] }}</p>
      <p>Income amount: {{ incomeInfo["amount"] }}</p>
      <p>Income period: {{ incomeInfo["period"] }}</p>

      <p>Outcome isActive: {{ outcomeInfo["isActive"] }}</p>
      <p>Outcome amount: {{ outcomeInfo["amount"] }}</p>
      <p>Outcome period: {{ outcomeInfo["period"] }}</p>
    </div>
  </div>
</template>



<style></style>