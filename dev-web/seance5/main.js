window.addEventListener("DOMContentLoaded", init);

function init() {
  const canvas = document.getElementById("toile");
  const ctx = canvas.getContext("2d");

  const workers = [];

  if (window.Worker) {
    for (let i = 0; i < 200; i++) {
      const myWorker = new Worker("worker.js");

      myWorker.onmessage = function (e) {
        const [x, y, r, g, b] = e.data;
        ctx.fillStyle = `rgb(${r}, ${g}, ${b})`;
        ctx.fillRect(x, y, 50, 50);
      };
      workers.push(myWorker);
    }
  }
}
