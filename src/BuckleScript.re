open Node.Fs;
open Node.Process;
open Logger;

type package = {
  name: string,
  cmtis: list(string),
  mlds: list(string),
};

let with_extension = (ext, name) =>
  Js.String.split(".", name)
  |> Array.to_list
  |> List.rev
  |> Belt.List.head
  |> (
    x =>
      switch (x) {
      | Some(ext2) => ext == ext2
      | _ => false
      }
  );

let package = (name, src_dir, lib_dir) => {
  /* Find bsconfig.json */
  let cmtis =
    readdirSync(lib_dir)
    |> Array.to_list
    |> List.filter(with_extension("cmti"));

  switch (cmtis) {
  | [] =>
    debug(
      {j|Could not find .cmti files in $lib_dir 🙀

This usually means you have no Reason/OCaml sources, that you have not compiled
your project, or that I'm looking for .cmti files in the wrong place.

|j},
    )
  | x =>
    let cmti_count = cmtis |> List.length;
    debug({j|Found $cmti_count .cmti files in $lib_dir: |j});
    List.iter(x => debug({j|  - $x |j}), cmtis);
  };

  let mlds =
    readdirSync(src_dir)
    |> Array.to_list
    |> List.filter(with_extension("mld"));

  switch (mlds) {
  | [] => debug({j|Could not find any .mld files in $lib_dir 🙀|j})
  | x =>
    let mld_count = mlds |> List.length;
    debug({j|Found $mld_count .mld files in $lib_dir|j});
    List.iter(x => debug({j|  - $x |j}), mlds);
  };

  {name, cmtis, mlds};
};
