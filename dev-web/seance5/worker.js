function randomNumber() {
  const x = Math.floor(Math.random() * 730);
  const y = Math.floor(Math.random() * 335);
  const r = Math.floor(Math.random() * 255);
  const g = Math.floor(Math.random() * 255);
  const b = Math.floor(Math.random() * 255);
  postMessage([x, y, r, g, b]);
}

setInterval(randomNumber, 20);
