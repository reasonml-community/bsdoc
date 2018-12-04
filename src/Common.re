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
  __unsafe__spawn(cmd, args |> Array.of_list)
  |> Node.Child_process.readAs
  |> (x => x##status |> Js.Null.toOption |>> (x => x == 0) <|> false);
};

[@bs.send] external __unsafe__buf_to_str: string => string = "toString";
let exec = str =>
  execSync(str, option()) |> __unsafe__buf_to_str |> Js.String.trim;


[@bs.deriving abstract]
type __mkdir_opts = {
  recursive: bool
};
[@bs.module "fs"]
external __unsafe__mkdir : (string, __mkdir_opts) => unit = "mkdirSync";

[@bs.module "fs"]
external __unsafe__exists : string => bool = "existsSync";

let mkdirp = path => {
  if (!__unsafe__exists(path)) {
    __unsafe__mkdir(path, __mkdir_opts(~recursive=true));
  };
}
