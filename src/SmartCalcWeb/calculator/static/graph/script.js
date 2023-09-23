expression = document.getElementById("expression-plot");
context = document.getElementById("chart");
xMin = document.getElementById("x-from");
xMax = document.getElementById("x-to");
yMin = document.getElementById("y-from");
yMax = document.getElementById("y-to");

let config = {
  type: 'line',
  options: {
    plugins: {
      legend: {
        display: true
      }
    },
    scales: {
      x: {
        display: true
      },
      y: {
        display: true,
      }
    }
  },
  data: {
    datasets: [{
      tension: 0.4
    }]
  }
}

chart = new Chart(context, config);

document.addEventListener("DOMContentLoaded", function () {
  DrawPlot({ x: [], y: [], label: "Undefined" });
});

function getCsrfToken() {
  const csrfCookie = document.cookie.match(/csrftoken=([\w-]+)/);
  return csrfCookie ? csrfCookie[1] : "";
}

$("#plot-form").on("submit", function (event) {
  event.preventDefault();

  let data = {
    expression: $("#expression-plot").val(),
    x_from: $("#x-from").val(),
    x_to: $("#x-to").val()
  }

  console.log(data);

  $.ajax({
    url: "/graph",
    type: "POST",
    contentType: "application/json",
    headers: {
      "X-CSRFToken": getCsrfToken(),
    },

    data: JSON.stringify(data),

    success: DrawPlot,

    error: function (xhr, status, error) {
      console.error("Error fetching plot:", status, error);
    },
  });
});

function DrawPlot(data) {
  console.log(data);

  chart.data.labels = data.x.map(x => x.toFixed(1));
  chart.data.datasets[0].data = data.y.filter(value => !isNaN(value));
  chart.data.datasets[0].label = data.label;

  chart.config.options.scales.y.min = $("#y-from").val();
  chart.config.options.scales.y.max = $("#y-to").val();

  chart.update();

}
