<template>
    <div class="container mt-5">
        <div class="row justify-content-center">
            <div class="row">
                <div class="col-md-6">
                    <div class="container">
                        <form>
                            <label for="amount" class="form-label">Amount:</label>
                            <div class="input-group mb-4">
                                <!-- tooltip -->
                                <span class="input-group-text">
                                    <i class="bi bi-cash-stack text-secondary"></i>
                                </span>
                                <input v-model="amount" type="number" min="10000" class="form-control"
                                    placeholder="e.g. 100000" required />
                                <!-- tooltip -->
                                <span class="input-group-text">
                                    <span class="tt" data-bs-placement="bottom"
                                        title="Enter an amount of money you want to borrow">
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
                                <input v-model="period" type="number" id="period" min="1" step="1" class="form-control"
                                    placeholder="e.g. 12" required />
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
                                <input v-model="rate" type="number" id="rate" min="1" step="1" class="form-control"
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
                                <select v-model="paymentsType" class="form-select" id="payments-type">
                                    <option value="annuity" selected>Annuity</option>
                                    <option value="differentiated">Differentiated</option>
                                </select>
                            </div>
                            <div class="mb-4 text-center">
                                <p>Amount: {{ amount }}</p>
                                <p>Period: {{ period }}</p>
                                <p>Rate: {{ rate }}</p>
                                <p>Payments type: {{ paymentsType }}</p>
                                <button type="submit" class="btn btn-secondary">Calculate</button>
                            </div>
                        </form>
                    </div>
                </div>
                <div class="col-md-6">
                    <div class="container">
                        <div class="container justify-content-center align-items-center ">
                            <Pie class="mt-5" :data="PieData" :options="PieOptions" @click="ClickMe" />
                        </div>
                    </div>
                </div>
            </div>
            <div class="col-lg-10">
                <div class="container justify-content-center align-items-center ">
                    <Bar class="mt-5" :data="Data" :options="Options" @click="ClickMe" />
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
                        <tr>
                            <th scope="row">1</th>
                            <td>1234</td>
                            <td>1234</td>
                            <td>1234</td>
                            <td>1234</td>
                        </tr>
                        <tr>
                            <th scope="row">2</th>
                            <td>1234</td>
                            <td>1234</td>
                            <td>1234</td>
                            <td>1234</td>
                        </tr>
                        <tr>
                            <th scope="row">3</th>
                            <td>1234</td>
                            <td>1234</td>
                            <td>1234</td>
                            <td>1234</td>
                        </tr>
                    </tbody>
                </table>
            </div>
        </div>
    </div>
</template>


<script>
import { Bar, Pie } from 'vue-chartjs'
import { Chart as ChartJS, ArcElement, Title, Tooltip, Legend, BarElement, CategoryScale, LinearScale } from 'chart.js'

ChartJS.register(Title, Tooltip, Legend, ArcElement, BarElement, CategoryScale, LinearScale)

export default {
    name: 'BarChart',
    components: { Bar, Pie },

    data() {
        return {
            amount: 100000,
            period: 12,
            rate: 5,
            paymentsType: 'annuity',

            pieData: {
                labels: ['VueJs', 'EmberJs', 'ReactJs', 'AngularJs'],
                datasets: [
                    {
                        backgroundColor: ['#41B883', '#E46651', '#00D8FF', '#DD1B16'],
                        hoverBackgroundColor: ["#FF5A5E", "#5AD3D1", "#FFC870", "#A8B3C5",],
                        data: [40, 20, 80, 10]
                    }
                ]
            },


            x: [1, 2, 3],
            from: -10.0,
            to: 10.0,
            label: '',
            scales: {
                xAxes: [{ ticks: { min: -10, max: 10 } }],
                yAxes: [{ ticks: { min: -10, max: 10 } }],
            }
        }
    },

    methods: {
        ClickMe(e) {
            let { x, y } = this.Calculate(this.from, this.to)
            this.x = x.map(value => value.toFixed(2));
            this.y = y.map(value => value.toFixed(2));
            this.label = this.expressions

        },
        Calculate(from = -10.0, to = 10.0) {
            let x = []
            let y = []
            let step = (to - from) / 100.0

            for (let i = from; i <= to; i += step) {
                let expression = this.expressions
                expression = expression.replaceAll('x', "(" + i + ")")
                x.push(i)
                y.push(eval(expression))
            }

            return { x, y }

        }
    },

    computed: {
        Data() {
            return {
                labels: this.x,
                datasets: [
                    {
                        label: 'Main debt',
                        data: [1, 2, 3],
                        backgroundColor: "#FF0000",
                    },
                    {
                        label: 'Percentage',
                        data: [2, 3, 1],
                        backgroundColor: "#0000FF",
                    },
                ]
            }
        },
        Options() {
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
                    xAxes: [{ ticks: { min: -10, max: 10 } }],
                    yAxes: [{ ticks: { min: -10, max: 10 } }],
                }
            }
        },
        PieData() {
            return this.pieData
        },

        PieOptions() {
            return {}
        }
    }
}
</script>
  
<style></style>