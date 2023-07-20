const ctx = document.getElementById("myChart");

//   {{ data.x }}
//   {{ data.y }}
// "{{ data.expression }}"
x = [];
y = [];
label = "x*x";

for (let i = -10; i <= 10; i++) {
  x.push(i);
  y.push(i * i);
}

new Chart(ctx, {
  type: "line",
  data: {
    labels: x.map((value) => value.toFixed(1)), // Round the x-axis values
    datasets: [
      {
        label: label,
        data: y.map((value) => value.toFixed(1)),
        borderWidth: 1,
      },
    ],
  },
  options: {
    scales: {
      y: {
        beginAtZero: false,
      },
    },
  },
});
