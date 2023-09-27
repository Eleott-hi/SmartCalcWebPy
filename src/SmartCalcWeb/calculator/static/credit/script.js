var context_chart_credit_pie = document.getElementById("chart-credit-pie").getContext('2d');
var chart_credit_pie = new Chart(context_chart_credit_pie, {
    plugins: [ChartDataLabels],
    type: 'pie',
    data: {
        labels: ["Red", "Green", "Yellow", "Grey", "Dark Grey"],
        datasets: [{
            data: [210, 130, 120, 160, 120],
            backgroundColor: ["#F7464A", "#46BFBD", "#FDB45C", "#949FB1", "#4D5360"],
            hoverBackgroundColor: ["#FF5A5E", "#5AD3D1", "#FFC870", "#A8B3C5", "#616774"]
        }]
    },
    options: {
        responsive: true,
        legend: {
            position: 'left',
            labels: {
                padding: 20,
                boxWidth: 10
            }
        },
        plugins: {
            datalabels: {
                formatter: (value, ctx) => {
                    let sum = 0;
                    let dataArr = ctx.chart.data.datasets[0].data;
                    dataArr.map(data => {
                        sum += data;
                    });
                    let percentage = (value * 100 / sum).toFixed(2) + "%";
                    return percentage;
                },
                color: 'white',
                labels: {
                    title: {
                        font: {
                            size: '16'
                        }
                    }
                }
            }
        }
    }
});

const labels = [1, 2, 3, 4, 5, 6, 7];
const data = {
    labels: labels,
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
};

const config_credit_stacked_bar_chart = {
    type: 'bar',
    data: data,
    options: {
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
            }
        }
    }
};


var context_chart_credit_stacked_bar = document.getElementById("chart-credit-stacked-bar");
var chart_credit_stacked_bar = new Chart(context_chart_credit_stacked_bar, config_credit_stacked_bar_chart);

