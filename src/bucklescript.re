type package = {
  name: string,
  cmtis: list(string),
  mlds: list(string),
};

let package = (name, src_dir, lib_dir) => {
  let modules: Hashtbl.t(string, Fpath.t) = Hashtbl.create(1024);

  Os.readdir(lib_dir)
  |> List.iter(path => {
       let filename = path |> Fpath.rem_ext |> Fpath.basename;
       let ext = path |> Fpath.get_ext;
       switch (ext) {
       | ".cmt"
       | ".cmti" =>
         switch (Hashtbl.find_opt(modules, filename)) {
         | None => Hashtbl.add(modules, filename, path)
         | Some(last) =>
           let last_extension = last |> Fpath.get_ext;
           switch (last_extension, ext) {
           | (".cmt", ".cmti") => Hashtbl.replace(modules, filename, path)
           | _ => ()
           };
         }
       | _ => ()
       };
     });

  let cmtis =
    Hashtbl.fold(
      (_, m, acc) => [m |> Fpath.to_string, ...acc],
      modules,
      [],
    );

  switch (cmtis) {
  | [] =>
    Logs.debug(m =>
      m(
        "Could not find .cmti files in %s 🙀\n\nThis usually means you have no Reason/OCaml sources, that you have not compiled\nyour project, or that I'm looking for .cmti files in the wrong place.\n\n",
        lib_dir,
      )
    )
  | _ =>
    let cmti_count = cmtis |> List.length;
    Logs.debug(m => m("Found %d .cmti files in %s: ", cmti_count, lib_dir));
    Logs.debug(m => List.iter(x => m("  - %s ", x), cmtis));
  };

  let mlds =
    Os.readdir(src_dir)
    |> List.filter(Fpath.has_ext("mld"))
    |> List.map(Fpath.to_string);

  switch (mlds) {
  | [] =>
    Logs.debug(m => m("Could not find any .mld files in %s 🙀", lib_dir))
  | _ =>
    let mld_count = mlds |> List.length;
    Logs.debug(m => m("Found %d .mld files in %s", mld_count, lib_dir));
    Logs.debug(m => List.iter(x => m("  - %s ", x), mlds));
  };

  {name, cmtis, mlds};
};
