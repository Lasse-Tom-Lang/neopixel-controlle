const checkboxes = document.querySelectorAll("input[type='checkbox']")
const output = document.getElementById("output")
const framesDiv = document.getElementById("frames")
const clearButton = document.getElementById("clearButton")

let frames = []

clearButton.addEventListener("click", () => {
  checkboxes.forEach(checkbox => {
    checkbox.checked = false
  })
})

function addFrame() {
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
  frames.push({number: frames.length + 1, text: string})
  showFrames()
}

function showFrames() {
  framesDiv.innerHTML = ""
  frames.forEach(frame => {
    let frameButton = document.createElement("button")
    frameButton.innerText = frame.number
    frameButton.addEventListener("click", loadFrame)
    frameButton.setAttribute("frameData", frame.text)
    framesDiv.appendChild(frameButton)
  })
}

function loadFrame(event) {
  frameInfo = event.target.getAttribute("frameData")
  frameInfo = frameInfo.substring(1, 74)
  for (let i = 0; i<37; i++) {
    if (frameInfo[i*2] == "0") {
      checkboxes[i].checked = false
    }
    else {
      checkboxes[i].checked = true
    }
  }
}

