open Node.Child_process;
open Operators.Option;

type verbosity =
  | Normal
  | Quiet
  | Verbose;

let verbosity_string =
  fun
  | Normal => "normal"
  | Quiet => "quiet"
  | Verbose => "verbose";

type flags = {
  debug: bool,
  verbosity,
};
let flags = (debug, verbosity) => {debug, verbosity};

[@bs.module "child_process"]
external __unsafe__spawn:
  (string, array(string)) => Node.Child_process.spawnResult =
  "spawnSync";

let run = (cmd, args) => {
  Js.log2(cmd, Array.of_list(args));
  __unsafe__spawn(cmd, args |> Array.of_list)
  |> Node.Child_process.readAs
  |> (x => x##status |> Js.Null.toOption |>> (x => x == 0) <|> false);
};

[@bs.send] external __unsafe__buf_to_str: string => string = "toString";
let exec = str =>
  execSync(str, option()) |> __unsafe__buf_to_str |> Js.String.trim;
