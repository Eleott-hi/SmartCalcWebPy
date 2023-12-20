<script>
import { Bar, Pie } from 'vue-chartjs'
import { Chart as ChartJS, ArcElement, Title, Tooltip, Legend, BarElement, CategoryScale, LinearScale } from 'chart.js'

ChartJS.register(Title, Tooltip, Legend, ArcElement, BarElement, CategoryScale, LinearScale)

export default {
    name: 'BarChart',
    components: { Bar, Pie },

    data() {
        return {
            input_data: {
                amount: 100000,
                rate: 5,
                period: 12,
                paymentsType: 'annuity',
            },
            loan_output: null,
        }
    },

    methods: {
        Calculate() {
            $.ajax({
                url: `http://localhost:8000/loan_calculate?${$.param(this.input_data)}`,
                type: "GET",
                success: (data) => { this.RenderResult(data); },
                error: this.showErrorAlert
            });
        },

        RenderResult(data) {
            const { payment, debth, percent, remain, overpay, all_sum } = data;
            let table = []

            for (let i = 0; i < payment.length; i++) {
                table.push({
                    month: i + 1,
                    payment_amount: payment[i].toFixed(2),
                    payment_principal: debth[i].toFixed(2),
                    payment_interest: percent[i].toFixed(2),
                    balance_owed: remain[i].toFixed(2),
                })
            }

            this.loan_output = {
                data: data,
                table: table,
                pie_data: [all_sum - overpay, overpay],
                payment: payment[0].toFixed(2),
                overpay: overpay.toFixed(2),
                all_sum: all_sum.toFixed(2),
            }
        },

        showErrorAlert(xhr, status, error) {
            if (xhr.responseJSON && xhr.responseJSON.error) {
                alert(
                    "Status: " + status +
                    "\nError: " + error +
                    "\nMessage: " + xhr.responseJSON.error);
            } else {
                alert("An error occurred.");
            }
        },
    },

    computed: {
        BarData() {
            let monthes = []

            for (let i = 0; i < this.loan_output.data.debth.length; i++) {
                monthes.push(i + 1)
            }

            return {
                labels: monthes,
                datasets: [
                    {
                        label: 'Main debt',
                        data: this.loan_output.data.debth,
                        backgroundColor: "#FF0000",
                    },
                    {
                        label: 'Percentage',
                        data: this.loan_output.data.percent,
                        backgroundColor: "#0000FF",
                    },
                ]
            }
        },
        BarOptions() {
            return {
                plugins: {
                    title: {
                        display: true,
                        text: 'Repayment schedule'
                    },
                },
                responsive: true,
                scales: {
                    x: {
                        stacked: true,
                    },
                    y: {
                        stacked: true
                    },
                }
            }
        },
        
        PieData() {
            return {
                labels: ['Main debt', 'Interest'],
                datasets: [
                    {
                        backgroundColor: ['#41B883', '#00D8FF'],
                        hoverBackgroundColor: ['#FFFFFF'],
                        data: this.loan_output.pie_data
                    }
                ]
            }
        },

        PieOptions() {
            return {}
        }
    }
}
</script>
  

<template>
    <div class="container mt-5">
        <div class="row justify-content-center">
            <div class="container">
                <div class="container">
                    <label for="amount" class="form-label">Amount:</label>
                    <div class="input-group mb-4">
                        <!-- tooltip -->
                        <span class="input-group-text">
                            <i class="bi bi-cash-stack text-secondary"></i>
                        </span>
                        <input v-model="input_data['amount']" type="number" min="10000" class="form-control"
                            placeholder="e.g. 100000" required />
                        <!-- tooltip -->
                        <span class="input-group-text">
                            <span class="tt" data-bs-placement="bottom" title="Enter an amount of money you want to borrow">
                                <i class="bi bi-question-circle text-muted"></i>
                            </span>
                        </span>
                    </div>
                    <label for="period" class="form-label">Period, month:</label>
                    <div class="mb-4 input-group">
                        <!-- tooltip -->
                        <span class="input-group-text">
                            <i class="bi bi-calendar-date text-secondary"></i>
                        </span>
                        <input v-model="input_data['period']" type="number" id="period" min="1" step="1"
                            class="form-control" placeholder="e.g. 12" required />
                        <!-- tooltip -->
                        <span class="input-group-text">
                            <span class="tt" data-bs-placement="bottom" title="Period within you plan to pay loan">
                                <i class="bi bi-question-circle text-muted"></i>
                            </span>
                        </span>
                    </div>
                    <label for="rate" class="form-label">Interest rate, %:</label>
                    <div class="mb-4 input-group">
                        <span class="input-group-text">
                            <i class="bi bi-percent text-secondary"></i>
                        </span>
                        <input v-model="input_data['rate']" type="number" id="rate" min="1" step="1" class="form-control"
                            placeholder="e.g. 5" required />
                        <!-- tooltip -->
                        <span class="input-group-text">
                            <span class="tt" data-bs-placement="bottom"
                                title="The interest rate at which you are going to repay the loan">
                                <i class="bi bi-question-circle text-muted"></i>
                            </span>
                        </span>
                    </div>
                    <label for="payments-type" class="form-label">Type of monthly payments:</label>
                    <div class="mb-4 input-group">
                        <span class="input-group-text">
                            <i class="bi bi-wallet2 text-secondary"></i>
                        </span>
                        <select v-model="input_data['paymentsType']" class="form-select" id="payments-type">
                            <option value="annuity" selected>Annuity</option>
                            <option value="differentiated">Differentiated</option>
                        </select>
                    </div>
                    <div class="mb-4 text-center">
                        <button type="submit" class="btn " :class="$store.state.primaryBtnBootstrapType"
                            @click="Calculate">Calculate</button>
                    </div>
                </div>
            </div>

            <div v-if="loan_output" class="container overflow-auto mt-5">
                <div class="row">
                    <div class="col-md-6">
                        <p>Month payment: {{ loan_output.payment }}</p>
                        <p>Interest charges: {{ loan_output.overpay }}</p>
                        <p>Debt + interest: {{ loan_output.all_sum }} </p>
                    </div>
                    <div class="col-md-6">
                        <div class="container justify-content-center align-items-center ">
                            <Pie class="mt-5" :data="PieData" :options="PieOptions" />
                        </div>
                    </div>
                </div>
                <div class="col-lg-10">
                    <div class="container justify-content-center align-items-center ">
                        <Bar class="mt-5" :data="BarData" :options="BarOptions" />
                    </div>
                </div>
                <div class="container overflow-auto mt-5" style="height: 400px;">
                    <table class="table table-striped">
                        <thead class="table-dark">
                            <tr>
                                <th scope="col">Month</th>
                                <th scope="col">Amount of payment</th>
                                <th scope="col">Principal payment</th>
                                <th scope="col">Interest payment</th>
                                <th scope="col">Balance owed</th>
                            </tr>
                        </thead>
                        <tbody>
                            <tr v-for="item in loan_output.table" :key="item['month']">
                                <th scope="row">{{ item["month"] }}</th>
                                <td>{{ item["payment_amount"] }}</td>
                                <td>{{ item["payment_principal"] }}</td>
                                <td>{{ item["payment_interest"] }}</td>
                                <td>{{ item["balance_owed"] }}</td>
                            </tr>
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    </div>
</template>

<style></style>