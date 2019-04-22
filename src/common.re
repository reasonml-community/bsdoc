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
