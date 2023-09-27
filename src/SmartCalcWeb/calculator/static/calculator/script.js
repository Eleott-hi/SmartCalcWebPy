var selectedInputId = "result";

function getCsrfToken() {
    const csrfCookie = document.cookie.match(/csrftoken=([\w-]+)/);
    return csrfCookie ? csrfCookie[1] : "";
}

function appendToResult(value) {
    var selectedInput = document.getElementById(selectedInputId);
    selectedInput.value += value;
}

function setInputId(inputId) {
    ids = ["result", "xValue"];

    for (const i of ids) {
        var resultInput = document.getElementById(i);
        resultInput.removeAttribute("custom-focus");
    }

    selectedInputId = inputId;
    document.getElementById(selectedInputId).setAttribute("custom-focus", "");
}

function calculate() {
    const payload = {
        expression: $("#result").val(),
        xValue: $("#xValue").val()
    };

    console.log(payload);

    $.ajax({
        url: "/calculate",
        type: "POST",
        contentType: "application/json",
        headers: {
            "X-CSRFToken": getCsrfToken(),
        },

        data: JSON.stringify(payload),

        success: (data) => { document.getElementById("result").value = data.result; },

        error: function (xhr, status, error) {
            console.error("Error calc:", xhr, status, error);

            // Handle the error here
            if (xhr.responseJSON && xhr.responseJSON.error) {
                alert("Error: " + xhr.responseJSON.error);
            } else {
                alert("An error occurred.");
            }
        },
    });
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

// window.addEventListener("keydown", function (event) {
//     var key = event.key;
//     var button = null;

//     switch (key) {
//         case "0":
//             button = document.querySelector('button[data-value="0"]');
//             break;
//         case "1":
//             button = document.querySelector('button[data-value="1"]');
//             break;
//         case "2":
//             button = document.querySelector('button[data-value="2"]');
//             break;
//         case "3":
//             button = document.querySelector('button[data-value="3"]');
//             break;
//         case "4":
//             button = document.querySelector('button[data-value="4"]');
//             break;
//         case "5":
//             button = document.querySelector('button[data-value="5"]');
//             break;
//         case "6":
//             button = document.querySelector('button[data-value="6"]');
//             break;
//         case "7":
//             button = document.querySelector('button[data-value="7"]');
//             break;
//         case "8":
//             button = document.querySelector('button[data-value="8"]');
//             break;
//         case "9":
//             button = document.querySelector('button[data-value="9"]');
//             break;
//         case "+":
//             button = document.querySelector('button[data-value="+"]');
//             break;
//         case "-":
//             button = document.querySelector('button[data-value="-"]');
//             break;
//         case "*":
//             button = document.querySelector('button[data-value="*"]');
//             break;
//         case "/":
//             button = document.querySelector('button[data-value="/"]');
//             break;
//         case ".":
//             button = document.querySelector('button[data-value="."]');
//             break;
//         case "%":
//             button = document.querySelector('button[data-value="%"]');
//             break;
//         case "(":
//             button = document.querySelector('button[data-value="("]');
//             break;
//         case ")":
//             button = document.querySelector('button[data-value=")"]');
//             break;
//         case "=":
//             button = document.querySelector('button[data-value="="]');
//             break;
//         case "Escape":
//             button = document.querySelector('button[data-value="C"]');
//             break;
//         case "a":
//             button = document.querySelector('button[data-value="Math.acos("]');
//             break;
//         case "c":
//             button = document.querySelector('button[data-value="Math.cos("]');
//             break;
//         case "s":
//             button = document.querySelector('button[data-value="Math.asin("]');
//             break;
//         case "i":
//             button = document.querySelector('button[data-value="Math.sin("]');
//             break;
//         case "t":
//             button = document.querySelector('button[data-value="Math.atan("]');
//             break;
//         case "n":
//             button = document.querySelector('button[data-value="Math.tan("]');
//             break;
//         case "r":
//             button = document.querySelector('button[data-value="Math.sqrt("]');
//             break;
//         case "^":
//             button = document.querySelector('button[data-value="Math.pow("]');
//             break;
//         case "Backspace":
//             button = document.querySelector('button[data-value="Backspace"]');
//             break;
//         case "x":
//             button = document.querySelector('button[data-value="x"]');
//             break;
//     }

//     if (button) {
//         animateCircle(button, event.clientX, event.clientY);
//         button.click();
//     }
// });







