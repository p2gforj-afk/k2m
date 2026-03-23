window.addEventListener("DOMContentLoaded", init);

// Rock >  Scissors > Paper > Rock > ...
const choices = ["rock", "scissors", "paper"];
let humanChoice; //0 for Rock,1 for Scissors or 2 for Paper
let computerChoice; // 0 for Rock,1 for Scissors or 2 for Paper

let humanScore = 0;
let computerScore = 0;

let gameLoop;
let cptGame = 0; // 3 sets for a game
let cptLoop = 0; // human can choose for 5 seconds, computer doesn't see the human's choice and play. Score is set within 2 seconds

//*********************
// HTML elements
let humanScoreLabel; //where to print the human's score
let computerScoreLabel; // guess :)

let ctxHuman; // the 2d context where to draw the human's choice
let ctxComputer;

let rockBtn; // the button with witch the human chooses a rock
let paperBtn; // ... a paper
let scissorsBtn; // ... a scissors
//*********************

//*******
// pre-loaded images to be drawn in canvases
var rockImage;
var paperImage;
var scissorsImage;
//*******

function init() {
  //*************
  // This parts sets values for HTML elements
  // >>>>>> retreive 2d contexts
  ctxHuman = document.getElementById("humanPlayerCanvas").getContext("2d");
  ctxComputer = document
    .getElementById("computerPlayerCanvas")
    .getContext("2d");
  // >>>>>> retreive score labels
  humanScoreLabel = document.getElementById("humanScoreLabel");
  computerScoreLabel = document.getElementById("computerScoreLabel");
  // >>>>>> retreive buttons
  rockBtn = document.getElementById("rockBtn");
  paperBtn = document.getElementById("paperBtn");
  scissorsBtn = document.getElementById("scissorsBtn");
  //*************

  //************************************************************
  // in this part, we wait for all the images to load before starting the game
  let rockImageOk = false;
  let paperImageOk = false;
  let scissorsImageOk = false;

  rockImage = new Image(); // create an image object
  rockImage.src = "./rock.png"; // set its source, may take some time
  paperImage = new Image();
  paperImage.src = "./paper.png";
  scissorsImage = new Image();
  scissorsImage.src = "./scissors.png";

  // >>>>>>>>>>>>> begin of callBacks
  function rockLoaded() {
    console.log("Rock Loaded");
    rockImageOk = true;
    fireEvent();
  }
  function paperLoaded() {
    console.log("Paper Loaded");
    paperImageOk = true;
    fireEvent();
  }
  function scissorsLoaded() {
    console.log("Scissors Loaded");
    scissorsImageOk = true;
    fireEvent();
  }
  function launchGame() {
    gameLoop = setInterval(playGame, 1000);
  }
  // >>>>>>>>>>>>> end of callBacks

  // >>>>>>>>>>>>> Link events and callBacks
  // Link the "load" event fired by the "rockImage" object with the "rockLoaded" callback
  rockImage.addEventListener("load", rockLoaded);
  // Link the "load" event fired by the "paperImage" object with the "paperLoaded" callback
  paperImage.addEventListener("load", paperLoaded);
  // Link the "load" event fired by the "scissorsImage" object with the "scissorsLoaded" callback
  scissorsImage.addEventListener("load", scissorsLoaded);
  // Link the "allImagesOk" event fired by the "window" object with the "launchGame" callback
  window.addEventListener("allImagesOk", launchGame);
  // Link the "click" event fired by the "rockBtn" object with a call to "humanSelects("rock")"
  rockBtn.addEventListener("click", helper1);
  // Link the "click" event fired by the "paperBtn" object with a call to "humanSelects("paper")"
  paperBtn.addEventListener("click", function () {
    humanSelects("paper");
  });
  // Link the "click" event fired by the "scissorsBtn" object with a call to "humanSelects("scissors")"
  scissorsBtn.addEventListener("click", function () {
    humanSelects("scissors");
  });
  // >>>>>>>>>>>>>

  function helper1() {
    humanSelects("rock");
  }

  var helper2 = function () {
    //.....
  };

  // this function fires a custom event "allImagesOk" when all images are loaded
  function fireEvent() {
    if (rockImageOk & scissorsImageOk & paperImageOk) {
      window.dispatchEvent(new Event("allImagesOk"));
    }
  }
}

