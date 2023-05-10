const checkboxes = document.querySelectorAll("input[type='checkbox']")
const output = document.getElementById("output")

function generateList() {
  let string = "{"
  let first = true
  checkboxes.forEach(checkbox => {
    if (first) {
      first = false
    }
    else {
      string += ","
    }
    if (checkbox.checked) {
      string += "1"
    }
    else {
      string += "0"
    }
  })
  string += "}"
  output.innerText = string
}

