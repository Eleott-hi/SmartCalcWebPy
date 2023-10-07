<template>
    <div class="container mt-5">
        <div class="row">
            <div class="col ">
                <div class="form-floating">
                    <input v-model="expression" class="form-control" type="text" id="expression-plot"
                        placeholder="e.g. sin(x)" required>
                    <label class="text-muted" for="expression-plot">Enter expression:</label>
                </div>

            </div>
        </div>
        <div class="row mt-2">
            <div class="col">
                <div class="form-floating">
                    <input v-model="xMin" class="form-control" type="number" step="0.01" lang="en" id="x-from" required>
                    <label class="text-muted" for="query">X min</label>
                </div>
            </div>
            <div class="col">
                <div class="form-floating">
                    <input v-model="xMax" class="form-control" type="number" step="0.01" lang="en" id="xMax" required>
                    <label class="text-muted" for="xMax">X max</label>
                </div>
            </div>
        </div>
        <div class="row mt-2">
            <div class="col">
                <div class="form-floating">
                    <input v-model="yMin" class="form-control" type="number" step="0.01" lang="en" id="yMin" required>
                    <label class="text-muted" for="yMin">Y min</label>
                </div>
            </div>
            <div class="col">
                <div class="form-floating">
                    <input v-model="yMax" class="form-control" type="number" step="0.01" lang="en" id="yMax" required>
                    <label class="text-muted" for="yMax">Y max</label>
                </div>
            </div>
        </div>
        <div class="mt-2 text-center">
            <button @click="ClickMe" class="btn btn-primary">Calculate</button>
        </div>
        <Line class="mt-5" :data="Data" :options="Options" id="plotLine"/>
    </div>
</template>
  
<script>
import { Line } from 'vue-chartjs'
import {
    Chart as ChartJS,
    CategoryScale,
    LinearScale,
    PointElement,
    LineElement,
    Title,
    Tooltip,
    Legend
} from 'chart.js'

ChartJS.register(
    CategoryScale,
    LinearScale,
    PointElement,
    LineElement,
    Title,
    Tooltip,
    Legend
)

export default {
    name: 'LineChart',
    components: { Line },

    data() {
        return {
            x: [1, 2, 3, 4, 5, 6, 7],
            y: [40, 39, 10, 40, 39, 80, 40],
            xMin: -10.0,
            xMax: 10.0,
            yMin: -10.0,
            yMax: 10.0,
            expression: 'x*x',
            label: '',
        }
    },

    methods: {
        ClickMe(e) {
            let { x, y } = this.Calculate(this.xMin, this.xMax)
            this.x = x.map(value => value.toFixed(2));
            this.y = y.map(value => value.toFixed(2));
            this.label = this.expression

        },
        Calculate(from = -10.0, to = 10.0) {
            let x = []
            let y = []
            let step = (to - from) / 100.0

            for (let i = from; i <= to; i += step) {
                let expression = this.expression
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
                        label: this.expression,
                        backgroundColor: '#00bd7e',
                        borderColor: '#00bd7e',
                        data: this.y
                    }
                ]
            }
        },

        Options() {
            return {
                responsive: true,
                // maintainAspectRatio: false,
                indexAxis: 'x',
                scales: {
                    // x: {
                    //     min: this.xMin,
                    //     max: this.xMax,
                    // },
                    y: {
                        min: this.yMin,
                        max: this.yMax,
                    },
                }
            }
        }
    }
}
</script>
  