function playGame() {
  cptLoop = cptLoop + 1;
  if (cptLoop == 5) {
    disableButtons();
    computerChoice = choices[Math.floor(Math.random() * 3)];
    computerSelects(computerChoice);
    setScore();
  }

  if (cptLoop == 7) {
    cptLoop = 0;
    resetGame();
  }
}

function setScore() {
  if (humanChoice == undefined) {
    computerScore++;
  } else {
    var val = computerChoice - humanChoice;
    console.log(
      "computer plays " +
        choices[computerChoice] +
        " and human plays " +
        choices[humanChoice],
    );
    if (val == 1 || val == -2) {
      humanScore++;
      console.log("    human wins");
    }
    if (val == -1 || val == 2) {
      computerScore++;
      console.log("    computer wins");
    }
  }
  humanScoreLabel.innerHTML = humanScore;
  computerScoreLabel.innerHTML = computerScore;
}

function resetGame() {
  cptGame++;
  ctxComputer.clearRect(0, 0, 328, 328);
  ctxHuman.clearRect(0, 0, 328, 328);
  computerChoice = undefined;
  humanChoice = undefined;
  if (cptGame == 3) {
    clearInterval(gameLoop); // End Gane
  } else {
    ableButtons();
  }
}

// this function sets the "disabled" property of buttons to "false" : human can click on any of them
function ableButtons() {
  rockBtn.disabled = false;
  paperBtn.disabled = false;
  scissorsBtn.disabled = false;
}

// this function sets the "disabled" property of buttons to "true": human cannot click on any of them
function disableButtons() {
  rockBtn.disabled = true;
  paperBtn.disabled = true;
  scissorsBtn.disabled = true;
}

function humanSelects(shifumi) {
  let image;
  switch (shifumi) {
    case "rock":
      image = rockImage;
      humanChoice = 0;
      break;
    case "scissors":
      image = scissorsImage;
      humanChoice = 1;
      break;
    case "paper":
      image = paperImage;
      humanChoice = 2;
      break;
    default:
      console.log("not a shifumi!");
  }
  ctxHuman.drawImage(image, 0, 0, 328, 328);
  disableButtons();
}
function computerSelects(shifumi) {
  let image;
  switch (shifumi) {
    case "rock":
      image = rockImage;
      computerChoice = 0;
      break;
    case "scissors":
      image = scissorsImage;
      computerChoice = 1;
      break;
    case "paper":
      image = paperImage;
      computerChoice = 2;
      break;
    default:
      console.log("not a shifumi!");
  }
  ctxComputer.drawImage(image, 0, 0, 328, 328);
}

class ImageManager {
  constructor({ name, src }, imageLoader) {
    this.name = name;
    this.src = src;
    this.image = new Image();
    this.image.addEventListener("load", (e) => {
      imageLoader.dispatchEvent(
        new CustomEvent(`imageLoaded`, { detail: this.name }),
      );
    });
  }
  loadThisImage() {
    this.image.src = this.src;
  }
}

const myArray = [
  { name: "rock", src: "./assets/rock.png" },
  { name: "paper", src: "./assets/paper.png" },
  { name: "scissors", src: "./assets/scissors.png" },
];
const myImagesLoader = new ImagesLoader(myArray);

window.addEventListener("allImagesOk", launchGame);
function launchGame() {
  rockImage = myImagesLoader.getImage("rock");
  paperImage = myImagesLoader.getImage("paper");
  scissorsImage = myImagesLoader.getImage("scissors");
  gameLoop = setInterval(playGame, 1000);
}
