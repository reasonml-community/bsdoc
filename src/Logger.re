open Common;

let verbosity = ref(Normal);

let info_prefix = "info: ";
let info = s =>
  switch (verbosity^) {
  | Quiet => ()
  | _ => Js.log(info_prefix ++ s)
  };

let debug_prefix = "debug: ";
let debug = s =>
  switch (verbosity^) {
  | Verbose => Js.log(debug_prefix ++ s)
  | _ => ()
  };

let error_prefix = "ERROR: ";
let error = s => Js.log(error_prefix ++ s);
