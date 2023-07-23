let plot;
x = [];
y = [];
label = "Undefined";

document.addEventListener("DOMContentLoaded", function () {
  DrawPlot();
});

function getCsrfToken() {
  const csrfCookie = document.cookie.match(/csrftoken=([\w-]+)/);
  return csrfCookie ? csrfCookie[1] : "";
}

$("#plot-form").on("submit", function (event) {
  event.preventDefault();

  var formData = {
    expression: $("#result").val(),
    x_from: $("#x_from").val(),
    x_to: $("#x_to").val(),
    y_from: $("#y_from").val(),
    y_to: $("#y_to").val(),
  };

  $.ajax({
    url: "/graph", // Replace with your API endpoint
    type: "POST",
    contentType: "application/json",
    headers: {
      "X-CSRFToken": getCsrfToken(), // Fetch the CSRF token from the cookie
    },
    data: JSON.stringify(formData),
    success: function (data) {
      x = data.x;
      y = data.y;
      label = data.expression;
      DrawPlot();
    },
    error: function (xhr, status, error) {
      console.error("Error fetching random number:", status, error);
    },
  });
});

function DrawPlot() {
  // Now you can access the global variables x, y, and label
  const ctx = document.getElementById("myChart");

  if (plot) {
    plot.destroy();
  }

  plot = new Chart(ctx, {
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
}
