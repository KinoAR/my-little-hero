open GameObjects;
open Utility;

type scene = {
  name: string,
  id: int,
  start: unit => unit,
  close: unit => unit
};

type battleScene = {
  name:string,
  id:int,
  player: player,
  enemy: enemy,
};

let hero = GameObjects.heroBase;
let waitInput = string => {
  string |> print_string;
  let _ = read_line();
  ();
};

let waitInputLine = string => {
  string |> print_endline;
  let _ = read_line();
  ();
};

let prompt = string => {
  string |> print_string;
  read_line();
};

let promptLine = string => {
  string |> print_endline;
  read_line();
};

let scene1 = {
  name: "Intro",
  id: 1,
  start: () => {
    waitInput("Welcome to the world of Flugel.");
    waitInput("A land where magic and wonders await.");
    let name = prompt("What is your name dear adventurer? ");
    let hero = hero.changeName(name);
    waitInput("Ahhh..." ++ hero.name ++ " is It?");
    waitInput(
      "Well, begin your journey with new vigor "
      ++ hero.name ++ "!"
    );
    ();
  },
  close: () => ()
};

let scene2 = {
  name: "Start", 
  id: 2, 
  start: () => {
    waitInput("Welcome to the city of Compashi");
    waitInput(
      trimLines({|In this city you find the inn.
      You can also find a shop for buying weapons, and
      much more! Please, take a look around.|}))
  }, 
  close: () => ()
};

let scene3 =  {
  name: "First Battle",
  id: 3,
  player: hero,
  enemy: cuteSoldier,
};

let sceneWin = {
  name: "Win", 
  id: 99,
  start: () => {
    waitInput("You have won the battle.");
  },
  close: () => ()
};

let sceneGameOver = {
  name: "Game Over",
  id: 0,
  start: () => {
    waitInput("You have died.");
    waitInput("Although, your effort was valiant...");
    waitInput("It was not enough");
  },
  close: () => ()
};