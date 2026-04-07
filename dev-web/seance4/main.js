class ManagedImage {
  constructor(src) {
    this.src = src;
    this.image = new Image();
    this.loaded = false;
  }

  load() {
    return new Promise((resolve, reject) => {
      this.image.src = this.src;
      this.image.onload = () => {
        this.loaded = true;
        resolve(this);
      };
      this.image.onerror = () => reject(`image not loaded`);
    });
  }

  getImage() {
    return this.image;
  }
}

class ImageManager {
  constructor() {
    this.managedImages = {};
  }

  async loadImages(imageSources) {
    const promises = Object.entries(imageSources).map(([name, src]) => {
      const mImg = new ManagedImage(src);
      this.managedImages[name] = mImg;
      return mImg.load();
    });
    return Promise.all(promises);
  }

  getImage(choice) {
    return this.managedImages[choice]?.getImage();
  }
}

class UI {
  constructor(canvasSize) {
    this.canvasSize = canvasSize;
  }

  initializeElements() {
    this.humanScoreLabel = document.getElementById("humanScoreLabel");
    this.computerScoreLabel = document.getElementById("computerScoreLabel");
    this.ctxHuman = document.getElementById("humanPlayerCanvas").getContext("2d");
    this.ctxComputer = document.getElementById("computerPlayerCanvas").getContext("2d");
    this.rockBtn = document.getElementById("rockBtn");
    this.paperBtn = document.getElementById("paperBtn");
    this.scissorsBtn = document.getElementById("scissorsBtn");
  }

  setupEventListeners(game) {
    this.rockBtn.addEventListener("click", () => game.humanPlaysChoice("rock"));
    this.paperBtn.addEventListener("click", () => game.humanPlaysChoice("paper"));
    this.scissorsBtn.addEventListener("click", () => game.humanPlaysChoice("scissors"));
  }

  drawHumanChoice(choice, imageManager) {
    const img = imageManager.getImage(choice);
    this.ctxHuman.drawImage(img, 0, 0, this.canvasSize, this.canvasSize);
  }

  drawComputerChoice(choice, imageManager) {
    const img = imageManager.getImage(choice);
    this.ctxComputer.drawImage(img, 0, 0, this.canvasSize, this.canvasSize);
  }

  enableButtons() {
    this.rockBtn.disabled = false;
    this.paperBtn.disabled = false;
    this.scissorsBtn.disabled = false;
  }

  disableButtons() {
    this.rockBtn.disabled = true;
    this.paperBtn.disabled = true;
    this.scissorsBtn.disabled = true;
  }
  updateScoreDisplay(hScore, cScore) {
    this.humanScoreLabel.textContent = hScore;
    this.computerScoreLabel.textContent = cScore;
  }

  clearCanvases() {
    this.ctxHuman.clearRect(0, 0, this.canvasSize, this.canvasSize);
    this.ctxComputer.clearRect(0, 0, this.canvasSize, this.canvasSize);
  }

  showGameOver(hScore, cScore) {
    if (hScore > cScore) {
      alert("human wins, well played")
    }
    else {
      alert("computer wins, try again")
    }
  }
}

class Game {
  constructor() {
    this.CHOICES = ["rock", "scissors", "paper"];
    this.CANVAS_SIZE = 328;
    this.humanScore = 0;
    this.computerScore = 0;
    this.cptLoop = 0; // timer for each round
  }

  setDependencies(imageManager, ui) {
    this.imageManager = imageManager;
    this.ui = ui;
  }

  startGame() {
    this.ui.initializeElements();
    this.ui.setupEventListeners(this);
    this.gameLoop = setInterval(() => this.playRound(), 1000);
  }

  stopGame() {
    clearInterval(this.gameLoop);
    this.ui.showGameOver(this.humanScore, this.computerScore);
  }

  playRound() {
    this.cptLoop++;
    if (this.cptLoop === 5) {
      this.ui.disableButtons();
      const randomIndex = Math.floor(Math.random() * 3);
      this.computerChoice = randomIndex;
      this.ui.drawComputerChoice(this.CHOICES[randomIndex], this.imageManager);
      this.calculateScore();
    }

    if (this.cptLoop === 7) {
      this.cptLoop = 0;
      this.resetRound();
    }
  }

  calculateScore() {
    if (this.humanChoice === undefined) {
      this.computerScore++;
    } else {
      const val = this.computerChoice - this.humanChoice;
      if (val === 1 || val === -2) this.humanScore++;
      else if (val === -1 || val === 2) this.computerScore++;
    }
    this.ui.updateScoreDisplay(this.humanScore, this.computerScore);
  }

  resetRound() {
    this.ui.clearCanvases();
    this.humanChoice = undefined;
    this.computerChoice = undefined;

    if (this.humanScore == 3 || this.computerScore == 3) {
      this.stopGame();
    } else {
      this.ui.enableButtons();
    }
  }

  humanPlaysChoice(choice) {
    this.humanChoice = this.getChoiceIndex(choice);
    this.ui.drawHumanChoice(choice, this.imageManager);
    this.ui.disableButtons();
  }

  getChoiceIndex(choice) {
    return this.CHOICES.indexOf(choice);
  }
}

// launch the game
const game = new Game();
const ui = new UI(game.CANVAS_SIZE);
const imgMgr = new ImageManager();

const sources = {
  rock: "./assets/rock.png",
  paper: "./assets/paper.png",
  scissors: "./assets/scissors.png"
};

imgMgr.loadImages(sources).then(() => {
  game.setDependencies(imgMgr, ui);
  game.startGame();
});
