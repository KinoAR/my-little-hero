open Utility;
type player = {
  name:string,
  isPlayer: bool,
  isAlive:bool,
  hp: int,
  mhp: int,
  mp: int,
  mmp: int,
  atk: int,
  def: int,
  mdef: int,
  takeDamage: (player, int) => player,
  statGrow: (player, string, int) => player,
  changeName: (string) => player,
};

type enemy = {
  name:string,
  isEnemy:bool,
  isAlive: bool,
  hp:int,
  mhp:int,
  mp:int,
  mmp:int,
  atk:int,
  def:int,
  mdef:int,
  takeDamage: (enemy, int) => enemy,
  asciiImage:string,
};

let rec heroBase:player = {
  name: "Timothy",
  isPlayer: true,
  isAlive:true,
  hp: 5,
  mhp: 5,
  mp: 5,
  mmp: 5,
  atk: 4,
  def: 3,
  mdef: 3,
  takeDamage: (player:player, damage) => {...player, hp: damageClamp(player.hp - damage)},
  changeName: (name) => {...heroBase, name: name},
  statGrow: (player, statName, growth) => switch(statName) {
  | "hp" => {...player, mhp: player.mhp + growth}
  | "mp" => {...player, mmp: player.mmp + growth}
  | "atk" => {...player, atk: player.atk + growth}
  | "def" => {...player, def: player.def + growth}
  | "mdef"=> {...player, mdef: player.mdef + growth}
  | _ => {...player, hp: player.hp}
  },
};

let cuteSoldier =  {
  name: "Cute Soldier",
  isEnemy: true,
  isAlive: true,
  hp: 3,
  mhp: 3,
  mp: 3,
  mmp: 3,
  atk: 2,
  def: 2,
  mdef: 2,
  takeDamage: (enemy, damage) => {...enemy, hp: damageClamp(enemy.hp - damage)},
  asciiImage: 
  trimLines({|
    
    .................+I.....................
    ........................................
    ..........I?+I=+?=????+?................
    .~?+?~+~+...........??I??+I..~~~:....~..
    ....7I7?==?==?.......I?++?I+??~~~~...:..
    ...I.:....=II=~I~=++III??++?==~~~:~..:7.
    ..+..............+==??III+==+~::::...:..
    .............+?..~~~+777+?=II=?:::~~....
    .................?~~7777=~=+::~::~......
    ..............=.~:,:,==+:,,=+++++.......
    ..........?.....::::?~?~::?77I.+??......
    .......+=.?.....:?,:7=++=I?=7++..II.....
    ...........~~?,,,,++=+~+7?==..,~.....I..
    ........=~=~:,:,??I.?+,I+7~=,.I7..~.....
    .......~~~.+...?II.I777.~~.,:~=.,~,.....
    ......~~.......I.~~.=?=+~,++~,.,::,.....
    .....~:.........:+..7+77+::++,::,,......
    .....?.........?.....I7+?~=+~:,.,:,.....
    ....................?~I7=:+++:::,:......
    .....................+,7?~~+.:+??+......
    ......................?=~=~~...7I.......
    ......................=I~=..............
    ......................??=...............
    .....................I7+~...............
    ....................??+?................
    ....................+=..................
    ...................I~...................
    ..................:,....................
    .................?:.....................
    ................+==.....................
    ........................................
    ........................................
    |})
};
