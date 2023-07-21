document.addEventListener("DOMContentLoaded", function () {
  // Now you can access the global variables x, y, and label
  const ctx = document.getElementById("myChart");

  new Chart(ctx, {
    type: "line",
    data: {
      labels: x.map((value) => value.toFixed(1)), // Round the x-axis values
      datasets: [
        {
          label: label,
          data: y,
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
});