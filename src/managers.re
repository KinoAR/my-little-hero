open GameObjects;

open Scenes;

open Utility;

module SceneManager = {
  let startScene = scene => scene.start();
  let endScene = scene => scene.close();
  let changeScene = scene => scene.start();
};

module BattleManager = {
  let drawStatusEnemy = enemy => {
    print_string(enemy.asciiImage);
    Printf.sprintf(
      "%s HP: %d/%d MP: %d/%d",
      enemy.name,
      enemy.hp,
      enemy.mhp,
      enemy.mp,
      enemy.mmp
    )
    |> drawStatusBox
    |> trimLines
    |> print_endline;
  };
  let drawStatusPlayer = (player: player) =>
    Printf.sprintf(
      "%s HP: %d/%d MP: %d/%d",
      player.name,
      player.hp,
      player.mhp,
      player.mp,
      player.mmp
    )
    |> drawStatusBox
    |> trimLines
    |> print_endline;
  let drawCommands = canEscape =>
    canEscape ? print_endline("Fight | Run") : print_endline("Fight");
  let calculateDamage = damage => damage |> abs |> damageClamp;
  let printDamage = (name, damage) => {
     damage > 0 ?
      Printf.sprintf("%s took %d damage!", name, damage) |> waitInput :
      Printf.sprintf("%s was unscathed!", name) |> waitInput;
  };
  let calculateAndPrintEscape = (name, number) => {
    let escaped = number > 50 ? true : false;
    let res = escaped ? Printf.sprintf("%s escaped!", name) : Printf.sprintf("%s failed to escape.", name);
    res |> waitInput;
    escaped;
  };
  let rec fight = (player: player, enemy, escaped, canEscape) => {
    let playerAlive = player.hp > 0;
    let enemyAlive = enemy.hp > 0; 
    switch (playerAlive, enemyAlive, escaped) {
    | (true, true, false) =>
      drawStatusEnemy(enemy);
      print_endline("The enemy lies before you; what will you do?");
      drawStatusPlayer(player);
      drawCommands(canEscape);
      let action = prompt("") |> String.lowercase;
      let (hitEnemy, player, escaped) =
        switch action {
        | "f" => {
          let enemyDamage = enemy.def - player.atk |> hpClamp |> calculateDamage;
          printDamage(enemy.name, enemyDamage);
          let playerDamage = player.def - enemy.atk |> hpClamp |> calculateDamage;
           printDamage(player.name, playerDamage);
          (enemy.takeDamage(enemy, enemyDamage), player.takeDamage(player, playerDamage), false);
        };
        | "fight" => {
          let enemyDamage = enemy.def - player.atk |> hpClamp |> calculateDamage;
          printDamage(enemy.name, enemyDamage);
          let playerDamage = player.def - enemy.atk |> hpClamp |> calculateDamage;
           printDamage(player.name, playerDamage);
          (enemy.takeDamage(enemy, enemyDamage), player.takeDamage(player, playerDamage), false);
        };
        | "r" => {
          (enemy, player, calculateAndPrintEscape(player.name, Random.int(100)));
        };
        | "run" => {
          (enemy, player, calculateAndPrintEscape(player.name, Random.int(100)));
        };
        | _ => (enemy, player, false)
        };
      fight(player, hitEnemy, escaped, canEscape);
    | (_, _, false) => ();
    | (_, _, true) => ();
    };
    switch (playerAlive, enemyAlive) {
    | (false, true) => SceneManager.startScene(sceneGameOver)
    | (true, false) =>
      drawStatusEnemy(enemy);
      drawStatusPlayer(player);
      Printf.sprintf("%s has been defeated.", enemy.name) |> waitInput;
      SceneManager.startScene(sceneWin);
    | (_, _) => ()
    };
  };
  let startBattle = (battleScene, canEscape) =>
    fight(battleScene.player, battleScene.enemy, false, canEscape);
};