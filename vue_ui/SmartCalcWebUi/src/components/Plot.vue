  
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
            data: {
                label: '',
                x: [1, 2, 3, 4, 5, 6, 7],
                y: [40, 39, 10, 40, 39, 80, 40],
            },
            input_data: {
                xMin: -10.0,
                xMax: 10.0,
                yMin: -10.0,
                yMax: 100.0,
                expression: '',
            }
        }
    },

    methods: {
        Calculate() {
            $.ajax({
                url: `http://localhost:8000/plot_calculate?${$.param(this.input_data)}`,
                type: "GET",
                success: (data) => { this.data = data; },
                error: this.showErrorAlert
            });
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
        Data() {
            return {
                labels: this.data['x'].map(value => value.toFixed(2)),
                datasets: [
                    {
                        label: this.data['label'],
                        backgroundColor: '#00bd7e',
                        borderColor: '#00bd7e',
                        data: this.data['y'],
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
                        min: this.input_data['yMin'],
                        max: this.input_data['yMax'],
                    },
                }
            }
        }
    }
}
</script>
  

<template>
    <div class="container mt-5">
        <div class="row">
            <div class="col ">
                <div class="form-floating">
                    <input v-model="input_data['expression']" class="form-control" type="text" id="expression-plot"
                        placeholder="e.g. sin(x)" required>
                    <label class="text-muted" for="expression-plot">Enter expression:</label>
                </div>

            </div>
        </div>
        <div class="row mt-2">
            <div class="col">
                <div class="form-floating">
                    <input v-model="input_data['xMin']" class="form-control" type="number" step="0.01" lang="en" id="x-from"
                        required>
                    <label class="text-muted" for="query">X min</label>
                </div>
            </div>
            <div class="col">
                <div class="form-floating">
                    <input v-model="input_data['xMax']" class="form-control" type="number" step="0.01" lang="en" id="xMax"
                        required>
                    <label class="text-muted" for="xMax">X max</label>
                </div>
            </div>
        </div>
        <div class="row mt-2">
            <div class="col">
                <div class="form-floating">
                    <input v-model="input_data['yMin']" class="form-control" type="number" step="0.01" lang="en" id="yMin"
                        required>
                    <label class="text-muted" for="yMin">Y min</label>
                </div>
            </div>
            <div class="col">
                <div class="form-floating">
                    <input v-model="input_data['yMax']" class="form-control" type="number" step="0.01" lang="en" id="yMax"
                        required>
                    <label class="text-muted" for="yMax">Y max</label>
                </div>
            </div>
        </div>
        <div class="mt-2 text-center">
            <button @click="Calculate" class="btn " :class="$store.state.primaryBtnBootstrapType">Calculate</button>
        </div>
        <Line class="mt-5" :data="Data" :options="Options" id="plotLine" />
    </div>
</template>
