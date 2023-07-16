var selectedInputId = "result";

function appendToResult(value) {
  var selectedInput = document.getElementById(selectedInputId);
  selectedInput.value += value;
  console.log(selectedInput.value);
}

function setInputId(inputId) {
  var resultInput = document.getElementById("result");
  var xValueInput = document.getElementById("xValue");
  resultInput.removeAttribute("custom-focus");
  xValueInput.removeAttribute("custom-focus");

  selectedInputId = inputId;
  var selectedInput = document.getElementById(selectedInputId);
  selectedInput.setAttribute("custom-focus", "");
}

function calculate() {
  sendPostRequest();
}

function clearResult() {
  document.getElementById(selectedInputId).value = "";
}

function deleteLastElement() {
  const resultField = document.getElementById(selectedInputId);
  const currentInput = resultField.value;
  resultField.value = currentInput.slice(0, -1);
}

function animateCircle(button, x, y) {
  const rect = button.getBoundingClientRect();
  const offsetX = x - rect.left;
  const offsetY = y - rect.top;

  const circle = document.createElement("div");
  circle.classList.add("circle");
  circle.style.left = `${offsetX}px`;
  circle.style.top = `${offsetY}px`;
  button.appendChild(circle);

  setTimeout(() => {
    circle.classList.add("active");
    button.classList.add("active");
    setTimeout(() => {
      circle.remove();
      button.classList.remove("active");
    }, 300);
  }, 10);
}

window.addEventListener("keydown", function (event) {
  var key = event.key;
  var button = null;

  switch (key) {
    case "0":
      button = document.querySelector('button[data-value="0"]');
      break;
    case "1":
      button = document.querySelector('button[data-value="1"]');
      break;
    case "2":
      button = document.querySelector('button[data-value="2"]');
      break;
    case "3":
      button = document.querySelector('button[data-value="3"]');
      break;
    case "4":
      button = document.querySelector('button[data-value="4"]');
      break;
    case "5":
      button = document.querySelector('button[data-value="5"]');
      break;
    case "6":
      button = document.querySelector('button[data-value="6"]');
      break;
    case "7":
      button = document.querySelector('button[data-value="7"]');
      break;
    case "8":
      button = document.querySelector('button[data-value="8"]');
      break;
    case "9":
      button = document.querySelector('button[data-value="9"]');
      break;
    case "+":
      button = document.querySelector('button[data-value="+"]');
      break;
    case "-":
      button = document.querySelector('button[data-value="-"]');
      break;
    case "*":
      button = document.querySelector('button[data-value="*"]');
      break;
    case "/":
      button = document.querySelector('button[data-value="/"]');
      break;
    case ".":
      button = document.querySelector('button[data-value="."]');
      break;
    case "%":
      button = document.querySelector('button[data-value="%"]');
      break;
    case "(":
      button = document.querySelector('button[data-value="("]');
      break;
    case ")":
      button = document.querySelector('button[data-value=")"]');
      break;
    case "=":
      button = document.querySelector('button[data-value="="]');
      break;
    case "Escape":
      button = document.querySelector('button[data-value="C"]');
      break;
    case "a":
      button = document.querySelector('button[data-value="Math.acos("]');
      break;
    case "c":
      button = document.querySelector('button[data-value="Math.cos("]');
      break;
    case "s":
      button = document.querySelector('button[data-value="Math.asin("]');
      break;
    case "i":
      button = document.querySelector('button[data-value="Math.sin("]');
      break;
    case "t":
      button = document.querySelector('button[data-value="Math.atan("]');
      break;
    case "n":
      button = document.querySelector('button[data-value="Math.tan("]');
      break;
    case "r":
      button = document.querySelector('button[data-value="Math.sqrt("]');
      break;
    case "^":
      button = document.querySelector('button[data-value="Math.pow("]');
      break;
    case "Backspace":
      button = document.querySelector('button[data-value="Backspace"]');
      break;
    case "x":
      button = document.querySelector('button[data-value="x"]');
      break;
  }

  if (button) {
    animateCircle(button, event.clientX, event.clientY);
    button.click();
  }
});

function getCsrfToken() {
  const csrfCookie = document.cookie.match(/csrftoken=([\w-]+)/);
  return csrfCookie ? csrfCookie[1] : "";
}


function sendPostRequest() {
  const payload = JSON.stringify({
    expression: document.getElementById("result").value,
  });

  fetch("/calculate", {
    method: "POST",
    headers: {
      "Content-Type": "application/json",
      "X-CSRFToken": getCsrfToken(),
    },
    body: payload,
  })
    .then((response) => {
      if (response.ok) {
        return response.json();
      } else {
        return { result: "Invalid Expression" };
      }
    })
    .then((data) => {
      document.getElementById("result").value = data.result;
    })
    .catch((error) => {
      console.error(error);
    });
}



const dragHandle = document.querySelector('.drag-handle');
const sidebar = document.querySelector('.sidebar');
const container = document.querySelector('.container');
const sidebarToggle = document.querySelector('#sidebarToggle');
const sidebarContent = document.querySelector('.sidebar-content');

let isResizing = false;
let sidebarWidth = sidebar.offsetWidth;
let isSidebarExpanded = true;

dragHandle.addEventListener('mousedown', startResize);
sidebarToggle.addEventListener('click', toggleSidebar);

function startResize(e) {
    e.preventDefault();
    isResizing = true;

    document.addEventListener('mousemove', resize);
    document.addEventListener('mouseup', stopResize);
}

function resize(e) {
    if (!isResizing) return;

    const containerWidth = container.offsetWidth;
    const mouseX = e.pageX;

    const minSidebarWidth = 60; // Minimum sidebar width
    const maxSidebarWidth = containerWidth - minSidebarWidth; // Maximum sidebar width

    sidebarWidth = Math.max(minSidebarWidth, Math.min(maxSidebarWidth, mouseX));

    sidebar.style.width = `${sidebarWidth}px`;
}

function stopResize() {
    isResizing = false;

    document.removeEventListener('mousemove', resize);
    document.removeEventListener('mouseup', stopResize);
}

function toggleSidebar() {
    if (isSidebarExpanded) {
        sidebarWidth = 60;
        sidebar.style.width = `${sidebarWidth}px`;
        sidebarToggle.innerHTML = '<i class="sidebar-toggle-icon fas fa-chevron-right"></i>';
    } else {
        sidebarWidth = 200;
        sidebar.style.width = `${sidebarWidth}px`;
        sidebarToggle.innerHTML = '<i class="sidebar-toggle-icon fas fa-chevron-left"></i>';
    }

    isSidebarExpanded = !isSidebarExpanded;
}


