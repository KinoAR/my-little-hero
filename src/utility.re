let trimLines = (string) => string 
|> Str.split(Str.regexp("[\n]")) 
|> List.map((string) => String.trim(string) ++ "\n") 
|> List.fold_left((initial, curr) => initial ++ curr, "");

let clamp = (min:int, max:int, value:int) =>  {
  value < min ? min : value > max ? max : value;
};

let hpClamp = clamp(-max_int, 0);
let damageClamp = clamp(0, max_int);

let drawStatusBox = (string) => {
  let length = String.length(string) + 1;
  let top = String.make(length, '=');
  let bottom = String.make(length, '=');
  String.concat("\n", [top, string, bottom]);
};