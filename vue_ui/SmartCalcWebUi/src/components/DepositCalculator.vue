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
              <label class="form-check-label" for="flexSwitchCheckChecked">
                Interest Capitalization</label
              >
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
              v-model="incomeInfo ['amount']"
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
            checked
          />
          <label class="form-check-label" for="flexSwitchCheckChecked">
            Outcome</label
          >
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
    <div class="container">
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

<script>
import VueDatePicker from "@vuepic/vue-datepicker";
import "@vuepic/vue-datepicker/dist/main.css";
export default {
  components: { VueDatePicker },
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
    };
  },
};
</script>

<style></style>