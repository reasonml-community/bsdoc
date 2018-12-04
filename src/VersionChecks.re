open OS;
open Js.Console;

let check = () => {
  let good_switch = "4.02.3+buckle-master";
  let installed_switch = exec("opam switch show");
  let has_good_switch = installed_switch === good_switch;

  if (!has_good_switch) {
    log(
      {j| 🔥 Could not find the needed opam switch: $good_switch.

Instead found: $installed_switch.

To install it, make sure you have `opam` installed and execute:

    opam switch create $good_switch
    eval \$(opam env)

Then try again 🙌🏼
|j},
    );
    exit(1);
  };

  let has_odoc_pkg = run("opam", ["show", "odoc"]);
  let has_odoc_in_path = run("which", ["odoc"]);

  if (!has_odoc_pkg) {
    log(
      {j| 🔥 Could not find the needed odoc package.

To install it, make sure you have `opam` installed and execute:

    opam install odoc

Then try again 🙌🏼
|j},
    );
    exit(2);
  };

  if (!has_odoc_in_path) {
    log(
      {j| 🔥 Could not find the needed odoc binary in your PATH.

To install it, make sure you have `opam` installed and execute:

    opam install odoc

Then try again 🙌🏼
|j},
    );
    exit(3);
  };
};
